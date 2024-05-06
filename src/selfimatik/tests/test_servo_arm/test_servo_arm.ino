#include <Servo.h>
#define SERVO_PIN 11
#define SERVO_ARM_CLOSE 9
Servo servo;
Servo servoClose;
int pos = 0;
void setup() {
  // put your setup code here, to run once:
// servo arm position
  servo.attach(SERVO_PIN);
  servo.write(10);  
}

void loop() {
  //positions test
  for (pos = 10; pos <= 120; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 120; pos >= 10; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
