#include "dungeonmap.h"

void DungeonMap::buildViews()
{
    roomViews.clear();
    passageViews.clear();

    // RoomViews Initialiasation
    RoomNode* r1 = graph->getRoomById(1);
    roomViews.emplace_back(r1, TileCoord(5, 1), TileCoord(9, 5));

    RoomNode* r2 = graph->getRoomById(2);
    roomViews.emplace_back(r2, TileCoord(4, 9), TileCoord(10, 13));

    RoomNode* r3 = graph->getRoomById(3);
    roomViews.emplace_back(r3, TileCoord(1, 14), TileCoord(3, 18));

    RoomNode* r4 = graph->getRoomById(4);
    roomViews.emplace_back(r4, TileCoord(14, 9), TileCoord(18, 13));

    RoomNode* r5 = graph->getRoomById(5);
    roomViews.emplace_back(r5, TileCoord(15, 1), TileCoord(17, 5));

    RoomNode* r6 = graph->getRoomById(6);
    roomViews.emplace_back(r6, TileCoord(4, 18), TileCoord(10, 26));

    RoomNode* r7 = graph->getRoomById(7);
    roomViews.emplace_back(r7, TileCoord(13, 18), TileCoord(18, 26));

    RoomNode* r8 = graph->getRoomById(8);
    roomViews.emplace_back(r8, TileCoord(13, 30), TileCoord(18, 33));

    
    // Passage Initialization
    Passage* p1 = graph->getPassageById(1);
    passageViews.emplace_back(p1, TileCoord(7,6), TileCoord(7,8));
    
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
    doors.emplace_back(1, TileCoord(7, 5));
    doors[0].addPassage(p1);
    doors[0].unlock(); // ΡΗΤΑ unlock first door -> also unlocks the passages she controls (p1) *thumbs up*
    

    doors.emplace_back(3, TileCoord(2,14));
    doors[0].addPassage(p2);

    doors.emplace_back(4, TileCoord(14, 11));
    doors[1].addPassage(p3);

    doors.emplace_back(5, TileCoord(16, 5));
    doors[2].addPassage(p4);

    doors.emplace_back(6, TileCoord(7, 18));
    doors[3].addPassage(p6);
    doors[3].addPassage(p7);


    doors.emplace_back(7, TileCoord(16, 18));
    doors[4].addPassage(p5);

    doors.emplace_back(8, TileCoord(16, 30));
    doors[5].addPassage(p10);

    doors.emplace_back(2, TileCoord(7, 13));
    doors[6].addPassage(p8);
    doors[6].addPassage(p9);
}

void DungeonMap::initializeDoorTiles()
{
    for (Door d : doors) {
        Tile& t = tileMap.at(d.getRow(), d.getCol());
        t.setType(d.isUnlocked() ? TileType::DOOR_OPEN
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
    initializeDoorTiles();
}

void DungeonMap::draw()
{
    // Draw tiles on grid (rooms, corridors, doors)
    tileMap.draw();

    //...
}

