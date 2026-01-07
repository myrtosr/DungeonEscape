#pragma once
#include "config.h"
#include <vector>
#include "sgg/graphics.h"
#include "button.h"
#include "dungeongraph.h"

class GameState {
	// Game states -----------
	typedef enum { STATUS_START, STATUS_PLAYING, STATUS_END } status_t;
	status_t status = STATUS_START;
	//------------------------
	// Update functions for different states of the game
	void updateStartScreen();
	void updateLevelScreen();
	void updateEndScreen();
	// Draw functions for different states of the game
	void drawStartScreen();
	void drawLevelScreen();
	void drawEndScreen();
	//------------------------
	// Mouse handling
	graphics::MouseState mouse; // keep this in check in the future - its uninitialized idk if that could cause problems, probs not
	float cx = 0.0f;
	float cy = 0.0f;
	bool inside_canvas = false;
	void updateMouseCanvasCoords();
	//------------------------
	unsigned int window_width = WINDOW_WIDTH;
	unsigned int window_height = WINDOW_HEIGHT;
	// DungeonGraph initialization
	DungeonGraph mygraph;
	// Button Initialization
	std::vector<Button> startButtons; // All buttons for the start menu
	// we can add more buttons for other states of the game if we want :)
	bool debug = false;
public:
	void update();
	void draw();
	void init();
	// Mouse handling
	unsigned int getWindowWidth() { return window_width; };
	unsigned int getWindowHeight() { return window_height; };
	float window2canvasX(float x);
	float window2canvasY(float y);
	void setWindowDimensions(unsigned int w, unsigned int h) { window_width = w; window_height = h; }
	void onWindowResized(unsigned int w, unsigned int h);
	bool canvas2tile(int px, int py, int& tx, int& ty);
	void setDebugMode(bool d) { debug = d; }
	bool getDebugMode() const { return debug; }

	// Constructor & Destructor 
	GameState();
	~GameState();
};