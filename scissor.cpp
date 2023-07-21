#include "scissor.h"

// Scissor.
AccelStepper scissor(1, SCISSOR_PIN_STP, SCISSOR_PIN_DIR);
Input<SCISSOR_ENDSTOP_PIN> endstopScissor(true);
Output<SCISSOR_PIN_ENABLE> enableScissor;

void initScissor() {
  debug("initScissor",String("debut"));
  // stepper scissor
  pinMode(SCISSOR_M0, OUTPUT);
  pinMode(SCISSOR_M1, OUTPUT);
  digitalWrite(SCISSOR_M0, HIGH);
  digitalWrite(SCISSOR_M1, LOW);
  enableScissor.write(LOW);
  scissor.setCurrentPosition(0);
  scissor.setMaxSpeed(SCISSOR_SPEED);
  scissor.setAcceleration(SCISSOR_ACCEL);
  closeScissor();
}

void cutPaper() {
  enableScissor.write(LOW);
  scissor.moveTo(SCISSOR_STEP_OPENED);

  while(scissor.distanceToGo() != 0){
    scissor.run();
  }
  enableScissor.write(HIGH);
}

void closeScissor() {
  enableScissor.write(LOW);
  scissor.moveTo((-SCISSOR_STEP_OPENED)-50); 
  bool bCloseScissor = !endstopScissor.read();
  while(!bCloseScissor){
    scissor.run();
    bCloseScissor = !endstopScissor.read();
  }
  scissor.stop();
  scissor.setCurrentPosition(0);
  scissor.run();
  enableScissor.write(HIGH);
}

bool readSWScissor(){
  return endstopScissor.read();
}
