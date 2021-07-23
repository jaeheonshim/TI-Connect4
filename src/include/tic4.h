struct screen {
    void (*init)();
    void (*draw)();
    void (*update)(unsigned long);
};

enum gamemode {PVP, PVAI, AIVAI};
int getDigitInput();
void setGameMode(char g);
char getGameMode();
void setScreen(struct screen *p);

extern struct screen screen_intro;
extern struct screen screen_menu;
extern struct screen screen_game;

extern char game_winner;