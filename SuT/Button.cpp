#include "Button.h"



Button::Button(Texture* ntexture, Vector2f nsize, RenderWindow* nwin)
{

	texture = ntexture;
	size = Vector2f(texture->getSize());

	button.setTexture(*texture);
	button.setScale(nsize.x/size.x,nsize.y/size.y);
	size = nsize;
	
	win = nwin;
}

Button::~Button()
{
}

void Button::constructor(Texture *ntexture, Vector2f nsize, RenderWindow* nwin)
{

	texture = ntexture;
	size = Vector2f(texture->getSize());

	button.setTexture(*texture);
	button.setScale(nsize.x / size.x, nsize.y / size.y);
	size = nsize;

	win = nwin;
}

bool Button::draw() {
	if (Mouse::isButtonPressed(Mouse::Left) && !mouseWasPressed && button.getGlobalBounds().contains(Vector2f(Mouse::getPosition(*win))))
		return true;

	if (Mouse::isButtonPressed(Mouse::Left)) mouseWasPressed = true;
	else mouseWasPressed = false;

	win->draw(button);
	return false;
}

void Button::setPosition(Vector2f npos)
{
	pos = npos;
	button.setPosition(pos);
}

void Button::setOrigin(Vector2f no)
{
	button.setOrigin(no);
}
