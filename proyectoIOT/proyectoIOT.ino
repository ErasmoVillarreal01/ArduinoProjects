
// Este código funciona con la siguiente configuración:
//    Board support API esp8266 (by ESP8266 Community) version 2.5.2
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "NodoCalef.h"
#include "NodoIlum.h"

NodoCalef cal;
NodoIlum ilu;

//#define WIFI_SSID "Tec-IoT"
//#define WIFI_PASSWORD "PreguntarADeptoTI"
//#define WIFI_SSID "TC1004B"
//#define WIFI_PASSWORD "Tec-IoT2020"
#define WIFI_SSID "INFINITUM5a5x"
#define WIFI_PASSWORD "e15efcd7fa"

//PIN NODO DE CALEFACCION
#define SENSOR_A0 A0
#define LED1 D0 //R-Rojo  ... IMPORTANTE: Validar si el LED es de ánodo o de cátodo común
#define LED2 D1 //G-Verde
#define LED3 D2 //B-Azul

//nodo de Iluminacion
#define pinLed D3 //led amarillo
#define ledPer D4 //led azul
#define pinSensorMov D5 //sensor de movimiento que me detecta si es un valor alto o bajo


const char *mqtt_server = "broker.hivemq.com";
const char *channelTopic = "equipo6";
 
WiFiClient espClient;
PubSubClient client(espClient);
char query[128];
char query2[128];

long tiempoAnterior = 0;
char msg[50];
int lecturaSensorA0 = 0;
int umbral=50; //Este valor define el umbral abajo del que se enviará un mensaje al "broker"


bool mov = false;
bool horario = false;
char modoCal = '0';


bool calComando = false;

void setup_wifi() {
    delay(100);
    Serial.println();
    Serial.print("macAddress: ");
    Serial.println(WiFi.macAddress());
    //Iniciar por conectar con la red WiFi
    Serial.print("Conectando WiFI --> ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    randomSeed(micros());
    Serial.println("");
    Serial.println("WiFi conectado!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
} // End setup_wifi()
 
void callback(char* topic, byte* payload, unsigned int length) {
    char *cstring = (char *) payload;
    cstring[length] = '\0';    // Adds a terminate terminate to end of string based on length of current payload
    //Serial.println(cstring);
    char modoHorario  = cstring[0];
    char modoComando = cstring[1];
    char modoMov = cstring[2];

    char stateLamp = cstring[3];
    char statePers = cstring[4];
    char modoCl = cstring[5];
    modoCal = cstring[6];
    
    
    //cn-comandoNeutral cf-comandoFrio cc-comandoCaliente
    if(modoHorario == '1' && modoComando == '0' && modoMov == '0'){
      mov=false;
      horario= true;
      //Serial.println("MODO HORARIO");
      //modo horario
    }else if(modoHorario == '0' && modoComando == '1' && modoMov == '0'){
      mov = false;
      horario= false;
      //Serial.println("MODO COMANDO");
      ilu.comando(stateLamp,statePers);
    }else if(modoHorario == '0' && modoComando == '0' && modoMov == '1'){
      //Serial.println("MODO MOVIMIENTO");
      //modo sensor movimiento
      mov = true;
      horario =false;
    }else{
      //Serial.println("MODO NO VALIDO POR FAVOR INSERTA 001, 010 O 100");
    }

      switch(modoCl){
    case 'c':
      calComando = true;
      break;
    case 'a':
      calComando =false;
      break;
    }
}  // End callback(...)
 
void reconnect() {
    // Ciclarse hasta lograr reconexión con "broker"
    while (!client.connected()) {
        Serial.print("Intentando conexión MQTT ...");
        // Create a random client ID
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        //Intentar reconexión ...
        // ... en caso de que el "broker" tenga clientID, username y password
        // ... cambiar la siguiente línea por --> if (client.connect(clientId,userName,passWord))
        if (client.connect(clientId.c_str())) {
            Serial.println("Conectado al 'broker' MQTT!!!");
            //Ya conectado al "borker" MQTT suscribirse al tópico
            client.subscribe(channelTopic);
        } else {
            Serial.print("Error de conexión, rc=");
            Serial.print(client.state());
            Serial.println(" ... reintentando en 5 seg.");
            // Esperar 6 segundos para el próximo intento de conexión
            delay(6000);
        }
    }
} //end reconnect()


void setup() {

    setTime(0,0,0,23,11,2021);//hr,min,seg,dia,mes,año

    pinMode(pinSensorMov, INPUT);
    pinMode(pinLed, OUTPUT);
    pinMode(ledPer, OUTPUT);
    
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);


    
    Serial.begin(9600);
    setup_wifi();
    //SECCION DEL MQTT    
    client.setServer(mqtt_server, 1883);//Usando el puerto 1883, estándar en MQTT
    client.setCallback(callback);

}

String dato(int digit){
  String dt = String("0")+digit;
  return dt.substring(dt.length()-2);
}

 
void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
    long ahora = millis();  //Obtener el reloj del sistema en milisegundos
    //Validar (por control de tiempo) si ya pasaron 0.5 segundos desde el reporte anterior
    if (ahora - tiempoAnterior > 500) {
        tiempoAnterior = ahora;
        
        int lecturaSensorA0=analogRead(SENSOR_A0);
        
        if(calComando == false){
            if(lecturaSensorA0 > 600){     
            cal.modoClima();
          }else if(lecturaSensorA0 < 300){
            cal.modoCalef();
          }else{
            cal.modoNeutro();
          } 
        }else if(calComando == true){
          cal.modoComando(modoCal);
        }
        
        //movimiento
        if(mov == true){ilu.movimiento();}
        if(horario == true){
          ilu.horario();
        }
        int temperatura = lecturaSensorA0/25;

                
        String msg="The temperature is (C°): ";
        msg= msg+temperatura;
        char message[58];
        msg.toCharArray(message,58);
        //Serial.println(message);
        //client.publish(channelTopic, message);
        
        if(ilu.lampState== 1 || ilu.curtainState==1){
          sprintf(query2,"INSERT into NodoIluminacion (fecha,idIlum,nodeId,lampstate,curtainState) VALUES('%d-%d-%d',%d,%d,%d,%d);",year(),month(),day(),1,1,ilu.lampState,ilu.curtainState);
          Serial.println(query2);
        }
        sprintf(query,"INSERT into NodoClima (fecha,idAireAcon,nodeId,temperature) VALUES('%d-%d-%d',%d,%d,%d);",year(),month(),day(),1,1,temperatura);
        Serial.println(query);
        delay(1000);
        
    }
}  //End loop
