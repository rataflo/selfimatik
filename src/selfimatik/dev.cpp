#include "dev.h"


Servo servoArm;
AccelStepper stepperX(1, X_PIN_STP, X_PIN_DIR);
AccelStepper stepperY(1, Y_PIN_STP, Y_PIN_DIR);
unsigned long startDryer = 0;

void initDev(){
  pinMode(DRYER_PIN, OUTPUT);
  digitalWrite(DRYER_PIN, HIGH);
  pinMode(EXIT_PIN, OUTPUT);
  #ifndef ISPROTO
    digitalWrite(EXIT_PIN, LOW);
  #else
    analogWrite(EXIT_PIN, 400);
  #endif
  pinMode(SERVO_POWER_PIN, OUTPUT);
  digitalWrite(SERVO_POWER_PIN, LOW);
  pinMode(LED_PIN, OUTPUT);
  

  pinMode(X_ENDSTOP_PIN, INPUT);
  pinMode(X_PIN_ENABLE, OUTPUT);
  digitalWrite(X_PIN_ENABLE, HIGH);
  pinMode(X_M0, OUTPUT);
  pinMode(X_M1, OUTPUT);
  digitalWrite(X_M0, HIGH);
  digitalWrite(X_M1, LOW);
  stepperX.setMaxSpeed(INIT_SPEED);
  stepperX.setAcceleration(INIT_ACCEL);
  stepperX.setCurrentPosition(0);

  pinMode(Y_ENDSTOP_PIN, INPUT);
  pinMode(Y_PIN_ENABLE, OUTPUT);
  digitalWrite(Y_PIN_ENABLE, HIGH);
  pinMode(Y_M0, OUTPUT);
  pinMode(Y_M1, OUTPUT);
  digitalWrite(Y_M0, HIGH);
  digitalWrite(Y_M1, LOW);
  stepperY.setMaxSpeed(INIT_SPEED);
  stepperY.setAcceleration(INIT_ACCEL);
  stepperY.setCurrentPosition(0);

  digitalWrite(X_PIN_ENABLE, LOW);
  digitalWrite(Y_PIN_ENABLE, LOW);
  #ifdef ISPROTO 
    moveArm(getParameters().servoPos3);
  #endif
  printStartup("init Y");
  initY();
  printStartup("init Arm");
  #ifdef ISPROTO 
    moveArm(getParameters().servoPos3);
  #else
    moveArm(getParameters().servoPos1);
  #endif
  printStartup("init X");
  
  initX();
  digitalWrite(X_PIN_ENABLE, HIGH);
  digitalWrite(Y_PIN_ENABLE, HIGH);

  if(getParameters().stopLight == 0){
    analogWrite(LEDSELFI_PIN, 100);
    analogWrite(LED_PIN, 130);//12v
  }

  stepperY.setMaxSpeed(Y_SPEED);
  stepperY.setAcceleration(Y_ACCEL);

  stepperX.setMaxSpeed(X_SPEED);
  stepperX.setAcceleration(X_ACCEL);

}

void initX(){
  debug("initX", String("debut"));
  stepperX.setCurrentPosition(0);
  stepperX.moveTo(99999);

  boolean bEndStop = !digitalRead(X_ENDSTOP_PIN);
  while(!bEndStop){
    stepperX.run();
    bEndStop = !digitalRead(X_ENDSTOP_PIN);
  }
  stepperX.stop();
  Serial.println(stepperX.currentPosition());
  stepperX.setCurrentPosition(0);
  stepperX.run();
}

void initY(){
  debug("initY", String("debut"));
  stepperY.setCurrentPosition(0);
  stepperY.moveTo(99999);

  boolean bEndStop = !digitalRead(Y_ENDSTOP_PIN);
  while(!bEndStop){
    stepperY.run();
    bEndStop = !digitalRead(Y_ENDSTOP_PIN);
  }
  stepperY.stop();
  Serial.println(stepperY.currentPosition());
  stepperY.setCurrentPosition(0);
  stepperY.run();
}

