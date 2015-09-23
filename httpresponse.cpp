#include "httpresponse.h"
/* HttpResponse */

HttpResponse::HttpResponse() {
  this->responseReady = false;
  this->responseStatusCode = "";
  this->responseStatusMessage = "";
  this->responseHeaders = "";
  this->responseBody = "";
}

HttpResponse::~HttpResponse() {
  
}

void HttpResponse::setStatus(String responseStatusCode, String responseStatusMessage) {
  this->responseStatusCode = responseStatusCode;  
  this->responseStatusMessage = responseStatusMessage;  
}

void HttpResponse::setReady() {
  this->responseReady = true;
}
void HttpResponse::addHeader(String responseHeader) {
  this->responseHeaders += responseHeader + "\n";
}

void HttpResponse::addBody(String responseBody) {
  this->responseBody += responseBody + "\n";
}

void HttpResponse::printResponse() {
  if (this->responseReady) {
    Serial.print("HTTP ");
    Serial.print(this->responseStatusCode);
    Serial.print(" ");
    Serial.println(this->responseStatusMessage);
    Serial.println("===== Response Headers =============================");
    Serial.print(this->responseHeaders);
    Serial.println("===== Response Body ================================");
    Serial.print(this->responseBody);
    Serial.println("====================================================");
  } else {
    Serial.println("HTTP Request Failed");
  }
}

