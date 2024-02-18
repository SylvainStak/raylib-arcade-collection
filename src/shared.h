#ifndef SHARED_H_
#define SHARED_H_

#include <raylib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "utils.h"

#define GAMEPAD_DEADZONE .05f
#define GAMEPAD_ID 0

#define LENGTH(x) (sizeof(x) / sizeof((x)[0]))

typedef enum { 
    SPACE_INVADERS,
    ARKANOID,
    SNAKE,

    GAMES_COUNT,
} GameID;

#endif
