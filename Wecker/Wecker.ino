// Including the ESP8266 WiFi library
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiManager.h>
#include <math.h> 
#include <SPI.h>
#include "LedMatrix.h"
#include <DS3231.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

RTClib RTC;
DS3231 Clock;

//Display
#define NUMBER_OF_DEVICES 4
#define CS_PIN 10
LedMatrix ledMatrix = LedMatrix(NUMBER_OF_DEVICES, CS_PIN);


const String NodeName = "Wecker";
//Pin Taster
const int pinTime = 3; //Pin fuer Toggle_Power und Einstellen der Uhrzeit (Lang)
const int pinSet = 0; //Pin fuer Sleep und Zeit_Einstellung im Alarm/Time Set Mode
const int pinAlarm = 2; //Pin fuer Alarm An/Aus und setzen der Alarmzeiten (Lang)
const int pinInput = 1; //Pin für die Eingangswahl

const int pinSleep = 9; //Pin Unbenutzt



//Pin Relay
const int outInput = 12;
const int outPower = 16;

int al1h = 0;
int al1m = 0;

int al2h = 0;
int al2m = 0;

long previousMillis = 0;
void setup() {
  // put your setup code here, to run once:
  // Initializing serial port for debugging purposes
  Serial.begin(115200);
  delay(10);
  
  Wire.begin();
  //Setup Display
  ledMatrix.init();
  ledMatrix.setTextAlignment(0);
  ledMatrix.setRotation(true);
  ledMatrix.setIntensity(0);
  
  display_text("U");
  delay(400);
  display_text("Uh");
  delay(400);
  display_text("Uhr");
  delay(400);
  display_text("Uhr");

  //WiFiManager intialisation. Once completed there is no need to repeat the process on the current board
  WiFiManager wifiManager;
  wifiManager.autoConnect();
  Serial.println("WiFi connected");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  delay(1000);

  //Set Alarm Times
  byte A1Day, A1Hour, A1Minute, A1Second, AlarmBits;
  bool A1Dy, A1h12, A1PM;
  Clock.getA1Time(A1Day, A1Hour, A1Minute, A1Second, AlarmBits, A1Dy, A1h12, A1PM);
  al1h = A1Hour;
  al1m = A1Minute;
  Serial.println("Alarm1 Set:" + String(A1Day) + ", " + String(A1Hour) + ", " + String(A1Minute) + ", " + String(AlarmBits) + ", " + String(A1Dy) + ", " + String(A1h12) + ", "); 

  Clock.getA2Time(A1Day, A1Hour, A1Minute,  AlarmBits, A1Dy, A1h12, A1PM);
  al2h = A1Hour;
  al2m = A1Minute;
  Serial.println("Alarm2 Set:" + String(A1Day) + ", " + String(A1Hour) + ", " + String(A1Minute) + ", " + String(AlarmBits) + ", " + String(A1Dy) + ", " + String(A1h12) + ", "); 
  
  delay(1000);

  //Pin Setup 
  pinMode(pinTime, INPUT);           // set pin to input
  digitalWrite(pinTime, HIGH);       // turn on pullup resistors

  pinMode(pinSet, INPUT);           // set pin to input
  digitalWrite(pinSet, HIGH);       // turn on pullup resistors

  pinMode(pinAlarm, INPUT);           // set pin to input
  digitalWrite(pinAlarm, HIGH);       // turn on pullup resistors

  pinMode(pinInput, INPUT);           // set pin to input
  digitalWrite(pinInput, HIGH);       // turn on pullup resistors

  pinMode(pinSleep, INPUT);           // set pin to input
  digitalWrite(pinSleep, HIGH);       // turn on pullup resistors

  pinMode(outPower, OUTPUT);           // set pin to input
  digitalWrite(outPower, HIGH);       // turn on pullup resistors
   
  pinMode(outInput, OUTPUT);           // set pin to input
  digitalWrite(outInput, HIGH);       // turn on pullup resistors


  previousMillis = millis();

  
  
  //-------------------------------------------------
  //OTA
  // No authentication by default
  ArduinoOTA.setPassword((const char *)"ota-password");

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  //-------------------------------------------------

}

long time_on = -1;
int minutes_sleep = -1;

int h = 0;
int m = 0;
int s = 0;

int d = 0;
int M = 0;
int y = 0;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
String dow = "-";

int setItem = 0;

long block_gui = -1;

void loop() {
  //OTA
  ArduinoOTA.handle();
  //OTA
  
  unsigned long currentMillis = millis();
  long intervall = currentMillis - previousMillis;
  
  release_gui(currentMillis);
  
  // put your main code here, to run repeatedly:
  if(setItem == 0){
      update_Time();
      run_alarm();
      if (block_gui < 0)
        show_current_time(intervall,currentMillis);
   }
   else{
      show_time_infos(intervall,currentMillis);
      previousMillis = currentMillis;
   }
  test_pin();
  handleSleep(intervall, currentMillis);
  delay(80);
}

void delay_gui(int millis_s){
  block_gui =  millis() + millis_s;
}

void release_gui(int currentMillis){
  if (block_gui < currentMillis)
    block_gui = -1;
  else
    return;
}
