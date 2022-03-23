#include <ESP8266WiFi.h>
// NAMA : WAHYU HANAFI
// NIM  : 3332190073
// TUGAS 3 SISTEM EMBEDDED

const char* ssid = "MECHANIC"; // menyambung pada nama wifi yang ingin dikonekkan
const char* password = "code9998"; // password wifi yang ingin dikonekkan
unsigned char status_led=0;

WiFiServer server(80);

void setup() {
  Serial.begin(115200); // menginisialisasi serial monitor pada 115200 baud
  pinMode(LED_BUILTIN, OUTPUT); // merubah mode pin LED menjadi mode output(keluaran)
  digitalWrite(LED_BUILTIN, HIGH); // kondisi awal pin LED dimatikan, disini ESP8266 Aktif low

  //Concect to WiFi Network
  Serial.println();			// menghubungkan ke wifi/ssid yang ingin dituju
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password); // login ke wifi dengan menggunakan ssid dan password diatas

  while (WiFi.status() != WL_CONNECTED) {		// ketika wifi konek
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected"); //menampilkan status konek pada serial monitor

  //Start The Server
  server.begin();
  Serial.println("Server started at. . .");
  Serial.println(WiFi.localIP());	// menampilkan local ip pada wifi yang kita konekkan
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
  if (req.indexOf("/ledoff") != -1) {	// ketika tombol off ditekan pada webserver yang tertampil diline 70
    status_led=0;
    digitalWrite(LED_BUILTIN, HIGH);  // maka LED diberi logika HIGH(mati) ket : ESP8266 aktif low
    Serial.println("LED OFF");		// keterangan LED Off pada serial monitor 
  }
  else if(req.indexOf("/ledon") != -1) {	// ketika tombol on ditekan pada webserver yang tertampil diline 69
    status_led=1;
    digitalWrite(LED_BUILTIN, LOW);	// maka LED diberi logika LOW(nyala) ket : ESP8266 aktif low
    Serial.println("LED ON");		// keterangan LED ON pada serial monitor
  }

  //Return Response
  //disini untuk menampilkan respon balik pada codingan html dibawah ini yang akan dieksekusi dimatch request
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
