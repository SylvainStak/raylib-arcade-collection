#include "shared.h"
#include "games/games.h"


void (*LoadGameSelector(int game_id))(void) {
    switch(game_id) {
        case SPACE_INVADERS: return LoadSpaceInvaders;
        case ARKANOID: return LoadArkanoid;
        case SNAKE: return LoadSnake;
        default: return NULL;
    }
}

void (*UpdateGameSelector(int game_id))(void) {
    switch(game_id) {
        case SPACE_INVADERS: return UpdateSpaceInvaders;
        case ARKANOID: return UpdateArkanoid;
        case SNAKE: return UpdateSnake;
        default: return NULL;
    }
}

void (*DrawGameSelector(int game_id))(void) {
    switch(game_id) {
        case SPACE_INVADERS: return DrawSpaceInvaders;
        case ARKANOID: return DrawArkanoid;
        case SNAKE: return DrawSnake;
        default: return NULL;
    }
}

void (*UnloadGameSelector(int game_id))(void) {
    switch(game_id) {
        case SPACE_INVADERS: return UnloadSpaceInvaders;
        case ARKANOID: return UnloadArkanoid;
        case SNAKE: return UnloadSnake;
        default: return NULL;
    }
}

bool (*IsFinishedGameSelector(int game_id))(void) {
    switch(game_id) {
        case SPACE_INVADERS: return IsFinishedSpaceInvaders;
        case ARKANOID: return IsFinishedArkanoid;
        case SNAKE: return IsFinishedSnake;
        default: return NULL;
    }
}
