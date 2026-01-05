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


};