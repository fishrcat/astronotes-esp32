#pragma once

class Adafruit_GFX;

namespace Menu {

void begin(Adafruit_GFX &display);

void pressUp();
void pressDown();
void pressOk();
void goHome();

}  // namespace Menu
