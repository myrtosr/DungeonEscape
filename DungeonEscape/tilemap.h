#pragma once
#include <vector>
#include "tile.h"
#include "config.h"

class TileMap {
	std::vector<Tile> tiles;
	int tilesX, tilesY;
public:
	TileMap();

	Tile& at(int x, int y);
	const Tile& at(int x, int y) const;

	bool pixelToTile(int px, int py, int& tx, int& ty) const {};
	void draw() const;


	// WHO CREATES THE GRID -> GAMESTATE!!! -> DungeonMap not TileMap
	// So we don't get default constructor

	// class TileMap {
	// std::vector<Tile> tiles;
	// int tilesX;   // tiles in X
	// int tilesY;  // tiles in Y

	//public:
    //	TileMap(int tilesX, int tilesY);

	//	Tile& at(int x, int y);
	//	const Tile& at(int x, int y) const;

	//	int getWidth() const { return tilesX; }
	//	int getHeight() const { return tilesY; }

	//	void draw() const;
	// };

	// 
};