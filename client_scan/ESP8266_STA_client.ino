// https://github.com/boblemaire/asyncHTTPrequest

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include "asyncHTTPrequest.h"
#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

int break_state = 0;
String url1;
asyncHTTPrequest request[85];
String response;

void requestCB(void* optParm, asyncHTTPrequest* request, int readyState){
    response = request->responseText();
    Serial.println(response);
    Serial.println("out");
    request->setDebug(false);
		break_state = 1;
}

void scan(int start, int quan) {
  int time;
  int j=0;
  for (int i=start; i<start+quan; i++) {
    request[j].onData(requestCB);
    request[j].setTimeout(2);
    time = millis();
    String url = "http://192.168.43."+String(i)+"/get";
    url1 = "192.168.1."+String(i);
    request[j].open("GET", url.c_str());
    request[j].send();
    Serial.print(url);
    while (time+500>millis()) {
      Serial.print(".");
      delay(100);
    }
    if (break_state == 1) {
      break;
    }
    Serial.println("/");
    j+=1;
  }
  if (break_state != 1) {
    delay(1000);
  }  
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin("Supod", "palace66");
  while (WiFi.status() != WL_CONNECTED) {
	  Serial.print(".");
    delay(200);
  }
  Serial.println(" ");
  scan(2,81);
  if (break_state!=1) {
    scan(83,81);
  }
  if (break_state!=1) {
    scan(164,81);
  }
}

void loop() {
  Serial.println(" ");
  Serial.println("IP_SCAN");
  Serial.println("==============");
  if (break_state==1) {
    Serial.println(response);
  } else {
    Serial.println("IP_SCAN Not found");
  }
  
  while (true) {
    delay(100);
  }
}
