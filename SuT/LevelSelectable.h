#pragma once
#include "defines.h"
#include "Button.h"


class LevelSelectable
{
public:
	LevelSelectable(string nname, Font* nfont, int nid, Texture* ntexture, RenderWindow* nwin);
	bool selected = false;
	void draw();
	void start();
	~LevelSelectable();
	int id;
	Button play;
	string name;
	RectangleShape box;
	Font *font;
	Text label;
	RenderWindow* window;
};

