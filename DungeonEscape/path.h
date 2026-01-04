#pragma once
#include "graphobject.h"
#include "roomnode.h"
#include "door.h"
#include <vector>
#include "tilecoord.h"

using namespace std;


class Path : GraphObject {
public:

	RoomNode* roomFromId;
	RoomNode* roomToId;

	Door* doorFromId;
	Door* doorToId;

	vector <TileCoord> pathTiles; // TileMap level


	float weight;
	bool isAccesible;

	int requiredKeyId;


	// Constructor
	Path(int id, int from, int to, float dist, int keyReq = -1);
	
	// getWeight method
	float getWeight();

	// unlock
	void unlock();
};
