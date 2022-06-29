#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>        
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include "WiFiManager.h"          
#include <SPI.h> 
#include <WiFiClient.h>
#include <TimeLib.h>

#define HTTP_LED D7
#define SERIAL_LED D8

void configModeCallback (WiFiManager *myWiFiManager) {
  WiFi.softAPIP();
  myWiFiManager->getConfigPortalSSID();
}

WiFiClient client; 

float pHValue = 0;
float Etemp = 0;
float Wtemp = 0;
unsigned int ppm = 0;
float tdsSensor;

int standartCO2 = 1500;
float standartPH = 6.1;

String regionID = "51"; 

unsigned long lastTimeSync;
unsigned long globalTimeBufferMillis = 0;

void setup() {
  pinMode(HTTP_LED, OUTPUT);
  pinMode(SERIAL_LED, OUTPUT);

  digitalWrite(HTTP_LED, HIGH);
  digitalWrite(SERIAL_LED, HIGH);

  Serial.setTimeout(5);
  Serial.end();
  Serial.begin(9600);
  Serial.flush();
  Serial.setDebugOutput(false); 
   
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

  Serial.println("-WiFiConfigEnd-");


  syncTime();
  getSchedule();

  awaitEvent();
 
  digitalWrite(HTTP_LED, LOW);
  digitalWrite(SERIAL_LED, LOW);

  Serial.end();
  Serial.begin(9600);
}

/*
* Получаем расписание проверок
*/
void getSchedule() {

}


/*
* Синхронизируем время c https://yandex.ru/time/sync.json?geo=51
*/
void syncTime () {                                                    
  if (client.connect("yandex.com", 443)) { 
    digitalWrite(HTTP_LED, HIGH);                                 
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
    digitalWrite(HTTP_LED, LOW);

    String StringCurrentTime = doc["time"].as<String>().substring(0, 10);   // get local date time witout ms
    unsigned long CurrentTime = StringToULong(StringCurrentTime);           //   String в unsigned long

    doc.clear();  
    setTime(CurrentTime); 
    lastTimeSync = now();
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
  awaitEvent();
}



void awaitEvent() {
  

  // Синхронизируем время каждую неделю
  if (now() - lastTimeSync >= 604800) {
    syncTime();
  }

  if (Serial.available()) {
      String expression = "";
      

      expression = Serial.readStringUntil('@');
      expression = Serial.readStringUntil('@');
      
      Serial.end();
      Serial.begin(9600);
      improvedDelay(200);

      if (expression.equals("getStandartsData")) {
        Serial.print("@");
        Serial.print(standartCO2);
        Serial.print(":");
        Serial.print(standartPH);
        Serial.println("@");

      }

      improvedDelay(200);
      Serial.end();
      Serial.begin(9600);

    }

  // Условие по времени
  if (false) {
    improvedDelay(1000);
    Serial.end();
    Serial.begin(9600);

    Serial.println("-RequestData-");
    improvedDelay(1000);
    digitalWrite(SERIAL_LED, HIGH);   

    if (Serial.available()) {

      String expression = "";

      expression = Serial.readStringUntil('*');
      expression = Serial.readStringUntil('*');
      
      improvedDelay(1000);
      digitalWrite(SERIAL_LED, LOW);   
      Serial.end();
      Serial.begin(9600);

      expression = expression.substring(expression.indexOf(':') + 1, expression.length());

      pHValue = expression.substring(0, expression.indexOf(":")).toDouble();
      expression = expression.substring(expression.indexOf(':') + 1, expression.length());

      Etemp = expression.substring(0, expression.indexOf(":")).toDouble();
      expression = expression.substring(expression.indexOf(':') + 1, expression.length());

      Wtemp = expression.substring(0, expression.indexOf(":")).toDouble();
      expression = expression.substring(expression.indexOf(':') + 1, expression.length());

      ppm = expression.substring(0, expression.indexOf(":")).toInt();
      expression = expression.substring(expression.indexOf(':') + 1, expression.length());

      tdsSensor = expression.substring(0, expression.length()).toDouble();
      expression = "";
      
      Serial.println(pHValue);
      Serial.println(tdsSensor);
    }
  
  }

}

/*
* Улучшенный метод ожидания
* Использовать только его, чтобы не ломать счёт времени 
*/
void improvedDelay(unsigned int waitTime) {
    globalTimeBufferMillis = millis();
    boolean cooldownState = true;

    while (cooldownState) {
        if (millis() - globalTimeBufferMillis > waitTime) 
            cooldownState = false;
    }
}