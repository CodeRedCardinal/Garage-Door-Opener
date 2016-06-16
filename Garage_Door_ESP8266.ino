//Garage Door webshite for Adafruit HUZZAH ESP8266
//Working as of May 11, 2016

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

MDNSResponder mdns;

// Replace with your network credentials
const char* ssid = "Amir";
const char* password = "amirjoya";

ESP8266WebServer server(80);

String webPage = "";

int gpio2_pin = 2;

void setup(void){
  webPage += "<h1>Garage Door</h1><a href=\"socket1On\"><button>Open/Close</button></a>";
 // webPage += "<p>Socket #2 <a href=\"socket2On\"><button>ON</button></a>&nbsp;<a href=\"socket2Off\"><button>OFF</button></a></p>";
  
  // preparing GPIOs
//  pinMode(gpio0_pin, OUTPUT);
//  digitalWrite(gpio0_pin, LOW);
  pinMode(gpio2_pin, OUTPUT);
  digitalWrite(gpio2_pin, LOW);
  
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  server.on("/socket1On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio2_pin, HIGH);
    delay(4000);
    digitalWrite(gpio2_pin, LOW);
  });
//  server.on("/socket1Off", [](){
//    server.send(200, "text/html", webPage);
//    digitalWrite(gpio0_pin, LOW);
//    delay(1000); 
//  });
//  server.on("/socket2On", [](){
//    server.send(200, "text/html", webPage);
//    digitalWrite(gpio2_pin, HIGH);
//    delay(1000);
//  });
//  server.on("/socket2Off", [](){
//    server.send(200, "text/html", webPage);
//    digitalWrite(gpio2_pin, LOW);
//    delay(1000); 
//  });
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
  server.handleClient();
} 