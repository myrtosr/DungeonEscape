#pragma once

// class Collidable {}

class GameObject {
protected:
	const class GameState& gamestate;
public:
	GameObject(const class GameState& mygame);
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
};
