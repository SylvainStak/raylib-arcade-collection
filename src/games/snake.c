#include "../shared.h"
#include "../pause_menu.h"

typedef struct GameManagerSnake {
    int scr_w;
    int scr_h;
    bool running;
    char text1[64];
    Vector2 text1_pos;
    Color text1_clr;
    int text_fontsize;
    PauseMenu pause_menu;
} GameManagerSnake;

static GameManagerSnake gm = { 0 };

void LoadSnake() {
    strcpy(gm.text1, "SNAKE\0");

    gm.scr_w = 1024;
    gm.scr_h = 768;
    gm.text_fontsize = 50;
    gm.text1_pos = (Vector2) { (gm.scr_w/2) - (MeasureText(gm.text1, gm.text_fontsize)/2), 200 };
    gm.text1_clr = GREEN;
    gm.running = true;
    gm.pause_menu = CreatePauseMenu(gm.scr_w);
    FitWindowToMonitor(gm.scr_w, gm.scr_h);
}

void UpdateSnake() {
    if (gm.pause_menu.active) {
        UpdatePauseMenu(&gm.pause_menu);
        if (gm.pause_menu.quit) {
            gm.running = false;
        }
        return;
    }

    if (IsKeyPressed(KEY_ESCAPE)) gm.pause_menu.active = true;
}

void DrawSnake() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText(gm.text1, gm.text1_pos.x, gm.text1_pos.y, gm.text_fontsize, gm.text1_clr);

    if (gm.pause_menu.active) DrawPauseMenu(&gm.pause_menu);
    EndDrawing();
}

void UnloadSnake() {
    UnloadPauseMenu(&gm.pause_menu);
    gm = (GameManagerSnake){ 0 };
}

bool IsFinishedSnake() { return !gm.running; }
