#include "log_stats.h"

namespace LogStats {

void rolloverIfNeeded(State &state, int32_t todayIndex) {
  if (todayIndex == state.lastLogDay)
    return;

  if (state.lastLogDay >= 0 && todayIndex == state.lastLogDay + 1)
    state.streakDays += 1;
  else
    state.streakDays = 1;

  state.totalDays += 1;
  state.todayMinutes = 0;
  state.lastLogDay = todayIndex;
}

void addMinutes(State &state, uint32_t minutes) {
  state.todayMinutes += minutes;
  state.totalMinutes += minutes;
}

}  // namespace LogStats
