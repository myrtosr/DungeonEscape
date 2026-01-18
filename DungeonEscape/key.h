#pragma once
#include "gameobject.h"
#include "util.h"
#include <string>

class Key : public GameObject {
	int id;
	TileCoord pos;
	std::string png;

public:
	// Constructor & Destructor
	Key(const class GameState& mygame, int id, TileCoord p, const std::string& png) : GameObject(mygame), id(id), pos(p), png(png) {}
	~Key() = default;

	// Getters
	int getRow() const { return pos.x; }
	int getCol() const { return pos.y; }
	int getId() const { return id; }

	void update() override;
	void draw() override;
	void init() override;
};