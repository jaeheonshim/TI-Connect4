#include <tice.h>
#include <stdlib.h>
#include <graphx.h>
#include <keypadc.h>
#include "include/drawing.h"
#include "include/connect.h"
#include "include/connectai.h"

#define MENU 0
#define GAME 1

static unsigned long lastTick;

void render();
int getDigitInput();
void loop(unsigned long delta);

static struct screen screen_menu = {
    menu_init,
    menu_draw,
    menu_update
};

static struct screen screen_game = {
    game_init,
    game_draw,
    game_update
};

static struct screen *currentScreen = &screen_menu;

/* Main function, called first */
int main(void)
{
    unsigned long delta;

    srandom(rtc_Time());
    timer_Enable(1, TIMER_32K, TIMER_NOINT, TIMER_UP);
    os_ClrHome();

    gfx_Begin();
    gfx_SetDrawBuffer();

    screen_menu.init();
    screen_game.init();
    
    lastTick = timer_Get(1);

    do {
        kb_Scan();
    } while(kb_Data[6] & kb_Enter);

    while (os_GetCSC() != sk_Clear) {
        delta = (timer_Get(1) - lastTick) / 32;
        lastTick = timer_Get(1);
        loop(delta);
    }

    gfx_End();

    return 0;
}

void loop(unsigned long delta) {
    kb_Scan();

    if(kb_Data[6] & kb_Enter && currentScreen == &screen_menu) {
        currentScreen = &screen_game;
    }

    currentScreen->update(delta);

    render();
}

void render() {
    gfx_FillScreen(255);
    gfx_SetColor(0);

    currentScreen->draw();

    gfx_SetTextFGColor(74);
    gfx_SetTextScale(1, 1);
    gfx_PrintStringXY("Exit: [CLEAR]", 234, 2);

    gfx_BlitBuffer();
}