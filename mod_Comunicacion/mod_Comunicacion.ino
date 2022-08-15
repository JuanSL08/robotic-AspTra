#include <SoftwareSerial.h>

SoftwareSerial miBT(7, 6);      // establecer pines TXD al pin 7 y RXD al pin 6
char DATO = 0;
int pinBUZZER = 3;

void setup() { 
  miBT.begin(38400);            // asignar velocidad de comunicacion con HC-05
  pinMode(pinBUZZER, OUTPUT);   
}

void loop() {                   // loop de prueba para modulo de COMUNICACION
  if(miBT.available()){         // condicional para constatar comunicacion de HC-05 con aplicativo
    DATO = miBT.read();         // asignar la lectura del dato o la variable enviada por aplicativo
    
    if(DATO == '1')
      buzzerParpadea();

    if(DATO == '2')
      buzzerApagado();
  }
}

void buzzerParpadea(){
  analogWrite(pinBUZZER, 60);   // encender el buzzer con un voltaje de 1.8v
}

void buzzerApagado(){
  analogWrite(pinBUZZER, 0);    // apagar buzzer
}
