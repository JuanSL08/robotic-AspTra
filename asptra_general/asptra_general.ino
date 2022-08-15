#include <SoftwareSerial.h>

// MOD. LOCOMOCION: DECLARACION DE PINES COMO CONSTANTES
const int IN1 = 13;               // L298N: pin IN1 a pin digital 13
const int IN2 = 12;               // L298N: pin IN2 a pin digital 12
const int ENA = 11;               // L298N: pin ENA a pin digital PWM 11
const int IN3 = 2;                // L298N: pin IN3 a pin digital 1
const int IN4 = 4;                // L298N: pin IN4 a pin digital 0
const int ENB = 10;               // L298N: pin ENA a pin digital PWM 10
const int VelAvance = 110;        // constante para la velocidad de avance
const int VelGiro = 90;           // constante para la velocidad de giro
const int VelRetroceso = 70;      // constante para la velocidad de retroceso
// MOD. DETECCION DE OBSTACULOS: DECLARACION DE PINES COMO CONSTANTES
const int pinTRIG = 8;            // HC-SR04: pin trigger a digital pin 8
const int pinECHO = 9;            // HC-SR04: pin echo a digital pin 9
const long distMinima = 25.0;     // DISTANCIA MINIMA ESTABLECIDA
// MOD. ASPIRACION: DECLARACION DE PINES COMO CONSTANTES
const int pinFAN = 5;             // FAN-PC a traves de MODULO RELE: pin S en pin 5
// MOD. COMUNICACION: DECLARACION DE PINES COMO CONSTANTES
SoftwareSerial miBT(7, 6);        // HC-05: pin TXD al pin 7 y RXD al pin 6
// MOD. ESTADO: DECLARACION DE PINES COMO CONSTANTES
const int pinLedRojo = 14;        // LED RED: pin voltage a pin digital 14
const int pinLedVerde = 15;       // LED GREEN: pin voltage a pin digital 15
const int pinBUZZER = 3;          // BUZZER: pin voltage a digital PWM pin 3

// CONSTANTES PARA CONTROL POR APLICATIVO
const char cstControlManual = 'q';
const char cstControlAutomatico = 'e';
const char cstAvanza = 'w';
const char cstDerecha = 'd';
const char cstIzquierda = 'a';
const char cstRetrocede = 's';
const char cstDetente = 'x';
const char cstRutaA = 'l';
const char cstRutaB = 'm';
const char cstRutaC = 'n';
const char cstAspiradorON = 'o';
const char cstAspiradorOFF = 'p';

// DECLARACION DE VARIABLES
int DURACION;                       // variable para almacenar valor de duracion de pulso
long DISTANCIA;                     // variable para almacenar valor de distancia
char DATO = 0;                      // variable para almacenar valor de dato a recibir del HC-05

void setup(){
  Serial.begin(9600);               // inicializacion de comunicacion serial a 9600 bps
  miBT.begin(38400);                // inicializacion velocidad de comunicacion con HC-05
  //MOD. LOCOMOCION: DECLARACION DE TIPO
  pinMode(IN1, OUTPUT);             // IN1 como salida  
  pinMode(IN2, OUTPUT);             // IN2 como salida
  pinMode(ENA, OUTPUT);             // ENA como salida
  pinMode(IN3, OUTPUT);             // IN3 como salida
  pinMode(IN4, OUTPUT);             // IN4 como salida
  pinMode(ENB, OUTPUT);             // ENB como salida
  //MOD. DETECCION DE OBSTACULOS: DECLARACION DE TIPO
  pinMode(pinTRIG, OUTPUT);         // trigger como salida
  pinMode(pinECHO, INPUT);          // echo como entrada
  pinMode(pinBUZZER, OUTPUT);       // buzzer como salida
  //MOD. ASPIRACION: DECLARACION DE TIPO
  pinMode(pinFAN, OUTPUT);          // fan como salida
  //MOD. ESTADO: DECLARACION DE TIPO
  pinMode(pinLedRojo, OUTPUT);      // LED RED como salida
  pinMode(pinLedVerde, OUTPUT);     // LED GREEN como salida
}

