#include <BH1750FVI.h>
#include <WiFiNINA.h>

char ssid[] = "Angad";                // your network SSID (name)
char pass[] = "mdrzx330bt";                // your network password (use for WPA, or use as key for WEP)

WiFiClient client;
BH1750FVI Sensor(BH1750FVI::k_DevModeContLowRes);

char   HOST_NAME[] = "maker.ifttt.com";
String queryString = "?value1=57&value2=25";
bool light;

void setup() {
  WiFi.begin(ssid, pass);

  Serial.begin(9600);
  while (!Serial);

  // connect to web server on port 80:
  if (client.connect(HOST_NAME, 80)) {
    // if connected:
    Serial.println("Connected to server");
  }
  else {// if not connected:
    Serial.println("connection failed");
  }
}
void sunlight_detected() {
  while (!Serial);

  // connect to web server on port 80:
  if (client.connect(HOST_NAME, 80)) {
    // if connected:
    Serial.println("Connected to server");
  }
  else {// if not connected:
    Serial.println("connection failed");
  }
  
  String PATH   = "/trigger/sunlight_detected/with/key/is7ETz0Gt6Xdaa9awR7GlCtGgFx8LayOKx6SR9rDkSQ"; // change your EVENT-NAME and YOUR-KEY
  
  // make a HTTP request:
  // send HTTP header
  client.println("GET " + PATH + queryString + " HTTP/1.1");
  client.println("Host: " + String(HOST_NAME));
  client.println("Connection: close");
  client.println(); // end HTTP header


  while (client.connected()) {
    if (client.available()) {
      // read an incoming byte from the server and print it to serial monitor:
      char c = client.read();
      Serial.print(c);
    }
  }
  
  client.stop();
  Serial.println();
  Serial.println("disconnected");
  
  light = true;
}

void sunlight_stop() {
  while (!Serial);

  // connect to web server on port 80:
  if (client.connect(HOST_NAME, 80)) {
    // if connected:
    Serial.println("Connected to server");
  }
  else {// if not connected:
    Serial.println("connection failed");
  }
  
  String PATH   = "/trigger/sunlight_stop/with/key/is7ETz0Gt6Xdaa9awR7GlCtGgFx8LayOKx6SR9rDkSQ"; // change your EVENT-NAME and YOUR-KEY
  
  // make a HTTP request:
  // send HTTP header
  client.println("GET " + PATH + queryString + " HTTP/1.1");
  client.println("Host: " + String(HOST_NAME));
  client.println("Connection: close");
  client.println(); // end HTTP header


  while (client.connected()) {
    if (client.available()) {
      // read an incoming byte from the server and print it to serial monitor:
      char c = client.read();
      Serial.print(c);
      }
    }
    
  client.stop();
  Serial.println();
  Serial.println("disconnected");
  
  light = false;
}

void loop() {
  int lightLevel = Sensor.GetLightIntensity();
  
  if(lightLevel > 50 && light == false)
  {
    sunlight_detected();
    delay(10000);
  }
  else if(lightLevel < 50 && light == true){
    sunlight_stop();
    delay(10000);
  }
}
