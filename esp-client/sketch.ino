#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>        
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include "WiFiManager.h"          
#include <WiFiClient.h>
#include <TimeLib.h>
#include <Wire.h>

#define HTTP_LED D8
#define FETCH_LED D7

void configModeCallback (WiFiManager *myWiFiManager) {
  WiFi.softAPIP();
  myWiFiManager->getConfigPortalSSID();
}

void transmitData(String data) {
  digitalWrite(FETCH_LED, HIGH);
  Wire.beginTransmission(8);  
  Wire.println(data);              
  Wire.endTransmission();
  digitalWrite(FETCH_LED, LOW);

}

WiFiClient client; 


int standartCO2 = 1500;
float standartPH = 6.1;

float pHValue = 0.00;
float Etemp = 0.00;
float Wtemp = 0.00;
int ppm = 0;
float tdsSensor = 0.00;

int refC02 = 0; 
float refNormalPh = 0; 
float refVolume = 0;

String regionID = "51"; 

unsigned long lastTimeSync;
unsigned long globalTimeBufferMillis = 0;

unsigned long awaitingCurrentTime;
unsigned long lastTimeCheckOnReferenceUpdate = 0;

boolean isNeedToUpdate = false;

IPAddress local(192, 168, 0, 14);
uint16_t port = 8080;
void getReferenceData() {

  if (client.connect(local, port)) {
    digitalWrite(HTTP_LED, HIGH);
    // Send HTTP request
    client.println("GET /esp/getReferenceData HTTP/1.0\r\n");
    client.println("Host: " + local.toString() + ":8080");

    // Skip HTTP headers
    char endOfHeaders[] = "\r\n\r\n";
    if (!client.find(endOfHeaders)) {                      
      // Serial.println("Invalid response");
      return;
    }

    const size_t capacity = 96;                                            
    DynamicJsonDocument doc(capacity); 
    doc.clear();

    deserializeJson(doc, client);
    client.stop();

    refC02 = doc["c02"].as<int>();
    refNormalPh = doc["normalPh"].as<float>();
    refVolume = doc["volume"].as<float>();

    doc.clear();
    digitalWrite(HTTP_LED, LOW);

  }

}

void updateRefernceCycle() {
  getReferenceData();
  sendStateReferenceUpdate();
  String msg = "Ref:";
  msg.concat(refC02);
  msg.concat(":");
  msg.concat(refNormalPh);
  msg.concat(":");
  msg.concat(refVolume);
  msg.concat("$");
  transmitData(msg);

}

void sendStateReferenceUpdate() {

  if (client.connect(local, port)) {
    digitalWrite(HTTP_LED, HIGH);

    // Write response headers
    client.println("POST /esp/stateReferenceUpdateState HTTP/1.1");
    client.println("Host: " + local.toString() + ":8080");
    client.println();
    client.stop();

    digitalWrite(HTTP_LED, LOW);
  }

}
void sendDataOnServer() {

  if (client.connect(local, port)) {
    digitalWrite(HTTP_LED, HIGH);
    StaticJsonDocument<100> docOut;

    docOut["environmentTemperature"] = Etemp;
    docOut["liquidTemperature"] = Wtemp;
    docOut["tds"] = tdsSensor;
    docOut["co2"] = ppm;
    docOut["ph"] = pHValue;

    // Write response headers
    client.println("POST /esp/sendSensorsData HTTP/1.1");
    client.println("Host: " + local.toString() + ":8080");
    client.println("Content-Type: application/json");
    client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(measureJsonPretty(docOut));
    client.println();

    serializeJsonPretty(docOut, client);

    client.stop();
    digitalWrite(HTTP_LED, LOW);
  }
}

void setup() {
  pinMode(HTTP_LED, OUTPUT);
  pinMode(FETCH_LED, OUTPUT);

  digitalWrite(HTTP_LED, HIGH);
  digitalWrite(FETCH_LED, HIGH);

  Serial.begin(9600);
  Serial.setDebugOutput(true); 
  Wire.begin();
   
  WiFiManager wifiManager;
  wifiManager.setDebugOutput(false);
  
  //reset settings - for testing
  // wifiManager.resetSettings();

  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);
  transmitData("WiFiConfigStart");

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect("ESP8266 ConfigMe")) {
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(1000);
  } 
  transmitData("WiFiConfigEnd");


  syncTime();
  getSchedule();

  updateRefernceCycle();

  setCurrentAwaitingTime();

  digitalWrite(HTTP_LED, LOW);
  digitalWrite(FETCH_LED, LOW);

}


void loop() {
  awaitEvent();
}

void awaitEvent() {

  // Синхронизируем время каждую неделю
  if (now() - lastTimeSync >= 604800) {
    syncTime();
  }

  // По расписанию отправляем данные на сервер
  if (now() >= awaitingCurrentTime) {
    fetchData();
    sendDataOnServer();
    setCurrentAwaitingTime();
  }

  if (now() - lastTimeCheckOnReferenceUpdate >= 180) {
    lastTimeCheckOnReferenceUpdate = now();
    checkOnReferenceUpdate();
    if (isNeedToUpdate) {
      updateRefernceCycle();
    }
  }

}


