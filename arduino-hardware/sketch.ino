void setup() {
    pinMode(A0, INPUT);
}

void loop() {
    Serial.println(analogRead(A0));
}