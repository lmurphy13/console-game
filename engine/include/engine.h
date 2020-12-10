#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define clear() printf("\033[H\033[J")                  /* clears terminal buffer */
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))     /* moves cursor in terminal buffer */

typedef struct {
    int SCREEN_W;       /* screen width */
    int SCREEN_H;       /* screen height */
    char **buf;         /* pointer to 2D char array that is dynamically allocated */
} screen;

void printScreen(screen *);
int initScreen(screen *);
void allocScreen(screen *);

void drawRect(screen *, int,int,int,int);     /* x, y, height, width */
void drawLine(screen *, int,int,int,int);     /* x1, y1, x2, y2 */
