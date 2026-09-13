#pragma once

#include <Arduino.h>
#include <cstdint>

namespace LogEvent {

struct Pause {
  int32_t dayIndex;
  uint32_t sessionMinutes;
  uint32_t todayMinutes;
  uint32_t totalMinutes;
  uint32_t streakDays;
  uint32_t totalDays;
};

String toJson(const Pause &event);
// Placeholder for a future off-device sync call; currently just builds the payload
void emit(const Pause &event);

}  // namespace LogEvent
