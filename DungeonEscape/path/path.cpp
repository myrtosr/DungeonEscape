#include "path.h"
#include "room.h"
#include "door.h"

#include <vector>

using namespace std;



// Constructor
Path ::	Path(int id, int from, int to, float dist, int keyReq = -1)
		: id(id), roomFromId(from), roomToId(to), weight(dist), requiredKeyId(keyReq) {};

// getWeight method
Path :: getWeight() {
		if (isAccesible) {
			return std::numeric_limits<float>::infinity(); // ??????? 1: Logic
		}
		return weight;
	};

// unlock
Path :: void unlock() {
		isAccesible = true;
	};
};
