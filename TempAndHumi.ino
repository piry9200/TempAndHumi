#include<DHTesp.h>
#define sensorPin 32
DHTesp dht;

void setup() {
  Serial.begin(115200);
  dht.setup(sensorPin,DHTesp::DHT11);
}

void loop() {
  TempAndHumidity newValues = dht.getTempAndHumidity();
  if(dht.getStatus() != 0){
    Serial.println("DHT11 error status:"+String(dht.getStatusString()));
  }
  float temp = newValues.temperature;
  float hemi = newValues.humidity;
  Serial.print("温度:");
  Serial.print(temp);
  Serial.print(" ");
  Serial.print("湿度:");
  Serial.println(hemi);
  delay(3000);
}
