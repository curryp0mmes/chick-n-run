#include "LevelMenu.h"


LevelMenu::LevelMenu(RenderWindow* nwindow) : window(nwindow) {
	
	selectedLevel = "";



}


string LevelMenu::run()
{
	sfg::Desktop desktop;
	
	
	auto button = sfg::Button::Create("1");
	button->SetPosition(Vector2f(100,100));
	button->GetSignal(sfg::Button::OnLeftClick).Connect(
		std::bind(&select1)
	);

	desktop.Add(button);


	while (true) {

		if (moving) {
			window->setPosition(Vector2i(Mouse::getPosition().x - movingStartingPos.x, Mouse::getPosition().y - movingStartingPos.y));
		}
		while (window->pollEvent(e)) {
			desktop.HandleEvent(e);

			if (e.type == e.Closed || (e.type == e.KeyPressed && e.key.code == Keyboard::Escape)) {
				return string(".");
			}
			else if (e.type == e.MouseButtonPressed && e.mouseButton.button == Mouse::Left && Mouse::getPosition(*window).y < window->getSize().y / 10) {
				moving = true;
				movingStartingPos = Vector2i(Mouse::getPosition(*window));
			}
			else if (e.type == e.MouseButtonReleased && e.mouseButton.button == Mouse::Left) moving = false;
		}

		desktop.Update(clock.restart().asSeconds());

		if (!selectedLevel.empty()) return selectedLevel;

		window->clear(Color::White);
		gui.Display(*window);
		window->display();
	}
}

LevelMenu::~LevelMenu()
{
}
