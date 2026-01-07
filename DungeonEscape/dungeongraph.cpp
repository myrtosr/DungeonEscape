#pragma once
#include "roomnode.h"
#include "passage.h"
#include "dungeongraph.h"
#include <vector>;
#include <unordered_map>


void DungeonGraph::addRoom(RoomNode* room)
{
    if (!room) return;
    rooms.push_back(room);

    // adding to the hash map
    roomsById[room->getId()] = room;
}

void DungeonGraph::addPassage(Passage* passage)
{
    if (!passage) return;
    passages.push_back(passage);

    // adding to the hash map
    passagesById[passage->getId()] = passage; //??
}


void DungeonGraph::initializeGraphStructure() {
    // constructing the 8 RoomNodes of our graph
    for (int i = 1; i <= 8; i++) { // 1 = start node and 8 = exit node
        addRoom(new RoomNode(i));
    }

    // Connecting the DungeonGraph RoomNodes by constructing the Edges/Passages
    addPassage(new Passage(1, 1, 2));
    addPassage(new Passage(2, 2, 3));
    addPassage(new Passage(3, 2, 4));
    addPassage(new Passage(4, 4, 5));
    addPassage(new Passage(5, 4, 7));
    addPassage(new Passage(6, 4, 6));
    addPassage(new Passage(7, 6, 7));
    addPassage(new Passage(8, 6, 2));
    addPassage(new Passage(9, 7, 2));
    addPassage(new Passage(10, 7, 8));

    // Passage weights will be set later based on corridor length in tiles 
    // (computed from the GridMap?)
}

RoomNode* DungeonGraph::getRoomById(int id)
{
    return roomsById[id];
}


//pathfind method
//updateWeight() 
