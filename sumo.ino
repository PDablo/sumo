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
#define motorLeftPinB 3
#define motorEnL 6            //PIN DIGITAL PARA HABILITAR CON PWM EL MOTOR IZQUIERDO
#define motorRightPin 4      //PIN DIGITAL PARA CONTROL DE MOTOR DERECHO
#define motorRightPinB 5
#define motorEnR 7            //PIN DIGITAL PARA HABILITAR CON PWM EL MOTOR DERECHO


//#define DEBUGGERS             //con esta macro permito hacer pruebas
#define PRODUCCION
//#define DEBUG_SEARCH        //macro que activa la funcin de busqueda del SUMO
#define DEBUG_SHARP          //macro que activa la funcion para mostrar las lecturas del sensor SHARP
//#define CENTER         //macro que avtiva la funcion para centrar un objeto
//#define MOTOR_TEST
//#define DEBUG_PRINT

/*------SHARP-----*/
//una lectura aproximada de ambos, con un objeto a:
//60cm = 400-440
//50cm = 395-430
//40cm = 380-425
//30cm = 415-432   <--?????
//20cm = 470-515
//10cm = 350-480
#define UMB_ATTACK 450
#define UMB_CENTER 400  //este mismo umbral voy a usar para saber si debo empezar a buscar o empezar a centrar el objetivo
#define LEC 20
/*----------------*/

#define DELAY_TEST 500
#define D_FRENO 500
#define LINE 500    //valor de umbral para detectar linea blanca

bool timer5s = false;

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
  pinMode(motorLeftPinB, OUTPUT);
  pinMode(motorRightPinB, OUTPUT);
  
}

float medicion (int sensorPin){
  long suma = 0;
  for(int i =0; i<LEC; i++){
    suma +=analogRead(sensorPin);
  }
  //float promedio = suma/LEC;
  return(suma/LEC);
  //float volt = promedio * (5.0/1023.0);     //No entiendo por que no funciona
  //float distancia = 17569.7 * pow(promedio, -1.2062);
  
  //return(distancia);
}



void motor_test(){
    F_motorLeft();
    delay(DELAY_TEST);
    freno();
    
    F_motorRight();
    delay(DELAY_TEST);
    freno();
    
    F_motors();
    delay(DELAY_TEST);
    freno();
    
}

void loop() {
  if(!timer5s){
    timer5s = true;
    delay(5000);
  }
  
  int cmLeft = medicion(sensorLeftPin); // funcion   que tomara 20 muestras
  int cmRight = medicion(sensorRightPin); // funcion   que tomara 20 muestras
  #ifdef PRODUCCION
    if(cmRight < UMB_CENTER && cmLeft < UMB_CENTER){
      //search();
    }else if(cmRight >= UMB_ATTACK && cmLeft > UMB_ATTACK){
      F_motors();
    }else{
      center(cmRight, cmLeft);
    }
  #endif
  
  #ifdef DEBUGGERS
    #ifdef DEBUG_SHARP
      Serial.print("Distancia IZQ: ");
      Serial.print(cmLeft);
      Serial.println(" u");
  
      Serial.print("Distancia DER: ");
      Serial.print(cmRight);
      Serial.println(" u");
    #endif
  
    #ifdef CENTER
      if(cmRight < 20 || cmLeft <20)    // pregunta si hay un objeto enfrente
        center(cmRight, cmLeft);
    #endif
  
    #ifdef DEBUG_SEARCH
      //search();
    #endif
    
   //   safe();
    
    #ifdef MOTOR_TEST
      //motor_test();
      F_motorRight();
      delay(1000);
      F_motorLeft();
      delay(1000);
      F_motors();
    #endif
  #endif
  delay(1000);

}

