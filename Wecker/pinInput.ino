void test_pin(){
  handle_Time_switch();
  handle_Set_switch();
  handle_Alarm_switch();
  handle_Input_switch();
}


void handle_Alarm_switch(){
  int state = digitalRead(pinAlarm);
  if(state == LOW && setItem == 0) {
    int presstime = get_pin_delay(pinAlarm);
    if (presstime > 10){
      set_alarm_item();
      delay(200);
      wait_to_release(pinAlarm);
    }
    else{
      switch_alarm_mode();
      delay(200);
    }
  }
  else if(state == LOW){
      set_alarm_item();
      delay(200);
  }
}


void handle_Set_switch(){
  int state = digitalRead(pinSet);
  if (state == LOW && setItem > 0){
      set_time();
      delay(200);
  }
  else if (state == LOW && setItem == 0){
      round_sleep();
      delay(200);
  }
}

void handle_Input_switch(){
  int state = digitalRead(pinInput);
  /*if (Set == LOW && setItem > 0){
      set_time();
      delay(200);
  }
  else */
  if (state == LOW){
      switch_input();
      delay(200);
  }
  wait_to_release(pinInput);
}


void handle_Time_switch(){
  int state = digitalRead(pinTime);
  if(state == LOW && setItem == 0) {
    int presstime = get_pin_delay(pinTime);
    if (presstime > 10){
      switch_set_item();
      delay(200);
      wait_to_release(pinTime);
    }
    else{
      toggle_power();
    }
  }
  else if(state == LOW){
    switch_set_item();
    delay(200);
  }
}


int get_pin_delay(int pin){
  int state = digitalRead(pin);
  int delay_count = 0;
  while(state == LOW && delay_count < 11)
  {
    state = digitalRead(pin); 
    delay(100);
    delay_count = delay_count +1;
  }
  return delay_count;
}

void wait_to_release(int pin){
  int state = digitalRead(pin);
  while(state == LOW)
  {
    state = digitalRead(pin); 
    delay(100);
  }
}


