#include "sgg/graphics.h"
#include "gamestate.h"
#include "config.h"

void GameState::updateStartScreen()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	// Avoiding phantom clicks -> black padding = innactive space 
	float cx = window2canvasX(ms.cur_pos_x);
	float cy = window2canvasY(ms.cur_pos_y);
	bool inside_canvas =
		cx >= 0 && cx <= CANVAS_WIDTH &&
		cy >= 0 && cy <= CANVAS_HEIGHT;

	
	if (ms.button_left_pressed && inside_canvas)
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

// check implementation
float GameState::window2canvasX(float x)
{
	float scale = std::min(
		window_width / (float)CANVAS_WIDTH,
		window_height / (float)CANVAS_HEIGHT
	);

	float offset_x = (window_width - CANVAS_WIDTH * scale) / 2.0f;

	return (x - offset_x) / scale;
}
// check implementation
float GameState::window2canvasY(float y)
{
	float scale = std::min(
		window_width / (float)CANVAS_WIDTH,
		window_height / (float)CANVAS_HEIGHT
	);

	float offset_y = (window_height - CANVAS_HEIGHT * scale) / 2.0f;

	return (y - offset_y) / scale;
}

GameState::GameState()
{
}

GameState::~GameState()
{
}
