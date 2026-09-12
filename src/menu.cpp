#include "menu.h"

#include <GEM_adafruit_gfx.h>

namespace Menu {
namespace {

GEM_adafruit_gfx *menu = nullptr;

GEMPage mainMenuPage("Astronotes");
GEMPage logPage("Log");
GEMPage tunerPage("Tuner");
GEMPage analyzePage("Analyze");

GEMItem logItem("Log", logPage);
GEMItem tunerItem("Tuner", tunerPage);
GEMItem analyzeItem("Analyze", analyzePage);

}  // namespace

void begin(Adafruit_GFX &display) {
  static GEM_adafruit_gfx instance(display, GEM_POINTER_ROW, GEM_ITEMS_COUNT_AUTO, 20, 20);
  menu = &instance;
  menu->setTextSize(2);

  mainMenuPage.addMenuItem(logItem);
  mainMenuPage.addMenuItem(tunerItem);
  mainMenuPage.addMenuItem(analyzeItem);

  menu->init();
  menu->setMenuPageCurrent(mainMenuPage);
  menu->drawMenu();
}

void pressUp() {
  if (menu->readyForKey())
    menu->registerKeyPress(GEM_KEY_UP);
}

void pressDown() {
  if (menu->readyForKey())
    menu->registerKeyPress(GEM_KEY_DOWN);
}

void pressOk() {
  if (menu->readyForKey())
    menu->registerKeyPress(GEM_KEY_OK);
}

void goHome() {
  menu->setMenuPageCurrent(mainMenuPage);
  menu->drawMenu();
}

}  // namespace Menu
