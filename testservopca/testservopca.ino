#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver myServo = Adafruit_PWMServoDriver();

#define SERVOMIN 150
#define SERVOMAX 600

uint8_t numberOfServos = 1;

void setup() {
  Serial.begin(9600);
  myServo.begin();
  myServo.setPWMFreq(60);
  delay(10);
}

void loop() {
  if (Serial.available() > 0) {
    int angle = Serial.parseInt();
    if (angle >= 0 && angle <= 180) {
      // Map the angle to the servo pulse width
      uint16_t pulselen = map(angle, 0, 180, SERVOMIN, SERVOMAX);
      myServo.setPWM(0, 0, pulselen); // Set servo 0 to the specified angle
      Serial.print("Set servo angle to: ");
      Serial.println(angle);
    } else {
      Serial.println("Invalid angle. Please enter a value between 0 and 180.");
    }
  }

  delay(100); // Add a small delay to prevent rapid input reading
}

//servo 0 = 0-180
//servo 1 = 0-unknown
//servo 2 = 0-120
//servo 3 = 0-180
//servoo 4 = 0-180
