#pragma once
#include "TileMap.h"
#include "Gui.h"
#include "defines.h"
#include "Sounds.h"
using namespace sf;
using namespace std;

class Game {
public:
	Game() {}
	void setWindow(RenderWindow* win) { window = win; }
	bool init();
	void frame();
	void animateChicken(int action);
	int update(string pathToLevel);
	bool doesCollide(Sprite playerToTest);
	IntRect texture(int number, bool mirrored);
private:
	Sounds sound;
	TileMap level;
	Texture PlayerSkin;
	Sprite player;
	Texture flagTexture;
	Sprite flag;
	vector<Sprite> feed;
	Font font;
	View view;
	Gui gui;
	Text f3menu;
	Text rip;
	Texture deathTexture;
	Sprite death;
	string levelpath;
	RenderWindow* window;
	Clock elapsed;
	Time thetime;
	bool shifting;
	vector<float> fps;
	int animationFrame = 0;
	int framesSinceLastAnimation = 0;
	bool standing = true;
	bool facingLeft = false;
	int isDead;
	int won;
	Text youwon;
	Texture wonBackground;
	Sprite wonSprite;
	float food = 0.5f;
	float xSpeed = 30;
	float yVel;
	bool f3p;
	bool f3;
	stringstream f3ss;

};