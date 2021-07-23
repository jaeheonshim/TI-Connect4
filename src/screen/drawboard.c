#include <tice.h>
#include <graphx.h>
#include "include/connect.h"

#define C_BLUE 26
#define C_RED 224
#define C_YELLOW 231
#define C_WHITE 255

#define C_LRED 244
#define C_LYELLOW 247

#define BOARD_WIDTH (255 * scale)
#define BOARD_HEIGHT (216 * scale)

#define SPACING (7 * scale)
#define RADIUS (14 * scale)

void drawBoard(char **board, int x, int y, float scale, char highlight) {
    int leftX = (x - (BOARD_WIDTH / 2)), topY = (y - BOARD_HEIGHT / 2);
    gfx_SetColor(C_BLUE);
    gfx_FillRectangle_NoClip(leftX, topY, BOARD_WIDTH, BOARD_HEIGHT);

    for(int row = 0; row < C_HEIGHT; row++) {
        for(int col = 0; col < C_WIDTH; col++) {
            if(col == highlight && row == c_lastplace(board, highlight)) {
                gfx_SetColor(31);
                gfx_FillCircle_NoClip(
                    leftX + (col * RADIUS * 2) + ((col + 1) * SPACING + RADIUS),
                    topY + (row * RADIUS * 2) + ((row + 1) * SPACING) + RADIUS, RADIUS + 2
                );
            }

            if(board[row][col] == EMPTY) gfx_SetColor(C_WHITE);
            if(board[row][col] == YELLOW) gfx_SetColor(C_YELLOW);
            if(board[row][col] == RED) gfx_SetColor(C_RED);
                
            gfx_FillCircle(
                leftX + (col * RADIUS * 2) + ((col + 1) * SPACING + RADIUS),
                topY + (row * RADIUS * 2) + ((row + 1) * SPACING) + RADIUS, RADIUS);
        }
    }
}

void drawPlacer(int x, int y, int pos, int color, float scale) {
    int leftX = (x - (BOARD_WIDTH / 2)), topY = (y - BOARD_HEIGHT / 2);

    if(color == RED) {
        gfx_SetColor(C_LRED);
    } else {
        gfx_SetColor(C_LYELLOW);
    }

    gfx_FillCircle(
        leftX + (pos * RADIUS * 2) + ((pos + 1) * SPACING + RADIUS),
        topY + SPACING + RADIUS, RADIUS);
}