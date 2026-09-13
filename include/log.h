#pragma once

class Adafruit_GFX;

namespace Log {

void begin();
void tick();
void toggleTimer();
void draw(Adafruit_GFX &screen, bool force = false);
void onEnter(Adafruit_GFX &screen);

}  // namespace Log
