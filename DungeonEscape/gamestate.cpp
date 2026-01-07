#include "sgg/graphics.h"
#include "gamestate.h"
#include "config.h"

void GameState::init() {
	// Button Initialization
	// Start Screen Buttons
	startButtons.push_back({
		CANVAS_WIDTH / 2 ,         
		CANVAS_HEIGHT / 2 + 180,
		170,                      
		60,                      
		"start.png"
		});

	startButtons.push_back({
		CANVAS_WIDTH / 2,
		CANVAS_HEIGHT / 2 + 270,
		170,
		60,
		"exit.png"
		});

	// I want to add an "about button" but how do I make a pop-up on a currnet game state? And do I have to make another button to close it? :(
	// Dungeon initialization
	mygraph.initializeGraphStructure();
}

void GameState::updateStartScreen()
{
	for (auto& b : startButtons) {
		b.updateHover(cx, cy);

		if (b.isClicked(mouse.button_left_pressed)) {
			if (b.getTexture() == "start.png") {
				status = STATUS_PLAYING;
			}
			else if (b.getTexture() == "exit.png") {
				status = STATUS_END;
			}
		}
	}
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
	br.texture = std::string(ASSET_PATH) + "background2.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	
	br.texture = "";
	char info[40];
	sprintf_s(info, "Dungeon Escape");
	graphics::drawText(CANVAS_WIDTH/2 - 280, CANVAS_HEIGHT/2 + 50 , 80, info, br);

	// Drawing the buttons
	for (auto& b : startButtons) {
		b.draw(); 
	}

}

void GameState::drawLevelScreen()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	// division by 255.0f -> convert regular RGB values (0–255) to range for SGG (0.0–1) 
	br.fill_color[0] = 26 / 255.0f;   // R
	br.fill_color[1] = 3 / 255.0f;  // G
	br.fill_color[2] = 46 / 255.0f;  // B
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
}

void GameState::drawEndScreen()
{
}

void GameState::updateMouseCanvasCoords()
{
	cx = window2canvasX(mouse.cur_pos_x);
	cy = window2canvasY(mouse.cur_pos_y);

	inside_canvas =
		cx >= 0 && cx <= CANVAS_WIDTH &&
		cy >= 0 && cy <= CANVAS_HEIGHT;
}

void GameState::update()
{
	graphics::getMouseState(mouse);
	updateMouseCanvasCoords();

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

	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.texture = std::string(ASSET_PATH) + "cursor.png";
	if (inside_canvas)
		graphics::drawRect(cx, cy, 50, 50, br);
}

float GameState::window2canvasX(float x)
{
	float scale = std::min(
		window_width / (float)CANVAS_WIDTH,
		window_height / (float)CANVAS_HEIGHT
	);

	float offset_x = (window_width - CANVAS_WIDTH * scale) / 2.0f;

	return (x - offset_x) / scale;
}

float GameState::window2canvasY(float y)
{
	float scale = std::min(
		window_width / (float)CANVAS_WIDTH,
		window_height / (float)CANVAS_HEIGHT
	);

	float offset_y = (window_height - CANVAS_HEIGHT * scale) / 2.0f;

	return (y - offset_y) / scale;
}

void GameState::onWindowResized(unsigned int w, unsigned int h)
{
	setWindowDimensions(w, h);
	updateMouseCanvasCoords();
}

bool GameState::canvas2tile(int px, int py, int& tx, int& ty) {
	tx = px / TILE_SIZE;
	ty = py / TILE_SIZE;

	return tx >= 0 && tx < TILES_X &&
		ty >= 0 && ty < TILES_Y;
}

GameState::GameState()
{
}

GameState::~GameState()
{
}
