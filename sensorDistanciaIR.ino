void setup() {
  //inicio de comunicacion serial 
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

/*!
 * A0 es el pin que se utiliza para la lectura de informacion
 * en este caso:
 *  amarillo --> dato
 *  rojo --> 5V
 *  negro --> GND
 */

void loop() {
  int cm = medicion(20); // funcion   que tomara 20 muestras
  Serial.print("ms Distancia: ");
  Serial.print(cm);
  Serial.println(" cm");
  delay(100);

}

float medicion (int n){
  long suma = 0;
  for(int i =0; i<n; i++){
    suma +=analogRead(A0);
  }
  float promedio = suma/n;
  float distancia = 17569.7 * pow(promedio, -1.2062);
  return(distancia);
}
