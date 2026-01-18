#pragma once
#include "util.h"
#include "passage.h"
#include "tilemap.h"


class PassageView {
	Passage* passage; // pointer to corresponding passage-edge 
	
	TileCoord first; // the first tile of a passage
	TileCoord last;  // the last tile of a passage
	TileCoord corner; // corner in case of cornered passage

public:
	// Constructor for straight passages
	PassageView(Passage* p, TileCoord f, TileCoord l)
		: passage(p), first(f), last(l), corner({-1, -1}){
	}

	// Constructor for cornered passages
	PassageView(Passage* p, TileCoord f, TileCoord l, TileCoord c)
		: passage(p), first(f), last(l), corner(c) {
	}

	// Getters
	Passage* getPassage() const { return passage; }
	TileCoord getFirstTile() const { return first; }
	TileCoord getLastTile() const { return last; }
	TileCoord getCorner() const { return corner; }
	bool isCornered() const { return (corner.x != -1) && (corner.y != -1); }

	void applyToTileMap(TileMap& map);
};