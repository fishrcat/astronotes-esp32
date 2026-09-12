#include "buttons.h"

#include <Arduino.h>
#include <OneButton.h>

namespace Buttons {
namespace {

enum Slot { kEnter, kDown, kUp, kSlotCount };

OneButton buttons[kSlotCount];
Callback clickCallbacks[kSlotCount] = {};
Callback holdCallback = nullptr;

void dispatchClick(void *slot) {
  Callback cb = clickCallbacks[reinterpret_cast<intptr_t>(slot)];
  if (cb)
    cb();
}

void dispatchHold(void *) {
  if (holdCallback)
    holdCallback();
}

}  // namespace

void begin() {
  buttons[kEnter].setup(0, INPUT_PULLUP, true);
  buttons[kDown].setup(1, INPUT_PULLDOWN, false);
  buttons[kUp].setup(2, INPUT_PULLDOWN, false);

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

}  // namespace Buttons
