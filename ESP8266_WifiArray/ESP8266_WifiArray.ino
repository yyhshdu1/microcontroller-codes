
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();

const short len = 1000;
bool ready = false;
bool start = false;

char ssid[] = "yale wireless";

char RESPONSE_MMA8451[] = "%d,%d,%d,%d;";
char RESPONSESTATUS[] = "Wireless Sensor Station Vibration 1, MAC address : %s, ssid : %s, IP address : %s";
char response[128];
char mac[18];
String mac_string;

unsigned long t[len];
short x[len];
short y[len];
short z[len];

unsigned long t_html[len];
short x_html[len];
short y_html[len];
short z_html[len];


ESP8266WebServer server(80);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
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
  digitalWrite(LED_BUILTIN, HIGH);

  if (! mma.begin()) {
    while (1);
  }
  Serial.println("MMA8451 connected");
  
  mma.setRange(MMA8451_RANGE_2_G);  

  server.on("/STATUS", statuspage);
  server.on("/START", startpage);
  server.on("/STOP", stoppage);
  server.on("/MMA8451", mma8451);
  server.begin();
  Serial.println("Server Ready");
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  if (start == true)
  {
    mma8451_data();
  }
}

void copy_short(short* src, short* dst, short len) {
    for (short i = 0; i < len; i++) {
        *dst++ = *src++;
    }
}
void copy_ulong(unsigned long* src, unsigned long* dst, short len){
    for (short i = 0; i < len; i++) {
        *dst++ = *src++;
    }
}

void mma8451_data(){
  unsigned long tstart = micros();
  for (int i = 0; i < len; i++){
      mma.read();
      t[i] = micros() - tstart;
      x[i] = mma.x;
      y[i] = mma.y;
      z[i] = mma.z;
//      x[i] = i;
//      y[i] = i;
//      z[i] = i;
      delay(5);
  }
  Serial.println("Acquisition ready");
  ready = true;
  copy_short(x, x_html, len);
  copy_short(y, y_html, len);
  copy_short(z, z_html, len);
  copy_ulong(t, t_html, len);
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

void startpage()
{
  start = true;
  server.send(200, "text/plain", "Start MMA8451 acquisition");
}

void stoppage()
{
  start = false;
  server.send(200, "text/plain", "Stop MMA8451 acquisition");
}

void mma8451() {
  digitalWrite(LED_BUILTIN, LOW);
  String resp = "";
  if (ready == true && start == true){
    for(int i = 0; i < len; i++)
    {
      sprintf(response, RESPONSE_MMA8451, t_html[i], x_html[i], y_html[i], z_html[i]);
      resp += String(response);
    }
    server.send(200, "text/plain", resp);
  }
  else {
    server.send(200, "text/plain", "Acquisition not started");
  }
    
  digitalWrite(LED_BUILTIN, HIGH);
}
