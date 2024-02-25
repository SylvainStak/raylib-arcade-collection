#include <raylib.h>
#include "pause_menu.h"

#define TITLE_FONTSIZE 40
#define TITLE_COLOR 0x828282

#define OPT_FONTSIZE 50
#define OPT_COLOR 0xFFFFFF

#define TITLE_Y 100
#define CONTINUE_Y 300
#define QUIT_Y 400

#define BG_COLOR 0x000000
#define BG_COLOR_FADE .9f

#define ARROW_GAP 20

enum { CONTINUE, QUIT };

static const char *t_text = "GAME PAUSED";
static const char *c_text = "CONTINUE";
static const char *q_text = "QUIT";
static const char *a_text = ">";

PauseMenu CreatePauseMenu(int scrW) {
    return (PauseMenu) {
        .t_fontsize = TITLE_FONTSIZE,
        .opt_fontsize = OPT_FONTSIZE,
        .t_pos = (Vector2) {(scrW / 2) - (MeasureText(t_text, TITLE_FONTSIZE) / 2), TITLE_Y},
        .c_pos = (Vector2) {(scrW / 2) - (MeasureText(c_text, OPT_FONTSIZE) / 2), CONTINUE_Y},
        .q_pos = (Vector2) {(scrW / 2) - (MeasureText(q_text, OPT_FONTSIZE) / 2), QUIT_Y},
        .selected = 0,
        .opt_sound = LoadSound("assets/pause_menu_opt.wav"),
        .active = false,
        .quit = false,
        .arrow = (Vector2) {0, -100},
        .arrow_size = MeasureText(a_text, OPT_FONTSIZE),
    };
}

void UpdatePauseMenu(PauseMenu *menu) {
    if (IsKeyPressed(KEY_DOWN)) {
        if (++menu->selected == 2) menu->selected = CONTINUE;
        PlaySound(menu->opt_sound);

    } else if(IsKeyPressed(KEY_UP)) {
        if (--menu->selected == -1) menu->selected = QUIT;
        PlaySound(menu->opt_sound);

    } else if (IsKeyPressed(KEY_ENTER)) {
        if (menu->selected == QUIT) menu->quit = true;
        menu->active = false;

    } else if (IsKeyPressed(KEY_ESCAPE)) {
        menu->active = false;
        menu->selected = CONTINUE;
    }

    Vector2 ref_pos = menu->selected == CONTINUE ? menu->c_pos : menu->q_pos;
    menu->arrow = (Vector2) { ref_pos.x - menu->arrow_size - ARROW_GAP, ref_pos.y };
}

void DrawPauseMenu(PauseMenu *menu) {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(GetColor(BG_COLOR), BG_COLOR_FADE));
    DrawText(t_text, menu->t_pos.x, menu->t_pos.y, menu->t_fontsize, GetColor(TITLE_COLOR));
    DrawText(c_text, menu->c_pos.x, menu->c_pos.y, menu->opt_fontsize, GetColor(OPT_COLOR));
    DrawText(q_text, menu->q_pos.x, menu->q_pos.y, menu->opt_fontsize, GetColor(OPT_COLOR));
    DrawText(a_text, menu->arrow.x, menu->arrow.y, menu->opt_fontsize, GetColor(OPT_COLOR));
}

void UnloadPauseMenu(PauseMenu *menu) {
    UnloadSound(menu->opt_sound);
}
