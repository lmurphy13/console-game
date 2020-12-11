#include "include/engine.h"

int main() {
    screen scr;
    allocScreen(&scr, 45, 180);

    initScreen(&scr);

    drawLine(&scr, 0,20, 180,20);
    drawLine(&scr, 10,5,150,35);
    drawLine(&scr, 10, 40, 150, 10);

    drawLine(&scr, scr.SCREEN_W / 2, 0, scr.SCREEN_W / 2, scr.SCREEN_H);
    
    drawRect(&scr, 0, 25, 5, 20, 0);
    drawRect(&scr, 25, 25, 5, 20, 1);

    drawPixel(&scr, 120, 5);
    
    int score = 4;

    char *scoreText = (char *)malloc(10 * sizeof(char));
    sprintf(scoreText, "Player: %d", score);

    drawText(&scr, 90, 2, scoreText);

    score++;
    sprintf(scoreText, "Player: %d", score);


    drawText(&scr, 90, 3, scoreText);

    printScreen(&scr);

    // while(1) {
    //     initScreen(&scr);
    //     printScreen(&scr);
    // }

    freeScreen(&scr);
}