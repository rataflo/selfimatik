
#ifndef shutter_h
#define shutter_h

#include "src/DirectIO/DirectIO.h"
#include "src/AccelStepper/src/AccelStepper.h"
#include "src/AccelStepper/src/MultiStepper.h"
#include "src/LedControl/src/LedControl.h"
#include "constants.h"
#include "tests.h"
#include "parameters.h"

// For LED Matrix (5, 4 ,3, 2, 1, smiley)
const byte IMAGES[][8] = {
{
  B00000000,
  B01100100,
  B01100010,
  B00000010,
  B00000010,
  B01100010,
  B01100100,
  B00000000
},{
  B00000000,
  B00000001,
  B00000001,
  B01111111,
  B01111111,
  B00010001,
  B00000001,
  B00000000
},{
  B00000000,
  B00110001,
  B01111001,
  B01001001,
  B01000101,
  B01100111,
  B00100011,
  B00000000
},{
  B00000000,
  B00110110,
  B01111111,
  B01001001,
  B01001001,
  B01100011,
  B00100010,
  B00000000
},{
  B00000000,
  B00000100,
  B01111111,
  B01111111,
  B00100100,
  B00010100,
  B00001100,
  B00000000
},{
  B00000000,
  B01001110,
  B01011111,
  B01010001,
  B01010001,
  B01110011,
  B01110010,
  B00000000
}};

const byte ARROWDOWN[8] = {
  B00001000,
  B00001100,
  B11111110,
  B11111111,
  B11111110,
  B00001100,
  B00001000,
  B00000000
};

const byte CROSS[8] = {
  B10000001,
  B01000010,
  B00100100,
  B00011000,
  B00011000,
  B00100100,
  B01000010,
  B10000001
};

const int IMAGES_LEN = sizeof(IMAGES)/8;


void initShutter();
void takeShot(byte numFrame);
void initLedMatrix();
void displayNumber(byte numero);
void showCountdown();
void refreshCountdown();
void showArrowDown();
void showCross();
void clearLedMatrix();
byte getCountDown();
boolean isFlashOn();
boolean readSWShutter();
void testShutter();
#endif
