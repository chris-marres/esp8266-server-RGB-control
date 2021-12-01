#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WebServer.h>
#include "Arduino.h"
#include <Vector.h>
using namespace std;
#define PIN 4
#define TOTAL_LEDS 30
#define INTENSITY 255  //1-255 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(TOTAL_LEDS, PIN, NEO_GRB + NEO_KHZ800);

ESP8266WebServer server(80);

vector<vector<int>> Groups = {
  {0,TOTAL_LEDS},
  {0, 3},
  {3, 3},
  {6, 3},
  {9, 3},
  {12, 3},
  {15, 3},
  {18, 3},
  {21, 3},
  {24, 3},
  {27, 3}
};

/* WIFI settings */
const char* ssid = "Mairh";  // Enter SSID here
const char* password = "fgrsfs2u4fg2af4h";  //Enter Password here

void test(){
  for (int i = 0; i < TOTAL_LEDS; i++){
    pixels.setPixelColor(i, 255, 0, 0);
    if (i != 0) pixels.setPixelColor(i - 1, 0, 0, 0);
    else pixels.setPixelColor(29, 0, 0, 0);
    pixels.show();
    delay(200);
  }
}

void fill(int R, int G, int B){
  pixels.fill(pixels.Color(R, G, B), 0, TOTAL_LEDS);
  pixels.show();
}

void fillGroup(int R, int G, int B, int start, int number){
  pixels.fill(pixels.Color(R, G, B), start, number);
  pixels.show();
}

void connectWiFi()
{
  Serial.println("Connecting to WIFI");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
    Serial.print("..");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("NodeMCU Local IP is : ");
  Serial.println((WiFi.localIP()));
}

void handle_OnConnect(){
  Serial.println("Someone Connected!");
  server.send(200, "text/plain", "Someone Connected!!");
}

void handle_test(){
  Serial.println("Test is running");
  server.send(200, "text/plain", "Test is running");
  test();
}

void handle_Args() { //Handler

  String message = "Number of args received:";
  message += server.args(); //Get number of parameters
  message += "\n";          //Add a new line

  for (int i = 0; i < server.args(); i++) {
    message += "Arg nº" + (String)i + " –> ";   //Include the current iteration value
    message += server.argName(i) + ": ";        //Get the name of the parameter
    message += server.arg(i) + "\n";            //Get the value of the parameter
  } 

  server.send(200, "text/plain", message);      //Response to the HTTP request
}

void handle_RGB(){
  fillGroup(server.arg(0).toInt(), server.arg(1).toInt(), server.arg(2).toInt(), Groups[server.arg(3).toInt()][0], Groups[server.arg(3).toInt()][1]);
  server.send(200, "text/plain", "");
}

void setup()
{
  /* start server communication */
  fillGroup(192, 192, 192, 0, TOTAL_LEDS);
  Serial.begin(115200);
  connectWiFi();

  server.on("/", handle_OnConnect);
  server.on("/test", handle_test);
  server.on("/RGB", handle_RGB);

  server.begin();

  pixels.begin(); //initialize
  pixels.show();

  fillGroup(0, 255, 0, 0, TOTAL_LEDS);
  delay(500);
  fillGroup(192, 192, 192, 0, TOTAL_LEDS);
}

void loop()
{ 
    server.handleClient();     
} 


