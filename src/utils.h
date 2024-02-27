#ifndef UTILS_H_
#define UTILS_H_

#include <raylib.h>
#include <math.h>

typedef enum {
    GAMEPAD_AXIS_LEFT_UP,
    GAMEPAD_AXIS_LEFT_DOWN,
    GAMEPAD_AXIS_LEFT_LEFT,
    GAMEPAD_AXIS_LEFT_RIGHT
} JoystickDirection;

void FitWindowToMonitor(int width, int height);
float SineWave(float min, float max, float freq, float dt);
float SyncedSineWave(float min, float max, float frequency);
bool IsGamepadLeftJoystickHolded(int gamepad, JoystickDirection dir);

#endif
