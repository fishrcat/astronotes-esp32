#pragma once

#include <cstdint>

namespace Config {

constexpr unsigned long kIdleTimeoutMs = 2 * 60 * 1000UL;
constexpr unsigned long kLogBlinkMs = 500;

constexpr uint8_t kMenuTextSize = 2;
constexpr uint8_t kMenuRowHeight = 10 * kMenuTextSize;

constexpr uint8_t kPageMargin = 6;
constexpr uint8_t kPageTopMargin = kMenuRowHeight + kPageMargin;
constexpr uint8_t kPagePadding = 4;
constexpr uint8_t kPageLineHeight = 8 * kMenuTextSize;

constexpr uint16_t kForegroundColor = 0xFFFF;
constexpr uint16_t kBackgroundColor = 0x0000;

constexpr uint8_t kPinEnter = 0;
constexpr uint8_t kPinDown = 1;
constexpr uint8_t kPinUp = 2;

}  // namespace Config
