#include "../shared.h"

typedef struct GameManagerSnake {
    int scr_w;
    int scr_h;
    bool running;
    char text1[64];
    char text2[64];
    Vector2 text1_pos;
    Vector2 text2_pos;
    Color text1_clr;
    Color text2_clr;
    int text_fontsize;
} GameManagerSnake;

static GameManagerSnake gm = { 0 };

void LoadSnake() {
    strcpy(gm.text1, "SNAKE\0");
    strcpy(gm.text2, "(PRESS [ESC] TO GO BACK)\0");

    gm.scr_w = 1024;
    gm.scr_h = 768;
    gm.text_fontsize = 50;
    gm.text1_pos = (Vector2) { (gm.scr_w/2) - (MeasureText(gm.text1, gm.text_fontsize)/2), 200 };
    gm.text2_pos = (Vector2) { ( gm.scr_w/2) - (MeasureText(gm.text2, gm.text_fontsize)/2), 300 };
    gm.text1_clr = GREEN;
    gm.text2_clr = GREEN;
    gm.running = true;
    FitWindowToMonitor(gm.scr_w, gm.scr_h);
}

void UpdateSnake() {
    if (IsKeyPressed(KEY_ESCAPE)) gm.running = false;
    gm.text2_clr.a = (int) SyncedSineWave(0.f, 255.f, .5f);
}

void DrawSnake() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText(gm.text1, gm.text1_pos.x, gm.text1_pos.y, gm.text_fontsize, gm.text1_clr);
    DrawText(gm.text2, gm.text2_pos.x, gm.text2_pos.y, gm.text_fontsize, gm.text2_clr);
    EndDrawing();
}

void UnloadSnake() {
    gm.running = false;
}

bool IsFinishedSnake() {
    return !gm.running;
}
