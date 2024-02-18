#ifndef START_MENU_H_
#define START_MENU_H_

#include "shared.h"

typedef struct StartMenuItem {
    char text[32];
    int fontsize;
    Vector2 pos;
    Color clr;
} StartMenuItem;

typedef struct StartMenu {
    int scr_w;
    int scr_h;
    bool menu_active;
    bool game_active;
    int item_selected;
    Sound item_sound;
    char hint_text[128];
    int hint_text_fontsize;
    Color hint_text_clr;
    Vector2 hint_text_pos;
    StartMenuItem items[GAMES_COUNT];
} StartMenu;

void LoadStartMenu(StartMenu *menu);
void UpdateStartMenu(StartMenu *menu);
void DrawStartMenu(StartMenu *menu);
void UnloadStartMenu(StartMenu *menu);

#endif
