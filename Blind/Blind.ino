int ENA1 = 10;
int IN3 = 9;
int IN4 = 8;
int L = 0;

boolean check = false;

void Rotation() {
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  analogWrite(ENA1,150);
} //열기

void Reverse() {
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  analogWrite(ENA1,150);
} //닫기

void AllStop() {
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  analogWrite(ENA1,0);
} //멈춤 

void setup() {
  // put your setup code here, to run once:
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA1,OUTPUT);
  Serial.begin(9600);
  pinMode(12,INPUT);
  pinMode(13,INPUT);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  L = analogRead(A0);
  Serial.print("light : ");
  Serial.print(analogRead(A0));
  Serial.println("");
  Serial.print("data : ");
  Serial.print(digitalRead(12));
  Serial.print("   data1 : ");
  Serial.println(digitalRead(13));
  Serial.println(check);
  Serial.println("\n");
  
 //check == false 블라인드 닫힌상황
 //check == true 블라인드 열린상황 
 
  if(L <= 100){ // 밝으면
    if(check == true){
      Reverse();
      delay(850);
      check = false;
    }
    AllStop();
    delay(1000);
  }
  else if(L >= 350){ //어두우면
    if(check == false){
      Rotation();
      delay(1300);
      check = true;
    }
    AllStop();
    delay(1000);
  }

  if(digitalRead(12) == 1){
    Serial.println("Blind OPEN\n");
    if(check == false){
      Rotation();
      delay(1300);
      check = true;
    }
    AllStop();
  }
  else if(digitalRead(13) == 1){
    Serial.println("Blind CLOSE\n");
    if(check == true){
      Reverse();
      delay(850);
      check = false;
    }
    AllStop();
  }
  else {
    AllStop();
  }
  
  delay(2000);

}
