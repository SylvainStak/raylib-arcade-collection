#include "utils.h"

void FitWindowToMonitor(int width, int height) {
    int mon = GetCurrentMonitor();
    Vector2 new_loc = GetMonitorPosition(mon);
    new_loc.x += (GetMonitorWidth(mon)/2) - (width/2);
    new_loc.y += (GetMonitorHeight(mon)/2) - (height/2);
    SetWindowSize(width, height);
    SetWindowPosition((int) new_loc.x, (int) new_loc.y);
}

float SineWave(float min, float max, float freq, float dt) {
    float amplitude = (max - min) / 2.f;
    float v_shift = (max + min) / 2.f;
    float wave_dt = sin(2 * PI * freq * dt);
    return amplitude * wave_dt + v_shift;
}

float SyncedSineWave(float min, float max, float freq) {
    return SineWave(min, max, freq, GetTime());
}

bool IsGamepadLeftJoystickHolded(int gamepad, JoystickDirection dir) {
    static bool prev_status[4] = { false };
    float axis_value;

    switch (dir) {
        case GAMEPAD_AXIS_LEFT_UP:    axis_value = -GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y); break;
        case GAMEPAD_AXIS_LEFT_RIGHT: axis_value =  GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X); break;
        case GAMEPAD_AXIS_LEFT_DOWN:  axis_value =  GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y); break;
        case GAMEPAD_AXIS_LEFT_LEFT:  axis_value = -GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X); break;
        default: return false;
    }

    if (axis_value > 0.5) {
        return (!prev_status[dir]) ? (prev_status[dir] = true) : false;
    } else return (prev_status[dir] = false);
}
