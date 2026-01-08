#pragma once
#include <vector>
#include "tile.h"
#include "config.h"

class TileMap {
	std::vector<Tile> tiles;
	int hoveredRow = -1;
	int hoveredCol = -1;

public:
	// WHO CREATES THE GRID -> GAMESTATE!!! -> DungeonMap not TileMap
	// So we get default constructor
	TileMap();

	Tile& at(int row, int col);
	// Grid coords → Canvas coords (used for drawing)
	void tileToCanvas(int row, int col, float& cx, float& cy) const;
	// Canvas coords → Grid coords (for mouse handling in grid coords)
	void canvasToTile(float cx, float cy, int& row, int& col) const;
	void setHoveredTile(int row, int col) { hoveredRow = row; hoveredCol = col; }
	void clearHover() { hoveredRow = hoveredCol = -1; }
	bool isHovered(int row, int col) const { return row == hoveredRow && col == hoveredCol; }
	void draw();
	void drawGridDebug();
};