void devProcess(){
  Serial.println("devProcess");
  byte startLight = getParameters().startLight;
  byte stopLight = getParameters().stopLight;
  Serial.print("starL=");
  Serial.println(startLight);
  Serial.print("stop=");
  Serial.println(stopLight);
  gotoPosY(getParameters().middlePos);

  for(byte i = 0; i < 4;i++){
    bool bStartLight = false;
    bool bStopLight = false;
    if(startLight != 0 && startLight - 1 == i){
      bStartLight = true;
    }
    if(stopLight != 0 && stopLight - 1 == i){
      bStopLight = true;
    }
    Serial.print("startL=");
    Serial.println(bStartLight);
    Serial.print("stopL=");
    Serial.println(bStopLight);
    gotoPosX(getParameters().tankPos[i]);
    bathTime(i, bStartLight, bStopLight);
  }
  
  moveArm(getParameters().servoPos2);

  for(byte i = 4; i < 8;i++){
    bool bStartLight = false;
    bool bStopLight = false;
    if(startLight != 0 && startLight - 1 == i){
      bStartLight = true;
    }
    if(stopLight != 0 && stopLight - 1 == i){
      bStopLight = true;
    }
    Serial.print("startL=");
    Serial.println(bStartLight);
    Serial.print("stopL=");
    Serial.println(bStopLight);
    gotoPosX(getParameters().tankPos[i]);
    bathTime(i, bStartLight, bStopLight);
  }

  //Exit
  #ifdef ISPROTO 
    gotoPosX(getParameters().servoRotatePos);
    moveArm(getParameters().servoPos3);
    gotoPosX(getParameters().exitPos);
    initY();
  #else 
    gotoPosX(getParameters().exitPos);
    digitalWrite(EXIT_PIN, HIGH);
    gotoPosY(0);
    delay(1000);
    digitalWrite(EXIT_PIN, LOW);
    // start dryer
    startDryer = millis();
    digitalWrite(DRYER_PIN, LOW);
    gotoPosY(getParameters().middlePos);
    //Return to park position
    gotoPosX(getParameters().servoRotatePos);
    moveArm(getParameters().servoPos1);
    initY();
    initX();
    digitalWrite(X_PIN_ENABLE, HIGH);
    digitalWrite(Y_PIN_ENABLE, HIGH);
  #endif
  
}

void gotoCamera(){
  digitalWrite(X_PIN_ENABLE, LOW);
  digitalWrite(Y_PIN_ENABLE, LOW);
  
  initY();
  #ifdef ISPROTO 
    initX();
    moveArm(getParameters().servoPos1);
  #endif
  stepperX.moveTo(getParameters().cameraPos);
  while(stepperX.distanceToGo() != 0){
    stepperX.run();
  }
  //do not disable steppers
}

void gotoPosX(long pos){
  stepperX.moveTo(pos);
  while(stepperX.distanceToGo() != 0){
    stepperX.run();
  }
}

void gotoPosY(long pos){
  stepperY.moveTo(pos);
  while(stepperY.distanceToGo() != 0){
    stepperY.run();
  }
}

void bathTime(byte nbTank, bool lightOn, bool lightOff){
  debug("bathTime",String("debut"));
  unsigned long nbSec = (unsigned long)getParameters().tankTimes[nbTank];
  unsigned long duration = (unsigned long)nbSec * (unsigned long)1000;
  unsigned long currentMillis = millis();
  unsigned long startMillis = currentMillis;

  if(lightOff){
    analogWrite(LEDSELFI_PIN, 0);
    analogWrite(LED_PIN, 0);
  }

  while (currentMillis - startMillis < duration){
    gotoPosY(getParameters().bottomPos);
    currentMillis = millis();
    if(currentMillis - startMillis < duration){
      gotoPosY(getParameters().agitateTopPos);
    }
  }

  if(lightOn){
    analogWrite(LEDSELFI_PIN, 100);//open gnd
    analogWrite(LED_PIN, 130);//12v
  }
  gotoPosY(getParameters().middlePos);
  nbSec = (unsigned long)getParameters().dripTimes[nbTank];
  duration = (unsigned long)nbSec * (unsigned long)1000;
  delay(duration);
}

void manageDryer(){
  //check dryer
  unsigned long currentMillis= millis();
  if(startDryer != 0 && currentMillis - startDryer  > DRYER_TIME){
    digitalWrite(DRYER_PIN, HIGH);
    startDryer = 0;
  }
}

void moveArm(byte pos){
  digitalWrite(SERVO_POWER_PIN, HIGH);
  servoArm.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
  servoArm.write(pos);  
  delay(1200);
  servoArm.detach();
  digitalWrite(SERVO_POWER_PIN, LOW);
}
