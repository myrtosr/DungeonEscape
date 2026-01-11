#pragma once
#include "util.h"
#include "gameobject.h"

class Player : public GameObject {
	TileCoord pos{-1, -1}; // position on grid
	float speed;

public:
	void update() override;
	void draw() override;
	void init() override;

	Player(const class GameState& mygame);
	~Player();
};