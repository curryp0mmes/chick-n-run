#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

#define RESPATH "../res/"

#define TILESETWIDTH 10 
#define TILESETHEIGHT 5

using namespace std;
using namespace sf;

enum TileNames {
	Air,
	GrassLeft,
	DirtLeft,
	DirtBottomLeft,
	CaveStoneTopLeft,
	Cloud1,
	Grass,
	Dirt,
	DirtBottom,
	CaveStoneTop,
	Cloud2,
	GrassRight,
	DirtRight,
	DirtBottomRight,
	CaveStoneTopRight,
	StoneTopLeft,
	StoneLeft,
	StoneBottomLeft,
	CaveLeft,
	CaveStoneBottomLeft,
	StoneTop,
	Stone,
	StoneBottom,
	Cave,
	CaveStoneBottom,
	StoneTopRight,
	StoneRight, 
	StoneBottomRight,
	CaveRight,
	CaveStoneBottomRight,
	MarbleBlock,
	Barn,
	BarnRoofLeft2,
	BarnRoofLeft3,
	BarnRoofRight,
	DarkBrick,
	BarnWithCrossLeft,
	BarnTop,
	BarnRoofLeft,
	BarnDoorTop,
	WindowBlock,
	BarnWithCrossRight,
	BarnRoofRight2,
	BarnRoofRight3,
	BarnDoor,
	GrassWithoutSky


	, BlockCount
};

enum availableSounds {
	JumpSound
};


enum availableGuiElements {
	GUIButton,

};



static void alertBox(string message) {
	try {
		string command = "PowerShell -Command \"Add-Type -AssemblyName PresentationFramework; [System.Windows.MessageBox]::Show('" + message + "')\"";
		system(command.c_str());
	}
	catch (exception e) {

	}
}