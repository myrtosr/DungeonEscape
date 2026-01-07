#pragma once
#include "roomnode.h"
#include "passage.h"
#include <vector>;


class DungeonGraph {
	std::vector<RoomNode*> rooms;
	std::vector<Passage*> passages;

public:
	void addRoom(RoomNode* room);
	void addPassage(Passage* passage);

	//pathfind method
	//updateWeight() 

	void initializeGraphStructure();
	
};