#include "power.h"

#include <Arduino.h>
#include <driver/gpio.h>
#include <driver/rtc_io.h>
#include <esp_sleep.h>

#include "buttons.h"
#include "config.h"

namespace Power {
namespace {

constexpr gpio_num_t kGpioEnter = static_cast<gpio_num_t>(Config::kPinEnter);
constexpr gpio_num_t kGpioDown = static_cast<gpio_num_t>(Config::kPinDown);
constexpr gpio_num_t kGpioUp = static_cast<gpio_num_t>(Config::kPinUp);
constexpr gpio_num_t kGpioBacklite = static_cast<gpio_num_t>(TFT_BACKLITE);

void configureWakePin(gpio_num_t pin, bool pullup) {
  rtc_gpio_init(pin);
  if (pullup) {
    rtc_gpio_pulldown_dis(pin);
    rtc_gpio_pullup_en(pin);
  } else {
    rtc_gpio_pullup_dis(pin);
    rtc_gpio_pulldown_en(pin);
  }
}

void sleep() {
  digitalWrite(TFT_BACKLITE, LOW);
  gpio_hold_en(kGpioBacklite);
  gpio_deep_sleep_hold_en();

  configureWakePin(kGpioEnter, true);
  configureWakePin(kGpioDown, false);
  configureWakePin(kGpioUp, false);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);

  esp_deep_sleep_start();
}

}  // namespace

void begin() {
  gpio_hold_dis(kGpioBacklite);
  gpio_deep_sleep_hold_dis();

  esp_sleep_enable_ext0_wakeup(kGpioEnter, 0);
  esp_sleep_enable_ext1_wakeup(BIT(kGpioDown) | BIT(kGpioUp), ESP_EXT1_WAKEUP_ANY_HIGH);
}

void tick() {
  if (millis() - Buttons::lastActivityMs() >= Config::kIdleTimeoutMs)
    sleep();
}

}  // namespace Power
