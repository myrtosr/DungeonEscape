#include "config.h"
#include "button.h"

void Button::updateHover(float cx, float cy)
{
	hovered = (cx >= x - w / 2) && (cx <= x + w / 2) &&
		(cy >= y - h / 2) && (cy <= y + h / 2);
}

bool Button::isClicked(bool mousePressed)
{
	return hovered && mousePressed;
}

void Button::draw()
{
	graphics::Brush br;        
	br.outline_opacity = 0.0f; 
	br.texture = std::string(ASSET_PATH) + texture;
	
	graphics::drawRect(x, y, w, h, br);

    if (hovered) {
        br.texture = "";            
        br.fill_opacity = 0.0f;
        br.outline_width = 1.5f;
        br.outline_opacity = 1.0f;
        br.outline_color[0] = 254 / 255.0f; 
        br.outline_color[1] = 221 / 255.0f;
        br.outline_color[2] = 14 / 255.0f;

        graphics::drawRect(x, y, w, h, br);
    }
}
