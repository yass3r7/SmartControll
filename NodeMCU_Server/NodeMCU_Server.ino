// NodeMCU esp
#include <ESP8266WiFi.h>
// Server
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Settings Vars
bool ini = false;
bool success = false;
int IN1 = 16; // D0
int IN2 = 5; // D1
int IN3 = 4; // D2
int IN4 = 0; // D3

// WiFi Network
const char ssid[] = "IEP"; // WiFi SSID
const char password[] = "IEP2021_by7"; // Password

// Network static IP
IPAddress ip(192, 168, 1, 100); // NodeMCU Fixed IP
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// Create web server
ESP8266WebServer server(80);

void setup() {

  // Connect to WiFi
  WiFi.disconnect();
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);
  
  while (WiFi.status() != WL_CONNECTED) {
    success = false;
    delay(500);
  }
  success = true;
  
  // Main Pins
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Handle server pages
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  // Tells the server tp begin listening for incoming requests
  server.begin();
}

void loop() {
  if (!ini) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    ini = true;
  }
  
  if (success) {
    digitalWrite(LED_BUILTIN, LOW);
    server.handleClient();
  }
}

void handleRoot() {
  if (server.argName(0) == "p1") { // 16 5 4 0
    if (server.arg(0) == "on") {
      digitalWrite(IN1, LOW);
    } else {
      digitalWrite(IN1, HIGH);
    }
  }

  if (server.argName(1) == "p2") {
    if (server.arg(1) == "on") {
      digitalWrite(IN2, LOW);
    } else {
      digitalWrite(IN2, HIGH);
    }
  }

  if (server.argName(2) == "p3") {
    if (server.arg(2) == "on") {
      digitalWrite(IN3, LOW);
    } else {
      digitalWrite(IN3, HIGH);
    }
  }

  if (server.argName(3) == "p4") {
    if (server.arg(3) == "on") {
      digitalWrite(IN4, LOW);
    } else {
      digitalWrite(IN4, HIGH);
    }
  }

  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", "{\"result\": \"success\"}");
}

void handleNotFound() {
  server.send(404, "text/html", "<h1>Page Not Found</h1>");
}
