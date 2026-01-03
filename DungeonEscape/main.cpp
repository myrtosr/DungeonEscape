#include "sgg/graphics.h"
#include "gamestate.h"
#include "config.h"

void update(float ms) {
    GameState* game = reinterpret_cast<GameState*>(graphics::getUserData());
    game->update();
}

// Window drawing function
void draw() {
    GameState* game = reinterpret_cast<GameState*>(graphics::getUserData());
    game->update();
}

int main() {
    GameState mygame;

    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dungeon Escape");

    graphics::setUserData(&mygame);

    // Callback functions
    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    mygame.init();
    graphics::startMessageLoop();

    return 0;
}