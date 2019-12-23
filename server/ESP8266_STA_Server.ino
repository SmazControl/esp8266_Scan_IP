#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer webServer(80);

void handlePost() {
  String message = "Number of args received:";
  message += webServer.args();  
  message += "\n";                  
  for (int i = 0; i < webServer.args(); i++) {
    message += "Arg nº" + (String)i + " –> ";
    message += webServer.argName(i) + ": ";
    message += webServer.arg(i) + "\n";
    if(webServer.argName(i)=="number") {
      Serial.println("Received "+String(webServer.arg(i)));
    }
  }
  webServer.send(200, "text/plain", message);
}

void handleGet() {
  String message = WiFi.localIP().toString();
  Serial.println("Send "+message);
  webServer.send(200, "text/plain", message);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin("phloenlom_2.4GHz","248248248");
  while (WiFi.status() != WL_CONNECTED) {
	  Serial.print('.');
    delay(200);
  }
  Serial.println(' ');
  Serial.println(WiFi.localIP());  
  Serial.println("Web Server Start...");
  webServer.on("/post", handlePost); 
  webServer.on("/get", handleGet);
  webServer.onNotFound([]() {
    Serial.println("Hello World!");
    String message = "Hello World!\n\n";
    message += "URI: ";
    message += webServer.uri();

    webServer.send(200, "text/plain", message);
  });
  webServer.begin();
}

void loop() {
  webServer.handleClient();
}
