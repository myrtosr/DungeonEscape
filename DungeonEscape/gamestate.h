#pragma once

class GameState {
	// update functions for different states of the game
	void updateStartScreen();
	void updateLevelScreen();
	void updateEndScreen();
	// draw functions for different states of the game
	void drawStartScreen();
	void drawLevelScreen();
	void drawEndScreen();
public:
	void update();
	void draw();
	void init();
	// Constructor & Destructor 
	GameState();
	~GameState();
};