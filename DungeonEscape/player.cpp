#include "player.h"

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
}

void Player::draw()
{
}

void Player::init()
{
	currentRoomId = 0;
	moving = false;
	float speed = 6.0f; // idk what this should be... we'll see in due time
	path.clear();
}



