#include <ESP8266WiFi.h>

const char* ssid = "MECHANIC";
const char* password = "code9998";
unsigned char status_led=0;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  //Concect to WiFi Network
  Serial.println();
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  //Start The Server
  server.begin();
  Serial.println("Server started at. . .");
  Serial.println(WiFi.localIP());
}

void loop() {
  //Check status client
  WiFiClient client = server.available();
  if (!client.available()){
    delay(1);
  }

  //Read First Line Request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  //Match Request
  if (req.indexOf("/ledoff") != -1) {
    status_led=0;
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("LED OFF");
  }
  else if(req.indexOf("/ledon") != -1) {
    status_led=1;
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("LED ON");
  }

  //Return Response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println(""); 

  client.println("<!DOCTYPE HTML>");
  client.println("<HTML>");
  client.println("<H1> LED CONTROL </H1>");
  client.println("<br />");
 
  client.println("<a href=\"/ledon\"\"> <button style='FONT-SIZE: 50px; HEIGHT: 200px;WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> LED ON </button> </a>");
  client.println("<a href=\"/ledoff\"\"> <button style='FONT-SIZE: 50px; HEIGHT: 200px; WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> LED OFF </button> </a>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}