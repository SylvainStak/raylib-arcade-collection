#include "utils.h"

void FitWindowToMonitor(int width, int height) {
    int mon = GetCurrentMonitor();
    Vector2 new_loc = GetMonitorPosition(mon);
    new_loc.x += (GetMonitorWidth(mon)/2) - (width/2);
    new_loc.y += (GetMonitorHeight(mon)/2) - (height/2);
    SetWindowSize(width, height);
    SetWindowPosition((int) new_loc.x, (int) new_loc.y);
}

float SyncedSineWave(float min, float max, float frequency) {
    float amplitude = (max - min) / 2.f;
    float v_shift = (max + min) / 2.f;
    float wave_dt = sin(2 * PI * frequency * GetTime());
    return (amplitude * wave_dt) + v_shift;
}
