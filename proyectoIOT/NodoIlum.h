#include <TimeLib.h>

class NodoIlum{
  
  public:
    char operationMode = '0';
    int lampState = 0;
    int curtainState = 0;
    
    //NodoIlum();
    void comando(char lamp, char pers){
      operationMode = 'c';
      if(lamp == '0'){
        //Serial.println("LAMPARA APAGADA");
        digitalWrite(D3, LOW);
        lampState = 0;
      }else{
        //Serial.println("LAMPARA PRENDIDA");
        digitalWrite(D3, HIGH);
        lampState = 1;
      }
      if(pers == '0'){
        //Serial.println("PERSIANA CERRADA");
        digitalWrite(D4, LOW);
        curtainState = 0;
      }else{
        //Serial.println("PERSIANA ABIERTA");
        digitalWrite(D4, HIGH);
        curtainState = 1;
      }
    }
    String dato(int digit){
      String dt = String("0")+digit;
      return dt.substring(dt.length()-2);
    }
    void horario(){
      operationMode = 'h';
      String tiempo = String(hour())+":"+dato(minute())+":"+dato(second());
      //Serial.print(minute()%2);
      Serial.print(tiempo);
      if(minute()%2== 0){
        //Serial.println(" PRENDIDO");
        digitalWrite(D3, HIGH);
        digitalWrite(D4, HIGH);
        curtainState=1;
        lampState = 1;
      }else{
        //Serial.println(" APAGADO");
        digitalWrite(D3, LOW);
        digitalWrite(D4, LOW);
        curtainState=0;
        lampState = 0;
        
      }
      delay(1000);
    }

    void movimiento(){
      operationMode = 'm';
      Serial.println("NO MOVIMIENTO");
        digitalWrite(D3, LOW);
        digitalWrite(D4, LOW);
        curtainState=0;
        lampState = 0;
      while(digitalRead(D5)== HIGH){
        Serial.println("MOVIMIENTO");
        digitalWrite(D3, HIGH);
        digitalWrite(D4, HIGH);
        curtainState=1;
        lampState = 1;
      }
    }
    
};
