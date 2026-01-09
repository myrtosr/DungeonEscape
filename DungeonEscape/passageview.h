#pragma once
#include "util.h"
#include "passage.h"
#include "tilemap.h"


class PassageView {
	Passage* passage; // pointer to corresponding passage-edge 
	// Conenction to passages could also be achieved with passageID since it's a unique property?

	
	TileCoord first; // the first tile of a passage
	TileCoord last;  // the last tile of a passage
	TileCoord corner; // corner in case of cornered passage
	// Assuming passages only have height = 1 tile, I changed the names a bit

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

	void applyToTileMap(TileMap& map);
};