void F_motorLeft(){
    #ifdef DEBUG_PRINT
      Serial.print("Motor Izq\n");
      delay(100);
    #endif
      
    digitalWrite(motorLeftPin, HIGH);
    digitalWrite(motorLeftPinB, LOW);
    digitalWrite(motorRightPin, LOW);
    digitalWrite(motorRightPinB, HIGH);
    analogWrite(motorEnL, 127);  
}

void freno(){
    digitalWrite(motorLeftPin, LOW);
    digitalWrite(motorLeftPinB, LOW);
    digitalWrite(motorRightPin, LOW);
    digitalWrite(motorRightPinB, LOW);
    delay(D_FRENO);
}

void F_motorRight(){
    #ifdef DEBUG_PRINT
      Serial.print("Motor Der\n");
      delay(100);
    #endif
    
    digitalWrite(motorLeftPin, LOW);    //PIN 2
    digitalWrite(motorLeftPinB, HIGH);  //PIN 3
    digitalWrite(motorRightPin, HIGH);  //PIN 4
    digitalWrite(motorRightPinB, LOW);  //PIN 5
    analogWrite(motorEnR, 127);
}
void F_motors(){
    #ifdef DEBUG_PRINT
      Serial.print("ADELANTE\n");
      delay(100);
    #endif
    
    digitalWrite(motorLeftPin, HIGH);
    digitalWrite(motorLeftPinB, LOW);
    digitalWrite(motorRightPin, HIGH);
    digitalWrite(motorRightPinB, LOW);
    analogWrite(motorEnL, 255);
    analogWrite(motorEnR, 255);
}

void B_motors(){
    digitalWrite(motorLeftPin, LOW);
    digitalWrite(motorLeftPinB, HIGH);
    digitalWrite(motorRightPin, LOW);
    digitalWrite(motorRightPinB, HIGH);
}

void center( int vR, int vL){
    if (vL < vR) {
      /*
      Serial.print("Giro a la derecha\n");
      digitalWrite(motorLeftPin, HIGH);
      digitalWrite(motorLeftPinB, LOW);
      digitalWrite(motorRightPin, LOW);
      digitalWrite(motorRightPinB, HIGH);
      */
      F_motorLeft();
             
    } else if (vL > vR) {
      /*
      Serial.print("Giro a la izquierda\n");
      digitalWrite(motorLeftPin, LOW);
      digitalWrite(motorLeftPinB, HIGH);
      digitalWrite(motorRightPin, HIGH);
      digitalWrite(motorRightPinB, LOW);
      */
      F_motorRight();
      
    } else {
      /*
      Serial.print("Avanzo\n");
      digitalWrite(motorLeftPin, HIGH);
      digitalWrite(motorLeftPinB, LOW);
      digitalWrite(motorRightPin, HIGH);
      digitalWrite(motorRightPinB, LOW);
      */
      F_motors();
    }
}

void safe(){
  int _back = 0;  //vble para leer el sensor trasero
  int _right = 0; //vble para leer el sensor delantero-derecho
  int _left = 0;  //vlbe para leer el senstor delantero-izquierdo
  
  _back = analogRead(sensorBack); //lee la entrada del sensor
  _left = analogRead(sensorLeftF);
  _right = analogRead(sensorRightF);

    #ifdef DEBUG_PRINT
      Serial.print("back: ");  //muestra por el monitor la lectura del sensor
      Serial.println(_back);

      Serial.print(" left: ");
      Serial.print(_left);

      Serial.print(" right: ");
      Serial.println(_right);
    #endif
  
  if(_back > LINE){
    #ifdef DEBUG_PRINT
      Serial.println("Avanzo");
    #endif
    F_motors();
  }
  if(_left > LINE || _right > LINE){
    #ifdef DEBUG_PRINT
      Serial.println("Retrocedo");
    #endif
    B_motors();
  }
}
/*
 * Esta funcion es la que se va a encargar de desplazar el sumo dentro del tablero para buscar un objetivo
 * 
 void search(){
   do{
   F_motorRight();
   }while(
 }

*/
