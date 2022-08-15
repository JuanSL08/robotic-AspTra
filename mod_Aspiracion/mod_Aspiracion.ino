int pinFAN = 5;         // FAN-PC a traves de MODULO RELE: pin S en pin 5

void setup() {
  pinMode(pinFAN, OUTPUT);    // fan como salida
  Serial.begin(9600);         // inicializacion de comunicacion serial a 9600 bps
}

void loop() {           // loop de prueba para modulo de ASPIRACION
  encenderFan();        // llamado a función encenderFan
  delay(6000);          // demora de 6 segundos
  
  apagarFan();          // llamado a función apagarFan
  delay(3000);          // demora de 3 segundos
}

void encenderFan(){             // creacion de funcion con objetivo: ENCENDER EL VENTILADOR
  digitalWrite(pinFAN, HIGH);
}

void apagarFan(){               // creacion de funcion con objetivo: APAGAR EL VENTILADOR
  digitalWrite(pinFAN, LOW);
}
