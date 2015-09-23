#include "httprequest.h"

/* HttpRequest */

HttpRequest::HttpRequest() {
  this->httpMethod = HttpRequest::GET;
  this->httpHost = "";
  this->httpPort = 80;
  this->httpLocation = "/";
  this->httpHeaders = "";
  this->httpBody = "";
}

HttpRequest::~HttpRequest() {
  
}

void HttpRequest::setMethod(HttpRequest::HttpMethod httpMethod) {
  this->httpMethod = httpMethod;
}

void HttpRequest::setHost(String httpHost) {
  this->httpHost = httpHost;
  this->addHeader("Host", String(httpHost));
}

void HttpRequest::setPort(uint16_t httpPort) {
  this->httpPort = httpPort;
}

void HttpRequest::setLocation(String httpLocation) {
  this->httpLocation = httpLocation;
}

void HttpRequest::addHeader(String httpHeaderName, String httpHeaderValue) {
  this->httpHeaders = this->httpHeaders + httpHeaderName + ": " + httpHeaderValue + "\r\n";
}

void HttpRequest::setBody(String httpBody) {
  this->httpBody = httpBody;
}

void HttpRequest::addDefaultHeaders() {
  this->addHeader("Connection", "close");
  if (this->httpBody.length() > 0) {
    this->addHeader("Content-Length", String(this->httpBody.length()));
  }
}

String HttpRequest::httpMethodString() {

  switch (this->httpMethod) {
    case HttpRequest::GET:
      return "GET";
      break;

    case HttpRequest::POST:
      return "POST";
      break;

    case HttpRequest::PUT:
      return "PUT";
      break;

    case HttpRequest::DELETE:
      return "DELETE";
      break;

    default:
      return "";
      break;
  
  }
 
}

String HttpRequest::httpRequestString() {

  /* add default headers before serializing request */
  this->addDefaultHeaders();

  /* build request string */
  String request = "";

  request += this->httpMethodString() + " " + this->httpLocation + " HTTP/1.1\r\n";
  request += this->httpHeaders;
  request += "\r\n";

  if (this->httpBody.length() > 0) {
    request += this->httpBody;
    request += "\r\n";
  }

  return request;
}

HttpResponse HttpRequest::makeRequest() {

  HttpResponse httpResponse;

  /* build request string */


  /* create client */
  WiFiClient client;

  /* connect to host */
  if (!client.connect(this->httpHost.c_str(), this->httpPort)) {
    Serial.print("connection to ");
    Serial.print(this->httpHost);
    Serial.print(":");
    Serial.print(this->httpPort);
    Serial.println(" failed");
    return httpResponse;
  } else {
    Serial.print("connected to ");
    Serial.print(this->httpHost);
    Serial.print(":");
    Serial.print(this->httpPort);
    Serial.println("");
  }

  String request = this->httpRequestString();

  /* debug request */
  Serial.println("===== Request ======================================");
  Serial.println(request);
  Serial.println("====================================================");

  /* send request */
  client.print(request);

  /* read and parse response */
  uint32_t n = 0;
  String line, word1, word2;
  bool readingHeaders = true;

  while (client.available()) {
    line = client.readStringUntil('\r');
    Serial.print(line);
  }
//    /* line number increment */
//    n++;
//
//    /* parse first line (HTTP response) */ 
//    if (n == 1) {
//      word1 = client.readStringUntil(' ');
//      if (word1 == "HTTP/1.1") {
//        Serial.println("Got " + word1);
//        word1 = client.readStringUntil(' ');
//        word2 = client.readStringUntil('\r');
//        word2.trim();
//        httpResponse.setReady();
//        httpResponse.setStatus(word1, word2);
//        Serial.println("code " + word1 + " - " + word2);
//      } else {
//        Serial.println("Wrong HTTP version in response: " + word1);
//      }
//      continue;
//    }
//
//    line = client.readStringUntil('\r');
//    line.trim();
//
//    if ((line == "") && (readingHeaders)) {
//      readingHeaders = false;
//    } else if (readingHeaders) {
//      httpResponse.addHeader(line);
//    } else {
//      Serial.println("adding line" + line);
//      httpResponse.addBody(line);
//    }
//  }

  Serial.print("closing connection after reading ");
  Serial.print(n);
  Serial.println(" lines");
  /* Connection is closed when loop() returns */

  return httpResponse;
}

