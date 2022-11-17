#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int sensorPin = A0;

void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);
  lcd.print("by Andronio 2014");
  Serial.println();
  Serial.println("Termometro 1.0 - by Andronio 2014");
  lcd.setCursor(0,1);
  for (int puntino = 0; puntino<16; puntino++) {
    lcd.print(".");
    Serial.print(".");
    delay(200);
  }
  Serial.println();
}

void loop() {
  int sensorVal = analogRead(sensorPin);
  float sensorVolt = (sensorVal/1024.0) * 5.0;
  float temperature = (sensorVolt - .5) * 100;
  float tempmed = temperature;
  
  for (int contatore = 0; contatore<10; contatore++) {
    sensorVal = analogRead(sensorPin);
    sensorVolt = (sensorVal/1024.0) * 5.0;
    temperature = (sensorVolt - .5) * 100;
    tempmed = (tempmed + temperature);
    delay(100);
  }
  
  temperature = tempmed/10;
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperatura:");
  lcd.setCursor(0,1);
  lcd.print(temperature);
  lcd.print(" gradi");
  Serial.print("La temperatura rilevata e' ");
  Serial.print(temperature);
  Serial.println(" gradi Celsius.");
  //delay(1000);
}
