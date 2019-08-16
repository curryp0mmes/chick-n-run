#pragma once
#include "defines.h"

using namespace sf;
class Tile
{
public:
	Tile(int nx,int ny);
	Tile(int nx,int ny,int type);
	Tile() {};
	~Tile();
	int x;
	int y;
	Vector2f pos;
	bool hasBounds;
	FloatRect bounds;
private:
};

