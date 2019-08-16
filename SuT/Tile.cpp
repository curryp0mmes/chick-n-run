#include "Tile.h"



Tile::Tile(int nx, int ny):x(nx),y(ny)
{
	hasBounds = false;
}

Tile::Tile(int nx, int ny, int type) : x(nx), y(ny)
{
	switch (type) {
	case CaveStoneTopLeft:
	case StoneTopLeft:
	case GrassLeft:
	case StoneTop:
	case CaveStoneTop:
	case Grass:
	case GrassRight:
	case StoneTopRight:
	case CaveStoneTopRight:
	case StoneLeft:
	case DirtLeft:
	case Dirt:
	case Stone:
	case DirtRight:
	case StoneRight:
	case DirtBottomLeft:
	case StoneBottomLeft:
	case CaveStoneBottomLeft:
	case DirtBottom:
	case StoneBottom:
	case CaveStoneBottom:
	case DirtBottomRight:
	case StoneBottomRight:
	case CaveStoneBottomRight:
		hasBounds = true;
		bounds = FloatRect(2, 2, 12, 12);
		break;
	default:
		hasBounds = false;
		break;
	}
}


Tile::~Tile()
{
}
