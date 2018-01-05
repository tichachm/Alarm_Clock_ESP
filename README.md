# Alarm_Clock_ESP

This is an Alarm Clock (Radio) based on the ESP8266 in combination with a MAX7219 LED-Matrix, Relay-Board and DS3231 RTC.

Note: This Project is under heavy development at the moment.

## Wiring

Image how to wire the project will follow.

###### LED-Matrix:

| LED-Matrix | ESP8266 |
| -------- | -------- |
| VCC     | Vin/5V+   |
| GND     | GND    |
| DIN     | GPIO13 (HSPID)   |
| CS    | GPIO 10  |
| CLK     | GPIO14 (HSPICLK)  |


###### RTC DS3231:

| DS3231 | ESP8266 |
| -------- | -------- |
| 3,3V | 3,3V |
| GND | GND |
| SCL | GPIO5 |
| SDA | GPIO4 |


###### Relay-Module:

| Relay-Module | ESP8266 | Type |
| -------- | -------- | -------- |
| VCC     | Vin/5V+   | Power |
| GND     | GND    | GND |
| In1     | GPIO16    | Power |
| In2     | GPIO12    | Input |
| In3     | GPIO12    | Input |
| In4     | GPIO12    | Input |


###### Switch:

The switch should connect the GPIO to ground if it is pressed down:

* power_sw: GPIO3
* input_sw: GPIO1
* alarm_sw: GPIO2
* sleep_sw: GPIO0


You can also change this at the beginning of the code:
```
//Pin Taster
const int pinTime = 3; //Pin fuer Toggle_Power und Einstellen der Uhrzeit (Lang)
const int pinSet = 0; //Pin fuer Sleep und Zeit_Einstellung im Alarm/Time Set Mode
const int pinAlarm = 2; //Pin fuer Alarm An/Aus und setzen der Alarmzeiten (Lang)
const int pinInput = 1; //Pin für die Eingangswahl

const int pinSleep = 9; //Pin Unbenutzt



//Pin Relay
const int outInput = 12;
const int outPower = 16;
```

## How does it work

The Clock can control 2 relays:

* Power Relay: is used to turn on/off a AMP, Radio or any other device.
* Input Relay: is to switch between two Inputs like Radio for Alarm and CD/MP3 or Aux for normal Music.
* If an alarm is triggerd both relays are switched on.

The Clock is controlled with 4 Buttons

* Power-Button: turn power relay on/off 
* Power-Button (long-press): Set clock (Day, Month, Year, Hour, Minute, Second) with Sleep-Button
* Input-Button: turn input relay on/off
* Alarm-Button: toggle active alarm (Alarm 1 -> Alarm 2 -> Alarm 1 and Alarm 2 -> Alarm off)
* Alarm-Button (long-press): set alarm time (Alarm 1 Hour, Alarm 1 Minute, Alarm 2 Hour, Alarm 2 Minute) with Sleep-Button
* Sleep-Button : set time to turn power relay off (90 Min -> 60 -> 30 -> 15 -> Off)

## Issues

* Alarm 2 is not working like expected. It will be triggered every hour. (Alarm 1 is ok, once a day)
* Networkconnection is not used to update time over NTP. (not implemented yet)
* Long-Press blocks display until release.

## Dependencies

LedMatrix.h : [https://github.com/squix78/MAX7219LedMatrix](https://github.com/squix78/MAX7219LedMatrix)

DS3231.h : [https://github.com/NorthernWidget/DS3231](https://github.com/NorthernWidget/DS3231)

WiFiManager.h : [https://github.com/tzapu/WiFiManager](https://github.com/tzapu/WiFiManager)
