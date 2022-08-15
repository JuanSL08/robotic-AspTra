int IN1 = 13;       // L298N: pin IN1 a pin digital 13
int IN2 = 12;       // L298N: pin IN2 a pin digital 12
int ENA = 11;       // L298N: pin ENA a pin digital PWM 11
int IN3 = 1;        // L298N: pin IN3 a pin digital 1
int IN4 = 0;        // L298N: pin IN4 a pin digital 0
int ENB = 10;       // L298N: pin ENA a pin digital PWM 10
int VELOCIDAD;      // variable para almacenar valor de velocidad

int pinLedRojo = 4;   // LED RED: pin voltage a pin digital 4
int pinLedVerde = 2;  // LED GREEN: pin voltage a pin digital 4

void setup(){
  pinMode(IN1, OUTPUT);   // IN1 como salida  
  pinMode(IN2, OUTPUT);   // IN2 como salida
  pinMode(ENA, OUTPUT);   // ENA como salida
  pinMode(IN3, OUTPUT);   // IN3 como salida
  pinMode(IN4, OUTPUT);   // IN4 como salida
  pinMode(ENB, OUTPUT);   // ENB como salida

  pinMode(pinLedRojo, OUTPUT);    // LED RED como salida
  pinMode(pinLedVerde, OUTPUT);   // LED GREEN como salida
}

void loop(){                  // loop de prueba para modulo de LOCOMOCION
  VELOCIDAD = 150;            // valor de velocidad para PWM de ENA y ENB

  vehiculoAvanza(VELOCIDAD);
  delay(5000);
  vehiculoDetente();
  delay(8000);
  
}

void vehiculoAvanza(int velocidad){     // funcion para giro antihorario de los 4 motorreductores
  digitalWrite(pinLedRojo, HIGH);       // encender Led Rojo
  digitalWrite(pinLedVerde, LOW);             // apagar Led Verde
  
  analogWrite(ENA, velocidad);          // velocidad mediante PWM en ENA
  digitalWrite(IN1, LOW);               // IN1 a cero logico
  digitalWrite(IN2, HIGH);              // IN2 a uno logico
  analogWrite(ENB, velocidad);          // velocidad mediante PWM en ENB
  digitalWrite(IN3, LOW);               // IN3 a cero logico
  digitalWrite(IN4, HIGH);              // IN4 a uno logico
}

void vehiculoVolteaIzquierda(int velocidad){  // funcion para giro antihorario de los motores del lado derecho
  digitalWrite(pinLedRojo, HIGH);             // encender Led Rojo
  digitalWrite(pinLedVerde, LOW);             // apagar Led Verde
  
  analogWrite(ENA, velocidad);                // velocidad mediante PWM en ENA
  digitalWrite(IN1, LOW);                     // IN1 a cero logico
  digitalWrite(IN2, HIGH);                    // IN2 a uno logico
  analogWrite(ENB, 0);                        // deshabilita motores del lado izquierdo
}

void vehiculoVolteaDerecha(int velocidad){    // funcion para giro antihorario de los motores del lado izquierdo
  digitalWrite(pinLedRojo, HIGH);             // encender Led Rojo
  digitalWrite(pinLedVerde, LOW);             // apagar Led Verde
  
  analogWrite(ENB, velocidad);                // velocidad mediante PWM en ENB
  digitalWrite(IN3, LOW);                     // IN3 a cero logico
  digitalWrite(IN4, HIGH);                    // IN4 a uno logico
  analogWrite(ENB, 0);                        // deshabilita motores del lado derecho
}

void vehiculoRetrocede(int velocidad){        // funcion para giro horario de los 4 motorreductores
  digitalWrite(pinLedRojo, HIGH);             // encender Led Rojo
  digitalWrite(pinLedVerde, LOW);             // apagar Led Verde
  
  analogWrite(ENA, velocidad);                // velocidad mediante PWM en ENA
  digitalWrite(IN1, HIGH);                    // IN1 a cero logico
  digitalWrite(IN2, LOW);                     // IN2 a uno logico
  analogWrite(ENB, velocidad);                // velocidad mediante PWM en ENB
  digitalWrite(IN3, HIGH);                    // IN3 a cero logico
  digitalWrite(IN4, LOW);                     // IN4 a uno logico
}

void vehiculoDetente(){                       // funcion que detiene los 4 motorreductores
  analogWrite(ENA, 0);                        // deshabilita motores del lado derecho
  analogWrite(ENB, 0);                        // deshabilita motores del lado izquierdo

  digitalWrite(pinLedRojo, LOW);              // apagar Led Rojo
  digitalWrite(pinLedVerde, HIGH);            // encender Led Verde
}

void vehiculoRutaA(int velocidad){            // creacion de ruta a seguir llamada 'A'
  vehiculoAvanza(velocidad);
  delay(4000);
  vehiculoVolteaIzquierda(velocidad);
  delay(2500);
  vehiculoAvanza(velocidad);
  delay(6000);
  vehiculoDetente();
}

void vehiculoRutaB(int velocidad){            // creacion de ruta a seguir llamada 'B'
  int velRetroceso = velocidad - 30;
  vehiculoRetrocede(velRetroceso);
  delay(5000);
  vehiculoVolteaIzquierda(velocidad);
  delay(2500);
  vehiculoAvanza(velocidad);
  delay(6000);
  vehiculoDetente();
}

void vehiculoRutaC(int velocidad){            // creacion de ruta a seguir llamada 'C'
  vehiculoAvanza(velocidad);
  delay(6000);
  vehiculoVolteaDerecha(velocidad);
  delay(2500);
  vehiculoAvanza(velocidad);
  delay(8000);
  vehiculoDetente();
}
