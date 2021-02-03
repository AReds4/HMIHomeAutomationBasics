#include <Modbus.h>
#include <ModbusIP_ESP8266.h>
#include <ModbusRTU.h>
#include <ESP8266WiFi.h> // Include ESP8266Wifi library

ModbusIP modbus;
const int port = 502;
void setup()
{
  Serial.begin(57600); // Intialize baud rate for serial monitor
  Serial.println(); // Print a blank line within serial monitor
  WiFi.begin("CBCI-D304-2.4", "camera8810brook"); // Initialialize the connection
  
  Serial.print("Connecting"); // Print "connecting" in serial monitor
  while (WiFi.status() != WL_CONNECTED) //  While WiFi is not connected
  {
    delay(500); // wait 500ms
    Serial.print("."); // print a dot... the output will look like " Connecting....."
  }
  Serial.println(); // Print a blank line within serial monitor

  Serial.print("Connected, IP address: "); // When While loop exits print "Connected, IP address:
  Serial.println(WiFi.localIP()); // Print the IP address of our ESP8266

  modbus.server(port);// Start our web server (listen on port 502)
}
void loop() {
Serial.println(WiFi.localIP());
}
