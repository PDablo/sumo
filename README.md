#  Robot SUMO para el grupo de robotica de la UTN-FRP
##  Objetivos del proyecto
+ Incentivar el auto-aprendizaje e investigacion
+ Diseñar/Modelar un chasis que se adapte a las necesidades y lograr imprimirlo en 3D
+ Progrmar un Software que logre:
    + Identificar un objetivo frente de si
    + Identificar limites del espacio
    + Variar entre dos o mas estrategias de combate y busqueda
    + Desplazarse sin complicaciones dentro del area delimitada

---

##    Proyecto
###    Software

_24/06/2024_

Probando como utilizar el sensor SHARP con arduino, en una primera instancia solo me da lecturas erroneas.

_31/07/2024_

El codigo quedo implementado de manera que el sumo detecte un objeto y avance hasta ese objeto.
Queda definida una funcion que se esta probando, la cual sirve para que el robot pueda centrar el objeto y avanzar para atacarlo.
Tambien tiene añadida una funcion para desplazarse en el tatami en caso de que no encuentre ningun objeto delante suyo.

###    Hardware

Personalmente trabajo con Fusion360 para el diseño del chasis, utilizando una licencia educativa; aunque lo ideal seria migrar a FreeCAD para poder trabaja con Software Libre.
Elementos:
+ Arduino UNO
+ Driver L298D
+ Sensor SHARP 2Y0A02
+ Sensores CNY70
+ Celdas 18650

_24/06/2024_

El archivo .F3d contiene la idea principal a llevar adelante.

_31/07/2024_

El sumo ya quedo montado con sus respectivos motores, puente H, sensores sharp y arduino; de momento solo funciona conectado a una fuente de alimentacion.

_10/09/2024_

Cada sensor SHARP consume, en promedio, 33mA en rafagas cortas y grandes (el fabricante recomienda colocar un capacitor de
10 µF o más grande entre la alimentación y la tierra cerca del sensor para
estabilizar la línea de suministro de energía)

Cada sensro CNY70 tiene una Ic = 50mA (MAX) y calculamos aproximadamente 20mA para el led IR, por ende cada sensor consumiria aproximadamente 70mA

Segun la web: https://docs.arduino.cc/hardware/uno-rev3/#tech-specs
La corriente maxima DC para I/O pines es de 20mA. Por lo que sera necesario agregar una alimentacion externa tambien para los sensores.

---

## Sobre el autor
  Soy un estudiante de ingenieria en electronica, muy entusiasta por la robotica y la integracion SW-HW.
  Llevo en paralelo un proyecto similar pero con modificaciones que permitirian al robot identificar el espacio y, en un futuro identificarse a si mismo dentro del espacio.

---


