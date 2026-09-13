#include <unity.h>

#include "log_stats.h"

void setUp() {}
void tearDown() {}

void test_first_start_counts_day() {
  LogStats::State state;
  LogStats::rolloverIfNeeded(state, 100);
  TEST_ASSERT_EQUAL_UINT32(1, state.streakDays);
  TEST_ASSERT_EQUAL_UINT32(1, state.totalDays);
  TEST_ASSERT_EQUAL_INT32(100, state.lastLogDay);
}

void test_same_day_is_noop() {
  LogStats::State state;
  LogStats::rolloverIfNeeded(state, 100);
  LogStats::addMinutes(state, 5);
  LogStats::rolloverIfNeeded(state, 100);
  TEST_ASSERT_EQUAL_UINT32(1, state.totalDays);
  TEST_ASSERT_EQUAL_UINT32(1, state.streakDays);
  TEST_ASSERT_EQUAL_UINT32(5, state.todayMinutes);
}

void test_consecutive_day_extends_streak() {
  LogStats::State state;
  LogStats::rolloverIfNeeded(state, 100);
  LogStats::addMinutes(state, 5);
  LogStats::rolloverIfNeeded(state, 101);
  TEST_ASSERT_EQUAL_UINT32(2, state.streakDays);
  TEST_ASSERT_EQUAL_UINT32(2, state.totalDays);
  TEST_ASSERT_EQUAL_UINT32(0, state.todayMinutes);
}

void test_gap_resets_streak() {
  LogStats::State state;
  LogStats::rolloverIfNeeded(state, 100);
  LogStats::rolloverIfNeeded(state, 101);
  LogStats::rolloverIfNeeded(state, 105);
  TEST_ASSERT_EQUAL_UINT32(1, state.streakDays);
  TEST_ASSERT_EQUAL_UINT32(3, state.totalDays);
}

void test_backwards_day_resets_streak() {
  LogStats::State state;
  LogStats::rolloverIfNeeded(state, 100);
  LogStats::rolloverIfNeeded(state, 101);
  LogStats::rolloverIfNeeded(state, 99);
  TEST_ASSERT_EQUAL_UINT32(1, state.streakDays);
  TEST_ASSERT_EQUAL_INT32(99, state.lastLogDay);
}

void test_minutes_accumulate_totals() {
  LogStats::State state;
  LogStats::addMinutes(state, 10);
  LogStats::addMinutes(state, 5);
  TEST_ASSERT_EQUAL_UINT32(15, state.todayMinutes);
  TEST_ASSERT_EQUAL_UINT32(15, state.totalMinutes);
}

void test_rollover_resets_today_minutes() {
  LogStats::State state;
  LogStats::rolloverIfNeeded(state, 100);
  LogStats::addMinutes(state, 20);
  LogStats::rolloverIfNeeded(state, 101);
  TEST_ASSERT_EQUAL_UINT32(0, state.todayMinutes);
  TEST_ASSERT_EQUAL_UINT32(20, state.totalMinutes);
}

int main(int argc, char **argv) {
  UNITY_BEGIN();
  RUN_TEST(test_first_start_counts_day);
  RUN_TEST(test_same_day_is_noop);
  RUN_TEST(test_consecutive_day_extends_streak);
  RUN_TEST(test_gap_resets_streak);
  RUN_TEST(test_backwards_day_resets_streak);
  RUN_TEST(test_minutes_accumulate_totals);
  RUN_TEST(test_rollover_resets_today_minutes);
  return UNITY_END();
}
