#include <cvzone.h>
#include <HCPCA9685.h>
#include "HCPCA9685.h"
#define  I2CAdd 0x40

HCPCA9685 HCPCA9685(I2CAdd);
SerialData serialData(1,1); //(numOfValsRec,digitsPerValRec)
int valsRec[1];

void setup(){
  serialData.begin(9600);
  HCPCA9685.Init(SERVO_MODE);
  HCPCA9685.Sleep(false);
  pinMode(13, OUTPUT);
}
void RotateForward(){ //For side 2,3,4
  digitalWrite(13, HIGH); 
  HCPCA9685.Servo(4,);
  digitalWrite(13, LOW);
}
void RotateLeftAndForward(){ //5
  digitalWrite(13, HIGH); 
  HCPCA9685.Servo(5,);
  RotateForward();
}
void RotateTwice(){ //6
  RotateForward();
  RotateForward();
}

void loop() {
  serialData.Get(valsRec);
  digitalWrite(13,valsRec[0]);  
//  unsigned int Pos=10;//10=0,400=180
//  HCPCA9685.Servo(1, Pos);
//  HCPCA9685.Servo(2, Pos+50);
//  delay(10);
//  HCPCA9685.Servo(3, Pos+100);
//  HCPCA9685.Servo(4, Pos+150);
//  delay(10);
//  HCPCA9685.Servo(5, Pos+200);
//  delay(10);
}

