
#include <Servo.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h> 

#define D0 16   // Arriba derecha 1
#define D1 5    // Arriba derecha 2
#define D2 4    // Arriba derecha 3
#define D3 0    // Arriba derecha 4
#define D4 2    // Arriba derecha 5
// Posiciones 6 3V3, 7 GND
#define D5 14   // Arriba derecha 8
#define D6 12   // Arriba derecha 9
#define D7 13   // Arriba derecha 10
#define D8 15   // Arriba derecha 11
#define SD3 10  // Arriba izquierda 4
#define SD2  9  // Arriba izquierda 5



const char* ssid = "Tec-IoT";
const char* password = "spotless.magnetic.bridge";

//const char* ssid = "Alegría";
//const char* password = "024681012";

const char* mqtt_server = "broker.emqx.io";
const char* topico_salida = "TopicoOutTemp1";

WiFiClientSecure espClient;
PubSubClient client(espClient);

Servo servoMotor1; //Window 1
Servo servoMotor2; //Window 1
Servo servoMotor3; //Window 2
Servo servoMotor4; //Window 2
Servo servoMotor5; //Window 3
Servo servoMotor6; //Window 3

void setup_wifi() {
  delay(10);
  Serial.println();    
  Serial.print("Connecting to ");   
  Serial.println(ssid);

  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println(""); Serial.println("WiFi connected"); Serial.print("IP address: "); Serial.println(WiFi.localIP());
}

void enviarRegistro(String jsonBody){
  String requestUrl = "https://iotrestapi.onrender.com/iot/api/insertRegistro";
  if (WiFi.status() == WL_CONNECTED) { 
    HTTPClient http; 
    http.begin(espClient,requestUrl);

    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(jsonBody); 

    if (httpResponseCode > 0) {
      String response = http.getString(); 
      Serial.println("Response code: " + String(httpResponseCode));
      Serial.println("Response: " + response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }
}

void obtenerRango(int id_cuarto, String sensor, float valor){
  String requestUrl = "https://iotrestapi.onrender.com/iot/api/getRange";
  String jsonBody;
  if (WiFi.status() == WL_CONNECTED) { 
    HTTPClient http;
    http.begin(espClient,requestUrl); 

    http.addHeader("Content-Type", "application/json");

    jsonBody = "{\"sensor\": \"" + sensor + "\",\"id_cuarto\":" + String(id_cuarto) + "}";

    int httpResponseCode = http.POST(jsonBody); 
    
    if (httpResponseCode > 0) {
      String response = http.getString(); 
      Serial.println("Response code: " + String(httpResponseCode));
      Serial.println("Response: " + response);
      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, response);
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
      }
      JsonObject data = doc["data"][0];

      float minimum = data["minimum"];
      float maximum = data["maximum"];

      actuadorCuarto(sensor, id_cuarto, valor, minimum, maximum);
  
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }
  
}

void revisarRangos(String jsonBody){
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, jsonBody);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  int id_cuarto = doc["id_cuarto"];
  float temp = doc["temp"];
  float humedad = doc["humedad"];
  float calidad = doc["calidad"];

  obtenerRango(id_cuarto, "temp", temp);
  obtenerRango(id_cuarto, "humedad", humedad);
  obtenerRango(id_cuarto, "calidad", calidad);
}

