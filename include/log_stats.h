#pragma once

#include <cstdint>

namespace LogStats {

struct State {
  uint32_t streakDays = 0;
  uint32_t totalDays = 0;
  uint32_t totalMinutes = 0;
  uint32_t todayMinutes = 0;
  int32_t lastLogDay = -1;
};

// Only count day if the timer was used
void rolloverIfNeeded(State &state, int32_t todayIndex);
void addMinutes(State &state, uint32_t minutes);

}  // namespace LogStats
