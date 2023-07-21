#include "paper.h"
#include "tests.h"

// Paper stepper
AccelStepper paper(1, PAPER_PIN_STP, PAPER_PIN_DIR);
// Opto endstops for paper.
Input<PAPER_SWITCH1_PIN> opto1(true);// Activate pullup
Output<PAPER_PIN_ENABLE> enablePaper;

void movePaperFirstShot() {
  debug("movePaperFirstShot", String("begin"));
  #ifndef SIMUL_MODE
  enablePaper.write(LOW);
  paper.setCurrentPosition(0);
  paper.moveTo(9999); 
  boolean bOpto1 = opto1.read();

  while (bOpto1) { 
    paper.run();
    bOpto1 = opto1.read();
  }
  paper.stop();
  paper.setCurrentPosition(0);
  paper.run();
  
  // marche arriére
  paper.moveTo(parametres.deltaFirstShot); 
  while(paper.distanceToGo() != 0){
    paper.run();
  }
  enablePaper.write(HIGH);
  #endif
}

void initPaper() {
  debug("initPaper", String("begin"));
  pinMode(PAPER_M0, OUTPUT);
  pinMode(PAPER_M1, OUTPUT);
  digitalWrite(PAPER_M0, LOW);
  digitalWrite(PAPER_M1, HIGH);
  enablePaper.write(LOW);
  paper.setCurrentPosition(0);
  paper.setMaxSpeed(PAPER_SPEED);
  paper.setAcceleration(PAPER_ACCEL);
  
  int homing = 0;
  boolean bOpto1 = opto1.read();
  // case no paper detected, move a little bit then stop to allow to insert new roll of paper manually.
  paper.moveTo(-1000);

  while (!bOpto1 && paper.distanceToGo() != 0) { 
    paper.run();
    bOpto1 = opto1.read();
  }

  // Manually mode if paper not detected.
  if(!bOpto1){
    enablePaper.write(HIGH);
    while (!bOpto1){
      bOpto1 = opto1.read();
    }
  }

  paper.setCurrentPosition(0);
  enablePaper.write(HIGH);
  movePaperFirstShot();
}

void movePaperNextShot() {
  debug("movePaperNextShot", String("begin"));
  #ifndef SIMUL_MODE
  showCountdown();
  enablePaper.write(LOW);
  paper.setCurrentPosition(0);

  paper.moveTo(parametres.nbStepOneShot); 
  while(paper.distanceToGo() != 0){
    paper.run();
    refreshCountdown();
  }

  while(getCountDown() > 0){
    refreshCountdown();
  }
  #endif
  //enablePaper.write(HIGH);
}

void movePaperPreviousShot() {
  debug("movePaperPreviousShot", String("begin"));
  #ifndef SIMUL_MODE
  enablePaper.write(LOW);
  paper.setCurrentPosition(0);

  paper.moveTo(-parametres.nbStepOneShot); 
  while(paper.distanceToGo() != 0){
    paper.run();
  }

  #endif
  //enablePaper.write(HIGH);
}

void movePaperOut() {
  debug("movePaperOut", String("begin"));
  #ifndef SIMUL_MODE
  enablePaper.write(LOW);
  paper.setCurrentPosition(0);
  paper.moveTo(parametres.nbStepPaperOut); 

  while(paper.distanceToGo() != 0){
    paper.run();
  }
  enablePaper.write(HIGH);
  #endif
}

boolean readSWPaper1(){
  return opto1.read();
}