#include "tilemap.h"
#include "config.h"
#include "sgg/graphics.h"

// Constructor of TileMap
TileMap::TileMap()
{   

    // Reserving space for vector
    tiles.reserve(GRID_WIDTH * GRID_HEIGHT);

    // Saving coordinates of grid_map in vector
    for (int row = 0; row < GRID_HEIGHT; ++row)
        for (int col = 0; col < GRID_WIDTH; ++col)
            tiles.emplace_back(row, col);
}

// Accessing tiles in row major order
Tile& TileMap::at(int row, int col) {
    return tiles[row * GRID_WIDTH + col ];
}

void TileMap::tileToCanvas(int row, int col, float& cx, float& cy) const
{
    cx = col * TILE_SIZE + TILE_SIZE * 0.5f;
    cy = row * TILE_SIZE + TILE_SIZE * 0.5f;
}

void TileMap::canvasToTile(float cx, float cy, int& row, int& col) const
{
    row = int(cy / TILE_SIZE);
    col = int(cx / TILE_SIZE);
}

void TileMap::draw()
{

    for ( Tile& t : tiles) {
        
        float cx, cy;
        tileToCanvas(t.getX(), t.getY(), cx, cy);

        graphics::Brush br;
        br.outline_opacity = 0.0f;

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
        */

        case TileType::PASSAGE:
            br.fill_color[0] = 0.0f;
            br.fill_color[1] = 0.4f;
            br.fill_color[2] = 0.0f;
            break;
        

        case TileType::EMPTY:
            br.fill_color[0] = 26 / 255.0f;  
            br.fill_color[1] = 3 / 255.0f;  
            br.fill_color[2] = 46 / 255.0f;  
            break;
        }

        if (isHovered(t.getX(), t.getY())) {
            br.outline_opacity = 1.0f;
            br.outline_color[0] = 0.3f;
            br.outline_color[1] = 0.0f;
            br.outline_color[2] = 0.3f;
            br.outline_width = 3.0f;
        }

        if (isClicked(t.getX(), t.getY())) {
            br.fill_color[0] = 0.3f;
            br.fill_color[1] = 0.0f;
            br.fill_color[2] = 0.3f;
        }

        graphics::drawRect(cx, cy, TILE_SIZE, TILE_SIZE, br);

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
        float cx, cy;
        tileToCanvas(tile.getX(), tile.getY(), cx, cy);

        graphics::drawRect(
            cx,
            cy,
            TILE_SIZE,
            TILE_SIZE,
            brush
        );
    }
}





