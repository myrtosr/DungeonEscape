#pragma once
#include "tilecoord.h"
#include "door.h"

class Door {
public:
	int id;
	TileCoord tilePos; // position in dungeon map
	bool islocked = true;

	class Passage* passage; //the edges we connect
	
	Door(int id, TileCoord pos)
		: id(id), tilePos(pos) {}


};