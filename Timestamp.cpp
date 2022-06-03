#include "Timestamp.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

String getTimestamp() {
  #define NTP_OFFSET   60 * 0      // In seconds
  #define NTP_INTERVAL 60 * 1000    // In miliseconds
  #define NTP_ADDRESS  "europe.pool.ntp.org"
  WiFiUDP ntpUDP;
  NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);
  timeClient.begin();
  
  timeClient.update();
  unsigned long timestamp = timeClient.getEpochTime();
  //unsigned long timeMilli = timestamp * 1000;
  return String(timestamp) + "000";
}
