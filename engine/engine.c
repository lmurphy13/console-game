#include "include/engine.h"

void printScreen(screen *scrn) {
    int rows, cols;
    
    gotoxy(0,0);
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

    //gotoxy(0,0);
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

void allocScreen(screen *scrn, int height, int width) {
    scrn->SCREEN_H = height;
    scrn->SCREEN_W = width;

    scrn->buf = malloc(scrn->SCREEN_H * sizeof(char *));
    
    int i;
    for (i = 0; i <= scrn->SCREEN_H; i++)
        scrn->buf[i] = malloc(scrn->SCREEN_W * sizeof(char));
}

void freeScreen(screen *scrn) {
    free(scrn->buf);
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
                //scrn->buf[relY][relX] = '#';
                drawPixel(scrn, relX, relY);
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
        //scrn->buf[y1][x1] = '#';
        drawPixel(scrn, x1, y1);
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

void drawPixel(screen *scrn, int x, int y) {
    scrn->buf[y][x] = '#';
}

void drawText(screen *scrn, int x, int y, char *text) {    
    int i = 0;
    char c;

    while ( (c = text[i]) != '\0') {
        scrn->buf[y][x + i] = c;
        i++;
    }
}

int checkKeys() {
    WINDOW *win = initscr();        /* puts streams into full buffered mode */
    cbreak();                       /* cbreak mode */
    nodelay(win, TRUE);
    int retval = 0;          

    timeout(100);
    char c = getch();

    if (c == 'a') {

        retval = -1;
    }
    if (c == 'd') {

        retval = 1;
    }

    endwin();                   
    setvbuf(stdout, NULL, _IOLBF, 0);   /* restores stdout to non-buffered mode */
    setvbuf(stderr, NULL, _IONBF, 0);   /* restores stderr to non-buffered mode */

    return retval;
}