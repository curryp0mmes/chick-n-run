#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Tile.h"
#include "defines.h"

using namespace std;
using namespace sf;



class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	vector<Tile> TileSet;
	TileMap() {
		for (int x = 0; x < TILESETWIDTH; x++) {
			for (int y = 0; y < TILESETHEIGHT; y++) {
				TileSet.push_back(Tile(x, y, TileSet.size()));
			}
		}
		feedTexture.loadFromFile(RESPATH"textures/food.png");
	}

	vector<vector<Tile>> loadLevelTileMap(string tilesFile) {
		vector<vector<Tile>> levelTiles;
		try {
			ifstream fstream(tilesFile);

			string line, nwidth, nheight;

			while (getline(fstream, line)) {
				string argument = line.substr(1, line.find(':') - 1);
				line.erase(0,argument.length() + 2);
				
				if (argument == "Name") {
					while (line.find('!') == std::string::npos) {
						name += line;
						getline(fstream, line);
					}
					name += line.substr(0, line.find('!'));
				}
				if (argument == "Creator") {
					while (line.find('!') == std::string::npos) {
						creator += line;
						getline(fstream, line);
					}
					creator += line.substr(0, line.find('!'));
				}
				if (argument == "Version") {
					while (line.find('!') == std::string::npos) {
						version += line;
						getline(fstream, line);
					}
					version += line.substr(0, line.find('!'));
				}
				if (argument == "X") {
					width = stoi(line.substr(0, line.find('!')));
				}
				if (argument == "Y") {
					height = stoi(line.substr(0, line.find('!')));
				}

				if (argument == "Spawn") {
					line = line.substr(0, line.find('!'));
					playerSpawn = Vector2f((stof(line.substr(0, line.find('|')))+.5f) * 16, (stof(line.substr(line.find('|') + 1))+.5f) * 16);
				}

				if (argument == "Map") {
					string fullLine;
					while (line.find('!') == std::string::npos) {
						fullLine += line;
						getline(fstream, line);
					}
					fullLine += line.substr(0, line.find('!'));
					
					vector<int> lineInts;
					size_t pos = 0;
					std::string token;
					while ((pos = fullLine.find(",")) != std::string::npos) {
						token = fullLine.substr(0, pos);
						lineInts.push_back(stoi(token));
						fullLine.erase(0, pos + 1);
					}
					if (lineInts.size() != width * height) throw exception("invalid string");

					for (int i = 0; i < height; i++) {
						vector<Tile> linevec(0);
						for (int j = 0; j < width; j++) {
							linevec.push_back(TileSet[lineInts[i*width + j]]);
						}
						levelTiles.push_back(linevec);
					}
					if (levelTiles.size() != height) throw exception("y != lines");
					for (int i = 0; i < levelTiles.size(); i++) {
						if (levelTiles[i].size() != width) throw exception("x wrong");
					}
				}

				if (argument == "Food") {
					string fullLine;
					while (line.find('!') == std::string::npos) {
						fullLine += line;
						getline(fstream, line);
					}
					fullLine += line.substr(0, line.find('!'));

					vector<Vector2f> feedPos;
					size_t pos = 0;
					std::string token;
					while ((pos = fullLine.find(",")) != std::string::npos) {
						token = fullLine.substr(0, pos);
						feedPos.push_back(Vector2f(stoi(token.substr(0,token.find("|"))) * 16,stoi(token.substr(token.find("|") +1))*16));
						fullLine.erase(0, pos + 1);
					}

					for (int i = 0; i < feedPos.size(); i++) {
						Sprite exampleFeed;
						exampleFeed.setTexture(feedTexture);
						exampleFeed.setPosition(feedPos[i]);
						feed.push_back(exampleFeed);
					}
				}

				if (argument == "Goal") {
					line = line.substr(0, line.find('!'));
					goalPos = Vector2f(stof(line.substr(0, line.find('|'))) * 16, stof(line.substr(line.find('|') + 1)) * 16);
				}
				
			}
			fstream.close();
			return levelTiles;
		}
		catch (exception e) {
			alertBox("Error loading level " + tilesFile + ": \"" + e.what() + "\" in");
			vector<vector<Tile>> levelTilesErr;
			return levelTilesErr;
		
		}
		return levelTiles;
	}

	bool load(const std::string& tileset, string tilesFile, sf::Vector2u tileSize = Vector2u(16,16))
	{
		// load the tileset texture
		if (!m_tileset.loadFromFile(tileset))
			return false;
		level = loadLevelTileMap(tilesFile);
		if (level.size() == 0) return false;


		int width = level[0].size();
		int height = level.size();


		// resize the vertex array to fit the level size
		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(width * height * 4);

		// populate the vertex array, with one quad per tile
		for (unsigned int j = 0; j < width; ++j)
			for (unsigned int i = 0; i < height; ++i)
			{
				// get the current tile number
				
				
				Tile tile = level[i][j];




				// find its position in the tileset texture
				int tu = tile.x;
				int tv = tile.y;

				// get a pointer to the current tile's quad
				sf::Vertex * quad = &m_vertices[(j + i * width) * 4];

				// define its 4 corners
				quad[0].position = sf::Vector2f(j * tileSize.x, i * tileSize.y);
				quad[1].position = sf::Vector2f((j + 1) * tileSize.x, i * tileSize.y);
				quad[2].position = sf::Vector2f((j + 1) * tileSize.x, (i + 1) * tileSize.y);
				quad[3].position = sf::Vector2f(j * tileSize.x, (i + 1) * tileSize.y);

				// define its 4 texture coordinates
				quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
				quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
				quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
				quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
			}

		return true;
	}

	vector<vector<Tile>> level;
	vector<Sprite> feed;
	Vector2f playerSpawn;
	Texture feedTexture;
	Vector2f goalPos;
	string name;
	string creator;
	string version;
	int width;
	int height;

	
private:

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &m_tileset;

		// draw the vertex array
		target.draw(m_vertices, states);
	}

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
};