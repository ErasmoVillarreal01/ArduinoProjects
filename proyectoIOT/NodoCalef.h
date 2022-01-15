class NodoCalef{
  public:
  char modo = '0';
   void modoCalef(){
      //Serial.println("\tRojo");
      digitalWrite(D0,HIGH);
      digitalWrite(D1,LOW);
      digitalWrite(D2,HIGH);
      modo = 'f';
   }
   void modoNeutro(){
      //Serial.println("\tGreen");
      digitalWrite(D0,LOW);
      digitalWrite(D1,HIGH);
      digitalWrite(D2,HIGH);
      modo = 'n';
   }
    
   void modoClima(){
      //Serial.println("\tAzul");
      digitalWrite(D0,LOW);
      digitalWrite(D1,LOW);
      digitalWrite(D2,HIGH);  
      modo = 'c';
   }
   
   void modoComando(char modo){
      switch(modo){
        case 'f':
          //Serial.println("\tRojo");
          digitalWrite(D0,HIGH);
          digitalWrite(D1,LOW);
          digitalWrite(D2,HIGH);
          modo = 'f';
          break;
        case 'c':
          //Serial.println("\tAzul");
          digitalWrite(D0,LOW);
          digitalWrite(D1,LOW);
          digitalWrite(D2,HIGH);  
          modo = 'c';
          break;
        case 'n':
          //Serial.println("\tGreen");
          digitalWrite(D0,LOW);
          digitalWrite(D1,HIGH);
          digitalWrite(D2,HIGH);
          modo = 'n';
          break;
      }
    
   }
};
