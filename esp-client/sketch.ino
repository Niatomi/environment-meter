#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>        
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include "WiFiManager.h"          
#include <SPI.h> 

#define HTTP_LED D1
#define SPI_LED D2

void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

void setup() {
  Serial.begin(9600);

  pinMode(HTTP_LED, OUTPUT);
  pinMode(SPI_LED, OUTPUT);
  pinMode(D4, INPUT);
  pinMode(D3, INPUT);

  digitalWrite(HTTP_LED, false);
  digitalWrite(SPI_LED, false);

  SPI.begin();
  char buff[] = "WCI\n";
  for(int i=0; i<sizeof buff; i++) {
    SPI.transfer(buff[i]);
  }

  
  // WiFiManager wifiManager;
  
  //reset settings - for testing
  // wifiManager.resetSettings();

  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  // wifiManager.setAPCallback(configModeCallback);

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  // if(!wifiManager.autoConnect("ESP8266 ConfigMe")) {
  //   Serial.println("failed to connect and hit timeout");
  //   //reset and try again, or maybe put it to deep sleep
  //   ESP.reset();
  //   delay(1000);
  // } 

  //if you get here you have connected to the WiFi
  // Serial.println(F("WIFIManager connected!"));

  // Serial.print(F("IP --> "));
  // Serial.println(WiFi.localIP());
  // Serial.print(F("GW --> "));
  // Serial.println(WiFi.gatewayIP());
  // Serial.print(F("SM --> "));
  // Serial.println(WiFi.subnetMask());

  // Serial.print(F("DNS 1 --> "));
  // Serial.println(WiFi.dnsIP(0));

  // Serial.print(F("DNS 2 --> "));
  // Serial.println(WiFi.dnsIP(1));
 
}

void loop() {

}