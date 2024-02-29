#include "start_menu.h"

void LoadStartMenu(StartMenu *menu) {
    char *hint_text = "[UP / DOWN] to select game.  [ENTER] to start playing.  [Q] to Quit.\0";
    strcpy(menu->hint_text, hint_text);

    menu->scr_w = 1024;
    menu->scr_h = 768;
    menu->menu_active = true;
    menu->game_active = false;
    menu->item_selected = 0;
    menu->item_sound = LoadSound("assets/start_menu_opt.wav");
    menu->hint_text_fontsize = 20;
    menu->hint_text_clr = GRAY;
    menu->hint_text_pos = (Vector2) { 
        .x = (menu->scr_w/2) - (MeasureText(hint_text, menu->hint_text_fontsize)/2),
        .y = 10.f,
    };
    menu->xbox_gpad_texture = LoadTexture("assets/gamepad_xbox.png");
    menu->playstation_gpad_texture = LoadTexture("assets/gamepad_ps.png");
    menu->current_gpad_texture = &menu->xbox_gpad_texture;
    menu->gpad_detected = false;

    int posY = -20;
    char *sm_item_list[] = {
        "Space Invaders\0",
        "Arkanoid\0",
        "Snake\0",
    };

    assert(LENGTH(sm_item_list) == GAMES_COUNT);

    for (int i = 0; i < GAMES_COUNT; i++) {
        strcpy(menu->items[i].text, sm_item_list[i]);
        menu->items[i].pos = (Vector2) { 0, (posY += 100) };
        menu->items[i].fontsize = 40;
        menu->items[i].clr = GREEN;
    }

    FitWindowToMonitor(menu->scr_w, menu->scr_h);
}

void UpdateStartMenu(StartMenu *menu) {
    if (IsKeyPressed(KEY_DOWN) || IsGamepadButtonPressed(GAMEPAD_ID, GAMEPAD_BUTTON_LEFT_FACE_DOWN) || IsGamepadLeftJoystickHolded(GAMEPAD_ID, GAMEPAD_AXIS_LEFT_DOWN)) {
        if (++menu->item_selected == GAMES_COUNT) menu->item_selected = 0;
        PlaySound(menu->item_sound);

    } else if(IsKeyPressed(KEY_UP) || IsGamepadButtonPressed(GAMEPAD_ID, GAMEPAD_BUTTON_LEFT_FACE_UP) || IsGamepadLeftJoystickHolded(GAMEPAD_ID, GAMEPAD_AXIS_LEFT_UP) ) {
        if (--menu->item_selected == -1) menu->item_selected = GAMES_COUNT-1;
        PlaySound(menu->item_sound);

    } else if (IsKeyPressed(KEY_ENTER) || IsGamepadButtonPressed(GAMEPAD_ID, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
        menu->menu_active = false;
    }

    for (int i = 0; i < GAMES_COUNT; i++) {
        if (i == menu->item_selected) {
            menu->items[i].clr = SKYBLUE;
            menu->items[i].fontsize = (int) SyncedSineWave(40.f, 60.f, 1.f);
        } else {
            menu->items[i].clr = GREEN;
            menu->items[i].fontsize = 40;
        }
        menu->items[i].pos.x = (menu->scr_w/2) - (MeasureText(menu->items[i].text, menu->items[i].fontsize)/2);
    }

    menu->gpad_detected = IsGamepadAvailable(GAMEPAD_ID);
    menu->current_gpad_texture = TextFindIndex(TextToLower(GetGamepadName(GAMEPAD_ID)), "xbox") >= 0 ? &menu->xbox_gpad_texture : &menu->playstation_gpad_texture;
}

void DrawStartMenu(StartMenu *menu) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText(menu->hint_text, menu->hint_text_pos.x, menu->hint_text_pos.y, menu->hint_text_fontsize, menu->hint_text_clr);
    for (int i = 0; i < GAMES_COUNT; i++) {
        DrawText(menu->items[i].text, menu->items[i].pos.x, menu->items[i].pos.y, menu->items[i].fontsize, menu->items[i].clr);
    }

    if (menu->gpad_detected) {
        DrawTextureEx(*menu->current_gpad_texture, (Vector2) { 0, 720 }, 0, .1f, WHITE);
        DrawText("Gamepad detected", 75, 732, 20, WHITE);
    }

    EndDrawing();
}

void UnloadStartMenu(StartMenu *menu) {
    UnloadSound(menu->item_sound);
    UnloadTexture(menu->xbox_gpad_texture);
    UnloadTexture(menu->playstation_gpad_texture);
}
