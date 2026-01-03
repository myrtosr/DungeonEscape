#include "sgg/graphics.h"

void update(float ms) {

}

void draw() {

}

int main() {
    // lets hope this works
    graphics::createWindow(1366, 768, "Tutorial");


    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(1366, 768);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);


    graphics::startMessageLoop();

    int a = 0;

    return 0;
}