void loop(){
  if(miBT.available()){         // condicional para constatar comunicacion de HC-05 con aplicativo
    char DATO_NUEVO = miBT.read();
    if(DATO != DATO_NUEVO){
      DATO = DATO_NUEVO;         // asignar la lectura del dato o la variable enviada por aplicativo
    }
    
    if(DATO == cstAspiradorON){
      encenderFan();
    }

    if(DATO == cstAspiradorOFF){
      apagarFan();
    }

    //LOCOMOCION AUTOMATICA
    // Seguir ruta A
      if(DATO == cstRutaA){
        vehiculoRutaA();
      }
    // Seguir ruta B
      if(DATO == cstRutaB){
        vehiculoRutaB();
      }
    // Seguir ruta C
      if(DATO == cstRutaC){
        vehiculoRutaC();
      }

    //LOCOMOCION MANUAL
    char DAT_TEMP;  
    // Avanzar
      if(DATO == cstAvanza){
        DISTANCIA = obtenerDistancia();
        Serial.println(DISTANCIA);
        while(DISTANCIA > distMinima){
          vehiculoAvanza(VelAvance);
          DISTANCIA = obtenerDistancia();
          DAT_TEMP = miBT.read();
            if(DAT_TEMP == cstDerecha || DAT_TEMP == cstIzquierda || DAT_TEMP == cstRetrocede || DAT_TEMP == cstDetente){
              DISTANCIA = -1.0;
            }
          delay(200);
        }
        if(DISTANCIA < distMinima && DISTANCIA > 0.0){
          vehiculoDetente();
          buzzerParpadea();
        }
      }
      if(DISTANCIA == -1.0){
        DATO = DAT_TEMP;
        DISTANCIA = obtenerDistancia();
      }
    delay(1);
    // Giro Izquierda
      if(DATO == cstIzquierda){
        DISTANCIA = obtenerDistancia();
        while(DISTANCIA > distMinima){
          vehiculoVolteaIzquierda(VelGiro);
          DISTANCIA = obtenerDistancia();
          DAT_TEMP = miBT.read();
            if(DAT_TEMP == cstAvanza || DAT_TEMP == cstDerecha || DAT_TEMP == cstRetrocede || DAT_TEMP == cstDetente){
              DISTANCIA = -1.0;
            }
          delay(200);
        }
        if(DISTANCIA < distMinima && DISTANCIA > 0.0){
          vehiculoDetente();
          buzzerParpadea();
        }
      }
      if(DISTANCIA == -1.0){
        DATO = DAT_TEMP;
        DISTANCIA = obtenerDistancia();
      }
    delay(1);
    // Giro Derecha
      if(DATO == cstDerecha){
        DISTANCIA = obtenerDistancia();
        while(DISTANCIA > distMinima){
          vehiculoVolteaDerecha(VelGiro);
          DISTANCIA = obtenerDistancia();
          DAT_TEMP = miBT.read();
            if(DAT_TEMP == cstAvanza || DAT_TEMP == cstIzquierda || DAT_TEMP == cstRetrocede || DAT_TEMP == cstDetente){
              DISTANCIA = -1.0;
            }
          delay(200);
        }
        if(DISTANCIA < distMinima && DISTANCIA > 0.0){
          vehiculoDetente();
          buzzerParpadea();
        }
      }
      if(DISTANCIA == -1.0){
        DATO = DAT_TEMP;
        DISTANCIA = obtenerDistancia();
      }
    delay(1);
    // Retroceder
      if(DATO == cstRetrocede){
        vehiculoRetrocede(VelRetroceso);
      }
    delay(1);
    // Detener
      if(DATO == cstDetente){
        vehiculoDetente();
      }
    delay(1);
  }
} 


// MOD. LOCOMOCION: CREACION DE FUNCIONES
void vehiculoAvanza(int velocidad){     // funcion para giro antihorario de los 4 motorreductores
  encenderLedVerde();
  
  analogWrite(ENA, velocidad);          // velocidad mediante PWM en ENA
  digitalWrite(IN1, LOW);               // IN1 a cero logico
  digitalWrite(IN2, HIGH);              // IN2 a uno logico
  analogWrite(ENB, velocidad);          // velocidad mediante PWM en ENB
  digitalWrite(IN3, LOW);               // IN3 a cero logico
  digitalWrite(IN4, HIGH);              // IN4 a uno logico
}

void vehiculoVolteaIzquierda(int velocidad){  // funcion para giro antihorario de los motores del lado derecho
  encenderLedVerde();
  
  analogWrite(ENA, velocidad);                // velocidad mediante PWM en ENA
  digitalWrite(IN1, LOW);                     // IN1 a cero logico
  digitalWrite(IN2, HIGH);                    // IN2 a uno logico
  analogWrite(ENB, 0);                        // deshabilita motores del lado izquierdo
}

