/*
 * ESP8266 HTTP Client
 */
#ifndef _include_libs_arduino_
#define _include_libs_arduino_
#include <Arduino.h>
#include <ESP8266WiFi.h>
#endif

#include "httprequest.h"
#include "httpresponse.h"
#include "secrets.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(S_WLAN_SSID);

  WiFi.begin(S_WLAN_SSID, S_WLAN_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected. IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  /* instantiate HttpRequest */
  HttpRequest httpRequest;
  HttpResponse httpResponse;

  /* values to send */
  int value1 = 0, value2 = 0;

  /* configuration */
  /* * http request type */
  httpRequest.setMethod(HttpRequest::POST);
  /* * host * */
  httpRequest.setHost("api.thingspeak.com");
  /* * location * */
  httpRequest.setLocation("/update");
  /* * headers * */
  httpRequest.addHeader("Connection", "close");
  httpRequest.addHeader("X-ThingSpeakAPIKey", S_THINGSPEAK_API_KEY);
  httpRequest.addHeader("Content-Type", "application/x-www-form-urlencoded");

  /* request body */
  value1 = (value1 + 1) % 100;
  value2 = random(0, 100);
  httpRequest.setBody("field1="  + String(value1) + "&field2=" + String(value2));

  /* make the request */
  httpResponse = httpRequest.makeRequest();

  /* print out the response */
  httpResponse.printResponse();

  /* thingspeak likes 15 second pauses between request per channel */
  delay(15000);

}

