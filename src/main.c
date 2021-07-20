#include <tice.h>
#include <stdlib.h>
#include <graphx.h>
#include "include/drawing.h"
#include "include/connect.h"

char **board;

/* Main function, called first */
int main(void)
{
    board = c_newboard();
    /* Clear the homescreen */
    os_ClrHome();

    gfx_Begin();
    gfx_SetDrawBuffer();

    drawBoard(board, LCD_WIDTH / 2, LCD_HEIGHT / 2);

    /* Waits for a key */
    while (!os_GetCSC());

    /* Return 0 for success */
    return 0;
}

void loop() {

}

int getDigitInput() {
    
}

void render() {
    drawBoard(board, LCD_WIDTH / 2, LCD_HEIGHT / 2);

    gfx_BlitBuffer();
}