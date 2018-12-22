int data = 0; //블루투스에서 읽어오는 값
int dustsensorPin = A0;
int rain = A1;
int gas = A15;
int ledPower = 7;//pin 설정
int ENA = 10;
int IN1 = 9;
int IN2 = 8; //창문 모터


int G=0;
int R=0; //센서값이름

int delayTime = 280;
int delayTime2 = 40;
int offTime = 9680;

float dustValue = 0;
//float dustDensity = 0; //먼지센서

boolean check = false;

void Rotation() {
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(ENA,150);
} //열기

void Reverse() {
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  analogWrite(ENA,200);
} //닫기

void AllStop() {
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  analogWrite(ENA,0);
} //멈춤

void setup() {
  pinMode(ledPower,OUTPUT);
  pinMode(dustsensorPin,INPUT);
  
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENA,OUTPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
  
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
}

void loop() {
  digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(delayTime);

  dustValue=analogRead(dustsensorPin); // read the dust value via pin 5 on the sensor
  delayMicroseconds(delayTime2);

  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(offTime);
  
  G = analogRead(gas);
  R = analogRead(rain);
  //dustDensity = (0.17 * (dustValue * (5.0 / 1024)) - 0.1) * 1000;

  Serial.print("Gas : ");
  Serial.println(G);
  Serial.print("Rain : ");
  Serial.println(R);
  Serial.print("Dust Density[ug/m3] : ");
  Serial.println(dustValue);
  Serial.println(" ");
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);

  //check == true 열린상황 
  //check == false 닫힌 상황
  if(G>500) {
    digitalWrite(4,HIGH);
    if(check == false){
      Rotation();
      delay(1000);
      check = true;
    }
    AllStop();
    delay(1000);
  }
  else if(R<500){
    digitalWrite(4,LOW);
    if(check == true){
      Reverse();
      delay(1000);
      check = false;  
    }
    AllStop();
    delay(1000);
  }
  else if(dustValue > 100){
    digitalWrite(5,HIGH);
    if(check == true){
      Reverse();
      delay(1000);
      check = false;
    }
    AllStop();
    delay(1000);
  }
  else{
    delay(1000);
    AllStop();
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
  }

  if(Serial1.available()) {
    data = Serial1.read();
    Serial.print("Recevied data : ");
    Serial.write(data);
    Serial.print("\n");

    if(data == '1') {
      if(check == false){
        Rotation();
        Serial.println("Window OPEN\n");
        delay(1100);
        check = true;
      }
      AllStop();
    }
    else if(data == '2') {
      if(check == true){
        Reverse();
        Serial.println("Window CLOSE\n");
        delay(1100);
        check = false;
      }
      AllStop();
    }
    else if(data == '3'){
      Serial.println("Blind OPEN\n");
      digitalWrite(12,HIGH);
      delay(100);
    }
    else if(data == '4'){
      Serial.println("Blind CLOSE\n");
      digitalWrite(13,HIGH);
      delay(100);
    }
    else {
      AllStop();
    }
  }
 
  delay(3000);
}
