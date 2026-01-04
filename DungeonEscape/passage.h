#pragma once
#include "roomnode.h"
#include <limits>


class Passage {
	int id;

	int roomFromId;
	int roomToId;


	int weight = 1000;  // infinity will cause overflow???
	bool accessible = false; //???

public:

	// Constructor
	Passage(int id, int from, int to)
		: id(id), roomFromId(from), roomToId(to) {
	};

	// getWeight method
	int getWeight();

	// unlock
	void unlock();

	// getId
	int getId() const { return id; }
};
