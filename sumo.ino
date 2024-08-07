//---SENSORES FRONTALES---//
#define sensorLeftPin A0      //PIN ANALOGICO DE LECTURA IZQUIERDO
#define sensorRightPin A1     //PIN ANALOGICO DE LECTURA DERECHA

//---SENSORES INFERIORES---//
#define sensorLeftF A2        //PIN ANALOGICO DE LECTURA SENSOR INFERIOR FRONTAL IZQ
#define sensorRightF A3       //PIN ANALOGICO DE LECTURA SENSOR INFERIOR FRONTAL DER
#define sensorBack A4         //PIN ANALOGICO DE LECTURA SENSOR INFERIOR TRASERO

//---MOTORES---//
#define motorLeftPin 2       //PIN DIGITAL PARA CONTROL DE MOTOR IZQUIERDO
#define motorRightPin 3      //PIN DIGITAL PARA CONTROL DE MOTOR DERECHO

void setup() {
  //inicio de comunicacion serial 
  Serial.begin(9600);
  //---DEFINICION DE PINES PARA SESNORES---//
  pinMode(sensorLeftPin, INPUT);
  pinMode(sensorRightPin, INPUT);
  pinMode(sensorLeftF, INPUT);
  pinMode(sensorRightF, INPUT);
  pinMode(sensorBack, INPUT);

  //---DEFINICION DE PINES PARA MOTORES---//
  pinMode(motorLeftPin, OUTPUT);
  pinMode(motorRightPin, OUTPUT);
  
}

/*!
 * A0 y A1 es el pin que se utiliza para la lectura de informacion
 * en este caso:
 *  amarillo --> dato
 *  rojo --> 5V
 *  negro --> GND
 */


float medicion (int sensorPin, int n){
  long suma = 0;
  for(int i =0; i<n; i++){
    suma +=analogRead(sensorPin);
  }
  float promedio = suma/n;
  float distancia = 17569.7 * pow(promedio, -1.2062);
  return(distancia);
}

void center( int vR, int vL){
  if (vL < vR) {
    digitalWrite(motorLeftPin, HIGH);
    digitalWrite(motorRightPin, LOW);
  } else if (vL > vR) {
    digitalWrite(motorLeftPin, LOW);
    digitalWrite(motorRightPin, HIGH);
  } else {
    digitalWrite(motorLeftPin, HIGH);
    digitalWrite(motorRightPin, HIGH);
  }
}
/*
 * Esta funcion es la que se va a encargar de desplazar el sumo dentro del tablero para buscar un objetivo
void search(){
  do{
    digitalWrite(motorLeftPin, HIGH);
    digitalWrite(motorRightPin, HIGH);
  }while(
}
*/
void loop() {
  int cmLeft = medicion(sensorLeftPin, 20); // funcion   que tomara 20 muestras
  int cmRight = medicion(sensorRightPin, 20); // funcion   que tomara 20 muestras
  Serial.print("Distancia IZQ: ");
  Serial.print(cmLeft);
  Serial.println(" u");

  Serial.print("Distancia DER: ");
  Serial.print(cmRight);
  Serial.println(" u");
  if(cmRight < 20 || cmLeft <20)    // pregunta si hay un objeto enfrente
    center(cmRight, cmLeft);
 
  delay(1000);

}