void vehiculoVolteaDerecha(int velocidad){    // funcion para giro antihorario de los motores del lado izquierdo
  encenderLedVerde();
  
  analogWrite(ENB, velocidad);                // velocidad mediante PWM en ENB
  digitalWrite(IN3, LOW);                     // IN3 a cero logico
  digitalWrite(IN4, HIGH);                    // IN4 a uno logico
  analogWrite(ENA, 0);                        // deshabilita motores del lado derecho
}

void vehiculoRetrocede(int velocidad){        // funcion para giro horario de los 4 motorreductores
  encenderLedVerde();
  
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

  apagarLedVerde();
}

void vehiculoRutaA(){            // creacion de ruta a seguir llamada 'A'
  vehiculoAvanza(VelAvance);
  delay(2000);
  vehiculoVolteaIzquierda(VelGiro);
  delay(600);
  vehiculoAvanza(VelAvance);
  delay(1500);
  vehiculoVolteaDerecha(VelGiro);
  delay(1400);
  vehiculoAvanza(VelAvance);
  delay(6000);
  vehiculoDetente();
}

void vehiculoRutaB(){            // creacion de ruta a seguir llamada 'B'
  vehiculoRetrocede(VelAvance);
  delay(1500);
  vehiculoVolteaIzquierda(VelGiro);
  delay(2100);
  vehiculoAvanza(VelAvance);
  delay(3000);
  vehiculoDetente();
}

void vehiculoRutaC(){            // creacion de ruta a seguir llamada 'C'
  vehiculoAvanza(VelAvance);
  delay(2000);
  vehiculoVolteaDerecha(VelGiro);
  delay(1050);
  vehiculoAvanza(VelAvance);
  delay(1500);
  vehiculoVolteaIzquierda(VelGiro);
  delay(500);
  vehiculoAvanza(VelAvance);
  delay(2500);
  vehiculoDetente();
}

// MOD. DETECCION DE OBSTACULOS: CREACION DE FUNCIONES
long obtenerDistancia(){         // creacion de ruta a seguir llamada 'B'
  digitalWrite(pinTRIG, HIGH);      
  delay(1);                         
  digitalWrite(pinTRIG, LOW);             // generacion del pulso a enviar al pin conectado al trigger del sensor
  
  DURACION = pulseIn(pinECHO, HIGH);      // con funcion pulseIn se espera un pulso alto en echo
  
  DISTANCIA = DURACION / 58.2;            // distancia medida en centimetros

  return DISTANCIA;
}

// MOD. ASPIRACION: CREACION DE FUNCIONES
void encenderFan(){                       // creacion de funcion con objetivo: ENCENDER EL VENTILADOR
  digitalWrite(pinFAN, HIGH);
  encenderLedRojo();
}
void apagarFan(){                         // creacion de funcion con objetivo: APAGAR EL VENTILADOR
  digitalWrite(pinFAN, LOW);
  apagarLedRojo();
}

// MOD. ESTADO: CREACION DE FUNCIONES
void buzzerParpadea(){                    // creacion de funcion con objetivo: ENCENDER EL BUZZER
  analogWrite(pinBUZZER, 60);             // encender el buzzer con un voltaje de 1.8v
  delay(1000);                            // demora de 1.5 segundos
  analogWrite(pinBUZZER, 0);              // apagar buzzer
  delay(200);                             // demora de 0.5 segundos
  analogWrite(pinBUZZER, 60);             // encender el buzzer con un voltaje de 1.8v
  delay(1000);                            // demora de 1.5 segundos
  analogWrite(pinBUZZER, 0);              // apagar buzzer
  delay(200);                             // demora de 0.5 segundos
}
void encenderLedRojo(){                   // creacion de funcion con objetivo: ENCENDER EL LED RED
  analogWrite(pinLedRojo, 250);         // encender Led Rojo
}
void apagarLedRojo(){                     // creacion de funcion con objetivo: APAGAR EL LED RED
  analogWrite(pinLedRojo, 0);          // apagar Led Rojo
}
void encenderLedVerde(){                  // creacion de funcion con objetivo: ENCENDER EL LED GREEN
  analogWrite(pinLedVerde, 200);        // encender Led Verde
}
void apagarLedVerde(){                    // creacion de funcion con objetivo: AOAGAR EL LED GREEN
  analogWrite(pinLedVerde, 0);         // apagar Led Verde
}
