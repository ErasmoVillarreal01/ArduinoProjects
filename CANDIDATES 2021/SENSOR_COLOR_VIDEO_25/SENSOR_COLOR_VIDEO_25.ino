
const int s0 = 22;
const int s1 = 23;
const int s2 = 24;
const int s3 = 25;
const int out = 27;

void setup()   
{  
  Serial.begin(9600);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);

  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);


}  
    
void loop() 
{ 
int R = getRojo();
delay(200);
int V = getVerde();
delay(200);
int A = getAzul();
delay(200);

Serial.print("Int R "+ String(R));
Serial.print("  --  Int V "+ String(V));
Serial.print("  --  Int Z "+ String(A));

  
  /*if(R < V && V > A && R > 2 && R < 7){
    Serial.print("  EL COLOR ES AMARILLO");           // AMARILLO
  }else if(R< V && V > A && R > 27 && R<37 ){
    Serial.print("  EL COLOR ES NEGRO");
  }else if(R < V && V > A && V > 14  && V < 31 ){
    Serial.print("  EL COLOR ES MORADO");             //LISTO
  }else if(R < V && V > A && V > 7 && V < 10 ){
    Serial.print("  EL COLOR ES ROSA");
  }else if(R> V && V > A && R > 10&& R < 18){
    Serial.print("  EL COLOR ES VERDE");
  }else if(R < V && V > A && R > 1  && R < 6 ){
    Serial.print("  EL COLOR ES ROSA");            
  }else{
    Serial.print("  EL COLOR ES BLANCO");
  }
  */
  if(R > V && V < A && R > 14 && R < 23){
    Serial.print("  EL COLOR ES VERDE");           // AMARILLO
  }else if(R> V && V > A && R > 20 && R<29 ){
    Serial.print("  EL COLOR ES AZUL");
  }else if(R < V && V > A && R > 3  && R < 9 ){
    Serial.print("  EL COLOR ES ROJO");             //LISTO
  }else{
    Serial.print("  EL COLOR ES NO HA SIDO REGISTRADO");
  }


  Serial.println(" ");

}  
 
int getRojo(){
  //leer color rojo
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  int ROJO = pulseIn(out, LOW);
  return ROJO;
}

int getAzul(){
  //leer color azul
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  int AZUL = pulseIn(out, LOW);
  return AZUL;
}

int getVerde(){
  //leer color verde
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  int VERDE = pulseIn(out, LOW);
  return VERDE;
}
