#include "log.h"

#include <Adafruit_GFX.h>
#include <Arduino.h>
#include <Preferences.h>
#include <array>
#include <cstdio>

#include "buttons.h"
#include "config.h"
#include "log_event.h"
#include "log_stats.h"
#include "net_time.h"
#include "page_draw.h"

namespace Log {
namespace {

Preferences prefs;
LogStats::State state;
bool running = false;
unsigned long runStartMs = 0;
bool blinkOn = true;
unsigned long lastBlinkMs = 0;

void load() {
  prefs.begin("log", false);
  state.streakDays = prefs.getUInt("streak", 0);
  state.totalDays = prefs.getUInt("total_days", 0);
  state.totalMinutes = prefs.getUInt("total_min", 0);
  state.todayMinutes = prefs.getUInt("today_min", 0);
  state.lastLogDay = prefs.getInt("last_day", -1);
}

void save() {
  prefs.putUInt("streak", state.streakDays);
  prefs.putUInt("total_days", state.totalDays);
  prefs.putUInt("total_min", state.totalMinutes);
  prefs.putUInt("today_min", state.todayMinutes);
  prefs.putInt("last_day", state.lastLogDay);
}

void formatUInt(char *buf, size_t size, uint32_t value) {
  (void)snprintf(buf, size, "%lu", static_cast<unsigned long>(value));
}

void drawCell(Adafruit_GFX &screen, int x, int y, int w, const char *label1, const char *label2,
              const char *value, bool visible) {
  PageDraw::Cell c = PageDraw::pad(x, y, w);
  PageDraw::setTextStyle(screen);
  PageDraw::text(screen, c.x, c.y, c.w, label1);
  PageDraw::text(screen, c.x, c.y + Config::kPageLineHeight, c.w, label2);
  PageDraw::text(screen, c.x, c.y + 2 * Config::kPageLineHeight, c.w, value, visible);
}

}  // namespace

void begin() {
  load();
}

void toggleTimer() {
  if (!running) {
    int32_t today = NetTime::todayIndex();
    if (today != state.lastLogDay) {
      LogStats::rolloverIfNeeded(state, today);
      save();
    }
    running = true;
    runStartMs = millis();
    Buttons::recordActivity();
    return;
  }

  uint32_t sessionMinutes = (millis() - runStartMs) / 60000;
  LogStats::addMinutes(state, sessionMinutes);
  save();

  LogEvent::Pause event{state.lastLogDay,   sessionMinutes,   state.todayMinutes,
                        state.totalMinutes, state.streakDays, state.totalDays};
  LogEvent::emit(event);

  running = false;
  blinkOn = true;
}

void tick() {
  if (running)
    Buttons::recordActivity();
}

void draw(Adafruit_GFX &screen, bool force) {
  unsigned long now = millis();
  if (!force && now - lastBlinkMs < Config::kLogBlinkMs)
    return;
  lastBlinkMs = now;

  PageDraw::Origin o = PageDraw::origin();
  int w = (screen.width() - 2 * Config::kPageMargin) / 2;
  int h = (screen.height() - o.y - Config::kPageMargin) / 2;
  int x0 = o.x;
  int y0 = o.y;

  if (running)
    blinkOn = !blinkOn;

  uint32_t displayToday = state.todayMinutes;
  if (running)
    displayToday += (millis() - runStartMs) / 60000;

  std::array<char, 8> streakText{};
  std::array<char, 8> totalDaysText{};
  std::array<char, 8> todayText{};
  std::array<char, 16> totalHrsMinsText{};
  formatUInt(streakText.data(), streakText.size(), state.streakDays);
  formatUInt(totalDaysText.data(), totalDaysText.size(), state.totalDays);
  formatUInt(todayText.data(), todayText.size(), displayToday);
  (void)snprintf(totalHrsMinsText.data(), totalHrsMinsText.size(), "%luh %lum",
                 static_cast<unsigned long>(state.totalMinutes / 60),
                 static_cast<unsigned long>(state.totalMinutes % 60));

  drawCell(screen, x0, y0, w, "Streak", "Days", streakText.data(), true);
  drawCell(screen, x0 + w, y0, w, "Total", "Days", totalDaysText.data(), true);
  drawCell(screen, x0, y0 + h, w, "Today", "Mins", todayText.data(), blinkOn);
  drawCell(screen, x0 + w, y0 + h, w, "Total", "Hrs Mins", totalHrsMinsText.data(), true);
}

void onEnter(Adafruit_GFX &screen) {
  draw(screen, true);
}

}  // namespace Log
