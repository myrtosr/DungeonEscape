#include "passage.h"
// #include "roomnode.h"


// getWeight method
int Passage ::  getWeight() {
	return accessible ? weight : 100;
}

// unlock
void Passage :: unlock() {
		accessible = true;
}
