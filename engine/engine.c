#include "include/engine.h"

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

/*
 * Mode is either 0 for hollow or 1 for filled in
 */
void drawRect(screen *scrn, int x, int y, int height, int width, int mode) {
    if (mode == 0) {
        height = height - 1;
        width = width - 1;

        drawLine(scrn, x, y, x + width, y);                       /* top */
        drawLine(scrn, x, y + height, x + width, y + height);   /* bottom */
        drawLine(scrn, x, y, x, y + height);                    /* left */
        drawLine(scrn, x + width, y, x + width, y + height);    /* right */
    }

    if (mode == 1) {    
        int relY, relX;

        for (relY = y; relY < y + height; relY++) {
            for (relX = x; relX < x + width; relX++) {
                scrn->buf[relY][relX] = '#';
            }
        }
    }
}

/* 
 * drawn using Bresenham's method 
 * https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 */
void drawLine(screen *scrn, int x1, int y1, int x2, int y2) {
    int dx, stepx, dy, stepy, error;
    dx = abs(x2 - x1);
    if (x1 < x2)
        stepx = 1;
    else
        stepx = -1;
    dy = -abs(y2 - y1);
    if (y1 < y2)
        stepy = 1;
    else
        stepy = -1;
    error = dx + dy;

    while ((x1 != x2 + stepx) && (y1 != y2 + stepy)) {
        scrn->buf[y1][x1] = '#';
        if (error * 2 >= dy) {
            x1 += stepx;
            error += dy;
        }
        if (error * 2 <= dx) {
            y1 += stepy;
            error += dx;
        }
    }
}