#include "dungeonmap.h"

void DungeonMap::buildViews()
{
    // Room Initialiasation
    RoomNode* r1 = graph->getRoomById(1);
    roomViews.emplace_back(r1, TileCoord(4, 1), TileCoord(8, 5));

    RoomNode* r2 = graph->getRoomById(2);
    roomViews.emplace_back(r2, TileCoord(4, 9), TileCoord(10, 13));

    RoomNode* r3 = graph->getRoomById(3);
    roomViews.emplace_back(r3, TileCoord(1, 14), TileCoord(3, 16));

    RoomNode* r4 = graph->getRoomById(4);
    roomViews.emplace_back(r4, TileCoord(14, 9), TileCoord(17, 13));

    RoomNode* r5 = graph->getRoomById(5);
    roomViews.emplace_back(r5, TileCoord(15, 3), TileCoord(17, 5));

    RoomNode* r6 = graph->getRoomById(6);
    roomViews.emplace_back(r6, TileCoord(4, 19), TileCoord(7, 23));

    RoomNode* r7 = graph->getRoomById(7);
    roomViews.emplace_back(r7, TileCoord(11, 19), TileCoord(17, 23));

    RoomNode* r8 = graph->getRoomById(8);
    roomViews.emplace_back(r8, TileCoord(11, 27), TileCoord(17, 32));

    /*
    // Passage init
    passageViews.emplace_back(8, 4, 12, 4);
    */
  
}

void DungeonMap::initializeTiles()
{
    // 1.Rooms
    for (RoomView& rv : roomViews)
        rv.applyToTileMap(tileMap);

}

void DungeonMap::draw()
{
    // Draw tiles on grid (rooms, corridors, doors)
    tileMap.draw();

    //...
}

