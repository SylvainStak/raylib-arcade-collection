#include "shared.h"
#include "start_menu.h"
#include "game_selector.h"

int main() {
    InitWindow(1, 1, "Arcade Collection");
    InitAudioDevice();
    SetTargetFPS(60);
    SetExitKey(KEY_Q);

    void (*LoadGame)(void) = NULL;
    void (*UpdateGame)(void) = NULL;
    void (*DrawGame)(void) = NULL;
    void (*UnloadGame)(void) = NULL;
    bool (*IsFinishedGame)(void) = NULL;

    StartMenu sm = { 0 };
    LoadStartMenu(&sm);

    while (!WindowShouldClose()) {
        if (sm.menu_active) {
            UpdateStartMenu(&sm);
            DrawStartMenu(&sm);
        } else {
            if (!sm.game_active) {
                LoadGame = LoadGameSelector(sm.item_selected);
                UpdateGame = UpdateGameSelector(sm.item_selected);
                DrawGame = DrawGameSelector(sm.item_selected);
                UnloadGame = UnloadGameSelector(sm.item_selected);
                IsFinishedGame = IsFinishedGameSelector(sm.item_selected);

                sm.game_active = true;
                LoadGame();
            } else {
                UpdateGame();
                DrawGame();
                if (IsFinishedGame()) {
                    UnloadGame();
                    sm.game_active = false;
                    sm.menu_active = true;
                    FitWindowToMonitor(sm.scr_w, sm.scr_h);
                }
            }
        }
    }

    if (sm.game_active) UnloadGame();
    UnloadStartMenu(&sm);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
