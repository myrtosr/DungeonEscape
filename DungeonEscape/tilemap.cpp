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

void TileMap::drawGridDebug()
{
    graphics::Brush brush;
    brush.fill_opacity = 0.0f;
    brush.outline_opacity = 1.0f;
    brush.outline_width = 1.0f;
    brush.outline_color[0] = 0.3f;
    brush.outline_color[1] = 0.0f;
    brush.outline_color[2] = 0.3f;

    for (Tile& tile : tiles)
    {
        float world_x = tile.getX() * TILE_SIZE + TILE_SIZE * 0.5f;
        float world_y = tile.getY() * TILE_SIZE + TILE_SIZE * 0.5f;

        graphics::drawRect(
            world_x,
            world_y,
            TILE_SIZE,
            TILE_SIZE,
            brush
        );
    }
}





