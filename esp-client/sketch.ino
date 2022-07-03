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
#define SERIAL_LED D7

void configModeCallback (WiFiManager *myWiFiManager) {
  WiFi.softAPIP();
  myWiFiManager->getConfigPortalSSID();
}

void transmitData(String data) {

  Wire.beginTransmission(8);  
  Wire.println(data);              
  Wire.endTransmission();

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

  // Serial.setTimeout(5);

  Serial.begin(9600);
  Serial.setDebugOutput(true); 
  Wire.begin();
   
  WiFiManager wifiManager;
  wifiManager.setDebugOutput(false);
  
  //reset settings - for testing
  wifiManager.resetSettings();

  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);

  Serial.println("WiFiConfigStart");
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
  Serial.println("WiFiConfigEnd");
  transmitData("WiFiConfigEnd");

  // Wire.setTimeout(100);

  // syncTime();
  getSchedule();

  digitalWrite(HTTP_LED, LOW);
  digitalWrite(SERIAL_LED, LOW);
}


int x = 1024;
void loop() {

  // transmitData("Aboba");

  // fetchData();

  delay(3000);

}



void fetchData() {
  Wire.requestFrom(8, 70);    // request 6 bytes from peripheral device #8
  String str = "";
  while (Wire.available()) { // peripheral may send less than requested
    str = Wire.readStringUntil('$'); // receive a byte as character
    str = Wire.readStringUntil('$'); // receive a byte as character
    str = str.substring(0, str.lastIndexOf('.') + 3);
    // str.concat(c);
    // Serial.print(c);         // print the character
  }
  Serial.println(str);

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