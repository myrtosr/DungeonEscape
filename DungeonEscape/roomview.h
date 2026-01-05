#pragma once
#include "tilemap.h"
#include "roomnode.h"

class RoomView {
	RoomNode* node; // pointer to corresponding room node

	int x, y;  // top-left tile
	int w, h;  // bottom-right tile
	// The bounds of the room get calculated based on those

public:
	RoomView(RoomNode* node, int x, int y, int w, int h);

	void applyToTileMap(TileMap& map); // we'll see about this
};