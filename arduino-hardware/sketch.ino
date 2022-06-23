#include <LiquidCrystal_I2C.h>
#define TDS A1 

LiquidCrystal_I2C lcd (0x27, 20, 4);


void setup() {
    Serial.begin(9600);

    pinMode(TDS, INPUT);
    
    lcd.init();
    lcd.backlight();
}

void loop() {
    lcd.setCursor(0, 0);
    lcd.print(analogRead(TDS));
    delay(250);
    lcd.clear();
}