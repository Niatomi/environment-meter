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


int standartCO2 = 1500;
float standartPH = 6.1;

float pHValue = 0.00;
float Etemp = 0.00;
float Wtemp = 0.00;
int ppm = 0;
float tdsSensor = 0.00;

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

  digitalWrite(HTTP_LED, LOW);
  digitalWrite(SERIAL_LED, LOW);
}

void loop() {

  // transmitData("Aboba");

  fetchData();

  delay(10000);

}


void fetchData() {
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