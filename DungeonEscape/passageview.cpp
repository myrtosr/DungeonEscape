#include "passageview.h"


void PassageView::applyToTileMap(TileMap& map) {
    int tileCount = 0;
    /// Straight horizontal
    if (first.x == last.x) {
        int dy = (last.y > first.y) ? 1 : -1;
        for (int y = first.y; y != last.y + dy; y += dy) {
            map.at(first.x, y).setType(TileType::PASSAGE);
            map.at(first.x, y).setClickable(false);
            tileCount++;
        }
        passage->setRealWeight(tileCount);
        return;
    }

    // Straight vertical
    if (first.y == last.y) {
        int dx = (last.x > first.x) ? 1 : -1;
        for (int x = first.x; x != last.x + dx; x += dx) {
            map.at(x, first.y).setType(TileType::PASSAGE);
            map.at(x, first.y).setClickable(false);
            tileCount++;
        }
        passage->setRealWeight(tileCount);
        return;
    }

    // Cornered passage
    // From first tile -> corner tile
    int dx = (corner.x > first.x) ? 1 : (corner.x < first.x ? -1 : 0);
    int dy = (corner.y > first.y) ? 1 : (corner.y < first.y ? -1 : 0);

    int x = first.x;
    int y = first.y;

    while (x != corner.x || y != corner.y) {
        map.at(x, y).setType(TileType::PASSAGE);
        map.at(x, y).setClickable(false);
        if (x != corner.x) x += dx;
        if (y != corner.y) y += dy;
        tileCount++;
    }
    // ------------------------
    // From corner tile -> last tile
    dx = (last.x > corner.x) ? 1 : (last.x < corner.x ? -1 : 0);
    dy = (last.y > corner.y) ? 1 : (last.y < corner.y ? -1 : 0);

    x = corner.x;
    y = corner.y;

    while (x != last.x || y != last.y) {
        map.at(x, y).setType(TileType::PASSAGE);
        map.at(x, y).setClickable(false);
        if (x != last.x) x += dx;
        if (y != last.y) y += dy;
        tileCount++;
    }
    // ------------------------
    // Making sure the last tile is drawn
    // Depending of how dx, dy move, while loops might stop before filling it  
    if (passage->getId() == 2) { // Stupid fix to avoid double tile count :P
        map.at(last.x, last.y).setType(TileType::PASSAGE);
        map.at(last.x, last.y).setClickable(false);
        tileCount++;
    }

    passage->setRealWeight(tileCount);
}