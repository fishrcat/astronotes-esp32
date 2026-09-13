#pragma once

class Adafruit_GFX;

namespace PageDraw {

struct Cell {
  int x, y, w;
};

struct Origin {
  int x, y;
};

void setTextStyle(Adafruit_GFX &screen);
void text(Adafruit_GFX &screen, int x, int y, int w, const char *str, bool visible = true);
Cell pad(int x, int y, int w);
Origin origin();

}  // namespace PageDraw
