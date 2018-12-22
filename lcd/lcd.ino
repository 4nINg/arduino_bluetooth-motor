#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27,16,2);
Servo esc_b;

int black = 0;

void AllStop(){
  black = 0;
  esc_b.write(black);
}

void Fan(){
  black = 50;
  esc_b.write(black);
  Serial.println(black);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  esc_b.attach(2, 1000, 2000);
  esc_b.write(0);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(5) == 1){ //G >500
    Fan();
    lcd.clear();
    lcd.print("Air Cleaner ON");
    //lcd.print("By Gas");
    delay(5000);
    AllStop();
  } else if(digitalRead(6) ==1){ //dust > 30
    Fan();
    lcd.clear();
    lcd.println("Air Cleaner ON");
    lcd.print("By Dust");
    delay(5000);
    AllStop();
  } else { //G<500 & dust <30
    lcd.clear();
    lcd.print("Air Cleaner OFF");
    delay(1000);
    AllStop();
  }
}
