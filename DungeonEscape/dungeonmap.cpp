#include "dungeonmap.h"
#include <cstdlib>
#include "sgg\graphics.h"
#include <iostream>
#include "config.h"

void DungeonMap::buildViews()
{
    roomViews.clear();
    passageViews.clear();

    // RoomViews Initialization
    RoomNode* r1 = graph->getRoomById(1);
    roomViews.emplace_back(r1, TileCoord(5, 1), TileCoord(9, 5));
    roomViews[0].addEntrance({ 7,5 });

    RoomNode* r2 = graph->getRoomById(2);
    roomViews.emplace_back(r2, TileCoord(4, 9), TileCoord(10, 13));
    roomViews[1].addEntrance({ 7, 9 });
    roomViews[1].addEntrance({ 4, 11 });
    roomViews[1].addEntrance({ 10, 11 });

    RoomNode* r3 = graph->getRoomById(3);
    roomViews.emplace_back(r3, TileCoord(1, 14), TileCoord(3, 18));
    // no entrances, only door

    RoomNode* r4 = graph->getRoomById(4);
    roomViews.emplace_back(r4, TileCoord(14, 9), TileCoord(18, 13));
    roomViews[3].addEntrance({ 16, 9 });
    roomViews[3].addEntrance({ 16, 13 });

    RoomNode* r5 = graph->getRoomById(5);
    roomViews.emplace_back(r5, TileCoord(15, 1), TileCoord(17, 5));
    // no entrances, only door

    RoomNode* r6 = graph->getRoomById(6);
    roomViews.emplace_back(r6, TileCoord(4, 18), TileCoord(10, 26));
    // no entrances, only door

    RoomNode* r7 = graph->getRoomById(7);
    roomViews.emplace_back(r7, TileCoord(13, 18), TileCoord(18, 26));
    roomViews[6].addEntrance({ 16, 26 });

    RoomNode* r8 = graph->getRoomById(8);
    roomViews.emplace_back(r8, TileCoord(13, 30), TileCoord(18, 33));
    roomViews[7].addEntrance({ 13, 32 });

    // Passage Initialization
    Passage* p1 = graph->getPassageById(1);
    passageViews.emplace_back(p1, TileCoord(7, 6), TileCoord(7, 8));

    Passage* p2 = graph->getPassageById(2);
    passageViews.emplace_back(p2, TileCoord(3, 11), TileCoord(2, 13), TileCoord(2, 11)); // corner passage

    Passage* p3 = graph->getPassageById(3);
    passageViews.emplace_back(p3, TileCoord(11, 11), TileCoord(13, 11));

    Passage* p4 = graph->getPassageById(4);
    passageViews.emplace_back(p4, TileCoord(16, 6), TileCoord(16, 8));

    Passage* p5 = graph->getPassageById(5);
    passageViews.emplace_back(p5, TileCoord(16, 14), TileCoord(16, 17));

    Passage* p6 = graph->getPassageById(6);
    passageViews.emplace_back(p6, TileCoord(16, 14), TileCoord(7, 17), TileCoord(16, 17)); // corner passage

    Passage* p7 = graph->getPassageById(7);
    passageViews.emplace_back(p7, TileCoord(16, 17), TileCoord(7, 17));

    Passage* p8 = graph->getPassageById(8);
    passageViews.emplace_back(p8, TileCoord(7, 14), TileCoord(7, 17));

    Passage* p9 = graph->getPassageById(9);
    passageViews.emplace_back(p9, TileCoord(7, 14), TileCoord(16, 17), TileCoord(7, 17)); // corner passage

    Passage* p10 = graph->getPassageById(10);
    passageViews.emplace_back(p10, TileCoord(16, 27), TileCoord(16, 29));

    // Door Initialization
    doors.push_back(new Door(3, { 2,14 }));
    doors[0]->addPassage(p2);

    doors.push_back(new Door(4, { 14,11 }));
    doors[1]->addPassage(p3);

    doors.push_back(new Door(5, { 16, 5 }));
    doors[2]->addPassage(p4);

    doors.push_back(new Door(6, { 7, 18 }));
    doors[3]->addPassage(p6);
    doors[3]->addPassage(p7);


    doors.push_back(new Door(7, { 16, 18 }));
    doors[4]->addPassage(p5);

    doors.push_back(new Door(8, { 16, 30 }));
    doors[5]->addPassage(p10);

    doors.push_back(new Door(2, { 7, 13 }));
    doors[6]->addPassage(p8);
    doors[6]->addPassage(p9);
}

void DungeonMap::initializeDoorTiles()
{
    for (Door* d : doors) {
        Tile& t = tileMap.at(d->getRow(), d->getCol());
        t.setType(d->isUnlocked() ? TileType::DOOR_OPEN
            : TileType::DOOR_LOCKED);
        t.setClickable(true);
    }
}

void DungeonMap::initializeTiles()
{
    // Rooms
    for (RoomView& rv : roomViews)
        rv.applyToTileMap(tileMap);
    // Passages
    for (PassageView& ps : passageViews)
        ps.applyToTileMap(tileMap);
    //initializeDoorTiles();
}

Door* DungeonMap::getDoorAt(int r, int c)
{
    for (Door* d : doors) {
        if (d->getRow() == r && d->getCol() == c)
            return d;
    }
    return nullptr;
}

