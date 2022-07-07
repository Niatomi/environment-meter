#include <DallasTemperature.h>
#include <math.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <OneWire.h>
#include <Wire.h>

#define UPDATE_LIGHT 8
#define MANUAL_CHECK_BUTTON 2
#define ZOOMER 9

/* PH Meter using PH Sensor
*
* https://bestengineeringprojects.com/arduino-ph-meter-using-ph-sensor/
*
*/
#define analogTemPin A3
#define ONE_WIRE_BUS 3
#define analogPhPin A1
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire); 
long phTot, temTot;
float phAvg, temAvg;
int x;
// Final
float pHValue = 0;
float Etemp = 0;
float Wtemp = 0;
// TODO: Поменять коэффициенты
const float C = 21.34; //Constant of straight line (Y = mx + C)
const float m = -5.70; // Slope of straight line (Y = mx + C)


/*
* C02 Meter
*
* https://itnan.ru/post.php?c=2&p=272090
*/
#define CO2 A3
SoftwareSerial mySerial(7, 6); // TX, RX
//Final
int ppm = 0;
byte cmd[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79}; 
unsigned char response[9];

/*
* TDS
*
* http://wiki.amperka.ru/products:troyka-tds-sensor
*/
#define TDS A2
// Final
float tdsSensor = 0.00;

LiquidCrystal_I2C lcd (0x27, 20, 4);

volatile unsigned long globalTimeBufferMillis = 0;

byte customChar[] = {
  B00000,
  B01110,
  B10001,
  B00100,
  B01010,
  B00000,
  B00100,
  B00000
};

boolean cooldownState;

// Standarts
int refC02 = 0; 
float refNormalPh = 0; 
float refVolume = 0;

void setup() {  
  Serial.setTimeout(5);
  Serial.begin(9600);
  mySerial.begin(9600);

  // lcd.createChar(0, customChar);
  lcd.init();
  lcd.createChar(0, customChar);
  lcd.home();

  sensors.begin();
  pinMode(TDS, INPUT);
  pinMode(UPDATE_LIGHT, OUTPUT);
  pinMode(MANUAL_CHECK_BUTTON, INPUT_PULLUP);


  digitalWrite(UPDATE_LIGHT, LOW);

  attachInterrupt(0, manuallCheck, FALLING);

  // lcd.init();
  lcd.backlight();
  // lcd.clear();
  // lcd.setCursor(0, 0);

  Wire.begin(51);                // join i2c bus with address #4         
  // Wire.setTimeout(100);
  Wire.onRequest(requestHandler);
  Wire.onReceive(receiveHandler);

}

int aboba = 1024;
boolean isWiFiAlert = false;
boolean isSuccessfulConnection = false;
void receiveHandler (int size) {
  Serial.println("receiveHandler");

  String buff = "";
  while (Wire.available() > 0) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    buff.concat(c);         // print the character
  }
  Serial.println(buff);


  if (buff.equals("WiFiConfigStart\r\n")) {
    isWiFiAlert = true;
    cooldownState = false;
  }

  if (buff.equals("WiFiConfigEnd\r\n")) {
    isWiFiAlert = false;
    isSuccessfulConnection = true;
    cooldownState = false;
  }

  if (buff.equals("ReadSensors\r\n")) {
    cooldownState = false;
  }

  if (buff.substring(0, 3).equals("Ref")) {
    buff = buff.substring(buff.indexOf(':') + 1, buff.length());

    int refC02 = buff.substring(0, buff.indexOf(':')).toInt(); 
    buff = buff.substring(buff.indexOf(':') + 1, buff.length());
    
    float refNormalPh = buff.substring(0, buff.indexOf(':')).toFloat();
    
    float refVolume = buff.substring(buff.indexOf(':') + 1, buff.indexOf('$')).toFloat();
  }

}

void requestHandler() {
  Serial.println("requestHandler");
  
  Wire.print("$");
  Wire.print(ppm);
  Wire.print(":");
  Wire.print(pHValue);
  Wire.print(":");
  Wire.print(Etemp);
  Wire.print(":");
  Wire.print(Wtemp);
  Wire.print(":");
  Wire.print(tdsSensor);
  Wire.println("$");

   


}


void manuallCheck() {
  cooldownState = false;
}

void loop() {
  
  if (isWiFiAlert) {
    printWiFiMessageOnLcd();
    improvedDelay(3000);
  }

  if (isSuccessfulConnection) {
    printWiFiSuccessOnLcd();
    improvedDelay(3000);
    isSuccessfulConnection = false;
  }

  getData();
  // alertCO2();
  printDataOnLcd();
  improvedDelay(60000);

}

void printWiFiMessageOnLcd() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(" Connect via Wi-Fi");
  lcd.setCursor(0, 2);
  lcd.print(" ESP8266 ConfigMe");
}

void printWiFiSuccessOnLcd() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(" Successful connect");
  lcd.setCursor(0, 2);
  lcd.print(" to local WiFi");
}

