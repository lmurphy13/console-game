#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
#define SCREEN_W	180
#define SCREEN_H	40

char screen[SCREEN_H][SCREEN_W];

void printScreen(void);
int initScreen(void);
void drawRect(int, int, int, int);

typedef struct {
	int x;
	int y;
	int dx;
	int dy;
	int size;
}ball;

void updateBall(ball *);

int main() {
	setbuf(stdout, NULL);

	if (initScreen())
		printScreen();

	/*
	drawRect(5, 5, 10, 3);
	drawRect(30, 5, 10, 3);
	drawRect(55, 5, 10, 3);
	*/
	
	ball myBall;
	myBall.x = 10;
	myBall.y = 10;
	myBall.dx = 3;
	myBall.dy = 3;
	myBall.size = 3;

	ball *pBall = &myBall;

	// game loop
	
	while (1) {
		updateBall(pBall);
		printScreen();
		initScreen();
	}
	return 0;
}

/* 
 * ' ' is blank
 * '#' is active
 * blank on init
 * return 1 if SUCCESS
 * return 0 if FAILURE
 */
int initScreen() {
	int rows, cols;
	for (rows = 0; rows < SCREEN_H; rows++) {
		for (cols = 0; cols < SCREEN_W; cols++) {
			screen[rows][cols] = ' ';
		}
	}

	return 1;
}

void printScreen() {
	int rows, cols;
	printf("  \t");
	for (cols = 0; cols < SCREEN_W; cols++) {
		printf("%d", cols % 10);
	}
	printf("\n");
	for (rows = 0; rows < SCREEN_H; rows++) {
		printf("%d.\t", rows);
		for (cols = 0; cols < SCREEN_W; cols++) {
			printf("%c", screen[rows][cols]);
		}
		printf("\n");
	}
	printf("\n");
	gotoxy(0,0);
}

// Draw a rectangle from the upper LH corner
void drawRect(int x, int y, int w, int h) {
	int relY, relX;

	for (relY = y; relY < y + h; relY++) {
		for (relX = x; relX < x + w; relX++) {
			screen[relY][relX] = '#';
		}
	}
}

void updateBall(ball *pball) {
	pball->x += pball->dx;
	pball->y += pball->dy;

	if (pball->x > SCREEN_W || pball->x < 0 + pball->size)
		pball->dx = -pball->dx;
	if (pball->y + pball->size > SCREEN_H || pball->y < 1)
		pball->dy = -pball->dy;

	drawRect(pball->x, pball->y, pball->size+2, pball->size);

}
