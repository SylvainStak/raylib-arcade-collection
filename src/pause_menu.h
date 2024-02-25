#ifndef PAUSE_MENU_H_
#define PAUSE_MENU_H

#include "shared.h"

typedef struct PauseMenu {
    bool active;
    bool quit;
    Vector2 t_pos;
    Vector2 c_pos;
    Vector2 q_pos;
    int t_fontsize;
    int opt_fontsize;
    int selected;
    Sound opt_sound;
    bool opened;
    Sound open_sound;
    Vector2 arrow;
    int arrow_size;
} PauseMenu;

PauseMenu CreatePauseMenu(int scrW);
void UpdatePauseMenu(PauseMenu *menu);
void DrawPauseMenu(PauseMenu *menu);
void UnloadPauseMenu(PauseMenu *menu);

#endif
