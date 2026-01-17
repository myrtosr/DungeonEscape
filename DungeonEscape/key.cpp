#include "key.h"
#include "gamestate.h"
#include "sgg\graphics.h"

void Key::update()
{

}

void Key::draw()
{
	float cx, cy;
	gamestate.getDungeonMap().getTileMap().tileToCanvas(pos.x, pos.y, cx, cy);

	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.fill_color[0] = 0.3f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 0.0f;

	graphics::drawDisk(cx, cy, TILE_SIZE * 0.4, br);
}

void Key::init()
{

}
