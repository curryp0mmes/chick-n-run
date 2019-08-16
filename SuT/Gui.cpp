#include "Gui.h"


void Gui::init(View *nview)
{
	view = nview;
	TextureHealth.loadFromFile(RESPATH"textures/foodBar.png");
	TextureHealthOverlay.loadFromFile(RESPATH"textures/foodBarOverlay.png");
	Health.setTexture(TextureHealth);
	HealthOverlay.setTexture(TextureHealthOverlay);
}

void Gui::update(float food)
{
	Health.setScale(Vector2f(food,1));
	viewPos = Vector2f(view->getCenter().x - view->getSize().x / 2,view->getCenter().y - view->getSize().y/2);

	HealthOverlay.setPosition(Vector2f(view->getCenter().x + view->getSize().x / 3, view->getCenter().y + view->getSize().y / 3));
	//Health.setPosition(Vector2f(viewPos.x + 9/10 * view->getSize().x, viewPos.y + 4/5 * view->getSize().y));
	Health.setPosition(HealthOverlay.getPosition());
}

void Gui::create(availableGuiElements type)
{
}

void Gui::draw(RenderWindow* win)
{
	win->draw(Health);
	win->draw(HealthOverlay);
}

Gui::~Gui()
{
}
