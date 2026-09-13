#include "net_time.h"

#include <Adafruit_GFX.h>
#include <WiFiManager.h>
#include <ctime>

#include "config.h"

namespace NetTime {
namespace {

constexpr time_t kCheckEpoch = 1700000000;

void showStatus(Adafruit_GFX &display, const char *text) {
  display.fillScreen(Config::kBackgroundColor);
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(Config::kForegroundColor, Config::kBackgroundColor);
  display.print(text);
}

}  // namespace

void begin(Adafruit_GFX &display) {
  showStatus(display, "Connecting WiFi...");
  WiFiManager wm;
  wm.setConfigPortalTimeout(0);
  while (!wm.autoConnect("Astronotes Setup"))
    delay(1000);

  showStatus(display, "Syncing time...");
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  while (time(nullptr) < kCheckEpoch)
    delay(500);
}

int32_t todayIndex() {
  return static_cast<int32_t>(time(nullptr) / 86400);
}

}  // namespace NetTime
