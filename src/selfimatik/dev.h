#ifndef dev_h
#define dev_h

#include "src/AccelStepper/src/AccelStepper.h"
#include "src/AccelStepper/src/MultiStepper.h"
#include <Servo.h>
#include "constants.h"
#include "parameters.h"
#include "tests.h"

void initDev();
void initX();
void initY();
void devProcess();
void gotoCamera();
void bathTime(byte nbBath);
void gotoPosX(long pos);
void gotoPosY(long pos);
void manageDryer();
void moveArm(byte pos);
#endif
