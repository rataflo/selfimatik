
#ifndef scissor_h
#define scissor_h

#include "src/DirectIO/DirectIO.h"
#include "src/AccelStepper/src/AccelStepper.h"
#include "src/AccelStepper/src/MultiStepper.h"
#include "constants.h"
#include "tests.h"

void initScissor();
void cutPaper();
void closeScissor();
bool readSWScissor();
void disableScissor();
#endif
