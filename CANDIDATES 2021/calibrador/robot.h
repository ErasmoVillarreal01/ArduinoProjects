#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
LiquidCrystal_I2C lcd(0x27,16,2);
Servo servo;
class robot {
  public:
     //Motores
    const int IN1 = 7;
    const int IN2 = 8;
    const int IN3 = 9;
    const int IN4 = 11;
    const int ENA = 5;
    const int ENB = 6;
    
    const int TiempoCasilla=490; //Establecer tiempo que tarda en avanzar una casilla
    const float grados90=405.0; //Establecer cuantos segundos se necesitan para girar 90 grados
   
    
    //PINES DEL SENSOR DE COLOR 
    const int s0 =22;
    const int s1 =23;
    const int s2 = 24;
    const int s3 = 25;
    const int out = 26;
    const int out2 = 27;

    int blanco=0;
    int rojo=1;
    int verde=2;
    int azul=3;
    int morado=4;

    int amarillo = 5;
    int negro = 6;
    int rosa = 7;
    
  //Ultrasonicos
    int Echo[3]= {12,38,40};
    int Trigger[3]= {13,39,41};
  
  
    //METODOS Y FUNCIONES
    void aadelante(int segundos);
    void aadelante();
    void aadelanteInf();
    void areversa();
    void areversa(int segundos);
    void aparar(int segundos);
    void agirarIzq();
    void agirarDer();
    void agirar180();
    
    int areadUltra(int posUltra);
    int readColorA();
    int readColorB();
    int readColorDer();
    int readColorIzq();
    int readNoPrint();

    void cerrarGarra();
    void abrirGarra();
    
    int getRojo();
    int getAzul();
    int getVerde();
    int getRojo2();
    int getAzul2();
    int getVerde2();
    
};

void robot::aparar(int segundos){
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  delay(segundos);
}

int robot::getRojo(){
  //leer color rojo
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  int ROJO = pulseIn(out, LOW);
  return ROJO;
}

int robot::getAzul(){
  //leer color azul
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  int AZUL = pulseIn(out, LOW);
  return AZUL;
}

int robot::getVerde(){
  //leer color verde
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  int VERDE = pulseIn(out, LOW);
  return VERDE;
}

int robot::getRojo2(){
  //leer color rojo
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  int ROJO = pulseIn(out2, LOW);
  return ROJO;
}

int robot::getAzul2(){
  //leer color azul
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  int AZUL = pulseIn(out2, LOW);
  return AZUL;
}

int robot::getVerde2(){
  //leer color verde
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  int VERDE = pulseIn(out2, LOW);
  return VERDE;
}


int robot::readColorIzq(){
  int color = 0;
  int R2 = getRojo2();
  delay(200);
  int V2 = getVerde2();
  delay(200);
  int A2 = getAzul2();
  delay(200);
  
  Serial.print("Izquierda Int R2 "+ String(R2));
  Serial.print("  --  Int V2 "+ String(V2));
  Serial.print("  --  Int Z2 "+ String(A2));
  
    if(R2 < V2 && V2 < A2 && R2 > 2 && R2 < 7){
      Serial.print("  EL COLOR ES AMARILLO");
      lcd.print("IZQ AMARILLO");
      color = amarillo;
    }else if(R2 < V2 && V2 > A2 && R2 > 27 && R2 <50){
      Serial.print("  EL COLOR ES NEGRO");
      lcd.print("IZQ NEGRO");
      color = negro;
    }else if(R2 < V2 && V2 > A2 && V2 > 7 && V2 < 10){
      Serial.print("  EL COLOR ES ROSA");          
      lcd.print("IZQ ROSA");
      color = rosa;
    }else if(R2 > V2 && V2 < A2 && R2 > 10 && R2 < 25){
      Serial.print("  EL COLOR ES VERDE");          
      lcd.print("IZQ VERDE");
      color = verde;
    }else{
      Serial.print("  EL COLOR ES BLANCO");          
      lcd.print("IZQ BLANCO");
      color = blanco;
    }

    Serial.println(" ");
    delay(2000);
    lcd.clear();
    return color;
}

int robot::readColorDer(){
  int color = 0;
  int R = getRojo();
  delay(200);
  int V = getVerde();
  delay(200);
  int A = getAzul();
  delay(200);
  
  Serial.print("Derecha: Int R1 "+ String(R));
  Serial.print("  --  Int V1 "+ String(V));
  Serial.print("  --  Int Z1 "+ String(A));
  
    if(R < V && V > A && R > 2 && R < 7){
      Serial.print(" EL COLOR ES AMARILLO");
      lcd.print("DER AMARILLO");
      color = amarillo;
    }else if(R < V && V > A && R > 27 && R <50){
      Serial.print("  EL COLOR ES NEGRO");
      lcd.print("DER NEGRO");
      color = negro;
    }else if(R < V && V > A && R > 1 && R < 8){
      Serial.print("  EL COLOR ES ROSA"); 
      lcd.print("DER ROSA");         
      color = rosa;
    }else if(R> V && V > A && R > 10&& R < 25){
      Serial.print("  EL COLOR ES VERDE");
      lcd.print("DER VERDE");          
      color = verde;
    }else{
      Serial.print("  EL COLOR ES BLANCO");
      lcd.print("DER BLANCO");          
      color = blanco;
    }
    


  Serial.println(" ");
  delay(2000);
  lcd.clear();
  return color;
}

