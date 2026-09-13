#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <ESPUI.h>
#include <ESPmDNS.h>
#include <WiFi.h>

#include "buttons.h"
#include "log.h"
#include "menu.h"
#include "net_time.h"
#include "power.h"

Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);
  delay(10);

  tft.init(135, 240);
  tft.setRotation(1);

  NetTime::begin(tft);
  MDNS.begin("astronotes");
  ESPUI.begin("Astronotes");
  MDNS.addService("http", "tcp", 80);

  Buttons::begin();
  Buttons::onEnter(Menu::pressOk);
  Buttons::onDown(Menu::pressDown);
  Buttons::onUp(Menu::pressUp);
  Buttons::onHold(Menu::goHome);

  Log::begin();
  Menu::begin(tft);
  Power::begin();
}

void loop() {
  Buttons::tick();
  Menu::tick();
  Log::tick();
  Power::tick();
}
