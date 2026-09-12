#include "menu.h"

#include <GEM_adafruit_gfx.h>
#include <array>
#include <cstdio>

#include "battery.h"
#include "config.h"

namespace Menu {
namespace {

GEM_adafruit_gfx *menu = nullptr;
Adafruit_GFX *screen = nullptr;
unsigned long lastDrawMs = 0;
float cachedBatteryPercent = 0.0F;

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

void refreshBatteryPercent() {
  if (Battery::available())
    cachedBatteryPercent = Battery::percent();
}

void drawBatteryIndicator() {
  if (!Battery::available())
    return;
  std::array<char, 8> text{};
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg, hicpp-vararg)
  (void)snprintf(text.data(), text.size(), "%3d%%", static_cast<int>(cachedBatteryPercent));
  screen->setTextSize(1);
  screen->setTextColor(Config::kForegroundColor, Config::kBackgroundColor);
  screen->setCursor(screen->width() - 30, 2);
  screen->print(text.data());
  screen->setTextSize(Config::kMenuTextSize);
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
  menu->setDrawMenuCallback(drawBatteryIndicator);

  mainMenuPage.addMenuItem(logItem);
  mainMenuPage.addMenuItem(tunerItem);
  mainMenuPage.addMenuItem(analyzeItem);
  mainMenuPage.addMenuItem(jamItem);
  mainMenuPage.addMenuItem(settingsItem);

  refreshBatteryPercent();
  menu->init();
  menu->setMenuPageCurrent(mainMenuPage);
  menu->drawMenu();
}

void tick() {
  unsigned long now = millis();
  if (now - lastDrawMs >= Config::kBatteryRefreshMs) {
    lastDrawMs = now;
    refreshBatteryPercent();
    drawBatteryIndicator();
  }
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
