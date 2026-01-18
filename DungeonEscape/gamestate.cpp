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
	//------------------------
	
	// End Screen Buttons
	endButtons.push_back({
		CANVAS_WIDTH / 2,
		CANVAS_HEIGHT / 2 + 168,
		170,
		60,
		"exit.png"
		});

	// Dungeon Initialization
	mygraph.initializeGraphStructure();

	// Grid and Views Initialization
	my_map.buildViews();
	my_map.init();
	initializeKeys();

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

	if (!levelInitialized) {
		graphics::playMusic(std::string(ASSET_PATH) + "main.mp3", 0.2f, 5.0f );
		levelInitialized = true;
	}

	TileMap& tilemap = my_map.getTileMap();
	tilemap.clearHover();

	int row, col;
	if (inside_canvas) {
		tilemap.canvasToTile(cx, cy, row, col);
		tilemap.setHoveredTile(row, col); // for visual feedback
		if (mouse.button_left_released) {

			if (handleKeyClick(row, col)) {
				return;
			}

			Tile& t = tilemap.at(row, col);
			if (t.isClickable()) {
				tilemap.setClickedTile(row, col);  // for visual feedback
				// Door tile is clicked
				if (t.getType() == TileType::DOOR_T || t.getType() == TileType::DOOR_L || t.getType() == TileType::DOOR_R) {
					handleDoorClick(row, col);
					return;
				}
				// Floor tile is clicked
				if (t.getType() == TileType::FLOOR) {
					handleFloorClick(row, col);
					return;
				}

			}	
		}

	}
	my_map.update(); // DungeonMap updates the tile types

	player->update();

	// Game Victory
	if ((player->getPos().x == 13) && (player->getPos().y == 32)) { // If player reaches exit tile {13, 32} -> Game ends
		status = STATUS_END;
		graphics::stopMusic();
	}
}

void GameState::updateEndScreen()
{

	if (!endInitialized) {
		graphics::playMusic(std::string(ASSET_PATH) + "victory.mp3", 0.6f, false);
		my_map.clear();
		mygraph.clear();
		std::cout << "[DEBUG] Deleting player" << std::endl;
		delete player;
		endInitialized = true;
	}

	for (auto& b : endButtons) {
		b.updateHover(cx, cy);

		if (b.isClicked(mouse.button_left_released)) {
			if (b.getTexture() == "exit.png") {
				graphics::stopMusic();
				status = STATUS_QUIT;
			}
		}
	}

}

void GameState::updateQuitScreen()
{
	if (!quitting) {
		quitting = true;
		quitStartTime = graphics::getGlobalTime(); // start counting for a goodbye message output
	}

	float elapsed = graphics::getGlobalTime() - quitStartTime;

	if (elapsed >= 2100.0f) { // show goodbye message for ~2 seconds
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

	for (auto& k : keys) {
		k->draw();
	}

	player->draw();

	if (debug) {
		TileMap& tilemap = my_map.getTileMap();
		tilemap.drawGridDebug();
	}


}

void GameState::drawEndScreen()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;

	br.texture = std::string(ASSET_PATH) + "background.png";
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	// Icon
	br.fill_color[0] = 1.0f; // reset
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	br.texture = std::string(ASSET_PATH) + "win.png";
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, 240, 240, br);

	// Buttons
	for (auto& b : endButtons) {
		b.draw();
	}

	// Successful Escape Message
	graphics::setFont(std::string(ASSET_PATH) + "simple_font.ttf");
	br.texture = "";
	float t = graphics::getGlobalTime() / 1000;	
	
	float floatOffset = sin(t * 2.0f) * 10.0f;

	char floatingText[100];
	sprintf_s(floatingText, "Escape Success!");

	graphics::drawText(
		CANVAS_WIDTH / 2 - 200,       
		CANVAS_HEIGHT / 2 - 150 + floatOffset,
		60,                        
		floatingText,
		br);
}

void GameState::drawQuitScreen()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;

	// Background
	br.fill_color[0] = 69 / 255.0f;   // R
	br.fill_color[1] = 72 / 255.0f;  // G
	br.fill_color[2] = 147 / 255.0f;  // B
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


bool GameState::handleKeyClick(int r, int c)
{
	Key* key = getKeyAt(r, c);
	if (!key) return false; // key doesn't exist in this click -> key click not handled

	RoomNode* room = my_map.getRoomAt(r, c);
	if (!room || !room->isAvailable()) {
		std::cout << "[DEBUG] Cannot handle key click in unavailable room" << std::endl;
		return false; // key exists in unavailable room -> key click not handled
	}

	std::cout << "[DEBUG] Handling key click at: " << r << "," << c << std::endl;

	player->addKey(key->getId()); // update player inventory
	removeKey(key); 
	return true;
}


void GameState::handleDoorClick(int r, int c)
{
	std::cout << "[DEBUG] Handling door click at: " << r << "," << c << std::endl;
	Door* door = my_map.getDoorAt(r, c);
	if (door) {
		if (door->isUnlocked()) {
			return; // door already unlocked -> nothing happens
		}

		if (player->hasKey(door->getId())) {
			door->unlock(mygraph); 
			std::vector<RoomView*>& rooms = my_map.getRoomViews();

			for (RoomView* rv : rooms) {
				if (rv->getRoomNode()->getId() == door->getId()) {
					rv->addEntrance({ r, c });
					break;
				}
			}
		}
		else {
			std::cout << "[DEBUG] Required key not found!" << std::endl;
		}
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

Key* GameState::getKeyAt(int r, int c)
{
	for (Key* k : keys) {
		if (k->getRow() == r && k->getCol() == c)
			return k;
	}
	return nullptr;
}

void GameState::removeKey(Key* key)
{
	auto it = std::find(keys.begin(), keys.end(), key);

	if (it != keys.end()) {
		delete* it; // Delete the key object
		keys.erase(it); // Free the corresponding space in keys vector
	}
}

void GameState::initializeKeys()
{
	keys.push_back(new Key(*this, 3, {9, 24}, "key3.png"));
	keys.push_back(new Key(*this, 4, {8, 2}, "key4.png"));
	keys.push_back(new Key(*this, 5, {17, 11}, "key5.png"));
	keys.push_back(new Key(*this, 7, {16, 2}, "key7.png"));
	keys.push_back(new Key(*this, 6, {14, 25}, "key6.png"));
	keys.push_back(new Key(*this, 2, {6, 24}, "key2.png"));
	keys.push_back(new Key(*this, 8, {2, 17}, "key8.png"));
}

GameState::~GameState()
{
}
