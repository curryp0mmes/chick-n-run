#include "Game.h"

bool Game::init() {
	if (!level.load(RESPATH"textures/tileset.png", RESPATH"levels/"+ levelpath + "/tiles.txt")) return false;
	feed = level.feed;

	font.loadFromFile(RESPATH"font.ttf");
	view = window->getDefaultView();
	view.zoom(0.22f);
	isDead = 0;
	won = 0;
	float yVel = 0;
	float food = .5f;
	float ViewX = 0;
	fps = { 9999999.f };
	gui.init(&view);
	food = .5f;
	rip.setFont(font);
	rip.setString("GAME OVER");
	rip.setCharacterSize(200);
	rip.setScale(Vector2f(0.25f, 0.25f));
	rip.setOrigin(Vector2f(rip.getGlobalBounds().width * 2,100/*rip.getGlobalBounds().height/2*/));
	
	youwon.setFont(font);
	youwon.setString("LEVEL COMPLETE");
	youwon.setCharacterSize(140);
	youwon.setScale(Vector2f(0.25f, 0.25f));
	youwon.setOrigin(Vector2f(rip.getGlobalBounds().width * 2,100/*rip.getGlobalBounds().height/2*/));

	flagTexture.loadFromFile(RESPATH"textures/flag.png");
	flag.setTexture(flagTexture);
	flag.setPosition(level.goalPos);

	//PlayerSkinImg.loadFromFile("../res/player.png");
	//PlayerSkinImg.createMaskFromColor(Color::White);
	PlayerSkin.loadFromFile(RESPATH"textures/player.png");
	player.setTexture(PlayerSkin);
	player.setTextureRect(texture(0,0));
	player.setOrigin(Vector2f(8, 8));
	
	player.setPosition(level.playerSpawn);
	
	deathTexture.loadFromFile(RESPATH"textures/dead.png");
	death.setTexture(deathTexture);
	death.setOrigin(Vector2f(death.getGlobalBounds().width/2,death.getGlobalBounds().height/2));
	wonBackground.loadFromFile(RESPATH"textures/won.png");
	wonSprite.setTexture(wonBackground);
	wonSprite.setOrigin(Vector2f(wonSprite.getGlobalBounds().width/2,wonSprite.getGlobalBounds().height/2));

	view.setCenter(player.getPosition());

	f3menu.setFont(font);
	f3menu.setFillColor(Color::Black);
	f3menu.setCharacterSize(50);
	f3menu.setScale(Vector2f(0.1f,0.1f));

	return true;
}


