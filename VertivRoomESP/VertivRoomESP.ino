#include <ESP8266WiFi.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_BUS 4  
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);

char ssid[] = "yale wireless";

WiFiClient client;                 // Use this for WiFi instead of EthernetClient
ESP8266WebServer server(80);

float t1, t2, t3;
char RESPONSE[] = "temperature1 : %f, temperature2 : %f, temperature3 : %f";
char RESPONSESTATUS[] = "Wireless Sensor Station Vertiv Room, MAC address : %s, ssid : %s, IP address : %s";
char response[128];
char mac[18];
String mac_string;

void setup(){
   sensors.begin();
   pinMode(LED_BUILTIN, OUTPUT);
   Serial.begin(9600);
   delay(500);
 
   Serial.println();
   Serial.print("MAC: ");
   Serial.println(WiFi.macAddress());
   Serial.printf("Connecting to %s ", ssid);
   WiFi.begin(ssid);
   while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
  Serial.println(WiFi.localIP());

  server.on("/temperature", temperature);
  server.on("/STATUS", statuspage);
  server.begin();
  Serial.println("Server Ready");
  delay(3000);
}
 
void loop() {
  server.handleClient();
}

void statuspage()
{
  digitalWrite(LED_BUILTIN, LOW);
  mac_string = WiFi.macAddress();
  mac_string.toCharArray(mac, 18);
  sprintf(response, RESPONSESTATUS, mac, ssid, WiFi.localIP().toString().c_str());
  server.send(200, "text/plain", response);
  digitalWrite(LED_BUILTIN, HIGH);
}

void temperature(){
  sensors.requestTemperatures();                // Send the command to get temperatures  
  float t1;
  float t2;
  float t3;
  t1 = sensors.getTempCByIndex(0);
  t2 = sensors.getTempCByIndex(1);
  t3 = sensors.getTempCByIndex(2);
  Serial.print("Temperature is: ");
  Serial.print(t1);
  Serial.print(", ");
  Serial.print(t2);
  Serial.print(", ");
  Serial.print(t3);
  Serial.println("");
  sprintf(response, RESPONSE, t1, t2, t3);
  server.send(200, "text/plain", response);
  }
