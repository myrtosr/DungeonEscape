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

	// Key shadow
	br.outline_opacity = 0.0f;
	br.fill_opacity = 0.3;
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	br.texture = std::string(ASSET_PATH) + png;
	graphics::drawRect(cx, cy, TILE_SIZE, TILE_SIZE, br);

	// Key
	br.fill_color[0] = 1.0f; // reset
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	br.fill_opacity = 1.0f;
	br.texture = std::string(ASSET_PATH) + png;
	graphics::drawRect(cx, cy - 10, TILE_SIZE *1.1, TILE_SIZE *1.1, br);
}

void Key::init()
{

}
