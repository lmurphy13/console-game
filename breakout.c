#include "engine/include/engine.h"
#include <unistd.h>

#define B_ROWS  3
#define B_COLS  13

typedef struct {
    int x;
    int y;
    int length;
    int height;
} paddle;

typedef struct {
    int x;
    int y;
    int length;
    int height;
    int state;          /* 1 = alive, 0 = dead (broken) */
} brick;

typedef struct {
    int x;
    int y;
    int dx;
    int dy;
    int size;
} ball;

void initPaddle(paddle *);
void drawPaddle(screen *, paddle *);

void initBrick(brick *, int x, int y);
void drawBrick(screen *, brick *);

void initBall(ball *, int x, int y);
void drawBall(screen *, ball *);
void updateBall(screen *, ball *, paddle *, brick *);

void resetLevel(ball *);
void gameOver(screen *);
void youWin(screen *);

brick bricks[B_ROWS][B_COLS];

int score = 0;
int lives = 3;

int main() {
    // Initialize game screen
    screen scrn;
    allocScreen(&scrn, 40, 180);    /* 40 rows, 180 columns */
    initScreen(&scrn);

    // Initialize paddle
    paddle p;
    initPaddle(&p);

    // Initialize bricks
    int rows, cols;
    for (rows = 0; rows < B_ROWS; rows++) {
        for (cols = 0; cols < B_COLS; cols++) {
            brick b;
            initBrick(&b, (cols * 14) + 1, (rows * 5) + 2);
            bricks[rows][cols] = b;
            
        }
    }

    // Initialize ball
    ball b;
    initBall(&b, 60, 20);

    // Game loop
    while (1) {

        initScreen(&scrn);

        switch (checkKeys()) {
            case -1:    p.x -= 10; break;
            case 1:     p.x += 10; break;
            case 0:     p.x += 0;  break;
        }

        for (rows = 0; rows < B_ROWS; rows++) {
            for (cols = 0; cols < B_COLS; cols++) {
                brick bk = bricks[rows][cols];

                updateBall(&scrn, &b, &p, &bk);
                bricks[rows][cols] = bk;
                drawBrick(&scrn, &bk);
            }
        }

        drawBall(&scrn, &b);
        drawPaddle(&scrn, &p);

        char *scoreTxt = (char *)malloc(11 * sizeof(char));
        char *livesTxt = (char *)malloc(10 * sizeof(char));

        sprintf(scoreTxt, "SCORE: %d", score);
        sprintf(livesTxt, "LIVES: %d", lives);     

        drawText(&scrn, 1, 0, scoreTxt);
        drawText(&scrn, 171, 0, livesTxt);
        printScreen(&scrn);

        b.x += b.dx;
        b.y += b.dy;

        if (lives <= 0) {
            b.dx = 0;
            b.dy = 0;

            gameOver(&scrn);
            break;
        }

        if (score >= (B_ROWS * B_COLS)) {
            b.dx = 0;
            b.dy = 0;

            youWin(&scrn);
            break;
        }

    }

    freeScreen(&scrn);
}

void initPaddle(paddle *p) {
    p->x = 82;
    p->y = 35;
    p->length = 20;
    p->height = 2;
}

void drawPaddle(screen *scrn, paddle *p) {
    drawRect(scrn, p->x, p->y, p->height, p->length, 1);
}

void initBrick(brick *b, int x, int y) {
    b->x = x;
    b->y = y;
    b->height = 3;
    b->length = 10;
    b->state = 1;
}

void drawBrick(screen *scrn, brick *b) {
    if (b->state == 1)
        drawRect(scrn, b->x, b->y, b->height, b->length, 1);
}

void initBall(ball *b, int x, int y) {
    b->x = x;
    b->y = y;
    b->dx = 1;
    b->dy = 1;
    b->size = 2;
}

void drawBall(screen *scrn, ball *b) {
    drawRect(scrn, b->x, b->y, b->size, b->size + 1, 1);
}

void updateBall(screen *scrn, ball *b, paddle *p, brick *bk) {
    // detect screen edge collisions
    if (b->x + b->size + 2 >= scrn->SCREEN_W || b->x <= 0) {
        b->dx = -b->dx;
        putchar(7);
    }
    if (b->y <= 0) {
        b->dy = -b->dy;
        putchar(7);
    }

    // ball hits the floor, so we subtract a life and reset level
    if (b->y + b->size >= scrn->SCREEN_H) {
        lives -= 1;
        putchar(7);
        resetLevel(b);
    }

    // paddle collisions
    if (b->y + b->size >= p->y
        && b->x >= p->x
        && b->x + b->size <= p->x + p->length) {
        b->dy = -b->dy;
        putchar(7);
    }

    // brick collisions
    
    if ((b->x >= bk->x
        && b->x + b->size+1 <= bk->x + bk->length
        && b->y <= bk->y + bk->height
        && b->y + b->size >= bk->y) && (bk->state == 1)) {

        bk->state = 0;
        score++;
        b->dx = -b->dx;
        putchar(7);
    }
}

void resetLevel(ball *b) {
    // reset bricks
    int rows, cols;
    for (rows = 0; rows < B_ROWS; rows++) {
        for (cols = 0; cols < B_COLS; cols++) {
            brick bk = bricks[rows][cols];
            bk.state = 1;
            bricks[rows][cols] = bk;
        }
    }

    // reset ball
    initBall(b, 60, 20);
}

void gameOver(screen *scrn) {
    drawText(scrn, (scrn->SCREEN_W / 2) - 5, 20, "GAME OVER");
    printScreen(scrn);
}

void youWin(screen *scrn) {
    drawText(scrn, (scrn->SCREEN_W / 2) - 5, 20, "YOU WIN!");
    printScreen(scrn);
}
