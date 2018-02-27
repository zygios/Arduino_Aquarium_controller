
#include "TimerObject.h"
const long LED_t =  900000L; //  15min*60000 = 900000
const long mais_t = 600000L; //  10min*60000
const long BURB_t = 9000000L; // 90min*60000 = 5400000
const long LED_t1 = 2700000L; // 45min*60000 = 2700000
const long delay_t= 900000L; // 15min*60000
const long total_t = LED_t + BURB_t + LED_t1;
unsigned long LastTime_mill;

TimerObject *timer1 = new TimerObject(LED_t);
TimerObject *timer2 = new TimerObject(BURB_t);
TimerObject *timer3 = new TimerObject(LED_t1);
TimerObject *timer4 = new TimerObject(delay_t);

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

//Reles 26, 28, 30, 32
#define SVIES 28
#define BURB 26
#define HEAT 30
#define REL4 32

#define butt A10 //buttons

int buttVal = 0;
boolean MAISTAS = true;
boolean VYKDYMAS = false;
boolean RUNNING = false;
boolean HEATER = false; 
boolean BACKLIGTH = false;

void setup() {
  Serial.begin(9600);

  timer1->setOnTimer(&BURB_on);
  timer1->setSingleShot(true);
  timer2->setOnTimer(&BURB_off);
  timer2->setSingleShot(true);
  timer3->setOnTimer(&LED_off);
  timer3->setSingleShot(true);
  timer4->setOnTimer(&delay_off);
  timer4->setSingleShot(true);
  
  pinMode(SVIES, OUTPUT);
  digitalWrite(SVIES, HIGH);
  pinMode(BURB, OUTPUT);
  digitalWrite(BURB, HIGH);
  pinMode(HEAT, OUTPUT);
  digitalWrite(HEAT, HIGH);
  pinMode(REL4, OUTPUT);
  digitalWrite(REL4, HIGH);

  lcd.begin();
  lcd.backlight();
  lcd.setBacklight(LOW);
}



void loop() {
  readButt();
    
  if (VYKDYMAS == true && RUNNING == false){
    RUNNING = true;
    LED_on();
    LastTime_mill = millis();
  }else{
    timer1->Update();
    timer2->Update();
    timer3->Update();
    timer4->Update();
  }
}


void readButt()
{
    buttVal = analogRead(butt);
    Serial.println(buttVal);
    if(buttVal > 870 && buttVal < 880){
      delay(100);
    }else if(buttVal > 495 && buttVal < 505){
      delay(100);
      if(MAISTAS == true){
        MAISTAS = false;
      }else{
        MAISTAS = true;
      }
    }else if(buttVal > 485 && buttVal < 495){
      delay(100);
      if(VYKDYMAS == false){
        VYKDYMAS = true;
      }
    }
}

void LED_on(){
  timer1->Start();
  digitalWrite(SVIES, LOW);
}

void BURB_on(){
  timer2->Start();
  digitalWrite(BURB, LOW);
}

void BURB_off(){
  timer3->Start();
  digitalWrite(BURB, HIGH);
}

void LED_off(){
  timer4->Start();
  digitalWrite(SVIES, HIGH);
  digitalWrite(BURB, HIGH);
}

void delay_off(){
  VYKDYMAS = false; 
  RUNNING = false;
}

