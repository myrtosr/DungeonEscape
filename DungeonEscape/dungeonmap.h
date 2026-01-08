#pragma once
#include "gameobject.h"
#include "tilemap.h"
#include "roomview.h"
#include "passageview.h"
#include <vector>
#include "dungeongraph.h"

class DungeonMap { 
	TileMap tileMap;
	DungeonGraph* graph;

	std::vector<RoomView> roomViews;
	std::vector<PassageView> passageViews;
	
public:
	DungeonMap(DungeonGraph* graph)
		: graph(graph) {
	};

	TileMap& getTileMap() { return tileMap; };

	// Initializing our setup
	void buildViews(); // building RoomView / PassageView / DoorView
	void initializeTiles(); // passes tileTypes in TileMap

	// Runtime handling
	void update();
	void draw();
};