#pragma once
#include "gameobject.h"
#include "util.h"

class Key : public GameObject {
	int id;
	TileCoord pos;

public:
	// Constructor & Destructor
	Key(const class GameState& mygame, int id, TileCoord p) : GameObject(mygame), id(id), pos(p) {}
	~Key() = default;

	int getRow() const { return pos.x; }
	int getCol() const { return pos.y; }

	void update() override;
	void draw() override;
	void init() override;

	int getId() const { return id; }

};