RoomNode* DungeonMap::getRoomAt(int r, int c)
{
    for (RoomView& rv : roomViews) {
        if (rv.contains(r, c)) {
            return rv.getRoomNode();
        }
    }
    return nullptr; 
}

std::vector<RoomView>& DungeonMap::getRoomViews()
{
    return roomViews;
}



bool DungeonMap::areAdjacent(const TileCoord& t1, const TileCoord& t2)
{
    int dx = std::abs(t1.x - t2.x);
    int dy = std::abs(t1.y - t2.y);
    return (dx+dy == 1);
}

std::vector<TileCoord> DungeonMap::findFullPath(TileCoord startTile, TileCoord targetTile)
{
    // Vector to store and return the final tile path the player will follow tile-by-tile
    std::vector<TileCoord> fullPath;

    RoomNode* startRoom = getRoomAt(startTile.x, startTile.y);
    RoomNode* targetRoom = getRoomAt(targetTile.x, targetTile.y);

    if (!startRoom || !targetRoom)
        return fullPath; // Returning empty path if one of the given tiles didn't translate to a room 

    int startRoomId = startRoom->getId();
    int targetRoomId = targetRoom->getId();

    // 1. Movement inside room
    // Both tiles translated to same roomId -> Movement inside a room
    // Only call BFS to calculate shortest path from startTile -> targetTile
    if (startRoomId == targetRoomId) {
        return tileMap.findTilePath(startTile, targetTile);
    }

    // 2. Movement room2room
    // Tiles belong to different rooms -> Movement room-to-room
    // Call Dijkstra to find shortest room-to-room (node-to-node) path
    // The path is given with a vector with roomIDs in the order we must traverse the rooms
    std::vector<int> roomPath = graph->getShortestRoomPath(startRoomId, targetRoomId);
    std::cout << "[DEBUG] Shortest room path: ";
    for (auto i : roomPath) std::cout << i << ' ';

    if (roomPath.empty())
        return fullPath; // Returning empty path in case of Dijkstra failure

    //------------------------
    std::vector<TileCoord> waypoints;
    waypoints.push_back(startTile); /// First waypoint -> start tile

    for (size_t i = 0; i < roomPath.size() - 1; ++i) { // For each consecutive pair of rooms
        
        int currentRoomId = roomPath[i];
        int nextRoomId = roomPath[i + 1];

        // Find passage that connects the two rooms
        PassageView* passage = nullptr;

        for (PassageView& pv : passageViews) {
            Passage* p = pv.getPassage();
            if ((p->getRoomFromId() == currentRoomId &&
                p->getRoomToId() == nextRoomId) ||
                (p->getRoomFromId() == nextRoomId &&
                    p->getRoomToId() == currentRoomId)) {
                passage = &pv;
                break;
            }
        }
        if (!passage)
            return {};

        // Decide direction (for backtracking?)
        bool forward =
            passage->getPassage()->getRoomFromId() == currentRoomId;

        TileCoord passageEnter =
            forward ? passage->getFirstTile()
            : passage->getLastTile();

        TileCoord passageExit =
            forward ? passage->getLastTile()
            : passage->getFirstTile();
        //------------------------

        // Find room exit tile
        TileCoord roomExit{ -1, -1 };
        for (RoomView& rv : roomViews) {
            RoomNode* node = rv.getRoomNode();
            if (node && node->getId() == currentRoomId) {
                // Look for an entrance that is adjacent to the passage entrance
                for (const TileCoord& e : rv.getEntrances()) {
                    if (areAdjacent(e, passageEnter)) {
                        roomExit = e;
                        break;
                    }
                }
            }
        }

        if (roomExit.x == -1) return {};
        //------------------------

        waypoints.push_back(roomExit);      // room entrance/exit waypoint
        waypoints.push_back(passageEnter);  // passage entrance waypoint
        if (passage->isCornered()) {
            waypoints.push_back(passage->getCorner()); // Γ-shaped
        }
        waypoints.push_back(passageExit); // passage exit waypoint
    }

    waypoints.push_back(targetTile); // last waypoint -> target tile

    for (size_t i = 0; i < waypoints.size() - 1; ++i) {
        TileCoord from = waypoints[i];
        TileCoord to = waypoints[i + 1];

        std::vector<TileCoord> segment = tileMap.findTilePath(from, to);
        if (segment.empty()) return {}; // failed segment

        // Avoid duplicating the starting tile
        if (!fullPath.empty()) segment.erase(segment.begin());

        fullPath.insert(fullPath.end(), segment.begin(), segment.end());
    }

    std::cout << "[DEBUG] Waypoints: ";
    for (auto w : waypoints) std::cout << "(" << w.x << ", " << w.y << ")" << std::endl;
    return fullPath;

}



void DungeonMap::update()
{
    for (Door* door : doors) {
        Tile& t = tileMap.at(door->getRow(), door->getCol());

        if (door->isUnlocked())
            t.setType(TileType::FLOOR);
    }
}

void DungeonMap::draw()
{
    // Draw tiles on grid (rooms, corridors, doors)
    tileMap.draw();

    //...
}

void DungeonMap::init()
{
    initializeTiles();
    initializeDoorTiles();
}

