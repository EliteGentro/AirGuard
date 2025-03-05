#include "DHT.h"
#define DHTPIN1 2  // Posicion equivalente a D2
#define DHTPIN2 3  // Posicion equivalente a D3
#define DHTPIN3 4  // Posicion equivalente a D4
#define DHTTYPE DHT11
DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
DHT dht3(DHTPIN3, DHTTYPE);

#define MSG_BUFFER_SIZE 100
char registroCuarto1[MSG_BUFFER_SIZE];
char registroCuarto2[MSG_BUFFER_SIZE];
char registroCuarto3[MSG_BUFFER_SIZE];



void medirCuarato1(){
  delay(1000);
  float h = dht1.readHumidity();
  float t = dht1.readTemperature();
     
  if (isnan(h) || isnan(t)) {
    Serial.print("Falló al leer el sensor DHT1\n");
    return;
  }

  int tint = t*100;
  int hint = h*100;

  int c = analogRead(A0);

  snprintf(registroCuarto1, MSG_BUFFER_SIZE, "{\"id_cuarto\":1,\"temp\":%d.%02d,\"humedad\":%d.%02d,\"calidad\":%d}", tint/100 , tint % 100, hint/100, hint % 100,c);
  Serial.println(registroCuarto1);
}

void medirCuarato2(){
  delay(1000);
  float h = dht2.readHumidity();
  float t = dht2.readTemperature();
     
  if (isnan(h) || isnan(t)) {
    Serial.print("Falló al leer el sensor DHT2\n");
    return;
  }

  int tint = t*100;
  int hint = h*100;

  int c = analogRead(A1);

  snprintf(registroCuarto2, MSG_BUFFER_SIZE, "{\"id_cuarto\":2,\"temp\":%d.%02d,\"humedad\":%d.%02d,\"calidad\":%d}", tint/100 , tint % 100, hint/100, hint % 100,c);
  Serial.println(registroCuarto2);
}

void medirCuarato3(){
  delay(1000);
  float h = dht3.readHumidity();
  float t = dht3.readTemperature();
     
  if (isnan(h) || isnan(t)) {
    Serial.print("Falló al leer el sensor DHT3\n");
    return;
  }

  int tint = t*100;
  int hint = h*100;

  int c = analogRead(A2);

  snprintf(registroCuarto3, MSG_BUFFER_SIZE, "{\"id_cuarto\":3,\"temp\":%d.%02d,\"humedad\":%d.%02d,\"calidad\":%d}", tint/100 , tint % 100, hint/100, hint % 100,c);
  Serial.println(registroCuarto3);
}

void setup() {
    Serial.begin(9600);
    dht1.begin();
    dht2.begin();
    dht3.begin();
}

void loop() {
  medirCuarato1();
  delay(10000);
  medirCuarato2();
  delay(10000);
  medirCuarato3();
  delay(10000);
  //Resetear los valores de los strings por si llega a haber un error de lectura
  snprintf(registroCuarto1, MSG_BUFFER_SIZE, "{\"id_cuarto\":1,\"temp\":0,\"humedad\":0,\"calidad\":0}");
  snprintf(registroCuarto2, MSG_BUFFER_SIZE, "{\"id_cuarto\":2,\"temp\":0,\"humedad\":0,\"calidad\":0}");
  snprintf(registroCuarto3, MSG_BUFFER_SIZE, "{\"id_cuarto\":3,\"temp\":0,\"humedad\":0,\"calidad\":0}");
}
