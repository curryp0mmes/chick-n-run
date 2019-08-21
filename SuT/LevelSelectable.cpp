#include "LevelSelectable.h"



LevelSelectable::LevelSelectable(string nname, Font *nfont, int nid, Texture* ntexture, RenderWindow* nwin) : window(nwin)
{
	name = nname;
	id = nid;
	font = nfont;
	label.setFont(*font);
	label.setString(name);

	label.setPosition(Vector2f( 1.5f * window->getSize().x / 10.f, (float)(id+0.35f) * window->getSize().y / 5.f + window->getSize().y / 10.f));
	box.setPosition(0.5f * window->getSize().x / 10.f, (float)(id+0.1f)* window->getSize().y / 5.f + window->getSize().y / 10.f);
	box.setSize(Vector2f(9*window->getSize().x / 10.f, 0.8f * window->getSize().y / 5.f));
	box.setFillColor(Color(150,150,150));
	play.setOrigin(Vector2f(play.button.getGlobalBounds().width,0));
	play.setPosition(Vector2f( 8.5f * window->getSize().x / 10.f, (float)(id+0.4f) * window->getSize().y / 5.f + window->getSize().y / 10.f));

	play.constructor(ntexture, Vector2f(100,30), nwin);
}

void LevelSelectable::draw()
{
	window->draw(box);
	if (play.draw()) selected = true;
	else selected = false;
	window->draw(label);
}

void LevelSelectable::start()
{
	selected = true;
}


LevelSelectable::~LevelSelectable()
{
}
