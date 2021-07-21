struct screen {
    void (*init)();
    void (*draw)();
    void (*update)(unsigned long);
};

void drawBoard(char **board, int x, int y, float scale);

void menu_init();
void menu_draw();
void menu_update(unsigned long);

void game_init();
void game_draw();
void game_update(unsigned long);