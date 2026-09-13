#include "menu.h"

#include <GEM_adafruit_gfx.h>

#include "config.h"
#include "log.h"

namespace Menu {
namespace {

GEM_adafruit_gfx *menu = nullptr;
Adafruit_GFX *screen = nullptr;

GEMPage mainMenuPage("Astronotes");
GEMPage logPage("Log");
GEMPage tunerPage("Tune");
GEMPage analyzePage("Analyze");
GEMPage jamPage("Jam");
GEMPage settingsPage("Settings");


GEMItem logItem("Log", logPage);
GEMItem tunerItem("Tune", tunerPage);
GEMItem analyzeItem("Analyze", analyzePage);
GEMItem jamItem("Jam", jamPage);
GEMItem settingsItem("Settings", settingsPage);

void drawOverlay() {
  if (menu->getCurrentMenuPage() == &logPage)
    Log::draw(*screen);
}

struct PageEnter {
  GEMPage *page;
  void (*onEnter)(Adafruit_GFX &);
};

PageEnter pageEnters[] = {
    {&logPage, Log::onEnter},
};

void enterPage(GEMPage *page) {
  for (auto &pe : pageEnters) {
    if (pe.page == page) {
      pe.onEnter(*screen);
      return;
    }
  }
}

}  // namespace

void begin(Adafruit_GFX &display) {
  static GEM_adafruit_gfx instance(display, GEM_POINTER_ROW, GEM_ITEMS_COUNT_AUTO,
                                    Config::kMenuRowHeight, Config::kMenuRowHeight);
  menu = &instance;
  screen = &display;
  menu->setTextSize(Config::kMenuTextSize);
  menu->setForegroundColor(Config::kForegroundColor);
  menu->setBackgroundColor(Config::kBackgroundColor);
  menu->setDrawMenuCallback(drawOverlay);

  mainMenuPage.addMenuItem(logItem);
  mainMenuPage.addMenuItem(tunerItem);
  mainMenuPage.addMenuItem(analyzeItem);
  mainMenuPage.addMenuItem(jamItem);
  mainMenuPage.addMenuItem(settingsItem);

  menu->init();
  menu->setMenuPageCurrent(mainMenuPage);
  menu->drawMenu();
}

void tick() {
  drawOverlay();
}

void pressUp() {
  if (menu->getCurrentMenuPage() == &logPage) {
    Log::toggleTimer();
    return;
  }
  if (menu->readyForKey())
    menu->registerKeyPress(GEM_KEY_UP);
}

void pressDown() {
  if (menu->readyForKey())
    menu->registerKeyPress(GEM_KEY_DOWN);
}

void pressOk() {
  if (!menu->readyForKey())
    return;
  GEMPage *before = menu->getCurrentMenuPage();
  menu->registerKeyPress(GEM_KEY_OK);
  GEMPage *after = menu->getCurrentMenuPage();
  if (after != before)
    enterPage(after);
}

void goHome() {
  menu->setMenuPageCurrent(mainMenuPage);
  menu->drawMenu();
  enterPage(&mainMenuPage);
}

}  // namespace Menu
