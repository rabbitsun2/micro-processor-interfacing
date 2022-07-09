#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;

#define DHTPIN A1     // DHT11이 연결된 핀


void setup() {
  Serial.begin(115200);

}

void loop() {
  DHT.read(DHTPIN);

  Serial.print("온도:");
  Serial.print(DHT.temperature);
  Serial.print("습도:");
  Serial.print(DHT.humidity);

  Serial.println();
  
}

/*
#include "DHT.h"

#define DHTPIN A1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


void setup(){
  Serial.begin(115200);
  dht.begin();  
}

void loop(){

  float humi = dht.readHumidity();
  float temp = dht.readTemperature();

  Serial.print("temperature:");
  Serial.print(temp);
  Serial.print("/");
  Serial.print("humidity:");
  Serial.print(humi);
  Serial.println();

  delay(100);

}
*/
