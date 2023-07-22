#ifndef paper_h
#define paper_h

#include "src/DirectIO/DirectIO.h"
#include "src/AccelStepper/src/AccelStepper.h"
#include "src/AccelStepper/src/MultiStepper.h"
#include "constants.h"
#include "parameters.h"
#include "shutter.h"


void movePaperFirstShot();
void initPaper();
void initPaperAutomatic();
void movePaperNextShot();
void movePaperPreviousShot();
void movePaperOut();

boolean readSWPaper1();

#endif
