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

void TileMap::draw()
{
    for ( Tile& t : tiles) {
        
        // MAKE pixel2Canvas function
        float px = t.getX() * TILE_SIZE;
        float py = t.getY() * TILE_SIZE;

        graphics::Brush br;

        switch (t.getType()) 
        {

        case TileType::FLOOR:
            br.fill_color[0] = 106/255.0f;
            br.fill_color[1] = 163/255.0f;
            br.fill_color[2] = 236/255.0f;
            break;

        case TileType::WALL_HOR:
        case TileType::WALL_VER:
        case TileType::WALL_TL:
        case TileType::WALL_TR:
        case TileType::WALL_BL:
        case TileType::WALL_BR:
            br.fill_color[0] = 247/ 255.0f;
            br.fill_color[1] = 229/ 255.0f;
            br.fill_color[2] = 134/ 255.0f;
            break;
        
        /*
        case TileType::DOOR:
            br.fill_color[0] = 0.8f;
            br.fill_color[1] = 0.5f;
            br.fill_color[2] = 0.2f;
            break;

        case TileType::PASSAGE:
            br.fill_color[0] = 0.4f;
            br.fill_color[1] = 0.4f;
            br.fill_color[2] = 0.4f;
            break;
        */

        case TileType::EMPTY:
            br.fill_opacity = 0.0f;
            break;
        }

        graphics::drawRect(px, py, TILE_SIZE, TILE_SIZE, br);

        }

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





