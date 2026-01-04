#pragma once


class RoomNode {
	int id;
	bool available = false;
	bool explored = false;

public:

	// Constructor
	RoomNode(int id_) : id(id_) {};

	// Getters
	int getId() const { return id; }
	bool isAvailable() { return available;  }
	bool isExplored() { return explored; }

	// Setters
	void setAvailable(bool a) { available = a; }
	void setExplored(bool a) { explored = a;  }

};
