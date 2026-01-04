#include "passage.h"
// #include "roomnode.h


// getWeight method
int Passage ::  getWeight() {
	return accessible ? weight : 1000;
}

// unlock
void Passage :: unlock() {
		accessible = true;
}
