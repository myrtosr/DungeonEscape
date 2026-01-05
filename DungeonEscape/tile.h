#pragma once

enum class TileType {
	EMPTY,
	FLOOR,
	WALL_HOR,
	WALL_VER,
	WALL_TL,
	WALL_TR,
	WALL_BL,
	WALL_BR,
	DOOR,
	PASSAGE
};

class Tile {
	int x, y;  //grid coordinates
	TileType type;

	bool clickable = false;
	bool occupied = false;

public:
	// Constructor -> intialize tileType=Empty
	Tile(int x, int y, TileType type = TileType::EMPTY)
		: x(x), y(y), type(type) {
	}

	int getX() { return x; };
	int getY() { return y; };
};