void checkOnReferenceUpdate() {

  if (client.connect(local, port)) {
    digitalWrite(HTTP_LED, HIGH);
    // Send HTTP request
    client.println("GET /esp/checkOnReferenceUpdate HTTP/1.0\r\n");
    client.println("Host: " + local.toString() + ":8080");

    // Skip HTTP headers
    char endOfHeaders[] = "\r\n\r\n";
    if (!client.find(endOfHeaders)) {                      
      // Serial.println("Invalid response");
      return;
    }

    const size_t capacity = 48;                                            
    DynamicJsonDocument doc(capacity); 
    doc.clear();
    deserializeJson(doc, client);
    client.stop();
    doc.clear();

    if (doc["updatable"].as<boolean>())
      isNeedToUpdate = true;

    digitalWrite(HTTP_LED, LOW);

  }

}


void fetchData() {
  digitalWrite(FETCH_LED, HIGH);
  transmitData("ReadSensors");
  improvedDelay(1000);
  Wire.requestFrom(8, 50);
  String str = "";
  while (Wire.available()) { 
    str = Wire.readStringUntil('$'); 
    str = Wire.readStringUntil('$'); 
    parseData(str);    
    str = "";
    printCurrentDataIntoSerial();

    while (Wire.available() > 0) {
      char c = Wire.read();
    }
    
  }
  digitalWrite(FETCH_LED, LOW);

  sendDataOnServer();

}

void parseData(String str) {

    ppm = str.substring(0, str.indexOf(':')).toInt();
    str = str.substring(str.indexOf(':') + 1, str.length());

    pHValue = str.substring(0, str.indexOf(':')).toFloat();
    str = str.substring(str.indexOf(':') + 1, str.length());

    Etemp = str.substring(0, str.indexOf(':')).toFloat();
    str = str.substring(str.indexOf(':') + 1, str.length());

    Wtemp = str.substring(0, str.indexOf(':')).toFloat();
    str = str.substring(str.indexOf(':') + 1, str.length());

    tdsSensor = str.substring(0, str.indexOf(':')).toFloat();

}
void printCurrentDataIntoSerial() {
    Serial.println(now());
    Serial.print("ppm: ");
    Serial.println(ppm);
    Serial.print("tdsSensor: ");
    Serial.println(tdsSensor);
    Serial.print("phValue: ");
    Serial.println(pHValue);
    Serial.print("ETemp: ");
    Serial.println(Etemp);
    Serial.print("WTemp: ");
    Serial.println(Wtemp);
    Serial.println();
}

/*
* Получаем расписание проверок
*/
const size_t capacity = 256;                                            
DynamicJsonDocument schedule(capacity);     
void getSchedule() {

  if (client.connect(local, port)) {
    digitalWrite(HTTP_LED, HIGH);
    // Send HTTP request
    client.println("GET /esp/getTimeSchedule HTTP/1.0\r\n");
    client.println("Host: " + local.toString() + ":8080");

    // Skip HTTP headers
    char endOfHeaders[] = "\r\n\r\n";
    if (!client.find(endOfHeaders)) {                      
      // Serial.println("Invalid response");
      return;
    }
    schedule.clear();
    deserializeJson(schedule, client);
    client.stop();
    digitalWrite(HTTP_LED, LOW);
  }
  
}

/*
* Устанавливаем минимальное время для ожидания из расписания проверок
*/
int currentTimeIndex = -1;
void setCurrentAwaitingTime() {
  currentTimeIndex++;
  if (currentTimeIndex == 10) {
    getSchedule();
    currentTimeIndex = 0;
  }

  awaitingCurrentTime = schedule["listOfSchedules"][currentTimeIndex].as<long>();
  
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

IPAddress local(192, 168, 137, 1);
uint16_t port = 8080;
void sendDataOnServer() {

      Serial.print("In method");
    if (client.connect(local, port)) {
      Serial.print("Sending data");
        digitalWrite(HTTP_LED, HIGH);
        StaticJsonDocument<100> docOut;

        docOut["environmentTemperature"] = Etemp;
        docOut["liquidTemperature"] = Wtemp;
        docOut["tds"] = tdsSensor;
        docOut["co2"] = ppm;
        docOut["ph"] = pHValue;

        // Write response headers
        client.println("POST /esp/sendSensorsData HTTP/1.1");
        client.println("Host: " + local.toString() + ":8080");
        client.println("Content-Type: application/json");
        client.println("Connection: close");
        client.print("Content-Length: ");
        client.println(measureJsonPretty(docOut));
        client.println();

        // client.stop();

        serializeJsonPretty(docOut, client);

        client.stop();
        digitalWrite(HTTP_LED, LOW);
        
    }

}