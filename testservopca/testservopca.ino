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
  
  HCPCA9685.Servo(1, 440);// 0-440
  HCPCA9685.Servo(2, 380);//440-
  HCPCA9685.Servo(3, 0);//0-200
  HCPCA9685.Servo(4, 200);//100-400
  HCPCA9685.Servo(5, 0);//0-440
}
void RotateForward(){ //For side 2,3,4
  digitalWrite(13, HIGH); 
  HCPCA9685.Servo(4,9240);
  digitalWrite(13, LOW);
  Serial.println("RotateForward()");
}
void RotateLeftAndForward(){ //5
  digitalWrite(13, HIGH); 
  HCPCA9685.Servo(5,240);
  RotateForward();
  Serial.println(" RotateLeftAndForward()");
}
void RotateTwice(){ //6
  RotateForward();
  RotateForward();
  Serial.println("RotateTwice()");
}

void loop() {
  serialData.Get(valsRec);
  int val=valsRec[0];
  switch(val){
    if(val==1){
      RotateForward();
    }
    else if(val==2){
      RotateLeftAndForward();
    }
    else if(val==3){
      RotateTwice();
    }
    else{
      Serial.println("Invalid Choice!!!");
    }
  }
}
//  unsigned int Pos=10;//10=0,400=180
//  HCPCA9685.Servo(1, Pos);
//  HCPCA9685.Servo(2, Pos+50);
//  delay(10);
//  HCPCA9685.Servo(3, Pos+100);
//  HCPCA9685.Servo(4, Pos+150);
//  delay(10);
//  HCPCA9685.Servo(5, Pos+200);
//  delay(10);

//servo 0 = 0-180
//servo 1 = 0-unknown
//servo 2 = 0-120
//servo 3 = 0-180
//servoo 4 = 0-180
