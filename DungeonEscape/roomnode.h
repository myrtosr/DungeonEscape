#pragma once
#include "door.h"
#include "tilecoord.h"
#include <vector>

using std::vector;


class RoomNode {
	int id;
	int x, y, w, h; // bounds
	vector<Door&> doors;
	vector<TileCoord> tiles;   // tiles room
public:

	// Constructor
	RoomNode(int id, int x, int y, int w, int h);
	
	// connectDoor method
	void connectDoor(int doorId);

	// Getters
	int getX() const { return x; }
	int getY() const { return y; }
	int getWidth() const { return w; }
	int getHeight() const { return h;  }
	const vector<Door>& getDoors() const { return doors; }
	int getId() const { return id; }

};
