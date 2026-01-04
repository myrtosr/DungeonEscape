#include "path.h"
#include "graphobject.h"
#include "room.h"
#include "door.h"

#include <vector>

using namespace std;


class Path : GraphObject {
public:
	RoomNode* roomFromId;
	RoomNode* roomToId;

	Door* doorFromId;
	Door* doorToId;

	vector<TileCoord> pathTiles; // TileMap level


	float weight;
	bool isAccesible;

	int requiredKeyId;

	// Constructor
	Path(int id, int from, int to, float dist, int keyReq = -1)
		: GraphObject(id), roomFromId(from), roomToId(to), weight(dist), requiredKeyId(keyReq) {};

	// getWeight method
	float getWeight() {
		if (isAccesible) {
			return std::numeric_limits<float>::infinity(); // ??????? 1: Logic
		}
		return weight;
	};

	// unlock
	void unlock() {
		isAccesible = true;
	};
};
