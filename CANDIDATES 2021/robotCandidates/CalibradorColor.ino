/*#include "robot.h"
robot r;
int cont=0;
int cont2=0;
void setup() {
  //SensorColor
  for (cont=0; cont<2; cont++){
    pinMode(r.getS0(cont),OUTPUT);
    pinMode(r.getS1(cont),OUTPUT);
    pinMode(r.getS2(cont),OUTPUT);
    pinMode(r.getS3(cont),OUTPUT);
    pinMode(r.getOUT(cont),INPUT);}
    
  //ColorSensorsFrequency  
  for (cont=0; cont<2; cont++){
    digitalWrite(r.getS0(cont),HIGH); 
    digitalWrite(r.getS1(cont),LOW);}

    Serial.begin(9600);
}


void loop() {
  delay(1000);
  for (cont=0; cont<2;cont++){
    //FotodiodosROJO
    for (cont2=0; cont<2; cont2++){
      digitalWrite(r.getS2(cont),LOW);
      digitalWrite(r.getS3(cont),LOW);
      //Readfotodiodosrojo
      float frecuenciarojo=pulseIn(r.getOUT(cont),LOW);
      Serial.print("Rojo= ");
      Serial.println(frecuenciarojo);
      delay(1000);}
    //FotodiodosVERDE
    for (cont2=0; cont<2; cont2++){
      digitalWrite(r.getS2(cont),HIGH);
      digitalWrite(r.getS3(cont),HIGH);
      //Readfotodiodosverde
      float frecuenciaverde=pulseIn(r.getOUT(cont),LOW);
      Serial.print("verde= ");
      Serial.println(frecuenciaverde);
      delay(1000);}
    //FotodiodosAZUL
    for (cont2=0; cont<2; cont2++){
      digitalWrite(r.getS2(cont),LOW);
      digitalWrite(r.getS3(cont),HIGH);
      //Readfotodiodosazul
      float frecuenciaazul=pulseIn(r.getOUT(cont),LOW);
      Serial.print("azul= ");
      Serial.println(frecuenciaazul);
      delay(1000);}  
  }

  Serial.println("SIGUIENTE SENSOR DE COLOR")
  delay(1000);
}*/ 
