#pragma once
#include "roomnode.h"
#include "config.h"


class Passage {
	int id;

	int roomFromId;
	int roomToId;

	int realWeight; // real weight is set by the number of tiles of the passage
	const int infWeight = INF;
	int weight = infWeight;  // big enough that no path sum will reach it, but safe for avoiding overflow
	// bool accessible = false; (most propably remove this)

public:

	// Constructors & Destructor
	Passage(int id, int from, int to)
		: id(id), roomFromId(from), roomToId(to) {
	};

	Passage(int id, int from, int to, int rw)
		: id(id), roomFromId(from), roomToId(to), realWeight(rw) {
	};

	// Setters & getters
	void setWeight(int w) { weight = w; }
	int getWeight() { return weight; }

	void setRealWeight(int rw) { realWeight = rw; }
	int getRealWeight() { return realWeight; }
	
	int getId() const { return id; }

	int getRoomFromId() const { return roomFromId; }
	int getRoomToId() const { return roomToId; }

	// Unlock logic
	bool isUnlocked(int w) { return w < infWeight; }
	void unlockPassage() { weight = realWeight; } // unlocking a passage (weight changes: infWeight -> realWeight)

	
	
};
