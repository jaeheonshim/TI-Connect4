struct screen {
    void (*init)();
    void (*draw)();
    void (*update)(unsigned long);
};

void drawBoard(char **board, int x, int y, float scale);

void intro_init();
void intro_draw();
void intro_update(unsigned long);

void menu_init();
void menu_draw();
void menu_update(unsigned long delta);

void game_init();
void game_draw();
void game_update(unsigned long);