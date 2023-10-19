#include <WiFi.h>

const char* ssid = "Proxima";
const char* password = "centauri";
const char* serverIP = "10.61.22.17";
const int serverPort = 3000; 
// This project requires an internet connection - everything worked on my home wifi however because proxima
//doesnt have internet it will not work. Please use a network with an internet connection.

WiFiClient client;

#define buzzerPin 21
#define echoPin 26
#define trigPin 25

long duration;
int distance;
int counter;
int previousDistance = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  Serial.begin(9600);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  if (counter % 5 == 0) {
    float speed = abs(previousDistance - distance) / 0.083; // in cm/s
    sendToServer(speed / 100.0); // Convert to m/s before sending
    previousDistance = distance;
  }
  counter++;

  delay(100);  // Add a delay to avoid spamming the server
}

void sendToServer(float speed) {
  String speedStr = String(speed, 2);

  if (client.connect(serverIP, serverPort)) {
    client.println("POST /speed HTTP/1.1");
    client.println("Host: " + String(serverIP));
    client.println("Content-Length: " + String(speedStr.length()));
    client.println("Content-Type: text/plain");
    client.println();
    client.println(speedStr); 

    Serial.println("Sent speed to server: " + speedStr);
    client.stop();
  } else {
    Serial.println("Failed to connect to server.");
  }
if (speed >= 7) {
   digitalWrite(LEDPin, HIGH);
   digitalWrite(LEDPin, LOW);
   digitalWrite(LEDPin, HIGH);
}
}
