#include "tilecoord.h"
#include "door.h"

class Door {
public:

	int id;
	TileCoord tilePos;
	
	// Constructor
	Door(int id, TileCoord pos)
		: id(id), tilePos(pos) {
	}
};
