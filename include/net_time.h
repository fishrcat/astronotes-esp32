#pragma once

#include <cstdint>

class Adafruit_GFX;

namespace NetTime {

void begin(Adafruit_GFX &display);
int32_t todayIndex();

}  // namespace NetTime
