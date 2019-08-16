#include "Button.h"
#include "Game.h"
#include "LevelSelectable.h"
#include "defines.h"


bool running = true;

int mode = 0;
int lastmode = 0;
int modelastframe = -1;
RenderWindow window;
bool reset = false;
Font stdFont;
vector<LevelSelectable> levelList;

void startGame() {
	lastmode = mode;
	mode = 1;
}




void exit() {
	running = false;
}

void goBack() {
	mode = lastmode;
}

void run() {
	//MENU
	stdFont.loadFromFile(RESPATH"font.ttf");
	Text title("CHICK-N-RUN",stdFont);
	title.setCharacterSize(70);
	title.setOrigin(Vector2f(title.getGlobalBounds().width / 2, title.getGlobalBounds().height /2));
	title.setFillColor(Color::Black);

	Texture playTexture;
	Texture settTexture;
	Texture exitTexture;
	Texture backTexture;

	playTexture.loadFromFile(RESPATH"textures/playbutton.png");
	settTexture.loadFromFile(RESPATH"textures/settingsbutton.png");
	exitTexture.loadFromFile(RESPATH"textures/exitbutton.png");
	backTexture.loadFromFile(RESPATH"textures/backbutton.png");

	Button playbutton(&playTexture, Vector2f(300, 90), &window);
	Button settbutton(&settTexture, Vector2f(300, 90), &window);
	Button exitbutton(&exitTexture, Vector2f(300, 90), &window);
	Button backbutton(&backTexture, Vector2f(300, 90), &window);

	playbutton.setOrigin(Vector2f(playbutton.button.getGlobalBounds().width / 2 / playbutton.button.getScale().x, playbutton.button.getOrigin().y));
	settbutton.setOrigin(Vector2f(settbutton.button.getGlobalBounds().width / 2 / settbutton.button.getScale().x, settbutton.button.getOrigin().y));
	exitbutton.setOrigin(Vector2f(exitbutton.button.getGlobalBounds().width / 2 / exitbutton.button.getScale().x, exitbutton.button.getOrigin().y));
	backbutton.setOrigin(Vector2f(backbutton.button.getGlobalBounds().width / 2 / backbutton.button.getScale().x, backbutton.button.getOrigin().y));

	bool moving = false;
	Vector2i movingStartingPos;

	string selectedLevel;
	string wasSelectedLevel;
	ifstream fstream;
	fstream.open(RESPATH"levels/list.txt");
	if (!fstream.good()) {
		alertBox("Resources Folder/Levels folder not found/invalid");
		return;
	}
	if (VideoMode::getDesktopMode().width < 1920) {
		alertBox("Your screen size does not fit the requirements. You need to have a FullHD monitor to play");
		return;
	}
	string line;

	while (getline(fstream, line)) {
		levelList.push_back(LevelSelectable(line,&stdFont,levelList.size(), &playTexture, &window));
	}
	fstream.close();

	Game game;

	Event e;
	while (running) {
		switch (mode) {
		case 0:
			//menu
			if (mode != modelastframe) {
				moving = false;
				window.setSize(Vector2u(VideoMode::getDesktopMode().height / 2, VideoMode::getDesktopMode().height / 2));
				window.setPosition(Vector2i(VideoMode::getDesktopMode().width / 2 - window.getSize().x / 2, VideoMode::getDesktopMode().height / 2 - window.getSize().y / 2));
				sf::FloatRect updateView(0.f, 0.f, window.getSize().x, window.getSize().y);
				window.setView(sf::View(updateView));
				modelastframe = mode;
			}
			if (moving) {
				window.setPosition(Vector2i(Mouse::getPosition().x - movingStartingPos.x,Mouse::getPosition().y - movingStartingPos.y));
			}
			while (window.pollEvent(e)) {
				if (e.type == e.Closed)
					exit();
				else if (e.type == e.MouseButtonPressed && e.mouseButton.button == Mouse::Left && Mouse::getPosition(window).y < window.getSize().y/3) {
					moving = true;
					movingStartingPos = Vector2i(Mouse::getPosition(window));
				}
				else if (e.type == e.MouseButtonReleased && e.mouseButton.button == Mouse::Left) moving = false;
			}
			title.setPosition(     Vector2f(window.getSize().x / 2, window.getSize().y     / 6));
			playbutton.setPosition(Vector2f(window.getSize().x / 2, window.getSize().y * 2 / 5));
			settbutton.setPosition(Vector2f(window.getSize().x / 2, window.getSize().y * 3 / 5));
			exitbutton.setPosition(Vector2f(window.getSize().x / 2, window.getSize().y * 4 / 5));


			window.clear(Color::White);
			window.draw(title);
			if (playbutton.draw())
			{
				lastmode = mode;
				mode = 2;
			}
			if (settbutton.draw()) 
			{

			}
			if(exitbutton.draw()) running = false;
			window.display();
			break;
		case 1:
			//main game
			if (wasSelectedLevel != selectedLevel) reset = true;
			if (mode != modelastframe) {
				window.setSize(Vector2u(1920,1080));
				window.setPosition(Vector2i((VideoMode::getDesktopMode().width-1920) / 2, (VideoMode::getDesktopMode().height - 1080) / 2));
				if (reset) {
					(&game)->~Game();
					new (&game) Game();
					reset = false;
				}
				game.setWindow(&window);

				
				sf::FloatRect updateView(0.f, 0.f, window.getSize().x, window.getSize().y);
				window.setView(sf::View(updateView));
				modelastframe = mode;
			}
			while (window.pollEvent(e)) {
				if (e.type == e.Closed || (e.type == e.KeyPressed && e.key.code == Keyboard::Escape)) {
					lastmode = mode;
					mode = 0;
				}
			}


			switch (game.update(selectedLevel)) {		// run game
			case 0:
				mode = 0;
				break;
			case 1:
				break;
			case 2:
				reset = true;
				mode = 0;
				break;
			case 3:
				reset = true;
				break;
			default:
				break;
			}
			window.clear(Color(49,162,238));

			//alles andere in Game.cpp
			game.frame();

			window.display();
			wasSelectedLevel = selectedLevel;
			break;
		case 2:
			selectedLevel = "";
			//choosing levels
			if (mode != modelastframe) {
				moving = false;
				window.setSize(Vector2u(1280,720));
				window.setPosition(Vector2i(VideoMode::getDesktopMode().width / 2 - window.getSize().x / 2, VideoMode::getDesktopMode().height / 2 - window.getSize().y / 2));
				sf::FloatRect updateView(0.f, 0.f, window.getSize().x, window.getSize().y);
				window.setView(sf::View(updateView));
				modelastframe = mode;
				
			}
			if (moving) {
				window.setPosition(Vector2i(Mouse::getPosition().x - movingStartingPos.x, Mouse::getPosition().y - movingStartingPos.y));
			}
			while (window.pollEvent(e)) {
				if (e.type == e.Closed || (e.type == e.KeyPressed && e.key.code == Keyboard::Escape)) {
					lastmode = mode;
					mode = 0;
				}
				else if (e.type == e.MouseButtonPressed && e.mouseButton.button == Mouse::Left && Mouse::getPosition(window).y < window.getSize().y / 10) {
					moving = true;
					movingStartingPos = Vector2i(Mouse::getPosition(window));
				}
				else if (e.type == e.MouseButtonReleased && e.mouseButton.button == Mouse::Left) moving = false;
			}
			backbutton.setPosition(Vector2f(window.getSize().x / 2, window.getSize().y * 4 / 5));

			window.clear(Color::White);
			for (int i = 0; i < levelList.size(); i++) {
				levelList[i].draw();
				if (levelList[i].selected) {
					selectedLevel = levelList[i].name;
					lastmode = mode;
					mode = 1;
				}
			}
			if(backbutton.draw()) mode = lastmode;
			window.display();
			break;
		default:
			break;
		}
		
	}
	window.close();
}

int main() {
	window.create(VideoMode(1280,720),"Chick-n-Run",Style::None);
	window.setFramerateLimit(120);
	//window.setVerticalSyncEnabled(true);
	run();
	//cin.get();
	return 0;
}