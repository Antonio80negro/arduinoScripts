/*
  Traffic Light
  
  You can switch lights OFF, sending '0' (zero) on the serial port;
  You can switch ligths ON again, sending '1' (one) on the serial port.
    
  by Antonio Negro (antonio80.negro@gmail.com)
 */


void setup() {
  Serial.begin(9600);
  for(int PINcounter = 2; PINcounter<5; PINcounter++) {
   pinMode(PINcounter, OUTPUT);
   digitalWrite(PINcounter, LOW);
  }
  pinMode(9, INPUT);
}

void LightOff() {
  int accendi = 0;
  delay(200);
  Serial.println("Traffic light has been switched OFF");
      for(int PINcounter = 2; PINcounter<5; PINcounter++) {
      digitalWrite(PINcounter, LOW);
    }
  int alternatore = 0;
  long previousMillis = millis();
  do {
    if (Serial.read()=='1' || digitalRead(9) == HIGH) {
        accendi = 1;
        delay(200);

    }
    else {
       if (alternatore == LOW && millis() > previousMillis + 500) {
          alternatore = HIGH;
          previousMillis = millis();
        }
        else if (alternatore == HIGH && millis() > previousMillis + 500) {
          alternatore = LOW;
          previousMillis = millis();
         };
         digitalWrite(3,alternatore);
    }
  } while (accendi != 1); // controllare 9 (0 o 1?)
  Serial.println("Traffic light is now ON");
  for (int PINcounter = 2; PINcounter < 5; PINcounter++) {
    digitalWrite(PINcounter,LOW);
  }
}

void loop() {
 digitalWrite(4, HIGH);   // turn RED LED on (HIGH is the voltage level)
 Serial.println("Traffic Light --> RED");
 long PreviousMillis = millis();
 while (millis() < PreviousMillis + 5000) {     //wait 5 seconds
   if(Serial.read() == '0' || digitalRead(9)== HIGH) { 
     LightOff();
     goto RESET;
   }
 }
 digitalWrite(4, LOW);    // turn RED LED off
 digitalWrite(2, HIGH);   //turn GREEN LED on
 Serial.print("Traffic Light --> GREEN");  
 PreviousMillis = millis();
 while (millis() < PreviousMillis + 4500) {
   if(Serial.read() == '0' || digitalRead(9)== HIGH) {
     Serial.println();
     LightOff();
     goto RESET;
   }
 }
 digitalWrite(3, HIGH);    // turn YELLOW LED on
 Serial.println("... YELLOW");
 PreviousMillis = millis();
 while (millis() < PreviousMillis + 1500) {
   if(Serial.read() == '0' || digitalRead(9)== HIGH) { //
     LightOff();
     goto RESET;
   }
 } 
 digitalWrite(2, LOW);
 digitalWrite(3, LOW);    //turn GREEN and YELLOW LED off
RESET:;
}
