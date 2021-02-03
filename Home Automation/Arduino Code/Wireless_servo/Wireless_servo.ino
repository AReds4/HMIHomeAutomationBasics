#include <Modbus.h>
#include <ModbusIP_ESP8266.h>
#include <ModbusRTU.h>
#include <ESP8266WiFi.h> // Include ESP8266Wifi library
#include <Servo.h>

Servo Servo1;
Servo Servo2;
int Servo1Pin=D7;
int Servo2Pin=D8;
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
  modbus.addCoil(0,false,15);
  modbus.addHreg(0,10,5);

Servo1.attach(Servo1Pin);  
Servo2.attach(Servo2Pin);  
pinMode(Servo1Pin,OUTPUT);
pinMode(Servo2Pin,OUTPUT);

}

void loop() {
  modbus.task();
  int Num=modbus.Hreg(1);
  delay(10);
  Servo1.write(Num);
  Servo2.write(Num);
  Serial.print(Num);
}
