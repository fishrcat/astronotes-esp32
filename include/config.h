#pragma once

#include <cstdint>

namespace Config {

constexpr unsigned long kIdleTimeoutMs = 0.1 * 60 * 1000UL;  // TODO: Small test value
constexpr unsigned long kBatteryRefreshMs = 30 * 1000UL;

constexpr uint8_t kMenuTextSize = 2;
constexpr uint8_t kMenuRowHeight = 10 * kMenuTextSize;

constexpr uint16_t kForegroundColor = 0xFFFF;
constexpr uint16_t kBackgroundColor = 0x0000;

constexpr uint8_t kPinEnter = 0;
constexpr uint8_t kPinDown = 1;
constexpr uint8_t kPinUp = 2;

}  // namespace Config
