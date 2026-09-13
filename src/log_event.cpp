#include "log_event.h"

#include <ArduinoJson.h>

namespace LogEvent {

String toJson(const Pause &event) {
  StaticJsonDocument<192> doc;
  doc["type"] = "log_pause";
  doc["day_index"] = event.dayIndex;
  doc["session_minutes"] = event.sessionMinutes;
  doc["today_minutes"] = event.todayMinutes;
  doc["total_minutes"] = event.totalMinutes;
  doc["streak_days"] = event.streakDays;
  doc["total_days"] = event.totalDays;

  String json;
  serializeJson(doc, json);
  return json;
}

void emit(const Pause &event) {
  Serial.println(toJson(event));
}

}  // namespace LogEvent
