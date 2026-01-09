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
	DOOR_LOCKED,
	DOOR_OPEN,
	PASSAGE
};

class Tile {
	int x, y;  //grid coordinates
	TileType type;

	bool hovered = false;
	bool clickable = false;
	bool occupied = false;

public:
	// Constructor -> intialize tileType=Empty
	Tile(int x, int y, TileType type = TileType::EMPTY)
		: x(x), y(y), type(type) {
	}

	int getX() { return x; };
	int getY() { return y; };

	TileType getType() const { return type; }
	void setType(TileType t) { type = t; }

	bool isHovered() const { return hovered; }
	void setHovered(bool h) { hovered = h; }

	bool isClickable() const { return clickable; }
	void setClickable(bool c) { clickable = c; }
};