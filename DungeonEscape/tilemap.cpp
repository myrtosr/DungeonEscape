#include "tilemap.h"
#include "config.h"
#include "sgg/graphics.h"

// Constructor of TileMap
TileMap::TileMap()
{
    // (m, n) -> tilesX=m, tilesY=n
    tilesX = CANVAS_WIDTH / TILE_SIZE;
    tilesY = CANVAS_HEIGHT / TILE_SIZE;

    // desmeusi xwro gia vector
    tiles.reserve(tilesX * tilesY);

    // saving coordinates of grid_map in vector
    for (int y = 0; y < tilesY; ++y)
        for (int x = 0; x < tilesX; ++x)
            tiles.emplace_back(x, y);
}

// Row major order to access tiles
Tile& TileMap::at(int x, int y) {
    return tiles[y * tilesX + x];
}

// const override 
//const Tile& TileMap::at(int x, int y) const {
//    return tiles[y * tilesX + x];
//}

// pixel -> tile
// πρόταση: αυτή η συνάρτηση να είναι στη Game state. Χειρίζεται mouse inputs -> αυτό είναι δουλειά της Game
// Ίσως το TileMap δεν πρέπει να ξέρει καθόλου canvas coordinates... δουλεύει με τις δικές του μονάδες. 
bool TileMap::pixelToTile(int px, int py, int& tx, int& ty) const {  
    tx = px / TILE_SIZE;
    ty = py / TILE_SIZE;

    return tx >= 0 && tx < tilesX &&
        ty >= 0 && ty < tilesY;
}

// draw()
void TileMap::draw() const {
    for (const Tile& t : tiles) {
        float px = t.getX() * TILE_SIZE;
        float py = t.getY() * TILE_SIZE;

        graphics::Brush br;

        switch (t.type) {
        case TileType::Floor:
            br.fill_color[0] = 0.6f;
            br.fill_color[1] = 0.6f;
            br.fill_color[2] = 0.6f;
            break;
        case TileType::Wall:
            br.fill_color[0] = 0.2f;
            br.fill_color[1] = 0.2f;
            br.fill_color[2] = 0.2f;
            break;
        case TileType::Door:
            br.fill_color[0] = 0.8f;
            br.fill_color[1] = 0.5f;
            br.fill_color[2] = 0.2f;
            break;
        default:
            br.fill_color[0] = 0.1f;
            br.fill_color[1] = 0.1f;
            br.fill_color[2] = 0.1f;
        }

        graphics::drawRect(px, py, TILE_SIZE, TILE_SIZE, br);
    }
}

