
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

const uint8_t sensor_address = 0x76;

char ssid[] = "yale wireless";

Adafruit_BME280 bme; // I2C

float h, t, p;
char RESPONSE_BME280[] = "temperature : %f, humidity : %f, pressure : %f";
char RESPONSESTATUS[] = "Wireless Sensor Station Lasertable 2, MAC address : %s, ssid : %s, IP address : %s";
char response[128];
char mac[18];
String mac_string;

//ESP8266WebServer server(80);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(9600);
  delay(500);
  Serial.println();

//  Serial.print("MAC: ");
//  Serial.println(WiFi.macAddress());
//  Serial.printf("Connecting to %s ", ssid);
//  WiFi.begin(ssid);
//  while (WiFi.status() != WL_CONNECTED)
//  {
//    digitalWrite(LED_BUILTIN, LOW);
//    delay(500);
//    digitalWrite(LED_BUILTIN, HIGH);
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.println(" connected");
//  Serial.println(WiFi.localIP());
//  digitalWrite(LED_BUILTIN, HIGH);

  Wire.begin(D3, D4);
  Wire.setClock(100000);

  Serial.println(F("Connect to BME280"));

  if (!bme.begin(sensor_address)) {
    Serial.println("BME280 not connected");
    while (1);
  }
  bme.setSampling(Adafruit_BME280::MODE_FORCED,
                  Adafruit_BME280::SAMPLING_X1, // temperature
                  Adafruit_BME280::SAMPLING_X1, // pressure
                  Adafruit_BME280::SAMPLING_X1, // humidity
                  Adafruit_BME280::FILTER_OFF   );

  sensors.begin();
  
  if (bme.begin(sensor_address)) {
    bme.takeForcedMeasurement();
    h = bme.readHumidity();
    t = bme.readTemperature();
    p = bme.readPressure() / 100.0F;
    Serial.printf("temperature : %f, humidity : %f, pressure : %f", t, h, p);
    Serial.println("");
  }
//  server.on("/BME280", bme280);
//  server.on("/STATUS", statuspage);
//  server.begin();
  Serial.println("Server Ready");
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  //server.handleClient();
}

void statuspage()
{
  digitalWrite(LED_BUILTIN, LOW);
//  mac_string = WiFi.macAddress();
//  mac_string.toCharArray(mac, 18);
//  sprintf(response, RESPONSESTATUS, mac, ssid, WiFi.localIP().toString().c_str());
//  server.send(200, "text/plain", response);
  digitalWrite(LED_BUILTIN, HIGH);
}

void bme280() {
  digitalWrite(LED_BUILTIN, LOW);
  if (bme.begin(sensor_address)) {
    bme.takeForcedMeasurement();
    h = bme.readHumidity();
    t = bme.readTemperature();
    p = bme.readPressure() / 100.0F;
    Serial.printf("temperature : %f, humidity : %f, pressure : %f", t, h, p);
    Serial.println("");
    sprintf(response, RESPONSE_BME280, t, h, p);
//    server.send(200, "text/plain", response);
  }
//  else {
//    server.send(200, "text/plain", "BME280 not connected");
//  }
  digitalWrite(LED_BUILTIN, HIGH);
}
