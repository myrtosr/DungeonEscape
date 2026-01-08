#pragma once
#include <vector>
#include "tile.h"
#include "config.h"

class TileMap {
	std::vector<Tile> tiles;
	// Hover logic
	int hoveredRow = -1;
	int hoveredCol = -1;
	// Click logic
	int clickedRow = -1;
	int clickedCol = -1;

public:
	// WHO CREATES THE GRID -> GAMESTATE!!! -> DungeonMap not TileMap
	// So we get default constructor
	TileMap();

	Tile& at(int row, int col);
	// Grid coords → Canvas coords (used for drawing)
	void tileToCanvas(int row, int col, float& cx, float& cy) const;
	// Canvas coords → Grid coords (for mouse handling in grid coords)
	void canvasToTile(float cx, float cy, int& row, int& col) const;
	// Hover logic
	void setHoveredTile(int row, int col) { hoveredRow = row; hoveredCol = col; }
	void clearHover() { hoveredRow = hoveredCol = -1; }
	bool isHovered(int row, int col) const { return row == hoveredRow && col == hoveredCol; }
	// Click Logic
	void setClickedTile(int row, int col) { clickedRow = row; clickedCol = col; }
	void clearClicked() { clickedRow = clickedCol = -1; }
	bool isClicked(int row, int col) const { return row == clickedRow && col == clickedCol; }
	//------------------------
	void draw();
	void drawGridDebug();
};