void getPHData() {

  // Финальные переменные
  phTot = 0;
  temTot = 0;
  phAvg = 0;
  temAvg = 0;
 
  //taking 10 sample and adding with 10 milli second delay
  for(x=0; x<10 ; x++)
    {
        phTot += analogRead(analogPhPin);
        temTot += analogRead(analogTemPin);
        improvedDelay(10);
    }
    float temAvg = temTot/10.0;
    float phAvg = phTot/10;
    // float temVoltage = temAvg * (1023.0 / 5000.0); //convert sensor reading into milli volt
    float phVoltage =  phAvg * (5.0 / 1023.0); //convert sensor reading into milli volt
 
    sensors.requestTemperatures(); // Send the command to get temperatures
    Etemp = (temAvg/1023.0)*5.0*1000/10; //convert milli volt to temperature degree Celsius
    pHValue = phVoltage*m+C;
    Wtemp = sensors.getTempCByIndex(0);
    float TempDif = fabs(Etemp-Wtemp); //calculating the absolute value of floating

}

/*
* Собираем информацию со всех датчиков
*/
void getData() {
  getPPMCO2();
  getPPMTDS();
  getPHData();
}

/*
*
* 350 — 450 ppm: Нормальный уровень на открытом воздухе.
*
* < 600 ppm: Приемлемые уровни. Уровень. рекомендованный для спален, детских садов и школ.
*
* 600 — 1000 ppm: Жалобы на несвежий воздух, возможно снижение концентрации внимания.
*
* 1000 ppm: Максимальный уровень стандартов ASHRAE
*
* 1000 — 2500 ppm: Общая вялость, снижение концентрации внимания, возможна головная боль.
*
* 2500 — 5000 ppm: Возможны нежелательные эффекты на здоровье.
* 
*/
void getPPMCO2() 
{
  digitalWrite(UPDATE_LIGHT, HIGH);
  mySerial.write(cmd, 9);
  memset(response, 0, 9);
  mySerial.readBytes(response, 9);
  int i;
  byte crc = 0;
  for (i = 1; i < 8; i++) crc+=response[i];
  crc = 255 - crc;
  crc++;

  if ( !(response[0] == 0xFF && response[1] == 0x86 && response[8] == crc) ) {
    Serial.println("CRC error: " + String(crc) + " / "+ String(response[8]));
  } else {
    unsigned int responseHigh = (unsigned int) response[2];
    unsigned int responseLow = (unsigned int) response[3];
    ppm = (256*responseHigh) + responseLow;
  }
  digitalWrite(UPDATE_LIGHT, LOW);
}

/*
*
* @link https://pronormy.ru/stroitelstvo/zhkh/zhestkost-vody-norma 
* Показатели для PPM  @endlink 
*
*/
void getPPMTDS() {
  digitalWrite(UPDATE_LIGHT, HIGH);
  int valueSensor = analogRead(TDS);
  float voltageSensor = valueSensor * 5 / 1024.0;
  tdsSensor = (133.42 * pow(voltageSensor, 3) - 255.86 * pow(voltageSensor, 2) + 857.39 * voltageSensor) * 0.5;
  digitalWrite(UPDATE_LIGHT, LOW);
}


/*
* Оповещаем пользователя о 
* завышенном колличестве CO2 в воздухе
*/
void alertCO2() {
  if (ppm >= refC02) {
    tone(ZOOMER, 100, 100);
    improvedDelay(200);
    noTone(ZOOMER);
    tone(ZOOMER, 100, 100);
    improvedDelay(200);
    noTone(ZOOMER);
    tone(ZOOMER, 100, 100);
  }
}


/*
* Печатаем информацию на LCD2004
*/
void printDataOnLcd() {
  lcd.clear();
  lcd.blink_off();
  lcd.setCursor(0, 0);
  lcd.print("C02: ");
  lcd.print(ppm);
  lcd.print(" ppm");

  lcd.setCursor(0, 1);
  lcd.print("TDS: ");
  lcd.print(tdsSensor);
  lcd.print(" ppm");

  lcd.setCursor(0, 2);
  lcd.print("PH : ");
  lcd.print(pHValue);

  lcd.setCursor(0, 3);
  lcd.print("E/W: ");
  lcd.print(Etemp);
  lcd.print("/");
  lcd.print(Wtemp);
  lcd.print("");
  lcd.write(B11011111);
  lcd.print("C");

  lcd.setCursor(19, 0);
  lcd.write(0);
  lcd.setCursor(19, 0);
  
  if (isWiFiAlert) {
    lcd.blink_on();
  } else {
    lcd.blink_off();
  } 
    
}

/*
* Улучшенный метод ожидания
* Использовать только его, чтобы не ломать счёт времени 
*/
void improvedDelay(unsigned int waitTime) {
    globalTimeBufferMillis = millis();
    cooldownState = true;

    while (cooldownState) {
        if (millis() - globalTimeBufferMillis > waitTime) 
            cooldownState = false;
    }
}

void waitMicros() {
    for (int i = 0; i < 200; i++) {
        
        unsigned int microsTimerBuffer = micros();
        
        boolean exitState = true;
        while (exitState) {
            if (micros() - microsTimerBuffer > 50000) {
                exitState = false;
            }
        }
    }
}