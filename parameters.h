#ifndef parameters_h
#define parameters_h

#include "constants.h"
#include "src/EEPROMEx/EEPROMex.h"
#include "src/EEPROMEx/EEPROMVar.h"

extern storage parametres;

void loadParameters();
void updateParameters();
storage getParameters();

#endif