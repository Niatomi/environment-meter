#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>        
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include "WiFiManager.h"          
#include <SPI.h> 
#include <WiFiClient.h>
#include <TimeLib.h>

#define HTTP_LED D1
#define SPI_LED D2

void configModeCallback (WiFiManager *myWiFiManager) {
  WiFi.softAPIP();
  //if you used auto generated SSID, print it
  myWiFiManager->getConfigPortalSSID();
}

WiFiClient client; 

String regionID = "51"; 

void setup() {
  Serial.end();
  Serial.begin(9600);
  Serial.flush();
  Serial.setDebugOutput(false); 
   

  pinMode(HTTP_LED, OUTPUT);
  pinMode(SPI_LED, OUTPUT);
  pinMode(D4, INPUT);
  pinMode(D3, INPUT);

  digitalWrite(HTTP_LED, false);
  digitalWrite(SPI_LED, false);
  
  WiFiManager wifiManager;
  wifiManager.setDebugOutput(false);
  
  //reset settings - for testing
  // wifiManager.resetSettings();

  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);
  Serial.setDebugOutput(false);
  Serial.flush();
  Serial.println("-WiFiConfigStart-");

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect("ESP8266 ConfigMe")) {

    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(1000);
  } 

  // String SSID = wifiManager.getWiFiSSID();
  // String password = wifiManager.getWiFiPass();

  Serial.println("-WiFiConfigEnd-");

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

  syncTime();
 
}

/*
* Синхронизируем время c https://yandex.ru/time/sync.json?geo=51
*/
void syncTime () {                                                    
  if (client.connect("yandex.com", 443)) {                                  
    client.println("GET /time/sync.json?geo=" + regionID + " HTTP/1.1"); 
    client.println("Host: yandex.com"); 
    client.println("Connection: close\r\n"); 
    delay(200);                           

    char endOfHeaders[] = "\r\n\r\n";                                   
    if (!client.find(endOfHeaders)) {                                      
        Serial.println("Invalid response");                                   
        return ;                                                         
    }
    const size_t capacity = 768;                                            
    DynamicJsonDocument doc(capacity);                                 
    deserializeJson(doc, client);                    
    client.stop();                                                         
    String StringCurrentTime = doc["time"].as<String>().substring(0, 10);   // get local date time witout ms
    unsigned long CurrentTime = StringToULong(StringCurrentTime);           //   String в unsigned long

    doc.clear();  
    setTime(CurrentTime); 
    Serial.println(now());
  }
}

unsigned long StringToULong(String Str) { 
  unsigned long ULong = 0;
  for (int i = 0; i < Str.length(); i++) {   
     char c = Str.charAt(i);
     if (c < '0' || c > '9') break;
     ULong *= 10;
     ULong += (c - '0');
  }
  return ULong;
}

void loop() {
}