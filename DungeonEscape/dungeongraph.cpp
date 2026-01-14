#pragma once
#include "roomnode.h"
#include "passage.h"
#include "dungeongraph.h"
#include <vector>
#include <unordered_map>
#include "config.h"
#include <algorithm>

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
    addPassage(new Passage(1, 1, 2, 3)); // adding weight manually since there's no door to set it (p1 is always open)
    rooms[0]->setAvailable(true); // room 1 available
    rooms[1]->setAvailable(true); // room 2 available
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

Passage* DungeonGraph::getPassageById(int id) {
    return passagesById[id];
}

std::vector<int> DungeonGraph::getShortestRoomPath(int startRoomId, int targetRoomId)
{
    // Using Dijkstra to find shortest path from startRoom to targetRoom

    // Info needed for Dijjkstra algorithm (mapping by roomIds)
    std::unordered_map<int, int> distance;
    std::unordered_map<int, int> previous;
    std::unordered_map<int, bool> visited;

    // Initialization of info for all rooms
    for (RoomNode* r : rooms) {
        int id = r->getId();
        distance[id] = INF; // initiate all distances to infinite
        previous[id] = -1; // no previous node
        visited[id] = false; // initiate all rooms as unvisited
    }

    // Our roomIds start with 1 and ends at 8
    distance[startRoomId] = 0; // distance of the first room = 0

    // Main Loop
    while (true) {
        int currentRoomId = -1;
        int smallestDistance = INF;

        for (auto& pair : distance) {
            int roomId = pair.first;
            int dist = pair.second;
            
            if (!visited[roomId] && dist < smallestDistance) {
                smallestDistance = dist;
                currentRoomId = roomId;
            }
        }

        // No reachable univisited rooms left -> stop
        if (currentRoomId == -1)
            break;

        // Mark this room as Visited
        visited[currentRoomId] = true;

        // Reach target room -> shortest path found
        if (currentRoomId == targetRoomId)
            break;

;
        
        for (Passage* p : passages) {
            // Relax all neighbouring rooms via passages 
            int neighboorRoomId = -1; 
            if (p->getRoomFromId() == currentRoomId) {
                neighboorRoomId = p->getRoomToId();
            }
            else if (p->getRoomToId() == currentRoomId) {
                neighboorRoomId = p->getRoomFromId();
            }
            else {
                continue;
            }

            // Don't touch already visited-finalized nodes
            if (visited[neighboorRoomId]) {
                continue;
            }
            
            // Safety checks to prevent overflow
            if (!p->isUnlocked(p->getWeight())) {
                continue;
            }
            if (distance[currentRoomId] >= INF)
                continue;
            //------------------------

            int newDistance = distance[currentRoomId] + p->getWeight();

            // If this path is cheaper than anything we knew before, update it
            if (newDistance < distance[neighboorRoomId]) {
                distance[neighboorRoomId] = newDistance;
                previous[neighboorRoomId] = currentRoomId;
            }
        }
    }

    // Constructing path using the previous map: target -> start
    std::vector<int> path;
    int current = targetRoomId;

    // If target was never reached, return empty path
    if (distance[current] >= INF) {
        return path;
    }
    while (current != -1) {
        path.push_back(current);
        current = previous[current];
    }
    
    // Return the path in correct order 
    std::reverse(path.begin(), path.end());
    return path;

}

// Constructor & Destructor
DungeonGraph::DungeonGraph()
{
}

// Deleting dynamically created objects
DungeonGraph::~DungeonGraph()
{
    for (auto r : rooms) delete r;
    for (auto p : passages) delete p;
}

//pathfind method
//updateWeight() 
