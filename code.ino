#include <ESP8266WiFi.h>
// Replace with your network credentials
// Connect to surajmukherjee@gmail.com for queries
const char* ssid = "Bhargava"; // Input your wifi network name
const char* password = "bhargava1234"; // Input your wifi password

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String relay1State = "off";
String relay2State = "off";
String relay3State = "off";
String relay4State = "off";
String relay5State = "off";
String relay6State = "off";
String relay7State = "off";
String relay0State = "off";
String relay8State = "off";
String relay9State = "off";

// Assign output variables to GPIO pins
const int relay1 = 16; // GPIO16 D0
const int relay2 = 5;  // GPIO5  D1
const int relay3 = 4;  // GPIO4  D2
const int relay4 = 0;  // GPIO0  D3
const int relay5 = 2;  // GPIO2  D4
const int relay6 = 14; // GPIO14 D5
const int relay7 = 12; // GPIO12 D6
const int relay0 = 13; // GPIO13 D7
const int relay8 = 15; // GPIO15 D8
const int relay9 = 3;  // GPIO3  D9

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay6, OUTPUT);
  pinMode(relay7, OUTPUT);
  pinMode(relay0, OUTPUT);
  pinMode(relay8, OUTPUT);
  pinMode(relay9, OUTPUT);
  // Set outputs to HIGH. relay active LOW
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  digitalWrite(relay0, HIGH);
  digitalWrite(relay8, HIGH);
  digitalWrite(relay9, HIGH);
  
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
    // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available(); // Listen for incoming clients

  if (client) { // If a new client connects,
    Serial.println("New Client."); // print a message out in the serial port
    String currentLine = ""; // make a String to hold incoming data from the client
    while (client.connected()) { // loop while the client's connected
      if (client.available()) { // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        Serial.write(c); // print it out the serial monitor
        header += c;
        if (c == '\n') { // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
             // turns the GPIOs on and off
            if (header.indexOf("GET /16/on") >= 0)
            {
              Serial.println("16 on");
              relay1State = "on";
              digitalWrite(relay1, LOW);
            }
            else if (header.indexOf("GET /16/off") >= 0)
            {
              Serial.println("16 off");
              relay1State = "off";
              digitalWrite(relay1, HIGH);
            }
            else if (header.indexOf("GET /5/on") >= 0) 
            { Serial.println("5 on");
              relay2State = "on";
              digitalWrite(relay2, LOW);
            }
            else if (header.indexOf("GET /5/off") >= 0) 
            { Serial.println("5 off");
              relay2State = "off";
              digitalWrite(relay2, HIGH);
            }
            else if (header.indexOf("GET /4/on") >= 0)
            {
              Serial.println("4 on");
              relay3State = "on";
              digitalWrite(relay3, LOW0);
