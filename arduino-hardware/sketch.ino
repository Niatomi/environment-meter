// #include <MHZ.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

/* PH Meter using PH Sensor
*
* https://bestengineeringprojects.com/arduino-ph-meter-using-ph-sensor/
*
*/
#define T1 A2 
#define T2 5
// #define P0 A0

/*
* C02 Meter
*
* https://itnan.ru/post.php?c=2&p=272090
*/
#define CO2 A3
SoftwareSerial mySerial(A0, A1); // TX, RX
unsigned int ppm = 0;
byte cmd[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79}; 
unsigned char response[9];

/*
* TDS
*
* http://wiki.amperka.ru/products:troyka-tds-sensor
*/
#define TDS A2
float tdsSensor;

LiquidCrystal_I2C lcd (0x27, 20, 4);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(TDS, INPUT);
  pinMode(T1, INPUT);
  pinMode(T2, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);

}

void loop() {
  getPPM();
  getPPMCO2();

  printDataOnLcd();
  delay(10000);
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
* (American Society of Heating, Refrigerating and Air-Conditioning Engineers) и 
* OSHA (Occupational Safety & Health Administration).
*
* 1000 — 2500 ppm: Общая вялость, снижение концентрации внимания, возможна головная боль.
*
* 2500 — 5000 ppm: Возможны нежелательные эффекты на здоровье.
* 
*/
void getPPM() 
{
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
}

void printDataOnLcd() {
  lcd.clear();
  lcd.setCursor(0, 0);
  // lcd.print("C02: ");
  lcd.print(ppm);
  // lcd.setCursor(9, 0);
  // lcd.print("ppm");

  lcd.setCursor(0, 1);
  // lcd.print("TDS: ");
  lcd.print(tdsSensor);
  // lcd.setCursor(9, 1);
  // lcd.print("ppm");

}

void getPPMCO2() {

  int valueSensor = analogRead(TDS);
  float voltageSensor = valueSensor * 5 / 1024.0;
  tdsSensor = (133.42 * pow(voltageSensor, 3) - 255.86 * pow(voltageSensor, 2) + 857.39 * voltageSensor) * 0.5;

}
