// Definir pines del sensor y motores
const int sensorPin = A0;       // ENTRADA UTILIZADA PARA LA LECTURA DEL SENSOR SHARP
//const int sensorPin = A1;       // ENTRADA UTILIZADA PARA LA LECTURA DEL SENSOR SHARP
/*!
 * A0/A1 es el pin que se utiliza para la lectura de informacion
 * en este caso:
 *  amarillo = celeste --> dato
 *  rojo = naranja --> 5V
 *  negro = naranja claro --> GND
 */
const int motorLeftPin1 = 2;    // PIN PARA CONTROLAR EL MOTOR IZQUIERDO
const int motorRightPin1 = 3;   // PIN PARA CONTROLAR EL MOTOR IZQUIERDO
const int motorTierra = 4;
/*!
 * Los siguientes controles podrian ser utilizados para controlar
 * la velocidad de los motores, no seria lo optimo.
 */
//const int enA = 9;              // PIN PARA PROPORCIONAR VELOCIDAD AL MOTOR
//const int enB = 10;             // PIN PARA PROPORCIONAR VELOCIDAD AL MOTOR

// Umbral de distancia (ajustar según sea necesario)
const int thresholdMin = 0;    // DISTANCIA MINIMA EN CM
const int thresholdMax = 20;    // DISTANCIA MINIMA EN CM

// COMUNICACION
const int COMUN = 9600;

void setup() {
  // CONFIGURAR PINES DE MOTORES COMO SALIDAS
  pinMode(motorLeftPin1, OUTPUT);
  pinMode(motorRightPin1, OUTPUT);
  pinMode(motorTierra, OUTPUT);
//  pinMode(enA, OUTPUT);
//  pinMode(enB, OUTPUT);

  // INICIAR COMUNICACION SERIE
  Serial.begin(COMUN);
}

void loop() {
  // Leer valor del sensor
  int sensorValue = analogRead(sensorPin);
  // Convertir el valor analógico a distancia en cm (calibrar esta fórmula)
  int distance = map(sensorValue, 0, 1023, 150, 10);
  
  // Imprimir la distancia medida
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Verificar si el objeto está dentro del rango deseado
  if (distance >= thresholdMin && distance <= thresholdMax) {
    // Mover hacia adelante
    moveForward();
  } else {
    // Detener motores
    stopMotors();
  }

  delay(100); // Pequeña pausa para estabilizar la lectura
}

void moveForward() {
  digitalWrite(motorLeftPin1, HIGH);
  Serial.print("Motor IZQ: ");
  Serial.print(motorLeftPin1);
  Serial.println("");
  
  digitalWrite(motorRightPin1, HIGH);
  Serial.print("Motor DER: ");
  Serial.print(motorRightPin1);
  Serial.println("");
}

void stopMotors() {
  digitalWrite(motorLeftPin1, LOW);
  Serial.print("Motor IZQ: ");
  Serial.print(motorLeftPin1);
  Serial.println("");
  
  digitalWrite(motorRightPin1, LOW);
  Serial.print("Motor DER: ");
  Serial.print(motorRightPin1);
  Serial.println("");
}
