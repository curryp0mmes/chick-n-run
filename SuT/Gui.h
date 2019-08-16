#pragma once
#include <SFML/Graphics.hpp>
#include "defines.h"
using namespace sf;


class Gui
{
public:
	Gui() {};
	void init(View* nview);
	void update(float food);
	void create(availableGuiElements type);
	void draw(RenderWindow *win);
	~Gui();
private:
	View *view;
	Vector2f viewPos;
	Sprite HealthOverlay;
	Sprite Health;
	Texture TextureHealthOverlay;
	Texture TextureHealth;
	
};

