#include "door.h"

void Door::addPassage(Passage* p) {
	if (p)
		controlledPassages.push_back(p);
}

void Door::unlock() {
	if (unlocked) return;   // no double unlock? man idk
	unlocked = true;

	// Unlock all connected passages
	for (Passage* p : controlledPassages) {
		if (p)
			p->unlockPassage();
	}
}