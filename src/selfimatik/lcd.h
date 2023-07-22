#ifndef lcd_h
#define lcd_h

#include <Wire.h>
#include "src/ArduinoMenu_library/src/menu.h"
#include "src/ArduinoMenu_library/src/menuIO/liquidCrystalOut.h"
#include "src/TimerThree/TimerThree.h"
#include "src/ArduinoMenu_library/src/menuIO/clickEncoderIn.h"
#include "src/ArduinoMenu_library/src/menuIO/keyIn.h"
#include "src/ArduinoMenu_library/src/menuIO/chainStream.h"
#include "src/ArduinoMenu_library/src/menuIO/serialOut.h"
#include "src/ArduinoMenu_library/src/menuIO/serialIn.h"
#include "constants.h"
#include "parameters.h"

void initLCD();
void checkMenu();
void idleOnLCD();
void idleOffLCD();
#endif