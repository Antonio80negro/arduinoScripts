#include <SPI.h>
#include <RFID.h>

RFID rfid(10,5); 
String tapparella1 = "000,000,000,000,000"; //lettura stringa da NFC
int codice_tap1; //stringa da NFC convertita in int

//le seguenti costanti sono i valori (int) degli NFC attaccati alla tapparella 
const int tap1_99 = -6214; // costante per tapparella completamente chiusa
const int tap1_88 = 3787; 
const int tap1_77 = 13668;
const int tap1_66 = 23669;
const int tap1_55 = -31866;
const int tap1_44 = -1871;
const int tap1_33 = 8130;
const int tap1_22 = 18131;
const int tap1_11 = 28140;
const int tap1_00 = -27395; //costante per tapparella completamente aperta

unsigned int comando_tap1 = 4;  //variabile che indica la posizione indicata dal comando (da scrivere)
unsigned int posizione_tap1 = 9; //variabile che indica la posizione letta dalla tapparella (letta)

unsigned int lenghtcode = 5; //lunghezza del vettore rfid.num

void setup()
{ 
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
  pinMode(4, OUTPUT); //da questo PIN parte il comando UP
  pinMode(5, OUTPUT); //da questo PIN parte il comando DOWN
  pinMode(6, INPUT); //a questo PIN collego il pulsante a parete UP
  pinMode(3, INPUT); //a questo PIN collego il pulsante a parete DOWN
  digitalWrite(4, LOW);
  digitalWrite(5,LOW);
}

void loop() {
    leggi_comando();
 //   Serial.println("Eccoci:");
//    delay(5000); //ferma per 5 secondi in caso di debug (togliere il commento a inizio linea)
    posizione_tap1 = leggi_posizione(); //recupero la posizione attuale della tapparella (globale?)
    stampa_posizione();
    while (posizione_tap1 < comando_tap1 || digitalRead(6) == HIGH) { //questo è il ciclo di apertura tapparella 
                                             //dovrò aggiungere un operatore OR per gestire il pulsante di apertura
                                             //ovviamente durante la pressione di quel pulsante la variabile comando_tap1 si aggiornerà
                                             //in automatico --> comando_tap1 = posizione_tap1;
          digitalWrite(5,LOW);
          digitalWrite(4,HIGH);
          posizione_tap1 = leggi_posizione();
          leggi_comando();
          if (digitalRead(6) == HIGH) {comando_tap1 = posizione_tap1; Serial.println("       U P ");} 
    stampa_posizione(); 
    }
    while (posizione_tap1 > comando_tap1 || digitalRead(3) == HIGH) { //questo è il ciclo di chiusura tapparella
                                             //dovrò aggiungere un operatore OR per gestire il pulsante di chiusura
                                             //ovviamente durante la pressione di quel pulsante la variabile comando_tap1 si aggiornerà
                                             //in automatico --> comando_tap1 = posizione_tap1;
          digitalWrite(4,LOW);
          digitalWrite(5,HIGH);
          posizione_tap1 = leggi_posizione();
          leggi_comando();
          if (digitalRead(3) == HIGH) {comando_tap1 = posizione_tap1; Serial.println("       DOWN");}
//ogni tanto si attiva il pulsante DOWN... bisogna evitare i falsi contatti
    stampa_posizione();
    }    
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
}

unsigned int leggi_posizione()
{
     if (rfid.isCard()) {
          if (rfid.readCardSerial()) {
                        tapparella1 = String(rfid.serNum[0] * 100000000 + rfid.serNum[1] * 1000000 + rfid.serNum[2] * 10000 + rfid.serNum[3] * 100 + rfid.serNum[4]);
                        codice_tap1 = tapparella1.toInt();
                          switch (codice_tap1) {     
                          case tap1_99: {posizione_tap1 = 9; //Serial.print(codice_tap1);Serial.print("-99-");Serial.println(posizione_tap1); 
                                break;}
                          case tap1_88: {posizione_tap1 = 8; //Serial.print(codice_tap1);Serial.print("-88-");Serial.println(posizione_tap1); 
                                break;}
                          case tap1_77: {posizione_tap1 = 7; //Serial.print(codice_tap1);Serial.print("-77-");Serial.println(posizione_tap1);
                                break;}
                          case tap1_66: {posizione_tap1 = 6; //Serial.print(codice_tap1);Serial.print("-66-");Serial.println(posizione_tap1);
                                break;}
                          case tap1_55: {posizione_tap1 = 5; //Serial.print(codice_tap1);Serial.print("-55-");Serial.println(posizione_tap1);
                                break;}
                          case tap1_44: {posizione_tap1 = 4; //Serial.print(codice_tap1);Serial.print("-44-");Serial.println(posizione_tap1);
                                break;}
                          case tap1_33: {posizione_tap1 = 3; //Serial.print(codice_tap1);Serial.print("-33-");Serial.println(posizione_tap1);
                                break;}
                          case tap1_22: {posizione_tap1 = 2; //Serial.print(codice_tap1);Serial.print("-22-");Serial.println(posizione_tap1);
                                break;}
                          case tap1_11: {posizione_tap1 = 1; //Serial.print(codice_tap1);Serial.print("-11-");Serial.println(posizione_tap1);
                                break;}
                          case tap1_00: {posizione_tap1 = 0; //Serial.print(codice_tap1);Serial.print("-00-");Serial.println(posizione_tap1);
                                break;}
                        }
          }
    }
    
    delay(100); //(bastano 10 letture al secondo)
    rfid.halt();
    return posizione_tap1; //restituisco il valore della posizione della tapparella
 //   rfid.halt();
 }
 
 void stampa_posizione() {
    Serial.print("Posizione: ");
    Serial.print(posizione_tap1);
    Serial.print(" - Comando: ");
    Serial.println(comando_tap1);
}

void leggi_comando() {
      if (Serial.available()) {
        switch (Serial.read()) {
          case '0': comando_tap1 = 0; break;
          case '1': comando_tap1 = 1; break;
          case '2': comando_tap1 = 2; break;
          case '3': comando_tap1 = 3; break;
          case '4': comando_tap1 = 4; break;
          case '5': comando_tap1 = 5; break;
          case '6': comando_tap1 = 6; break;
          case '7': comando_tap1 = 7; break;
          case '8': comando_tap1 = 8; break;
          case '9': comando_tap1 = 9; break;
        } // aggiunta la funzione di lettura comando da esterno (un numero da 0 a 9 che entra dalla porta seriale)
    }
}

