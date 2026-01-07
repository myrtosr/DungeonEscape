#pragma once
#include "roomnode.h"
#include "passage.h"
#include <vector>;
#include <unordered_map>


class DungeonGraph {
	std::vector<RoomNode*> rooms;
	std::unordered_map<int, RoomNode*> roomsById;
	std::vector<Passage*> passages;
	std::unordered_map<int, Passage*> passagesById; //??

public:
	void addRoom(RoomNode* room);
	void addPassage(Passage* passage);

	//pathfind method
	//updateWeight() 

	void initializeGraphStructure();
	RoomNode* getRoomById(int id);
	
};