void round_sleep(){
  if (minutes_sleep > 60){
    minutes_sleep = 60;
  }
  else if (minutes_sleep > 45){
    minutes_sleep = 45;
  }
  else if (minutes_sleep > 30){
    minutes_sleep = 30;
  }
  else if (minutes_sleep > 15){
    minutes_sleep = 15;
  }
  else if (minutes_sleep > 0){
    minutes_sleep = 0;
  }
  else{
    minutes_sleep = 90;
  }
  setSleepTimer(minutes_sleep);
}


void setSleepTimer(int Minutes){
  if (Minutes == 0)
  {
    time_on = -1;
    minutes_sleep = -1;
  }
  else{
    unsigned long currentMillis = millis();
    time_on = currentMillis + ((Minutes *60) *1000);
    powerOn();
  }
  display_text("S " + String(Minutes));
  delay_gui(1000);

}

void handleSleep(long intervall, long currentMillis){
  if(time_on < 0){
    return;
  }
  else if (currentMillis > time_on)
  {
    powerOff();
    time_on = -1;
    minutes_sleep = -1;
  }
}

void switch_input(){
  int currentIn = digitalRead(outInput);
  if(currentIn == LOW){
    switch_in(true);
  }
  else{    
    switch_radio(true);
  }
}

void switch_radio(bool display_switch){
  digitalWrite(outInput, LOW);
  if(display_switch){
    display_text("Radio");
    delay_gui(500);
  }
}

void switch_in(bool display_switch){
  digitalWrite(outInput, HIGH);
  if(display_switch){
    display_text("In");
    delay_gui(500);
  }
}

void toggle_power(){
  int currentState = digitalRead(outPower);
  if (currentState == LOW){
    powerOff();
  }
  else{
    powerOn();
  }
}

void powerOff(){
  time_on = -1;
  int currentState = digitalRead(outPower);
  if (currentState != HIGH){
    Serial.println("OFF");
    digitalWrite(outPower, HIGH);
    display_text("OFF");
    delay_gui(1000);
  }
  switch_in(false);
}

void powerOn(){
  int currentState = digitalRead(outPower);
  if (currentState != LOW){
    Serial.println("ON");
    digitalWrite(outPower, LOW);
    display_text("ON");
    delay_gui(1000);
  }  
}

