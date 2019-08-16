#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "defines.h"
using namespace std;
using namespace sf;
class Button
{
public:
	Button(Texture* ntexture, Vector2f nsize, RenderWindow *nwin);
	Button() {};
	~Button();
	void constructor(Texture* ntexture, Vector2f size, RenderWindow* nwin);
	bool draw();
	void setPosition(Vector2f npos);
	void setOrigin(Vector2f no);
	 
	Sprite button;
	Vector2f size;
	
private:
	RenderWindow *win;
	Texture *texture;
	Vector2f pos;

	bool mouseWasPressed = 1;
};

