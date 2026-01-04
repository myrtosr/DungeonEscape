#pragma once
#include "roomnode.h"
#include "passage.h"
#include <vector>;


class DungeonGraph {
	std::vector<RoomNode*> rooms;
	std::vector<Passage*> passages;

public:
	void addRoom(RoomNode* const room);
	void addPassage(Passage* const passage);

	//pathfind method
	//updateWeight() 
	
};