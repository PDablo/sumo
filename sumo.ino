//---SENSORES FRONTALES---//
/*
 * A0 y A1 es el pin que se utiliza para la lectura de informacion
 * en este caso:
 *  amarillo        -->   dato
 *  rojo            -->   5V
 *  negro           -->   GND
 */
#define sensorLeftPin A0      //PIN ANALOGICO DE LECTURA IZQUIERDO
#define sensorRightPin A1     //PIN ANALOGICO DE LECTURA DERECHA

//---SENSORES INFERIORES---//
/*
 * A2, A3 y A4 son pines para lectura de informacion con sensor CNY70 
 * wiring diagram:
 *  amarillo/yellow  -->   dato/data
 *  rojo/red         -->   5V
 *  negro/black      -->   GND
 * CNY70:
 *  colector         -->   5V
 *  emisor           -->   nodo(salida + R = 10k)
 *  cadoto           -->   5V -> catodo led
 *  anodo            -->   R = 220 -> GND
 */
#define sensorLeftF A2        //PIN ANALOGICO DE LECTURA SENSOR INFERIOR FRONTAL IZQ
#define sensorRightF A3       //PIN ANALOGICO DE LECTURA SENSOR INFERIOR FRONTAL DER
#define sensorBack A4         //PIN ANALOGICO DE LECTURA SENSOR INFERIOR TRASERO

//---MOTORES---//
#define motorLeftPin 2       //PIN DIGITAL PARA CONTROL DE MOTOR IZQUIERDO
#define motorRightPin 3      //PIN DIGITAL PARA CONTROL DE MOTOR DERECHO


//#define DEBUG_SEARCH        //macro que activa la funcin de busqueda del SUMO
//#define DEBUG_SHARP   //macro que activa la funcion para mostrar las lecturas del sensor SHARP
//#define DEBUG_CENTER  //macro que avtiva la funcion para centrar un objeto

#define LINE 500    //valor de umbral para detectar linea blanca

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

float medicion (int sensorPin, int n){
  long suma = 0;
  for(int i =0; i<n; i++){
    suma +=analogRead(sensorPin);
  }
  float promedio = suma/n;
  float distancia = 17569.7 * pow(promedio, -1.2062);
  /*
  * Debo corregir el codigo anterior adaptando:
  * 
  * int rawValue = analogRead(sensorPin);
  * float volt = rawValue * (5.0 / 1023.0);
  * distancia = 60,374 X POW(volt, -1,16)
  *
  * Donde:
  * como 'rawValue' es un valor analogico leido por el arduino
  * y puede estar entre 0 y 1023 dependiendo su valor; se multiplica
  * por '5.0' siendo este los 5V de referencia del arduino, y se divide 
  * entre '1023.0' siendo el maximo posible que se podria tomar.
  * es una regla de 3:
  *    1023.5     --> 5V
  *    rawValeue  --> ?      =>    (rawValue * 5V) / 1023.0
  *
  * Luego:
  * la ecuacion "60,374 X POW(volt, -1,16)" es una formula empirica
  * del sensor que indica la distancia en centimetros; siendo '60.374'
  * un factor de ajuste que se obtiene a traves de la experimentacion y 
  * '-1.16' indica la relacion inversa entre la tension y la distancia
  */
  return(distancia);
}

void center( int vR, int vL){
  if (vL < vR) {
    digitalWrite(motorLeftPin, HIGH);
    Serial.print("Motor Izq\n");
    digitalWrite(motorRightPin, LOW);
  } else if (vL > vR) {
    digitalWrite(motorLeftPin, LOW);
    digitalWrite(motorRightPin, HIGH);
    Serial.print("Motor Der\n");
  } else {
    digitalWrite(motorLeftPin, HIGH);
    digitalWrite(motorRightPin, HIGH);
    Serial.print("Adelante\n");
  }
}

void safe(){
  int _back = 0;  //vble para leer el sensor trasero
  int _right = 0; //vble para leer el sensor delantero-derecho
  int _left = 0;  //vlbe para leer el senstor delantero-izquierdo
  
  _back = analogRead(sensorBack); //lee la entrada del sensor
  _left = analogRead(sensorLeftF);
  _right = analogRead(sensorRightF);
  
  Serial.print("back: ");  //muestra por el monitor la lectura del sensor
  Serial.println(_back);

  Serial.print(" left: ");
  Serial.print(_left);

  Serial.print(" right: ");
  Serial.println(_right);

  
  if(_back > LINE){
    Serial.println("Avanzo");
  }
  if(_left > LINE || _right > LINE){
    Serial.println("Retrocedo");
  }
}
/*
 * Esta funcion es la que se va a encargar de desplazar el sumo dentro del tablero para buscar un objetivo
 * 
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
  #ifdef DEBUG_SHARP
    Serial.print("Distancia IZQ: ");
    Serial.print(cmLeft);
    Serial.println(" u");

    Serial.print("Distancia DER: ");
    Serial.print(cmRight);
    Serial.println(" u");
  #endif

  #ifdef DEBUG_CENTER
    if(cmRight < 20 || cmLeft <20)    // pregunta si hay un objeto enfrente
      center(cmRight, cmLeft);
  #endif

  #ifdef DEBUG_SEARCH
  //search();
  #endif
  safe();
  delay(1000);

}
