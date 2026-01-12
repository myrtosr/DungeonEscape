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

void Player::update()
{
	if (!moving)
		return;
}

void Player::draw()
{
    if (pos.x < 0 || pos.y < 0)
        return;

    float cx, cy;
    gamestate.getDungeonMap().getTileMap().tileToCanvas(pos.x, pos.y, cx, cy);

    graphics::Brush br;
    br.fill_color[0] = 1.0f;
    br.fill_color[1] = 0.2f;
    br.fill_color[2] = 0.2f;
    br.outline_opacity = 0.0f;

    graphics::drawDisk(cx, cy, TILE_SIZE * 0.35f, br);
}

void Player::init()
{
	currentRoomId = 0;
	moving = false;
	float speed = 6.0f; // idk what this should be... we'll see in due time
	path.clear();
}



