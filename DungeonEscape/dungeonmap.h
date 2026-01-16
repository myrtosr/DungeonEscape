#pragma once
#include "gameobject.h"
#include "tilemap.h"
#include "roomview.h"
#include "passageview.h"
#include "door.h"
#include <vector>
#include "dungeongraph.h"
#include "key.h"

class DungeonMap { 
	TileMap tileMap;
	DungeonGraph* graph;

	std::vector<RoomView> roomViews;
	std::vector<PassageView> passageViews;
	std::vector<Door*> doors;
	std::vector<Key*> keys;
	
public:
	DungeonMap(DungeonGraph* graph)
		: graph(graph) {
	};


	TileMap& getTileMap() { return tileMap; };
	const TileMap& getTileMap() const { return tileMap; }

	// Initializing our setup
	void buildViews(); // building RoomView / PassageView / DoorView
	void initializeDoorTiles();
	void initializeTiles(); // passes tileTypes in TileMap
	//------------------------

	Door* getDoorAt(int r, int c);
	RoomNode* getRoomAt(int r, int c);
	Key* getKeyAt(int r, int c);
	void removeKey(Key* key);

	std::vector<TileCoord> findFullPath(TileCoord startTile, TileCoord targetTile);

	// Runtime handling
	void update();
	void draw();
	void init();
};