//game logic
int Game::update(string pathToLevel) {
	if (levelpath != pathToLevel) {
		levelpath = pathToLevel;
		if (!init()) return false;
	}
	else {
		thetime = elapsed.getElapsedTime();
		fps.insert(fps.begin(), (1000.f / ((float)thetime.asMilliseconds())));
		if (fps.size() > fps[0] && fps.size() > 10) fps.pop_back();
		elapsed.restart();
		
	}
	rip.setPosition(view.getCenter());
	death.setPosition(view.getCenter());
	youwon.setPosition(view.getCenter());
	wonSprite.setPosition(view.getCenter());
	standing = true;


	if (!isDead && !won) {
		food -= 0.001f / fps[0];
		for (int i = 0;i<feed.size();i++) 
			if (player.getGlobalBounds().intersects(feed[i].getGlobalBounds())) {
				feed.erase(feed.begin() + i);
				food += 0.5f;
		}
		if (food > 1) {
			food = 1;
		}
		if (flag.getGlobalBounds().intersects(player.getGlobalBounds())) won = 1;


		shifting = Keyboard::isKeyPressed(Keyboard::Key::LShift);

		float xSpeedPS = xSpeed / fps[0];
		if (shifting) xSpeedPS *= 1.7f;

		if (Keyboard::isKeyPressed(Keyboard::Space) && yVel >= 0 && (int)((player.getPosition().y + 10) / 16.f) < level.height && (int)((player.getPosition().x + 8) / 16.f) < level.width) {
			if (level.level[(int)((player.getPosition().y + 10) / 16.f)][(int)((player.getPosition().x - 8) / 16.f)].hasBounds) {
				FloatRect bounds = level.level[(int)((player.getPosition().y + 10) / 16.f)][(int)((player.getPosition().x - 8) / 16.f)].bounds;
				bounds.left += (int)((player.getPosition().x - 8) / 16.f) * 16;
				bounds.top += (int)((player.getPosition().y + 10) / 16.f) * 16;

				if (bounds.intersects(FloatRect(player.getPosition().x - 8, player.getPosition().y + 8, 16, 3))) {
					yVel = -6.8;
					food -= 0.01f;
					sound.jump.play();
				}
			}
			if (level.level[(int)((player.getPosition().y + 10) / 16.f)][(int)((player.getPosition().x + 8) / 16.f)].hasBounds) {
				FloatRect bounds = level.level[(int)((player.getPosition().y + 10) / 16.f)][(int)((player.getPosition().x + 8) / 16.f)].bounds;
				bounds.left += (int)((player.getPosition().x + 8) / 16.f) * 16;
				bounds.top += (int)((player.getPosition().y + 10) / 16.f) * 16;

				if (bounds.intersects(FloatRect(player.getPosition().x - 8, player.getPosition().y + 8, 16, 3))) {
					yVel = -6.8;
					food -= 0.01f;
					sound.jump.play();
				}
			}
		}
		//Hier scrollt it
		view.move(Vector2f(20 / fps[0], 0));

		if (player.getPosition().x < view.getCenter().x - view.getSize().x / 2 || player.getPosition().y >(level.height + 5) * 16 || food < 0)
		{
			isDead = 1;
			
		}
		
		if (!Keyboard::isKeyPressed(Keyboard::Key::Return)) {
			player.move(Vector2f(0, yVel / fps[0] * 16));
			if (doesCollide(player)) {
				player.move(Vector2f(0, yVel / fps[0] * -16));
				yVel = 0;
			}
			else if (player.getPosition().y < view.getCenter().y - 10 || player.getPosition().y > view.getCenter().y + 30) view.move(Vector2f(0, yVel / fps[0] * 16));
		}

		if (yVel < 9.81f) yVel += 9.81f / fps[0];

		if (Keyboard::isKeyPressed(Keyboard::A)) {
			facingLeft = true;
			if (shifting) animateChicken(2);
			else animateChicken(1);
			player.move(Vector2f(-xSpeedPS, 0));
			if (doesCollide(player)) player.move(Vector2f(xSpeedPS, 0));
			else food -= shifting ? 0.04 / fps[0] : 0.01 / fps[0];
			//else if(player.getPosition().x < view.getCenter().x - 60) view.move(Vector2f(-xSpeedPS, 0));
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			facingLeft = false;
			if (shifting) animateChicken(2);
			else animateChicken(1);
			player.move(Vector2f(xSpeedPS, 0));
			if (doesCollide(player)) player.move(Vector2f(-xSpeedPS, 0));
			else food -= shifting ? 0.04 / fps[0] : 0.01 / fps[0];
			//else if(player.getPosition().x > view.getCenter().x + 30) view.move(Vector2f(xSpeedPS, 0));
		}
		if (Keyboard::isKeyPressed(Keyboard::Period)) window->setFramerateLimit(20);
		else window->setFramerateLimit(120);
		if (yVel > 1) {
			animateChicken(3);
		}
		if (Keyboard::isKeyPressed(Keyboard::F3) && !f3p) f3 = !f3;
		f3p = Keyboard::isKeyPressed(Keyboard::F3);
		f3ss.str(std::string());
		int avFps = 0;
		for (int i = 0; i < fps.size(); i++) avFps += fps[i];
		avFps /= fps.size();

		f3ss << "Chick-n-run early alpha\n[F3] to close\nfps: " << avFps
			<< "\nX: " << (int)(player.getPosition().x / 16.f) << " / " << player.getPosition().x / 16
			<< "\nY: " << (int)(player.getPosition().y / 16.f) << " / " << player.getPosition().y / 16
			<< "\nshifting: " << Keyboard::isKeyPressed(Keyboard::Key::LShift)
			<< "\nfood: " << food
			<< "\ndead? " << isDead
			<< "\nwon? " << won;
		f3menu.setString(f3ss.str());
		f3menu.setPosition(Vector2f(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2));

		gui.update(food);


		if (standing) animateChicken(0);

		//view.setCenter(Vector2f(view.getCenter().x,player.getPosition().y));
		window->setView(view);
	}
	else if (isDead)
	{
		isDead++;
		if (isDead > 1 * fps[0]) {
			levelpath.clear();
			return 0;
		}
		else return 3;
	}
	else if (won)
	{
		won++;
		if (won > 2 * fps[0]) {
			levelpath.clear();
			return 0;
		}
		else return 3;
	}
	return 1;
}

