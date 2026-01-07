#pragma once
#include <vector>
#include "tile.h"
#include "config.h"

class TileMap {
	std::vector<Tile> tiles;

public:
	// WHO CREATES THE GRID -> GAMESTATE!!! -> DungeonMap not TileMap
	// So we get default constructor
	TileMap();

	Tile& at(int x, int y);

	bool pixelToTile(int px, int py, int& tx, int& ty) const {};
	void draw();

	void drawGridDebug();
};