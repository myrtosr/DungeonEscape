#pragma once

// Prepei na exei id, getId, setId

class GraphObject {
protected:
	const int id;

public:

	GraphObject(int id);
	// if we create GraphObjects dynamically we need distctuctor too

	int getId() const {
		return id;
	};
};