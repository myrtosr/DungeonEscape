#include "player.h"
#include "sgg\graphics.h"
#include "gamestate.h"
#include "config.h"

Player::Player(const GameState& mygame) : GameObject(mygame)
{
	init();
}

Player::~Player()
{
}


void Player::spawnAt(TileCoord tile, int start)
{
	pos = tile;
	currentRoomId = start;
}

void Player::setPath(const std::vector<TileCoord>& newPath)
{
	path = newPath;
	pathIndex = 0;
}

void Player::update()
{
    if(!moving) return;       // nothing to do if not moving
	
    if(!path.empty()) {
        // Move one tile along the path
        pos = path.front();   // teleport to next tile
        path.erase(path.begin());     // remove tile from path

        // Optional: you can add animation logic here instead of instant teleport
        // Example: lerp from old position to new for smooth animation
     }

    if (path.empty()) {
        moving = false;  // finished moving
    }
}

void Player::draw()
{
    if (pos.x < 0 || pos.y < 0)
        return;

    float cx, cy;
    gamestate.getDungeonMap().getTileMap().tileToCanvas(pos.x, pos.y, cx, cy);

    graphics::Brush br;
    br.outline_opacity = 0.0f;
	br.texture = std::string(ASSET_PATH) + "char.png";

    graphics::drawRect(cx, cy - 12, TILE_SIZE * 1.15 , TILE_SIZE * 1.3,  br);
}

void Player::init()
{
	currentRoomId = 0;
	moving = false;
	float speed = 6.0f; // idk what this should be... we'll see in due time
	path.clear();
}



