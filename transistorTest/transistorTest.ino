#include <SoftwareSerial.h>
 
SoftwareSerial mySerial(2, 5);
 
int Motor_A_Enable = 9;
int Motor_A_Reverse = 3;
int Motor_A_Forward = 4;
 
int Motor_B_Enable = 10;
int Motor_B_Reverse = 12;
int Motor_B_Forward = 7;
 
int Weapon = 6;
 
void setup() {
  Serial.begin(4800);
  mySerial.begin(9600);
  pinMode(Motor_A_Enable, OUTPUT);
  pinMode(Motor_A_Forward, OUTPUT);
  pinMode(Motor_A_Reverse, OUTPUT);
 
  pinMode(Motor_B_Enable, OUTPUT);
  pinMode(Motor_B_Forward, OUTPUT);
  pinMode(Motor_B_Reverse, OUTPUT);
 
  pinMode(Weapon, OUTPUT);
}
 
 String readString;
int weaponMode = 0;
void loop() {
    while (mySerial.available()) {
      delay(2);  //delay to allow byte to arrive in input buffer
      char c = mySerial.read();
      if(c >= '0' && c <= '9') // get only the numbers
       readString += c;
    }
 
    switch (readString[readString.length() - 1])
    {
      case '1': // FORWARD
        analogWrite(Motor_B_Enable, 255);
        analogWrite(Motor_A_Enable, 255);
        digitalWrite(Motor_A_Reverse, LOW);
        digitalWrite(Motor_B_Reverse, LOW);
        digitalWrite(Motor_A_Forward, HIGH);
        digitalWrite(Motor_B_Forward, HIGH);
        break;
      case '2': // REVERSE
        analogWrite(Motor_B_Enable, 255);
        analogWrite(Motor_A_Enable, 255);
        digitalWrite(Motor_A_Forward, LOW);
        digitalWrite(Motor_B_Forward, LOW);
        digitalWrite(Motor_A_Reverse, HIGH);
        digitalWrite(Motor_B_Reverse, HIGH);
        break;
      case '3': // LEFT
        analogWrite(Motor_A_Enable, 255);
        analogWrite(Motor_B_Enable, 255);
        digitalWrite(Motor_A_Reverse, LOW);
        digitalWrite(Motor_A_Forward, HIGH);
        digitalWrite(Motor_B_Reverse, HIGH);
        digitalWrite(Motor_B_Forward, LOW);
        break;
      case '4': // RIGHT
        analogWrite(Motor_B_Enable, 255);
        analogWrite(Motor_A_Enable, 255);
        digitalWrite(Motor_B_Reverse, LOW);
        digitalWrite(Motor_B_Forward, HIGH);
        digitalWrite(Motor_A_Reverse, HIGH);
        digitalWrite(Motor_A_Forward, LOW);
        break;
      case '7': // Weapon Off
        digitalWrite(Weapon, LOW);
        break;
      case '8': // Weapon On
        digitalWrite(Weapon, HIGH);
        break;
      case '0': // Motors Off
        analogWrite(Motor_B_Enable, 0);
        analogWrite(Motor_A_Enable, 0);
        break;
    }
    readString="";
}
