#include "door.h"
#include "dungeongraph.h"

void Door::addPassage(Passage* p) {
	if (p)
		controlledPassages.push_back(p);
}

void Door::unlock(DungeonGraph& mygraph) {
	if (unlocked) return;   // no double unlock? man idk
	unlocked = true;

	// Unlock all connected passages
	for (Passage* p : controlledPassages) {
		if (p){
			p->unlockPassage();
			mygraph.unlockRoomsFromPassage(p);
		}
	}
}