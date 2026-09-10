#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <ESPUI.h>
#include <ESPmDNS.h> 
#include <WiFi.h>

Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_RST);

// Update the text on the screen
void onText(Control *sender, int type) {
  if (type != T_VALUE)
    return;
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.print(sender->value);
}

void setup() {
  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);
  delay(10);

  tft.init(135, 240);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setTextWrap(true);
  tft.print("hello world");

  WiFi.softAP("Astronotes");
  MDNS.begin("astronotes");
  ESPUI.text("Text", &onText, ControlColor::Peterriver, "hello world");
  ESPUI.begin("Astronotes");
  MDNS.addService("http", "tcp", 80);
}

void loop() {}
