#pragma once

enum class TileType {
	EMPTY,
	FLOOR,
	WALL_T,
	WALL_B,
	WALL_L,
	WALL_R,
	WALL_TL,
	WALL_TR,
	WALL_BL,
	WALL_BR,
	DOOR_LOCKED, // REMOVE
	DOOR_T,
	DOOR_L,
	DOOR_R,
	DOOR_OPEN, // REMOVE
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