#pragma once
#include "sgg\graphics.h"
#include <string>

struct Button {
	// Constructor
	Button(float x, float y, float w, float h, const std::string& texture)
		: x(x), y(y), w(w), h(h), texture(texture) {
	}
	// Getters
	float getX() const { return x; }
	float getY() const { return y; }
	float getWidth() const { return w; }
	float getHeight() const { return h; }
	const std::string& getTexture() const { return texture; }
	bool isHovered() const { return hovered; }
	//------------------------
	void updateHover(float cx, float cy);
	bool isClicked(bool mousePressed);
	void draw();
private:
	float x, y;
	float w, h;
	std::string texture;
	bool hovered = false;
};