#include <WiFi.h>
#include <WiFiUDP.h>

const char ssid[] = "************"; // ルーターのSSID
const char pass[] = "************";  // ルーターのpassword

static WiFiUDP wifiUdp; 
static const char *kRemoteIpadr = "***.***.***.**"; //送信先のIPアドレス
static const int kRmoteUdpPort = 9000; //送信先のポート


static const int sensorPin = 32;
DHTesp dht;

static void WiFi_setup()
{
  static const int kLocalPort = 7000;  //自身のポート
  const IPAddress ip(192,168,1,201);//espp32のIPアドレスを固定
  const IPAddress subnet(255,255,255,0);
  WiFI.config(ip,ip,subnet); //espp32のIPアドレスを固定

  WiFi.begin(ssid, pass);
  while( WiFi.status() != WL_CONNECTED) {
    delay(500);  
  }  
  wifiUdp.begin(kLocalPort);
}

static void Serial_setup()
{
  Serial.begin(115200);
  Serial.println(""); //　改行用
}

void setup() {
  Serial_setup();
  WiFi_setup();
  dht.setup(sensorPin,DHTesp::DHT11);
}

void loop() 
{
  TempAndHumidity newValues = dht.getTempAndHumidity();
  if(dht.getStatus() != 0){
  Serial.println("DHT11 error status:"+String(dht.getStatusString()));
  }
  float temp = newValues.temperature;
  float hemi = newValues.humidity;

  wifiUdp.beginPacket(kRemoteIpadr, kRemoteUdpPort);
  wifiUdp.write(temp);
  wifiUdp.write(hemi);
  wifiUdp.endPacket();  

  delay(3000); //3秒ごとに温度湿度のデータを発信し続ける

}

