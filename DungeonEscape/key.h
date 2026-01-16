#pragma once
#include "gameobject.h"

class Key : public GameObject {
	int id;
	TileCoord pos;

public:
	// Constructor & Destructor
	Key(const class GameState& mygame, int id, TileCoord p) : GameObject(mygame), id(id), pos(p) {};
	~Key();

	int getRow() const { return pos.x; }
	int getCol() const { return pos.y; }

	void update();
	void draw();
	void init();

	int getId() const { return id; }

};