#include "page_draw.h"

#include <Adafruit_GFX.h>

#include "config.h"

namespace PageDraw {

void setTextStyle(Adafruit_GFX &screen) {
  screen.setTextSize(Config::kMenuTextSize);
  screen.setTextColor(Config::kForegroundColor, Config::kBackgroundColor);
}

void text(Adafruit_GFX &screen, int x, int y, int w, const char *str, bool visible) {
  screen.fillRect(x, y, w, Config::kPageLineHeight, Config::kBackgroundColor);
  if (!visible)
    return;
  screen.setCursor(x, y);
  screen.print(str);
}

Cell pad(int x, int y, int w) {
  return Cell{x + Config::kPagePadding, y + Config::kPagePadding, w - 2 * Config::kPagePadding};
}

Origin origin() { return Origin{Config::kPageMargin, Config::kPageTopMargin}; }

}  // namespace PageDraw
