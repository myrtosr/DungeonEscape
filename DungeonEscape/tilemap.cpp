#include "tilemap.h"
#include "config.h"
#include "sgg/graphics.h"

// Constructor of TileMap
TileMap::TileMap()
{   

    // Reserving space for vector
    tiles.reserve(TILES_X * TILES_Y);

    // Saving coordinates of grid_map in vector
    for (int y = 0; y < TILES_Y; ++y)
        for (int x = 0; x < TILES_X; ++x)
            tiles.emplace_back(x, y);
}

// Row major order to access tiles
Tile& TileMap::at(int x, int y) {
    return tiles[y * TILES_X + x];
}




