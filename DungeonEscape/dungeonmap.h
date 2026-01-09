#pragma once
#include "gameobject.h"
#include "tilemap.h"
#include "roomview.h"
#include "passageview.h"
#include "door.h"
#include <vector>
#include "dungeongraph.h"

class DungeonMap { 
	TileMap tileMap;
	DungeonGraph* graph;

	std::vector<RoomView> roomViews;
	std::vector<PassageView> passageViews;
	std::vector<Door> doors;
	
public:
	DungeonMap(DungeonGraph* graph)
		: graph(graph) {
	};

	TileMap& getTileMap() { return tileMap; };

	// Initializing our setup
	void buildViews(); // building RoomView / PassageView / DoorView
	void initializeDoorTiles();
	void initializeTiles(); // passes tileTypes in TileMap

	// Runtime handling
	void update();
	void draw();
};