#include <SoftwareSerial.h>

SoftwareSerial miBT(7, 6);    // establecer pines TXD al pin 7 y RXD al pin 6

void setup() {
  Serial.begin(9600);         // asignar velocidad de comunicacion con el Serial   
  miBT.begin(38400);          // asignar velocidad de comunicacion con HC-05
}

void loop() {
  if(miBT.available()){
    Serial.write(miBT.read());    // lee HC-05 y envia a Arduino
  }

  if(Serial.available()){
    miBT.write(Serial.read());    // lee Arduino y envia a HC-05
  }
}
