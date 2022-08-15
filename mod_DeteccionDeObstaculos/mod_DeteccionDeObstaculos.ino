int pinTRIG = 8;        // HC-SR04: pin trigger en pin 8
int pinECHO = 9;        // HC-SR04: pin echo en pin 9
int pinBUZZER = 3;      // BUZZER en pin 3
int DURACION;
int DISTANCIA;

void setup(){
  pinMode(pinTRIG, OUTPUT);     // trigger como salida
  pinMode(pinECHO, INPUT);      // echo como entrada
  pinMode(pinBUZZER, OUTPUT);   // buzzer como salida
  Serial.begin(9600);           // inicializacion de comunicacion serial a 9600 bps
}

void loop(){                          // loop de prueba para modulo de DETECCION
  digitalWrite(pinTRIG, HIGH);      
  delay(1);                         
  digitalWrite(pinTRIG, LOW);         // generacion del pulso a enviar al pin conectado al trigger del sensor
  
  DURACION = pulseIn(pinECHO, HIGH);  // con funcion pulseIn se espera un pulso alto en echo
  
  DISTANCIA = DURACION / 58.2;        // distancia medida en centimetros

  Serial.println(DISTANCIA);          // envio de valor de distancia por monitor serial
  delay(200);                         // demora entre datos

  if (DISTANCIA <= 20 && DISTANCIA >= 0)   // si la distancia esta entre 0 y 20 cms.
    buzzerParpadea();
}

void buzzerParpadea(){
  analogWrite(pinBUZZER, 60);             // encender el buzzer con un voltaje de 1.8v
  delay(300);                             // demora de 0.3 segundos
  analogWrite(pinBUZZER, 0);              // apagar buzzer
}
