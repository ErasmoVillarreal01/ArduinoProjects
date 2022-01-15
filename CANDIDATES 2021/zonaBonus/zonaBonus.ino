//Motores
const int IN1 = 7;
const int IN2 = 8;
const int IN3 = 9;
const int IN4 = 11;
const int ENA = 5;
const int ENB = 6;
int grados90 = 405;

void adelante(int tiempo){
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1, LOW);      
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, HIGH);      
  digitalWrite(IN4, LOW);
  delay(tiempo);
  }

void reversa(int segundos){
  digitalWrite(ENA,HIGH); 
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1, HIGH);      
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, LOW);      
  digitalWrite(IN4, HIGH);
  delay(segundos);  
  }
  
void motorStop(){
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  delay(100);
  }
  
void girarIzq(){
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1, LOW);      
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, LOW);      
  digitalWrite(IN4, HIGH);
  delay(grados90);
  }
void girarDer(){
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1, HIGH);      
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, HIGH);      
  digitalWrite(IN4, LOW);
  delay(grados90);
  }
 
    
void setup() {
  //Motores
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  digitalWrite(ENA,HIGH); 
  digitalWrite(ENB,HIGH);

}

void faseGrupos(){
  adelante(1800);
  girarDer();
  adelante(1000);
  }

void finales(){
for (int cont=0; cont<2; cont++){
  adelante(1750);
  girarDer();
  adelante(300);
  girarDer();
  }
  }
  
void loop() {
  faseGrupos();
  //finales();
}
