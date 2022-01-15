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

void zonaC(){
  int sumaDer = 0;
  int sumaIzq = 0;
  int sumaAccum = 0;
  int colorIzq = 0;
  int colorDer = 0;
  
  while(colorDer != 7){
    r.aadelante();
    colorIzq = r.readColorIzq();
    colorDer = r.readColorDer();
    switch(colorIzq){
      case 5:
        sumaIzq += 1;
        break;
      case 2:
        sumaIzq += 2;
        break;
      case 6:
        sumaDer = 0;
        break;
      case 0:
        break;
      default:
        break;
    }
    switch(colorDer){
      case 5:
        sumaDer += 2;
        break;
      case 2:
        sumaDer += 1;
        break;
      case 6:
        sumaIzq = 0;
        break;
      case 0:
        break;
      default:
        break;
    }
    sumaAccum = sumaIzq+sumaDer;
    String stringOne =  String(sumaAccum, BIN);
    lcd.print(stringOne);
    delay(1000);
    lcd.clear();
    if(r.areadUltra(uAdelante) < 12){
      
      if(sumaAccum % 2 == 0){
        r.agirarIzq();
      }else{
        r.agirarDer();
      }
    }
  }
  lcd.print("sum accum");
  delay(1500);
  lcd.clear();
  lcd.print(sumaAccum);
  delay(1500);
  lcd.clear();
  r.agirarIzq();
  r.aadelante(10000); //checar si es el tiempo en el que sube
  lcd.print("se acabo");
  delay(20000);
  return;
}

void zonaB2(){
  while (r.readColorA()!=morado){
    while (r.areadUltra(uDerecha)< 20){
     if (r.areadUltra(uAdelante) < 13){
        r.areversa(100);
        r.agirarIzq();
      }
        else{
        r.aadelante ();
        }
    }
      r.agirarDer();
      r.aadelante();
  }
}
//ZONA A

void zonaA(){
  r.aadelante();
  r.readColorA();
  while (r.readColorA()!=blanco){
    while (r.areadUltra(uDerecha)< 25){
     if (r.areadUltra(uAdelante) < 10){
        r.agirarIzq();
        r.readColorA();}
        else{
        r.aadelante ();
        r.readColorA();}
      }
      r.agirarDer();
      r.aadelante();
      r.readColorA();}
}

void zonaB(){
cont=0;
    //Busca casilla color verde
    r.abrirGarra();
    while (r.readColorA()!=verde){
      if (r.areadUltra(uAdelante)<13){
          r.areversa(50);
          r.agirarIzq();
          cont++;
        if (cont == 4){
          r.aadelante();
          r.agirarIzq();}
      }
      r.aadelanteInf();}
      r.areversa(75);
      r.aparar(100);
      r.cerrarGarra();
      delay(500);
if (cont==4){
  while(r.readColorA()!=morado){
    r.aadelante();}
  }
  else if(cont==3){
    r.aadelante(100);
    r.agirarIzq();
    while (r.readColorA()!=morado){
    while (r.areadUltra(uIzquierda)< 20){
     if (r.areadUltra(uAdelante) < 13){
        r.areversa(100);
        r.agirarDer();
      }
        else{
        r.aadelante ();
        }
    }
      r.agirarIzq();
      r.aadelante();
  }
    }
    else{
    while (r.readColorA()!=morado){
    while (r.areadUltra(uDerecha)< 20){
     if (r.areadUltra(uAdelante) < 13){
        r.areversa(100);
        r.agirarIzq();
      }
        else{
        r.aadelante ();
        }
    }
      r.agirarDer();
      r.aadelante();
  }
    }
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

    Serial.print("Color sensor ");
    r.readColorDer();
    Serial.print("Color sensor ");
    r.readColorIzq();
    Serial.println(" ");
    

    }

void loop() {

  //CALIBRADORES
  /*
  r.aadelante();
  r.agirarIzq();
  r.aparar(2000);
  r.agirarDer();
  r.aparar(2000);
  */
  
  //colorZonaA();
  //colorsZonaC();


  
   
  
  if(r.readColorDer() == rosa){
    r.aadelante(20000); //checar si es el tiempo en el que sube
    lcd.print("se acabo");
    delay(10000);
    }
  else if(r.readColorA()==morado){
    zonaC();
    }
  zonaA();
  lcd.print("ZONA B");
  delay(1000);
  lcd.clear();
  //zonaB();
  zonaB2();
  lcd.print("ZONA C");
  delay(500);
  lcd.clear();
  delay(1000);
  zonaC();
 
  
}