int robot::readColorA(){
  int color=0;
  int R = getRojo();
  delay(200);
  int V = getVerde();
  delay(200);
  int A = getAzul();
  delay(200);
  
  Serial.print("Int R "+ String(R));
  Serial.print("  --  Int V "+ String(V));
  Serial.print("  --  Int Z "+ String(A));
  
    if(R > V && V > A && R > 14 && R < 25){
      Serial.print("  EL COLOR ES VERDE");
      lcd.print("VERDE");
      color=verde;
    }else if(R> V && V > A && R > 24 && R<38){
      Serial.print("  EL COLOR ES AZUL");
      lcd.print("AZUL");
      color=azul;
    }else if(R < V && V > A && V > 20  && V < 30 ){
      Serial.print("  EL COLOR ES ROJO");             //LISTO
      lcd.print("ROJO");
      color=rojo;
    }else if(R < V && V > A && R > 18  && R < 29 ){
      lcd.print("MORADO");
      Serial.print("  EL COLOR ES MORADO");
      color=morado;
    }else {
      Serial.print("  BLANCO");
      color=blanco;
    }
  Serial.println(" ");
  delay(1000);
  lcd.clear();
  return color;
}

int robot::readNoPrint(){
  int color=0;
  int R = getRojo();
  delay(200);
  int V = getVerde();
  delay(200);
  int A = getAzul();
  delay(200);
  
  Serial.print("Int R "+ String(R));
  Serial.print("  --  Int V "+ String(V));
  Serial.print("  --  Int Z "+ String(A));
  
    if(R > V && V > A && R > 14 && R < 25){
      Serial.print("  EL COLOR ES VERDE");
      color=verde;
    }else if(R> V && V > A && R > 24 && R<38 ){
      Serial.print("  EL COLOR ES AZUL");
      color=azul;
    }else if(R < V && V > A && R > 3  && R < 9 ){
      Serial.print("  EL COLOR ES ROJO");             //LISTO
      color=rojo;
    }else if(R < V && V > A && R > 3  && R < 9 ){
      Serial.print("  EL COLOR ES MORADO");
      color=morado;
    }else if(R < V && V > A && R > 1 && R < 8){
      Serial.print("  EL COLOR ES ROSA"); 
      lcd.print("DER ROSA");         
      color = rosa;
    }else{
      Serial.print(" BLANCO");
      lcd.print("Blanco");
    }
  Serial.println(" ");
  delay(1000);
  lcd.clear();
  return color;
}

int robot::areadUltra(int posUltra){
  long t; 
  long d;        
  digitalWrite(Trigger[posUltra], HIGH);
  delayMicroseconds(10);          
  digitalWrite(Trigger[posUltra], LOW);        
  t = pulseIn(Echo[posUltra], HIGH); 
  d = t/59;            
  delay(100);
  return d;
}

void robot::aadelante(){
  digitalWrite(ENA, HIGH); 
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, LOW);      
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, HIGH);      
  digitalWrite(IN4, LOW);
  delay(TiempoCasilla);
  digitalWrite(IN1, LOW);      
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, LOW);      
  digitalWrite(IN4, HIGH);
  delay(10);
  areversa(75);
  aparar(200);
  areversa(15);
}
void robot::aadelanteInf(){
  digitalWrite(ENA, HIGH); 
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, LOW);      
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, HIGH);      
  digitalWrite(IN4, LOW);
  delay(50);
  digitalWrite(IN1, LOW);      
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, LOW);      
  digitalWrite(IN4, HIGH);
  delay(5);
  aparar(300);
  }
  
void robot::aadelante(int segundos){
  digitalWrite(ENA, HIGH); 
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, LOW);      
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, HIGH);      
  digitalWrite(IN4, LOW);
  delay(segundos);
  digitalWrite(IN1, LOW);      
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, LOW);      
  digitalWrite(IN4, HIGH);
  delay(10);
  aparar(200);
}

void robot::areversa(){
  digitalWrite(ENA,HIGH); 
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1, HIGH);      
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, LOW);      
  digitalWrite(IN4, HIGH);
  delay(TiempoCasilla);  
  aparar(200);
}


void robot::areversa(int segundos){
  digitalWrite(ENA,HIGH); 
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1, HIGH);      
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, LOW);      
  digitalWrite(IN4, HIGH);
  delay(segundos);  
  aparar(200);
}
void robot::agirarDer(){
  digitalWrite(ENA, HIGH); 
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, HIGH);      
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, HIGH);      
  digitalWrite(IN4, LOW);
  delay(grados90-10);
  aparar(200);
}

void robot::agirarIzq(){
  digitalWrite(ENA, HIGH); 
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, LOW);      
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, LOW);      
  digitalWrite(IN4, HIGH);
  delay(grados90);
  aparar(200);
}

void robot::agirar180(){
  digitalWrite(ENA, HIGH); 
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, HIGH);      
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, HIGH);      
  digitalWrite(IN4, LOW);
  delay((2*grados90));
  digitalWrite(ENA, 250); 
  digitalWrite(ENB, 100);
  digitalWrite(IN1, LOW);      
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, LOW);      
  digitalWrite(IN4, HIGH);
  delay(grados90);
  aparar(200);
}

void robot::cerrarGarra(){
  servo.write(25);
  delay(200);
  }
  
void robot::abrirGarra(){
  servo.write(180);
  delay(200);
  }
