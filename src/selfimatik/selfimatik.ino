/*
 * Selfimatik program.
 * Run on Atmega 2560. 
 * 
 * (c) Flo Gales 2023 : rataflo@free.fr
 * Licence cc-by-nc-sa : https://creativecommons.org/licenses/by-nc-sa/4.0/
 *
 * Libraries : 
 *  Fast Read\Write : https://github.com/mmarchetti/DirectIO
 *  Steppers control: http://www.airspayce.com/mikem/arduino/AccelStepper/index.html
 *  Arduino menu library: https://github.com/neu-rah/ArduinoMenu
 *  Led matrix: https://github.com/wayoda/LedControl
 *  EEPROM managment : https://github.com/thijse/Arduino-EEPROMEx
 *  Timer Three: https://github.com/PaulStoffregen/TimerThree
 */

#include "src/DirectIO/DirectIO.h"
#include "constants.h"
#include "parameters.h"
#include "dev.h"
#include "scissor.h"
#include "shutter.h"
#include "paper.h"
#include "lcd.h"
#include "tests.h"

// Work variables
byte stepTakeShot = 0;
byte nbTotExp = 0;
byte numExp = 0;
byte numFrame = 0;
Input<START_BTN_PIN> startBtn(true);

void setup() {
  pinMode(FLASH_PIN, OUTPUT);
  digitalWrite(FLASH_PIN, LOW);
  /*delay(5000);
  digitalWrite(FLASH_PIN, HIGH);
  delay(100);
  digitalWrite(FLASH_PIN, LOW);*/
  
  
  pinMode(LEDSELFI_PIN, OUTPUT);
  analogWrite(LEDSELFI_PIN, 100);
  //pinMode(LEDSELFIBIS_PIN, OUTPUT);
  //digitalWrite(LEDSELFIBIS_PIN, HIGH);
  
  loadParameters();
  initPhotomaton();
}

void loop() {
  unsigned long currentMillis = millis();

  // If coin acceptor OK and clic start button.
  if(stepTakeShot == 0){
    #ifdef ISPROTO 
      displayNumber(0);
    #else
      showArrowDown();
    #endif
    
    if(!startBtn.read()) {
      parametres.totStrip += 1;
      parametres.userCount1 += 1;
      parametres.userCount2 += 1;
      updateParameters();
      idleOnLCD();
      stepTakeShot = 1;
    }
    checkMenu();
  }

  if(stepTakeShot > 0) {
    if(parametres.userMode1 == true){ // Simple code made in a hurry for "Faites de l'image". TODO: refactor.
      showCountdown();
      while(getCountDown() > 0){
        refreshCountdown();
      }
      takeShot(0);
      movePaperNextShot();
      takeShot(1);
      movePaperNextShot();
      takeShot(2);
      movePaperNextShot();
      takeShot(3);
      movePaperNextShot();
      takeShot(0);
      movePaperPreviousShot();
      showCross();
      gotoCamera();
      analogWrite(LEDSELFI_PIN, 0);
      //digitalWrite(LEDSELFIBIS_PIN, 0);
      movePaperOut();
      cutPaper();
      closeScissor();
      movePaperFirstShot();
      devProcess();
      idleOffLCD();
      stepTakeShot = 0;

    }else{
      manageStepsTakeShot(); 
    }
    
  } 

  manageDryer();
}

void manageStepsTakeShot(){
  debug("manageStepsTakeShot-begin:", stepTakeShot);
  switch (stepTakeShot) {
    case 1: // First countdown
      showCountdown();
      while(getCountDown() > 0){
        refreshCountdown();
      }
      break;
      
    case 2: // Take photo.
    case 4:
    case 6:
    case 8:
      // Multiple exposure
      if(numExp == 0){
        nbTotExp = (parametres.bDefineEachShot ? parametres.shotNbExps[numFrame] : parametres.nbExp) - 1;
      }

      takeShot(numFrame);
      
      // Multiple exposure
      if(numExp < nbTotExp){
        stepTakeShot--;
        showCountdown();
        while(getCountDown() > 0){
          refreshCountdown();
        }
      }
      numExp++;
      break;
      
    case 3: // move paper for next shot + countdown
    case 5:
    case 7:
      movePaperNextShot();
      numExp = 0;
      numFrame++;
      break;
      
    case 9:// last paper move, need to wait for spider to be at the correct position and scissor opened.  
      numFrame = 0;
      numExp = 0;
      showCross();
      gotoCamera();
      analogWrite(LEDSELFI_PIN, 0);
      //digitalWrite(LEDSELFIBIS_PIN, LOW);
      movePaperOut();
      break;
      
    case 10: // cut paper and zou!
      cutPaper();
      closeScissor();
      break;
      
    case 12: // move paper back for first shot.
      movePaperFirstShot();
      devProcess();
      break;
    case 13: // check for free slot.
      idleOffLCD();
      break;
  }

  bool bNextStep = true;

  if(bNextStep){
    stepTakeShot = stepTakeShot >= 13 ? 0 : stepTakeShot + 1;
  }
}


/***************************
 *  INIT & STARTUP
 **************************/
void initPhotomaton(){
  debug("initPhotomaton-", String("begin"));
  
  initLCD();
  initLedMatrix();
  initDev();
  printStartup("init Shutter");
  initShutter();
  printStartup("init Scissor");
  initScissor();
  printStartup("init Paper");
  initPaper();
  showArrowDown();
  #ifdef ISPROTO 
    displayNumber(0);
  #endif
  printStartup("init OK");
  debug("initPhotomaton-", String("end"));
}
