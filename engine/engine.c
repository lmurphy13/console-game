#include "engine.h"

void printScreen(screen *scrn) {
    int rows, cols;

    printf("\n");
    for (cols = 0; cols < scrn->SCREEN_W + 1; cols++) {
        printf("-");
    }
    printf("\n");

    for (rows = 0; rows < scrn->SCREEN_H; rows++) {
        printf("|");
        for (cols = 0; cols < scrn->SCREEN_W; cols++) {
            printf("%c", scrn->buf[rows][cols]);
        }
        printf("|\n");
    }

    for (cols = 0; cols < scrn->SCREEN_W + 1; cols++) {
        printf("-");
    }
    printf("\n");
    gotoxy(0,0);
}

int initScreen(screen *scrn) {
    int rows, cols;
    for (rows = 0; rows < scrn->SCREEN_H; rows++) {
        for (cols = 0; cols < scrn->SCREEN_W; cols++) {
            scrn->buf[rows][cols] = ' ';
        }
    }

    return 1;
}

void allocScreen(screen *scrn) {
    scrn->buf = malloc(scrn->SCREEN_H * sizeof(char *));
    
    int i;
    for (i = 0; i < scrn->SCREEN_H; i++)
        scrn->buf[i] = malloc(scrn->SCREEN_W * sizeof(char));
}

void drawRect(screen *scrn, int x, int y, int height, int width) {
    int relY, relX;

    for (relY = y; relY < y + height; relY++) {
        for (relX = x; relX < x + width; relX++) {
            scrn->buf[relY][relX] = '#';
        }
    }
}

void drawLine(screen *scrn, int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int D = (2 * dy) - dx;
    int y = y1;
    int x;

    for (x = x1; x <= x2; x++) {
        scrn->buf[x][y] = '#';
        if (D > 0) {
            y++;
            D = D - (2 * dx);
        }
        D = D + (2 * dy);
    }
}