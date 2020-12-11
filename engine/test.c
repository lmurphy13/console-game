#include "include/engine.h"

int main() {
    screen scr;
    scr.SCREEN_H = 40;
    scr.SCREEN_W = 180;
    allocScreen(&scr);

    if (initScreen(&scr))
        printScreen(&scr);

    drawLine(&scr, 0,20, 180,20);
    drawLine(&scr, 10,5,150,35);
    drawLine(&scr, 10, 39, 150, 10);
    
    drawRect(&scr, 0, 25, 5, 20, 0);
    drawRect(&scr, 25, 25, 5, 20, 1);
    
    
    printScreen(&scr);

    // while(1) {
    //     initScreen(&scr);
    //     printScreen(&scr);
    // }
}