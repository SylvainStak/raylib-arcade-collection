#include "../shared.h"
#include "../pause_menu.h"

#define RAYGUI_IMPLEMENTATION
#include "../raygui.h"

static int scr_w;
static int scr_h;
static bool running;
static PauseMenu pause_menu;
static Vector2 pos;
static float radius;
static float speed;
static short dirX;
static short dirY;

void LoadSnake() {
    scr_w = 1024;
    scr_h = 768;
    running = true;
    pause_menu = CreatePauseMenu(scr_w);
    pos = (Vector2) { GetScreenWidth() / 2, GetScreenHeight() / 2 };
    radius = 15.f;
    speed = 100.f;
    dirX = 1;
    dirY = 1;
    FitWindowToMonitor(scr_w, scr_h);
}

void UpdateSnake() {
    if (pause_menu.active) {
        UpdatePauseMenu(&pause_menu);
        if (pause_menu.quit) {
            running = false;
        }
        return;
    }

    pos.x += speed * dirX * GetFrameTime();
    pos.y += speed * dirY * GetFrameTime();

    if (pos.x + radius > GetScreenWidth() || pos.x - radius < 0) dirX = -dirX;
    if (pos.y + radius > GetScreenHeight() || pos.y - radius < 0) dirY = -dirY;

    if (IsKeyPressed(KEY_ESCAPE) || IsGamepadButtonPressed(GAMEPAD_ID, GAMEPAD_BUTTON_MIDDLE_RIGHT)) pause_menu.active = true;
}

void DrawSnake() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawCircle(pos.x, pos.y, radius, GREEN);

    if (pause_menu.active) DrawPauseMenu(&pause_menu);

    GuiSliderBar((Rectangle) {100, 500, 300, 20}, "10", "100", &radius, 10.f, 100.f);
    EndDrawing();
}

void UnloadSnake() {
    UnloadPauseMenu(&pause_menu);
}

bool IsFinishedSnake() { return !running; }
