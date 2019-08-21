#pragma once
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include "defines.h"
	

static string selectedLevel = "";
static void select1() {selectedLevel = "A Flat Earth";}
static void select2() {selectedLevel = "A Flat Earth";}
static void select3() {selectedLevel = "A Flat Earth";}
static void select4() {selectedLevel = "A Flat Earth";}
static void select5() {selectedLevel = "A Flat Earth";}
static void select6() {selectedLevel = "A Flat Earth";}


class LevelMenu
{
public:
	LevelMenu(RenderWindow* nwindow);
	string run();
	~LevelMenu();


	bool moving = false;
	Vector2i movingStartingPos;
	bool menuOpen = true;
	RenderWindow *window;
	sfg::SFGUI gui;
	Event e;
	sf::Clock clock;


};

