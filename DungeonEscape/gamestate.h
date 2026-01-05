#pragma once
#include "config.h"
#include "sgg/graphics.h"
#include "dungeongraph.h"

class GameState {
	// game states -----------
	typedef enum { STATUS_START, STATUS_PLAYING, STATUS_END } status_t;
	status_t status = STATUS_START;
	//------------------------
	// update functions for different states of the game
	void updateStartScreen();
	void updateLevelScreen();
	void updateEndScreen();
	// draw functions for different states of the game
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

	// DungeonGraph initialization
	DungeonGraph mygraph;

	// Constructor & Destructor 
	GameState();
	~GameState();
};