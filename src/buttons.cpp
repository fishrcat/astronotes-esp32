#include "buttons.h"

#include <Arduino.h>
#include <OneButton.h>

#include "config.h"

namespace Buttons {
namespace {

enum Slot { kEnter, kDown, kUp, kSlotCount };

OneButton buttons[kSlotCount];
Callback clickCallbacks[kSlotCount] = {};
Callback holdCallback = nullptr;
unsigned long lastActivity = 0;

void dispatchClick(void *slot) {
  lastActivity = millis();
  Callback cb = clickCallbacks[reinterpret_cast<intptr_t>(slot)];
  if (cb != nullptr)
    cb();
}

void dispatchHold(void *slot) {
  (void)slot;
  lastActivity = millis();
  if (holdCallback != nullptr)
    holdCallback();
}

}  // namespace

void begin() {
  buttons[kEnter].setup(Config::kPinEnter, INPUT_PULLUP, true);
  buttons[kDown].setup(Config::kPinDown, INPUT_PULLDOWN, false);
  buttons[kUp].setup(Config::kPinUp, INPUT_PULLDOWN, false);

  for (int slot = 0; slot < kSlotCount; slot++)
    buttons[slot].attachClick(dispatchClick, reinterpret_cast<void *>(slot));
  buttons[kEnter].attachLongPressStart(dispatchHold, nullptr);
}

void tick() {
  for (auto &button : buttons)
    button.tick();
}

void onEnter(Callback cb) { clickCallbacks[kEnter] = cb; }
void onDown(Callback cb) { clickCallbacks[kDown] = cb; }
void onUp(Callback cb) { clickCallbacks[kUp] = cb; }
void onHold(Callback cb) { holdCallback = cb; }

unsigned long lastActivityMs() { return lastActivity; }
void recordActivity() { lastActivity = millis(); }

}  // namespace Buttons
