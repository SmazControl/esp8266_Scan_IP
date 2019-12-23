// https://github.com/boblemaire/asyncHTTPrequest

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include "asyncHTTPrequest.h"
#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;
asyncHTTPrequest request[100];

int break_state = 0;
String url1;

void requestCB(void* optParm, asyncHTTPrequest* request, int readyState){
    if(readyState == 4 && request->responseText()!=""){
        Serial.println(request->responseText());
        Serial.println("out");
        request->setDebug(false);
		    break_state = 1;
    }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin("phloenlom_2.4GHz", "248248248");
  while (WiFi.status() != WL_CONNECTED) {
	  Serial.print(".");
    delay(200);
  }
  Serial.println(" ");
  int time;
  for (int i=2; i<100; i++) {
    request[i].onReadyStateChange(requestCB);
    request[i].setTimeout(2);
	  time = millis();
    String url = "http://192.168.1."+String(i)+"/get";
    url1 = "192.168.1."+String(i);
    request[i].open("GET", url.c_str());
    request[i].send();
    Serial.print(url);
  	while (time+500>millis()) {
      Serial.print(".");
	  	delay(100);
	  }
	  if (break_state == 1) {
		  break;
	  }
    Serial.println("/");
  }
}

void loop() {
  Serial.println(" ");
  Serial.println("IP_SCAN");
  Serial.println("==============");
  Serial.println(url1);
  while (true) {
    delay(100);
  }
}
