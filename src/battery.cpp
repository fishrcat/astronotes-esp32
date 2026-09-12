#include "battery.h"

#include <Adafruit_LC709203F.h>
#include <Adafruit_MAX1704X.h>
#include <Wire.h>

namespace Battery {
namespace {

enum class Gauge { kNone, kMax17048, kLc709203f };

Adafruit_MAX17048 max17048;
Adafruit_LC709203F lc709203f;
Gauge detected = Gauge::kNone;

}  // namespace

void begin() {
  Wire.begin();
  if (max17048.begin(&Wire))
    detected = Gauge::kMax17048;
  else if (lc709203f.begin(&Wire))
    detected = Gauge::kLc709203f;
}

bool available() { return detected != Gauge::kNone; }

float percent() {
  if (detected == Gauge::kMax17048)
    return max17048.cellPercent();
  if (detected == Gauge::kLc709203f)
    return lc709203f.cellPercent();
  return 0.0F;
}

}  // namespace Battery
