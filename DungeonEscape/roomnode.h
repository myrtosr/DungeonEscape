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
	bool isAvailable() const { return available;  }
	bool isExplored() const { return explored; }

	// Setters
	void setAvailable(bool a) { available = a; }
	void setExplored(bool a) { explored = a;  }

};
