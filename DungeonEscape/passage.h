#pragma once
#include "roomnode.h"
#include <limits>


class Passage {
	int id;

	int roomFromId;
	int roomToId;

	int realWeight; // real weight is set by the number of tiles of the passage
	int weight = 1000;  // big enough that no path sum will reach it, but safe for avoiding overflow
	// bool accessible = false; (most propably remove this)

public:

	// Constructor
	Passage(int id, int from, int to)
		: id(id), roomFromId(from), roomToId(to) {
	};


	// Setters & getters
	void setWeight(int w) { weight = w; }
	int getWeight() { return weight; }

	void setRealWeight(int rw) { realWeight = rw; }
	int getRealWeight() { return realWeight; }
	
	int getId() const { return id; }

	// Unlocking a passage (weight changes from inf, that represents locked, to realWeight)
	void unlockPassage() { weight = realWeight; }

	
	
};