void actuadorCuarto(String sensor, int id_cuarto, float valor, float minimum, float maximum){
  int rango = checkRange(valor, minimum, maximum);
  if(id_cuarto == 1){
    if(sensor == "temp"){
      if(rango == 0){
        Serial.println("Temperatura Baja en el cuarto 1");
        digitalWrite(D2,HIGH); //Calentador
      }
      if(rango == 1){
        Serial.println("Temperatura Normal en el cuarto 1");
        digitalWrite(D2,LOW);
      }
      if(rango == 2){
        Serial.println("Temperatura Alta en el cuarto 1");
        digitalWrite(D2,HIGH);//Clima
      }
    }
    if(sensor == "humedad"){
      if(rango == 0){
        Serial.println("Humedad Baja en el cuarto 1");

        //Ventanas y Abanico

        servoMotor1.write(135);
        servoMotor2.write(45); 

        digitalWrite(D2,HIGH);
      }
      if(rango == 1){
        Serial.println("Humedad Normal en el cuarto 1");

        servoMotor1.write(0);
        servoMotor2.write(180);

        digitalWrite(D2,LOW);
      }
      if(rango == 2){
        Serial.println("Humedad Alta en el cuarto 1");

        servoMotor1.write(135);
        servoMotor2.write(45);  

        digitalWrite(D2,HIGH);
      }
    }
    if(sensor == "calidad"){
      if(rango == 0){
        Serial.println("Calidad del aire Baja en el cuarto 1");
        //Esto no debería de pasar porque el valor mínimo debe ser 0
      }
      if(rango == 1){
        Serial.println("Calidad del air Normal en el cuarto 1");

        servoMotor1.write(0);
        servoMotor2.write(180);

      }
      if(rango == 2){
        Serial.println("Calidad del air Alta en el cuarto 1");

        servoMotor1.write(135);
        servoMotor2.write(45); 
      }
    }
  } else if(id_cuarto == 2){
    if(sensor == "temp"){
      if(rango == 0){
        Serial.println("Temperatura Baja en el cuarto 2");
        digitalWrite(D5,HIGH); //Calentador
      }
      if(rango == 1){
        Serial.println("Temperatura Normal en el cuarto 2");
        digitalWrite(D5,LOW);
      }
      if(rango == 2){
        Serial.println("Temperatura Alta en el cuarto 2");
        digitalWrite(D5,HIGH);//Clima
      }
    }
    if(sensor == "humedad"){
      if(rango == 0){
        Serial.println("Humedad Baja en el cuarto 2");

        //Ventanas y Abanico

        servoMotor3.write(135);
        servoMotor4.write(45);

        digitalWrite(D5,HIGH);
      }
      if(rango == 1){
        Serial.println("Humedad Normal en el cuarto 2");

        servoMotor3.write(0);
        servoMotor4.write(180);

        digitalWrite(D5,LOW);
      }
      if(rango == 2){
        Serial.println("Humedad Alta en el cuarto 2");

        servoMotor3.write(135);
        servoMotor4.write(45);

        digitalWrite(D5,HIGH);
      }
    }
    if(sensor == "calidad"){
      if(rango == 0){
        Serial.println("Calidad del aire Baja en el cuarto 2");
        //Esto no debería de pasar porque el valor mínimo debe ser 0
      }
      if(rango == 1){
        Serial.println("Calidad del air Normal en el cuarto 2");

        servoMotor3.write(0);
        servoMotor4.write(180);

      }
      if(rango == 2){
        Serial.println("Calidad del air Alta en el cuarto 2");

        servoMotor3.write(135);
        servoMotor4.write(45);
      }
    }
  } else if(id_cuarto == 3){
    if(sensor == "temp"){
      if(rango == 0){
        Serial.println("Temperatura Baja en el cuarto 3");
        digitalWrite(D8,HIGH); //Calentador
      }
      if(rango == 1){
        Serial.println("Temperatura Normal en el cuarto 3");
        digitalWrite(D8,LOW);
      }
      if(rango == 2){
        Serial.println("Temperatura Alta en el cuarto 3");
        digitalWrite(D8,HIGH);//Clima
      }
    }
    if(sensor == "humedad"){
      if(rango == 0){
        Serial.println("Humedad Baja en el cuarto 3");

        //Ventanas y Abanico

        
        servoMotor5.write(135);
        servoMotor6.write(45); 

        digitalWrite(D8,HIGH);
      }
      if(rango == 1){
        Serial.println("Humedad Normal en el cuarto 3");

        servoMotor5.write(0);
        servoMotor6.write(180);

        digitalWrite(D8,LOW);
      }
      if(rango == 2){
        Serial.println("Humedad Alta en el cuarto 3");

        servoMotor5.write(135);
        servoMotor6.write(45); 

        digitalWrite(D8,HIGH);
      }
    }
    if(sensor == "calidad"){
      if(rango == 0){
        Serial.println("Calidad del aire Baja en el cuarto 3");
        //Esto no debería de pasar porque el valor mínimo debe ser 0
      }
      if(rango == 1){
        Serial.println("Calidad del air Normal en el cuarto 3");

        servoMotor5.write(0);
        servoMotor6.write(180);

      }
      if(rango == 2){
        Serial.println("Calidad del air Alta en el cuarto 3");

        servoMotor5.write(135);
        servoMotor6.write(45);
      }
    }
  }
}

int checkRange(float valor, float minimum, float maximum){
  int output = 3;

  if(valor < minimum){
    output = 0; //Bajo del rango
  }
  if(valor >= minimum && valor <= maximum){
    output = 1; //Dentro del rango
  }
  if(valor > maximum){
    output = 2; //Arriba del rango
  }
  return output;
}
  
void setup() {
  Serial.begin(9600);
  espClient.setInsecure();
  setup_wifi();

  servoMotor1.attach(D0); //1
  servoMotor2.attach(D1); //1
  servoMotor3.attach(D3); //2
  servoMotor4.attach(D4); //2
  servoMotor5.attach(D6); //3
  servoMotor6.attach(D7); //3

  pinMode(D2, OUTPUT); //1
  pinMode(D5, OUTPUT); //2
  pinMode(D8, OUTPUT); //3
}

void loop() {
  if (Serial.available()) {
        String data = Serial.readStringUntil('\n');
        // Parse data as needed
        Serial.println("Received: " + data);
        enviarRegistro(data);
        revisarRangos(data);
    }
}
