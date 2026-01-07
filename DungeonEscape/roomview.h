#pragma once
#include "util.h"
#include "roomnode.h"

class RoomView {
	RoomNode* roomNode; // pointer to corresponding room node 
	// Conenction to roomnode could also be achieved with roomID since it's a unique property?

	TileCoord topLeft; // the first tile of a room
	TileCoord bottomRight;  // the last tile of a room
	// The bounds of the room get calculated based on those

public:
	RoomView(RoomNode* node, TileCoord tl, TileCoord br)
		: roomNode(node), topLeft(tl), bottomRight(br) {
	}

	// Getters
	RoomNode* getRoomNode() const { return roomNode; }
	TileCoord getTopLeft() const { return topLeft; }
	TileCoord getBottomRight() const { return bottomRight; }

	// void applyToTileMap(TileMap& map); // we'll see about this
};