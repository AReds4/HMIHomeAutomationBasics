#include <Modbus.h>
#include <ModbusIP_ESP8266.h>
#include <ModbusRTU.h>
#include <FastLED.h>
#include <ESP8266WiFi.h> // Include ESP8266Wifi library

#define CLOCK_PIN 8
#define NUM_LEDS 60
#define DATA_PIN 8
#define BRIGHTNESS  255
#define COLOR_ORDER GRB
String COLOR="Green";
CRGB leds[NUM_LEDS];
  int i;
float voltage = 0;
float degreesF = 0;  
float degreesC = 0;

int count=1;
ModbusIP modbus;
const int ledPin = D0;
const int TempInp = A0;
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
  modbus.addCoil(0,false,15);//adds 15 coils starting from register 0
  modbus.addHreg(0,1,5);//adds 5 registers staring from 0
  pinMode(ledPin, OUTPUT);//Sets pin D0 as an output
  
 FastLED.addLeds<WS2812B, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
 modbus.Hreg(1,BRIGHTNESS);// reads the value of register 4x-1 to determine brightness
}
void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }//Used for 
void loop() {
  modbus.task();

  //Roughly estimates room temperature and prints the value to register 0x 0
if(count>=10000){
  voltage = (analogRead(TempInp) * 0.004882813);   
  degreesC = (voltage - 0.5) * 100.0;
  degreesF = (degreesC * (9.0 / 5.0) + 32.0)-74.89;
  modbus.Hreg(0,degreesF);
  
  count=0;}
  count+=1;
  
  FastLED.setBrightness(modbus.Hreg(1));

  //Following If statements will print a certain color when the corresponding bit is turned on.
if(modbus.Coil(0)==1){
  for (i=0; i< NUM_LEDS; i = i + 1) {
    leds[i] = CRGB::  Black;
  }}
  
if(modbus.Coil(1)==1){
  for (i=0; i< NUM_LEDS; i = i + 1) {
    leds[i] = CRGB::  White;
  }}
  
if(modbus.Coil(2)==1){
  for (i=0; i< NUM_LEDS; i = i + 1) {
    leds[i] = CRGB::  Yellow;
  }}
  
if(modbus.Coil(3)==1){
  for (i=0; i< NUM_LEDS; i = i + 1) {
    leds[i] = CRGB::  Orange;
  }}
  
if(modbus.Coil(4)==1){
  for (i=0; i< NUM_LEDS; i = i + 1) {
    leds[i] = CRGB::  Red;
  }}
  
if(modbus.Coil(5)==1){
  for (i=0; i< NUM_LEDS; i = i + 1) {
    leds[i] = CRGB::  Green;
  }}
  
if(modbus.Coil(6)==1){
  for (i=0; i< NUM_LEDS; i = i + 1) {
    leds[i] = CRGB::  Blue;
  }}

 
if(modbus.Coil(10)==1){
  for (i=0; i< NUM_LEDS; i = i + 1) {
    leds[i] = CRGB(modbus.Hreg(2),modbus.Hreg(3),modbus.Hreg(4));
  }}
  //will print a random color to each individual LED
if (count%100==0)
if(modbus.Coil(9)==1){
  for (i=0; i< NUM_LEDS; i = i + 1) {
    leds[i] = CRGB(random(20,255),random(20,255),random(20,255));
  }}

//will rotate the LED strip through an array of colors when bit 9 is on
  if (count%80==0){
    if(modbus.Coil(11)==1){
       modbus.task();
    static uint8_t hue = 0;
  Serial.print("x");
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show(); 
    fadeall();
    delay(10);
  }
  Serial.print("x"); 
  for(int i = (NUM_LEDS)-1; i >= 0; i--) {
    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show();
    fadeall();
    delay(10);
  }}
  }
  
  //sets every LED to one random color.
  if (count%80==0){
    if(modbus.Coil(12)==1){
       int r1=random(0,255);
       int r2=random(0,255);
       int r3=random(0,255);
       for (i=0; i< NUM_LEDS; i = i + 1) {
    leds[i] = CRGB(r1,r2,r3);
    FastLED.show();
    delay(10);
  }
       }
  }
    FastLED.show();
}
