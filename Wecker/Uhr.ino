void show_current_time(long intervall, long currentMillis){
  if(intervall > 16000){
    previousMillis = currentMillis;
  }
  if (intervall > 14000){
    display_date(d,M,y);
  }
  /*else if (intervall > 12000){
    display_year(d,M,y);
  }
      else if (intervall > 10000){
        display_text(dow);
      }
      else if (intervall > 9000){
        display_text(readDHT());
      }
      else if (intervall > 8000){
        display_text("Temp");
      }*/
  else{
    display_time(h,m,s);
  }
  setBrightnes(h);
}

void show_time_infos(long intervall, long currentMillis){
  if(setItem == 1 || setItem == 2){
    display_date(d,M,y);
   }
   else if(setItem == 2){
    display_date(d,M,y);
   }
   else if(setItem == 3){
    display_year(d,M,y);
   }
   else if(setItem == 4 || setItem == 5 || setItem == 6){      
    display_time(h,m,s);
   }
   else if(setItem == 11 || setItem == 12){      
    display_time(al1h,al1m,0);
   }
   else if(setItem == 13 || setItem == 14){      
    display_time(al2h,al2m,0);
   }
}


//####################################################################################################
//Setup
void switch_set_item(){
    setItem = setItem + 1;
    if(setItem > 6)
    {
      set_clock();
      setItem = 0;
      display_text(" OK ");
      delay_gui(1000);
    }
}

void set_time(){
     if(setItem == 1){
        add_day(1);
      }
      else if(setItem == 2){
        add_month(1);
      }
      else if(setItem == 3){
        add_year(1);
      }
      else if(setItem == 4){
        add_hour(1);
      }
      else if(setItem == 5){
        add_minute(1);
      }
      else if(setItem == 6){
        add_second(1);
      }
      else if(setItem == 11){
        add_al1_hour(1);
      }
      else if(setItem == 12){
        add_al1_minute(1);
      }
      else if(setItem == 13){
        add_al2_hour(1);
      }
      else if(setItem == 14){
        add_al2_minute(1);
      }
}

//###################################################################################################################################
//Time Code
void update_Time(){
  DateTime now = RTC.now();
  h = now.hour(); //24-hr  
  m = now.minute(); 
  s = now.second(); 

  d = now.day();
  M = now.month();
  y = now.year();

  if (summertime_EU(y,M,d,h,1))
  {
    h = h + 1;
    if (h == 24){
      h = 0;
    }
  }
  
  dow = daysOfTheWeek[Clock.getDoW()];
  Serial.println(String(h) + ":" + String(m) + ":" + String(s) + " - " + String(d) + "." + String(M) + "." + String(y) + " | DST: " + String(summertime_EU(y,M,d,h,1)));
}

//###################################################################################################################################
//Display Code
void display_year(int Day, int Month, int Year){
  display_text(String(Year));
}

void display_time(int Stunde, int Minute, int Sekunde){
  String Min = String(Minute);
  String Stu = String(Stunde);
  if (Minute < 10)
  {
    Min = "0" + Min;
  }
  if (Stunde < 10)
  {
    Stu = "0" + Stu;
  }
  if(setItem == 4)
  {
      display_text("h :" + Stu);
  }
  else if(setItem == 5)
  {
      display_text("m :" + Min);
  }
  else if(setItem == 6)
  {
      display_text("s :" + String(Sekunde));
  }
  else if(setItem == 11)
  {
      display_text("h1:" + Stu);
  }
  else if(setItem == 12)
  {
      display_text("m1:" + Min);
  }
  else if(setItem == 13)
  {
      display_text("h2:" + Stu);
  }
  else if(setItem == 14)
  {
      display_text("m2:" + Min);
  }
  else if (Sekunde % 2 == 0){
      display_text(Stu + ":" + Min);
  }
  else{
    display_text(Stu + "." + Min);
  }
}

void display_date(int Day, int Month, int Year){
  String Mon = String(Month);
  String Da = String(Day);
  if (Day < 10)
  {
    Da = "0" + Da;
  }
  if (Month < 10)
  {
    Mon = "0" + Mon;
  }
  if(setItem == 1)
  {
      display_text("T :" + Da);
  }
  else if(setItem == 2)
  {
      display_text("M :" + Mon);
  }
  else{
    display_text(Da + "." + Mon);
  }
}

void display_text(String text){
  Serial.println("Display:");
  Serial.println(text);
  ledMatrix.clear();
  ledMatrix.setText(text);
  ledMatrix.drawText();
  ledMatrix.commit();
}


void setBrightnes(int h){
  if (h > 20 || h < 7){
    ledMatrix.setIntensity(0);
  }
  else{
    ledMatrix.setIntensity(4);
  }
}


//########################################################################################################
//Helpers

void add_second(int i){
  s = s + i;
  if (s > 59)
  {
    s = s - 60;
  }
}

void add_hour(int i){
  h = h + i;  
  if (h > 23){
    h = 0;
  }
}

void add_minute(int i){
  m = m + i; 
  if (m > 59){
    m = m - 60;
  }
}

void add_month(int i){
  M = M + i; 
  if (m > 12){
    m = 1;
  }  
}

void add_day(int i){
  d = d + i; 
  if (d > 31){
    d = 1;
  }
}

void add_year(int i){
  y = y + i; 
  if (y > 2030){
    y = 2017;
  }
}

void set_clock(){
  Clock.setClockMode(false);  // set to 24h 
  //setClockMode(true); // set to 12h 

  Clock.setYear(y-2000); 
  Clock.setMonth(M); 
  Clock.setDate(d); 
  //Clock.setDoW(DoW); 
  if (summertime_EU(y,M,d,h,1))
  {
    Clock.setHour(h-1);   
  }
  else{
    Clock.setHour(h);
  } 
  Clock.setMinute(m); 
  Clock.setSecond(s); 

}


boolean summertime_EU(int year, byte month, byte day, byte hour, byte tzHours)
// European Daylight Savings Time calculation by "jurs" for German Arduino Forum
// input parameters: "normal time" for year, month, day, hour and tzHours (0=UTC, 1=MEZ)
// return value: returns true during Daylight Saving Time, false otherwise
{
  if (month<3 || month>10) return false; // keine Sommerzeit in Jan, Feb, Nov, Dez
  if (month>3 && month<10) return true; // Sommerzeit in Apr, Mai, Jun, Jul, Aug, Sep
  if (month==3 && (hour + 24 * day)>=(1 + tzHours + 24*(31 - (5 * year /4 + 4) % 7)) || month==10 && (hour + 24 * day)<(1 + tzHours + 24*(31 - (5 * year /4 + 1) % 7)))
    return true;
  else
    return false;
}
