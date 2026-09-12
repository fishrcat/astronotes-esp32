#pragma once

class Adafruit_GFX;

namespace Menu {

void begin(Adafruit_GFX &display);
void tick();

void pressUp();
void pressDown();
void pressOk();
void goHome();

}  // namespace Menu
