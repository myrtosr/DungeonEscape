#pragma once
#include "roomnode.h"
#include "passage.h"
#include <vector>
#include <unordered_map>
#include "config.h"


class DungeonGraph {
	// Vectors for fast iteration, maps for fast access
	std::vector<RoomNode*> rooms;
	std::unordered_map<int, RoomNode*> roomsById;
	std::vector<Passage*> passages;
	std::unordered_map<int, Passage*> passagesById; 

public:
	void addRoom(RoomNode* room);
	void addPassage(Passage* passage);

	void initializeGraphStructure();
	RoomNode* getRoomById(int id);
	Passage* getPassageById(int id);

	void unlockRoomsFromPassage(Passage* p);

	// Pathfinding for shortest roompath using Dijkstra algorithm
	std::vector<int> getShortestRoomPath(int startRoomId, int targetRoomId);

	void clear();
	// Constructor & Destructor
	DungeonGraph();
	~DungeonGraph();
};