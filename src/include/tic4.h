struct screen {
    void (*init)();
    void (*draw)();
    void (*update)(unsigned long);
};

enum gamemode {PVP, PVAI, AIVAI};
int getDigitInput();
void setGameMode(char g);
void setHumanPlayer(char c);
char getGameMode();
void setScreen(struct screen *p);

extern struct screen screen_intro;
extern struct screen screen_menu;
extern struct screen screen_game;
extern struct screen screen_cai;

extern char game_winner;