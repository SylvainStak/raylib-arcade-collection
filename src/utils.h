#ifndef UTILS_H_
#define UTILS_H_

#include <raylib.h>
#include <math.h>

void FitWindowToMonitor(int width, int height);
float SineWave(float min, float max, float freq, float dt);
float SyncedSineWave(float min, float max, float frequency);

#endif
