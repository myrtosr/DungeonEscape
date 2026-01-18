#include "tilemap.h"
#include "config.h"
#include "sgg/graphics.h"
#include <queue>
#include <algorithm>

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

std::vector<TileCoord> TileMap::findTilePath(TileCoord start, TileCoord target)
{
    // The final tile-by-tile path will be stored in this vector
    std::vector<TileCoord> path;

    // Grid size
    int rows = GRID_HEIGHT;
    int cols = GRID_WIDTH;

    // Info needed for BFS stored in vectors
    // visited
    std::vector<std::vector<bool>> visited(
        rows, std::vector<bool>(cols, false));
    // previous 
    std::vector<std::vector<TileCoord>> prev(
        rows, std::vector<TileCoord>(cols, {-1,-1}));

    // Queue needed for BFS
    std::queue<TileCoord> q;
    q.push(start);
    visited[start.x][start.y] = true;

    // Movement directions
    const int dx[4] = { -1, 1, 0, 0 };
    const int dy[4] = { 0, 0, -1, 1 };

    //Main loop
    while (!q.empty()) {

        TileCoord current = q.front();
        q.pop();

        // If target tile reached -> stop BFS
        if (current.x == target.x && current.y == target.y) {
            break;
        }

        // Exploring neighbouring tiles
        for (int i = 0; i < 4; ++i) {
            int nX = current.x + dx[i];
            int nY = current.y + dy[i];

            // Boundary check
            if (nX < 0 || nX >= rows || nY < 0 || nY >= cols) {
                continue;
            }

            // Tile-type check
            Tile& tile = at(nX, nY);
            if (tile.getType() != TileType::FLOOR && tile.getType() != TileType::PASSAGE) {
                continue;
            }

            // Exclude already visited tiles
            if (visited[nX][nY]) {
                continue;
            }

            visited[nX][nY] = true;
            prev[nX][nY] = current;
            q.push({nX, nY});
        }
    }

    // If target not visited return empty path
    if (!visited[target.x][target.y]) {
        return path;
    }

    // Construct path: target -> start
    TileCoord c = target;
    while (!(c.x == start.x && c.y == start.y)) {
        path.push_back(c);
        c = prev[c.x][c.y];
    }
    path.push_back(start);

    // Return the path in correct order: start -> target
    std::reverse(path.begin(), path.end());

    return path;

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

        case TileType::FLOOR: br.texture = std::string(ASSET_PATH) + "FLOOR.png"; break;
            
        case TileType::WALL_T: br.texture = std::string(ASSET_PATH) + "T.png"; break;
        case TileType::WALL_B: br.texture = std::string(ASSET_PATH) + "B.png"; break;
        case TileType::WALL_L: br.texture = std::string(ASSET_PATH) + "L.png"; break;
        case TileType::WALL_R: br.texture = std::string(ASSET_PATH) + "R.png"; break;
        case TileType::WALL_TL: br.texture = std::string(ASSET_PATH) + "TL.png"; break;
        case TileType::WALL_TR: br.texture = std::string(ASSET_PATH) + "TR.png"; break;
        case TileType::WALL_BL: br.texture = std::string(ASSET_PATH) + "BL.png"; break;
        case TileType::WALL_BR: br.texture = std::string(ASSET_PATH) + "BR.png"; break;
           
        case TileType::DOOR_T: br.texture = std::string(ASSET_PATH) + "DOOR_T.png"; break;
        case TileType::DOOR_L: br.texture = std::string(ASSET_PATH) + "DOOR_L.png"; break;
        case TileType::DOOR_R: br.texture = std::string(ASSET_PATH) + "DOOR_R.png"; break;
        

        case TileType::PASSAGE: br.texture = std::string(ASSET_PATH) + "FLOOR.png"; break;
      
        case TileType::EMPTY:
            br.fill_color[0] = 26 / 255.0f;  
            br.fill_color[1] = 3 / 255.0f;  
            br.fill_color[2] = 46 / 255.0f;  
            break;
        }
        
        // Visual feedback for hover and click
        if (isHovered(t.getX(), t.getY())) {
            br.outline_opacity = 1.0f;
            br.outline_color[0] = 53 / 255.0f;
            br.outline_color[1] = 37 / 255.0f;
            br.outline_color[2] = 108 / 255.0f;
            br.outline_width = 3.0f;
        }

        if (isClicked(t.getX(), t.getY())) {

            br.fill_color[0] = 186 / 255.0f;
            br.fill_color[1] = 180 / 255.0f;
            br.fill_color[2] = 221 / 255.0f;
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