bool Game::doesCollide(Sprite playerToTest) {
	Vector2i playerSquare;
	FloatRect playerBounds = playerToTest.getGlobalBounds();
	playerBounds.left += 0.1f;
	playerBounds.top += 0.1f;
	playerBounds.width -= 0.1f;
	playerBounds.height -= 0.1f;

	playerSquare.x = (int)(playerToTest.getPosition().x / 16.f);
	playerSquare.y = (int)(playerToTest.getPosition().y / 16.f);

	if (playerSquare.x < 0 || playerSquare.y < 0 || playerSquare.x > level.width - 1|| playerSquare.y > level.height + 10) return true;
	if (playerToTest.getPosition().x < 0) return true;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (playerSquare.x + i < 0 || playerSquare.y + j < 0 || playerSquare.x + i > level.width -1 || playerSquare.y + j > level.height -1) continue;

			Tile Square = level.level[playerSquare.y + j][playerSquare.x + i];
			if (Square.hasBounds) {
				FloatRect bounds = Square.bounds;
				bounds.left += (playerSquare.x + i)*16;
				bounds.top  += (playerSquare.y + j)*16;

				if(bounds.intersects(playerBounds)) return true;
			}
		}
	}

	return false;
}

IntRect Game::texture(int number, bool mirrored)
{

	IntRect result(16 * number,0,16,16);
	if (mirrored) result.top = 16;
	
	return result;
}


//drawing stuff
void Game::frame() {
	window->draw(level);

	for (int i = 0; i < feed.size(); i++) {
		if (feed[i].getGlobalBounds().intersects(FloatRect(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2, view.getSize().x, view.getSize().y))) window->draw(feed[i]);
	}

	if (flag.getGlobalBounds().intersects(FloatRect(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2, view.getSize().x, view.getSize().y))) window->draw(flag);

	window->draw(player);
	if(f3) window->draw(f3menu);
	gui.draw(window);
	
	if (isDead) {
		window->draw(death);
		window->draw(rip);
	}
	if (won) {
		window->draw(wonSprite);
		window->draw(youwon);
	}

}

void Game::animateChicken(int action)
{
	switch (action) {
	case 1:
		framesSinceLastAnimation++;
		if (framesSinceLastAnimation > fps[0] / 10.f) {
			animationFrame++;
			if (animationFrame > 4) animationFrame = 0;
			framesSinceLastAnimation = 0;
		}
		player.setTextureRect(texture(1+animationFrame, facingLeft));
		standing = false;
		break;
	case 2:
		framesSinceLastAnimation++;
		if (framesSinceLastAnimation > fps[0] / 15.f) {
			animationFrame++;
			if (animationFrame > 4) animationFrame = 0;
			framesSinceLastAnimation = 0;
		}
		player.setTextureRect(texture(1 + animationFrame, facingLeft));
		standing = false;
		break;
	case 3:
		framesSinceLastAnimation = 0;
		animationFrame = 0;
		player.setTextureRect(texture(6, facingLeft));
		standing = false;
		break;
	default:
		framesSinceLastAnimation = 0;
		animationFrame = 0;
		player.setTextureRect(texture(0, facingLeft));
		break;
	}
}
