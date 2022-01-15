#include "robot.h"
robot r;

//Sensor Ultrasonico
const int uAdelante=2;
const int uDerecha=1;
const int uIzquierda=0;


//contadores y colores
int cont=0;
int blanco=0;
int rojo=1;
int verde=2;
int azul=3;
int morado=4;
int amarillo = 5;
int negro = 6;
int rosa = 7;
//Servos


void setup() {
  //PuenteH
  Serial.begin(9600);
  
  pinMode(r.IN1,OUTPUT);
  pinMode(r.IN2,OUTPUT);
  pinMode(r.IN3,OUTPUT);
  pinMode(r.IN4,OUTPUT);
  pinMode(r.ENA,OUTPUT); 
  pinMode(r.ENB,OUTPUT);
  digitalWrite(r.ENA,HIGH); 
  digitalWrite(r.ENB,HIGH);
  
  //SensorColor
  pinMode(r.s0,OUTPUT);
  pinMode(r.s1,OUTPUT);
  pinMode(r.s2,OUTPUT);
  pinMode(r.s3,OUTPUT);
  pinMode(r.out,INPUT);
  pinMode(r.out2,INPUT);
  
  digitalWrite(r.s0, HIGH);
  digitalWrite(r.s1, HIGH);
  

  //Servos
  servo.attach(3);
  r.cerrarGarra();
  


  //UltraSensor
  for (cont=0; cont < 3; cont++){
   pinMode(r.Echo[cont], INPUT);
   pinMode(r.Trigger[cont], OUTPUT); 
   digitalWrite(r.Trigger[cont], LOW);}
  
  //LCD
  lcd.init();
  lcd.backlight();
   
}

void ultraSensors(){
  int d1 = r.areadUltra(uAdelante);
  int d2 = r.areadUltra(uIzquierda);
  int d3 = r.areadUltra(uDerecha);

    Serial.print("Adelante= ");
    Serial.print(d1);
    Serial.print("  Izquierda= ");
    Serial.print(d2);
    Serial.print("  Derecha= ");
    Serial.println(d3); 
  }

  void colorZonaA(){
    r.readColorA();
    }

   void colorsZonaC(){
    Serial.print("Color sensor DERECHA");
    r.readColorDer();
    Serial.print("Color sensor IZQUIERDA");
    r.readColorIzq();

    }



void loop() {

  //r.aadelante();
  //r.agirarIzq();
  //r.agirarDer();
  //ultraSensors();
  //colorZonaA();
  //colorZonaC();
   
}
