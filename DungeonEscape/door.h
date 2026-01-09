#pragma once
#include <vector>
#include "util.h"
#include "passage.h"

class Door {
	int id; // I'll set ids based on the room the door belongs to ;)
	TileCoord pos; // door position on tilemap

	bool unlocked = false;

	// Why vector? Some doors control 2 passages :[
	std::vector<Passage*> controlledPassages; 

public:
	Door(int id, TileCoord p)
		: id(id), pos(p), unlocked(false) {
	}

	// Getters
	int getId() const { return id; }
	int getRow() const { return pos.x; }
	int getCol() const { return pos.y; }
	bool isUnlocked() const { return unlocked; }

	// Passage Connection
	void addPassage(Passage* p);

	void unlock();
};