#include "engine.h"

int main() {
    screen scr;
    scr.SCREEN_H = 40;
    scr.SCREEN_W = 180;
    allocScreen(&scr);

    if (initScreen(&scr))
        printScreen(&scr);

    drawLine(&scr, 0,0,100,35);

    while(1) {
        initScreen(&scr);
        printScreen(&scr);
    }
}