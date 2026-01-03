#include "sgg/graphics.h"

void update(float ms) {

}

void draw() {

}

int main() {
    // lets hope this works
    graphics::createWindow(1920, 1000, "Tutorial");


    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(1920, 1000);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);


    graphics::startMessageLoop();

    int a = 0;

    return 0;
}