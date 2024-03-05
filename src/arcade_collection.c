#include "shared.h"
#include "start_menu.h"
#include "game_selector.h"

int main() {
    InitWindow(1, 1, "Arcade Collection");
    InitAudioDevice();
    SetTargetFPS(60);
    SetExitKey(KEY_Q);

    void (*LoadGame)(void);
    void (*UpdateGame)(void);
    void (*DrawGame)(void);
    void (*UnloadGame)(void);
    bool (*IsFinishedGame)(void);

    StartMenu sm;
    LoadStartMenu(&sm);

    while (!WindowShouldClose()) {
        // StartMenu logic
        if (sm.menu_active) {
            UpdateStartMenu(&sm);
            DrawStartMenu(&sm);
            continue;
        }

        // Bind functions and load selected game
        if (!sm.game_active) {
            GameSelector(sm.item_selected, &LoadGame, &UpdateGame, &DrawGame, &UnloadGame, &IsFinishedGame);
            sm.game_active = true;
            LoadGame();
        }

        // Shared game loop logic
        UpdateGame();
        DrawGame();
        if (IsFinishedGame()) {
            UnloadGame();
            sm.game_active = false;
            sm.menu_active = true;
            FitWindowToMonitor(sm.scr_w, sm.scr_h);
        }
    }

    if (sm.game_active) UnloadGame();
    UnloadStartMenu(&sm);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
