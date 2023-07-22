#include "shutter.h"
#include "constants.h"
#include "tests.h"

// Shutter
AccelStepper shutter(1, SHUTTER_PIN_STP, SHUTTER_PIN_DIR);
bool bCloseShutter = false; // Shutter is closed?
Input<SHUTTER_ENDSTOP_PIN> endstopShutter(true);
Output<SHUTTER_PIN_ENABLE> enableShutter;
Output<SHUTTER_M0> m0Shutter;

// LED Matrix
LedControl ledMatrix = LedControl(LED_MATRIX_SDI_PIN, LED_MATRIX_SCL_PIN, LED_MATRIX_CS_PIN, 1); 
unsigned long prevousMillisCountdown = 0;
byte countDown = 5;

void initShutter() {
  debug("initShutter",String("debut"));
  initLedMatrix();
  
  // stepper shutter
  pinMode(SHUTTER_M0, OUTPUT);
  pinMode(SHUTTER_M1, OUTPUT);
  digitalWrite(SHUTTER_M0, LOW);
  digitalWrite(SHUTTER_M1, HIGH);
  enableShutter.write(LOW);
  shutter.setMaxSpeed(300);
  shutter.setAcceleration(200);
  shutter.setCurrentPosition(0);
  int homing = 0;
  boolean bEndStop = !endstopShutter.read();

  // do 3step backward to be sure shutter it's not close of switch.
  /*while (!bEndStop && homing > -4) { 
    shutter.moveTo(homing); 
    shutter.run();
    homing--;
    delay(5);
    bEndStop = !endstopShutter.read();
  }
  shutter.setCurrentPosition(0);
  shutter.setMaxSpeed(1000);
  shutter.setAcceleration(400);
  homing = 0;*/
  
  while (!bEndStop) { 
    shutter.moveTo(homing); 
    shutter.run();
    homing--;
    delay(5);
    bEndStop = !endstopShutter.read();
  }
  Serial.println(shutter.currentPosition());
  shutter.setCurrentPosition(0);
  enableShutter.write(HIGH);
  bCloseShutter = true;
}

void testShutter() {
  debug("takeShot", String("begin"));
  // TODO calculate duration of the shot.
  enableShutter.write(LOW);
  shutter.setMaxSpeed(SHUTTER_SPEED);
  shutter.setAcceleration(SHUTTER_ACCEL);
  shutter.setCurrentPosition(0);
  shutter.moveTo(100);
  
  while(shutter.currentPosition() > SHUTTER_STEP_REVOL / 2){
      shutter.run();
  }
  shutter.stop();
  shutter.setCurrentPosition(0);
  shutter.run();
  enableShutter.write(HIGH);
  debug("takeShot", String("end"));
}

void takeShot() {
  debug("takeShot", String("begin"));
  #ifndef SIMUL_MODE
  // TODO calculate duration of the shot.
  enableShutter.write(LOW);
  shutter.setMaxSpeed(SHUTTER_SPEED);
  shutter.setAcceleration(SHUTTER_ACCEL);
  shutter.moveTo(SHUTTER_STEP_REVOL);
  bCloseShutter = false;
  unsigned long startFlash = 0;
  unsigned long flashDuration = 150;
  unsigned long currentMillis = millis();
  long flashPos = -100;

  while(!bCloseShutter){
    currentMillis = millis();
    boolean bEndStop = false;
    long currentPos = shutter.currentPosition();
    if( currentPos < (long)-50){ // Digital read at the last time.
      bEndStop = !endstopShutter.read();
    }
    
    // Time to flash. Full aperture.
    if(currentPos == flashPos){
      digitalWrite(FLASH_PIN, LOW);
      startFlash = currentMillis;
      //Serial.println("startflash");
    }
    // stop flash
    /*if(startFlash != 0 && currentMillis - startFlash > flashDuration){
      digitalWrite(FLASH_PIN, LOW);
      startFlash = 0;
    }*/
    
    if(bEndStop){
      Serial.println(shutter.currentPosition());
      shutter.stop();
      shutter.setCurrentPosition(0);
      shutter.run();
      enableShutter.write(HIGH);
      digitalWrite(FLASH_PIN, HIGH);
      bCloseShutter = true;
    } else{
      if(shutter.distanceToGo() == 0){// Case shutter get stuck.
        shutter.moveTo(shutter.currentPosition() - 1);
      }
      shutter.run();
    }
  }
  clearLedMatrix();
  #endif
  debug("takeShot", String("end"));
}

/********************************
 *  LED MATRIX FOR COUNTDOWN
 ********************************/
void initLedMatrix(){
  ledMatrix.shutdown(0,false);  // Wake up displays
  ledMatrix.setIntensity(0,1);  // Set intensity levels at the minimum
  ledMatrix.clearDisplay(0);  // Clear Displays
}

void displayNumber(byte numero)
{
  for (int i = 0; i < 8; i++)  
  {
    ledMatrix.setRow(0,i,IMAGES[numero][i]);
  }
}

void showCountdown()
{
  debug("showCountdown", String("begin"));
  countDown = 5;
  displayNumber(countDown);
  prevousMillisCountdown = millis();
}

void refreshCountdown()
{
  unsigned long currentMillis = millis();
  if(currentMillis - prevousMillisCountdown >= 1000){
    prevousMillisCountdown = currentMillis;
    countDown = countDown > 0 ? countDown-1 : 0;
    displayNumber(countDown);
  }
}

void showArrowDown()
{
  for (int i = 0; i < 8; i++)  
  {
    ledMatrix.setRow(0,i,ARROWDOWN[i]);
  }
}

void showCross()
{
  for (int i = 0; i < 8; i++)  
  {
    ledMatrix.setRow(0,i,CROSS[i]);
  }
}

void clearLedMatrix(){
  ledMatrix.clearDisplay(0);
}

byte getCountDown(){
  return countDown;
}

boolean readSWShutter(){
  return endstopShutter.read();
}
