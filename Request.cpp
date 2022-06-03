#include "Request.h"
#include <WiFiClientSecure.h> 
#include <ESP8266WiFi.h>
#include "variables.h"

void wifiConnect(const char* ssid, const char* password) {
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(500);
  WiFi.mode(WIFI_STA);        //Only Station No AP, This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected to ");
  Serial.println(ssid);
}

WiFiClientSecure serverConnect(const char* FINGERPRINT) {
  WiFiClientSecure httpsClient; //Declare object of class WiFiClient
  httpsClient.setFingerprint(FINGERPRINT);
  httpsClient.setTimeout(15000); // 15 Seconds
  return httpsClient;
}

String GET_Request(String LINK) {
  const char* HOST_NAME = __HOST_NAME__; 
  const int PORT = __PORT__;
  WiFiClientSecure httpsClient = serverConnect();
  Serial.printf("\n[Connecting to %s ... ", HOST_NAME);
  if (httpsClient.connect(HOST_NAME, PORT)) {
    Serial.println("Connected]");
    httpsClient.print(String("GET ") + LINK + " HTTP/1.1\r\n" +
                             "Host: " + HOST_NAME + "\r\n" +               
                             "Connection: close\r\n\r\n");
    while (httpsClient.connected()) {
      String HEADERS = httpsClient.readStringUntil('\n');
      if (HEADERS == "\r") {
      break;
      }
    }
    String line;
    while(httpsClient.available()){        
      line = httpsClient.readStringUntil('\n');  //Read Line by Line
      }
    return line;    
    httpsClient.stop();                       
  } else {
    Serial.println("Connection Failed");
    return "error";
  }
}
