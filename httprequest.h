#ifndef _httprequest_h_
#define _httprequest_h_

#ifndef _include_libs_arduino_
#define _include_libs_arduino_
#include <Arduino.h>
#include <ESP8266WiFi.h>
#endif


#include "httpresponse.h"

class HttpRequest {
  
  public:
  enum HttpMethod { POST, PUT, GET, DELETE };

  HttpRequest();
  ~HttpRequest();
  
  void setMethod(HttpMethod httpMethod);
  
  void setHost(String host);

  void setPort(uint16_t port);

  void setLocation(String location);

  void addHeader(String header, String value);

  void setBody(String body);

  HttpResponse makeRequest();

  private:
  HttpMethod httpMethod;
  String httpHost;
  uint16_t httpPort;
  String httpLocation;
  String httpHeaders;
  String httpBody;

  void (*httpCallback)();

  String httpMethodString();
  String httpRequestString();
  void addDefaultHeaders();

};

#endif /* _httprequest_h_ */
