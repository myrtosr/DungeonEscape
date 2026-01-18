#pragma once
#include "util.h"
#include "gameobject.h"
#include "key.h"
#include <vector>

class RoomNode;

class Player : public GameObject {
	TileCoord pos{-1, -1}; // position on grid
	int currentRoomId; // logical position

	// Movement
	std::vector<TileCoord> path; // Player moves tile by tile ... smooth animation later
	int pathIndex = 0;
	bool moving;

	std::vector<int> keyInventory;
public:
	// Constructor & Destructor
	Player(const class GameState& mygame);
	~Player();

	void update() override;
	void draw() override;
	void init() override;

	void spawnAt(TileCoord tile, int start);

	// Getters
	bool isMoving() const { return moving; }
	TileCoord getPos() const { return pos; }
	int getRoom() const { return currentRoomId; }

	// Setters
	void setRoom(int r) { currentRoomId = r; }
	void setPath(const std::vector<TileCoord>& newPath);
	void setMoving(bool c) { moving = c; }

	// Inventory handling
	void addKey(int id) { keyInventory.push_back(id); }
	bool hasKey(int id) { return std::find(keyInventory.begin(), keyInventory.end(), id) != keyInventory.end(); }
};