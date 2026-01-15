#include "sgg/graphics.h"
#include "gamestate.h"
#include "tilemap.h"
#include "config.h"
#include <iostream>

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
		"quit.png"
		});

	// I want to add an "about button" but how do I make a pop-up on a current game state? And do I have to make another button to close it? :(
	// Dungeon Initialization
	mygraph.initializeGraphStructure();

	// Grid and Views Initialization
	my_map.buildViews();
	my_map.initializeTiles();

	// Player Initialization
	player = new Player(*this);
	player->init();
	player->spawnAt({ 7, 3 }, 1);
}

void GameState::updateStartScreen()
{
	for (auto& b : startButtons) {
		b.updateHover(cx, cy);

		if (b.isClicked(mouse.button_left_released)) {
			if (b.getTexture() == "start.png") {
				status = STATUS_PLAYING;
			}
			else if (b.getTexture() == "quit.png") {
				status = STATUS_QUIT;
			}
		}
	}
}

void GameState::updateLevelScreen()
{
	TileMap& tilemap = my_map.getTileMap();
	tilemap.clearHover();

	int row, col;
	if (inside_canvas) {
		tilemap.canvasToTile(cx, cy, row, col);
		tilemap.setHoveredTile(row, col); // for visual feedback

		if (mouse.button_left_released) {
			Tile& t = tilemap.at(row, col);
			if (t.isClickable()) {
				tilemap.setClickedTile(row, col);  // for visual feedback
				// Door tile is clicked
				if (t.getType() == TileType::DOOR_LOCKED) {
					handleDoorClick(row, col);
					return;
				}
				// Floor tile is clicked
				if (t.getType() == TileType::FLOOR || t.getType() == TileType::DOOR_OPEN) {
					handleFloorClick(row, col);
					return;
				}

			}	
		}

	}
	my_map.update(); // DungeonMap updates the tile types

	player->update();
}

void GameState::updateEndScreen()
{
}

void GameState::updateQuitScreen()
{
	if (!quitting) {
		quitting = true;
		quitStartTime = graphics::getGlobalTime(); // start counting for a goodbye message output
	}

	float elapsed = graphics::getGlobalTime() - quitStartTime;

	if (elapsed >= 2200.0f) { // show goodbye message for ~2 seconds
	graphics::destroyWindow(); // close the SGG window
	exit(0);                   // ensure program terminates
	}
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
	// Division by 255.0f -> convert regular RGB values (0–255) to range for SGG (0.0–1) 
	br.fill_color[0] = 26 / 255.0f;   // R
	br.fill_color[1] = 3 / 255.0f;  // G
	br.fill_color[2] = 46 / 255.0f;  // B
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	
	my_map.draw();

	player->draw();

	if (debug) {
		TileMap& tilemap = my_map.getTileMap();
		tilemap.drawGridDebug();
	}


}

void GameState::drawEndScreen()
{
}

void GameState::drawQuitScreen()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;

	// Background
	br.fill_color[0] = 75 / 255.0f;   // R
	br.fill_color[1] = 59 / 255.0f;  // G
	br.fill_color[2] = 131 / 255.0f;  // B
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	// Goodbye text
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	graphics::setFont(std::string(ASSET_PATH) + "simple_font.ttf");

	char info[100];
	sprintf_s(info, "Bye bye! Exiting the game...");
	graphics::drawText(CANVAS_WIDTH / 2 - 300, CANVAS_HEIGHT / 2, 50, info, br);
}

void GameState::updateMouseCanvasCoords()
{
	cx = window2canvasX(mouse.cur_pos_x);
	cy = window2canvasY(mouse.cur_pos_y);

	inside_canvas =
		cx >= 0 && cx <= CANVAS_WIDTH &&
		cy >= 0 && cy <= CANVAS_HEIGHT;
}

void GameState::handleDoorClick(int r, int c)
{
	Door* door = my_map.getDoorAt(r, c);
	if (door) {
		if (door->isUnlocked()) {
			return; // door already unlocked -> nothing happens
		}
		/* else if (player has the key in inventory)
			door->unlock(); 
		}
		else {
			show message "Door is locked! You need a key..."
		}*/
	}
}

void GameState::handleFloorClick(int r, int c)
{
	if (player->isMoving()) return;
	std::cout << "[DEBUG] Handling floor click at: " << r << "," << c << std::endl;
	RoomNode* room = my_map.getRoomAt(r, c);
	std::cout << "[DEBUG] Room ID: " << room->getId() << " available:" << (room->isAvailable() ? "true" : "false") << std::endl;
	if (room && room->isAvailable()) {
		// trigger pathfinding to tile {r, c}
		std::vector<TileCoord> path = my_map.findFullPath(player->getPos(), { r, c });
		std::cout << "[DEBUG] Path length: " << path.size() << std::endl;
		player->setPath(path);
		player->setMoving(!path.empty());
	}
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
	else if (status == STATUS_QUIT) {
		updateQuitScreen();	
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
	else if (status == STATUS_QUIT) {
		drawQuitScreen();
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

GameState::~GameState()
{
}
