#ifndef _httpresponse_h_
#define _httpresponse_h_

#ifndef _include_libs_arduino_
#define _include_libs_arduino_
#include <Arduino.h>
#include <ESP8266WiFi.h>
#endif

class HttpResponse {
  public:
  
  HttpResponse();
  ~HttpResponse();

  void setStatus(String responseStatusCode, String responseStatusMessage);
  void setReady();
  void addHeader(String responseHeader);
  void addBody(String responseBody);
  void printResponse();
  
  bool responseReady;
  String responseStatusCode;
  String responseStatusMessage;
  String responseHeaders;
  String responseBody;
};

#endif /* _httpresponse_h_ */
