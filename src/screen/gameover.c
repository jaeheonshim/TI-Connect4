#include <tice.h>
#include <graphx.h>
#include "include/connect.h"
#include "include/tic4.h"
#include <string.h>

#define WINNER_TEXT(winner) ((winner) == RED ? "RED" : (winner) == YELLOW ? "YELLOW" : "TIE")

#define WIDTH 220
#define HEIGHT 80

static char *winnerText;
static int wTextW;

void game_over_init() {
    winnerText = malloc(sizeof(char) * (strlen("Winner: ") + strlen(WINNER_TEXT(game_winner)) + 1));
    strcpy(winnerText, "Winner: ");
    strcat(winnerText, WINNER_TEXT(game_winner));

    gfx_SetTextScale(2, 2);
    wTextW = gfx_GetStringWidth(winnerText);
}

void draw_game_over() {
    gfx_SetColor(183);
    gfx_FillRectangle_NoClip((LCD_WIDTH / 2) - (WIDTH / 2), (LCD_HEIGHT / 2) - (HEIGHT / 2), WIDTH, HEIGHT);
    gfx_SetTextScale(2, 2);
    gfx_PrintStringXY("Game Over!", (LCD_WIDTH / 2) - (WIDTH / 2) + 40, (LCD_HEIGHT / 2) - (HEIGHT / 2) + 5);

    gfx_PrintStringXY(winnerText, (LCD_WIDTH / 2) - (wTextW / 2), (LCD_HEIGHT / 2) - (HEIGHT / 2) + 26);
    gfx_SetTextScale(1, 1);
    gfx_PrintStringXY("[Enter]: Play Again", (LCD_WIDTH / 2) - (WIDTH / 2) + 10, (LCD_HEIGHT / 2) - (HEIGHT / 2) + 48);
    gfx_PrintStringXY("[Clear]: Exit Game", (LCD_WIDTH / 2) - (WIDTH / 2) + 10, (LCD_HEIGHT / 2) - (HEIGHT / 2) + 58);
}