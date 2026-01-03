#include "sgg/graphics.h"
#include "gamestate.h"
#include "config.h"

void GameState::updateStartScreen()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	if (ms.button_left_pressed)
		status = STATUS_PLAYING;
}

void GameState::updateLevelScreen()
{
}

void GameState::updateEndScreen()
{
}

void GameState::drawStartScreen()
{
	graphics::setFont(std::string(ASSET_PATH) + "title_font.ttf");

	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "background.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	br.texture = "";
	char info[40];
	sprintf_s(info, "Enter the Dungeon");
	graphics::drawText(CANVAS_WIDTH * 0.405, CANVAS_HEIGHT * 0.50, 30, info, br);

	graphics::MouseState ms;
	graphics::getMouseState(ms);
	br.texture = std::string(ASSET_PATH) + "cursor.png";
	graphics::drawRect(window2canvasX(ms.cur_pos_x), window2canvasY(ms.cur_pos_y), 50, 50, br);
}

void GameState::drawLevelScreen()
{
}

void GameState::drawEndScreen()
{
}

void GameState::update()
{
	if (status == STATUS_START) {
		updateStartScreen();
	}
	else if (status == STATUS_PLAYING) {
		updateLevelScreen();
	}
	else if (status == STATUS_END) {
		updateEndScreen();
	}
}

void GameState::draw()
{
	if (status == STATUS_START) {
		drawStartScreen();
	}
	else if (status == STATUS_PLAYING) {
		drawLevelScreen();
	}
	else if (status == STATUS_END) {
		drawEndScreen();
	}
}

void GameState::init()
{
}

float GameState::window2canvasX(float x)
{
	return x * CANVAS_WIDTH / (float)window_width;
}

float GameState::window2canvasY(float y)
{
	return y * CANVAS_HEIGHT / (float)window_height;
}

GameState::GameState()
{
}

GameState::~GameState()
{
}
