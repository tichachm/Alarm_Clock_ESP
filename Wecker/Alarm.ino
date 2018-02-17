void run_alarm(){
  if (test_alarm())
  {
    display_text("ALARM");
    delay_gui(1000);
    switch_radio(false);
    setSleepTimer(30);
  }
}

//####################################################################################################

void switch_alarm_mode(){
  bool A1 = Clock.checkAlarmEnabled(1);
  bool A2 = Clock.checkAlarmEnabled(2);
  if (A1 && A2){
    Clock.turnOffAlarm(1);
    Clock.turnOffAlarm(2);
  }
  else if (A1 && !A2){
    Clock.turnOffAlarm(1);
    Clock.turnOnAlarm(2);
  }
  else if (!A1 && A2){
    Clock.turnOnAlarm(1);
    Clock.turnOnAlarm(2);
  }
  else if (!A1 && !A2){
    Clock.turnOnAlarm(1);
    Clock.turnOffAlarm(2);
  }
  A1 = Clock.checkAlarmEnabled(1);
  A2 = Clock.checkAlarmEnabled(2);
  if (A1 && A2)
  {
    display_text("A1/2");
  }
  else if (A1)
  {
        display_text("A1");
  }
  else if (A2)
  {
        display_text("A2");
  }
  else
  {
        display_text("A Off");
  }
  delay_gui(1000);
}

void set_alarm_item(){
  if (setItem == 0)
  {
    setItem = 10;
  }
  setItem = setItem + 1;
  if(setItem == 13)
  {
      set_alarm1(); 
  }
  else if (setItem > 14)
  {
      set_alarm2();
      setItem = 0;
  }
}

//####################################################################################################

bool test_alarm(){
  bool A1 = Clock.checkIfAlarm(1);
  bool A2 = Clock.checkIfAlarm(2);
  bool A1_en = Clock.checkAlarmEnabled(1);
  bool A2_en = Clock.checkAlarmEnabled(2);
  return ((A1 && A1_en) || (A2 && A2_en));
}

//########################################################################################################
//Helpers


void add_al1_hour(int i){
  al1h = al1h + i;  
  if (al1h > 23){
    al1h = 0;
  }
}

void add_al1_minute(int i){
  al1m = al1m + i; 
  if (al1m > 59){
    al1m = al1m - 60;
  }
}

void add_al2_hour(int i){
  al2h = al2h + i;  
  if (al2h > 23){
    al2h = 0;
  }
}

void add_al2_minute(int i){
  al2m = al2m + i; 
  if (al2m > 59){
    al2m = al2m - 60;
  }
}


void set_alarm1(){
  Clock.setA1Time(0, al1h, al1m, 0, 1000, true, false, false);
  //Clock.turnOnAlarm(1);
  byte A1Day, A1Hour, A1Minute, A1Second, AlarmBits;
  bool A1Dy, A1h12, A1PM;
  Clock.getA1Time(A1Day, A1Hour, A1Minute, A1Second, AlarmBits, A1Dy, A1h12, A1PM);
  Serial.println("Alarm1 Set:" + String(A1Day) + ", " + String(A1Hour) + ", " + String(A1Minute) + ", " + String(A1Second) + ", " + String(AlarmBits) + ", " + String(A1Dy) + ", " + String(A1h12) + ", "); 
  display_text("A1");
  delay(1000);
  display_text(String(A1Hour) + ":" +String(A1Minute));
  delay(1000); 
}


void set_alarm2(){
  Clock.setA2Time(0, al2h, al2m, 0b1000000, true, false, false);
  //Clock.turnOnAlarm(1);
  byte A1Day, A1Hour, A1Minute, AlarmBits;
  bool A1Dy, A1h12, A1PM;
  Clock.getA2Time(A1Day, A1Hour, A1Minute, AlarmBits, A1Dy, A1h12, A1PM);
  Serial.println("Alarm2 Set:" + String(A1Day) + ", " + String(A1Hour) + ", " + String(A1Minute) + ", " + String(AlarmBits) + ", " + String(A1Dy) + ", " + String(A1h12) + ", "); 
  display_text("A2");
  delay(1000);
  display_text(String(A1Hour) + ":" +String(A1Minute));
  delay_gui(1000);
}
