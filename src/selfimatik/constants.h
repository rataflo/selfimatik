#ifndef constants_h
#define constants_h

#include "Arduino.h"

// uncomment to activate debug with serial output.
#define DEBUG_MODE
// uncomment to activate simulation mode (no paper advance, cut paper & shot).
//#define SIMUL_MODE

// Uncomment if protoype of selfimatik
// Y MAX = 2984
// X MAX = 3923
#define ISPROTO



//PINS
#define X_PIN_STP 54
#define X_PIN_DIR 55
#define X_ENDSTOP_PIN 2
#define X_PIN_ENABLE 38
#define X_M0 5
#define X_M1 6

#define Y_PIN_STP 60
#define Y_PIN_DIR 61
#define Y_ENDSTOP_PIN 3
#define Y_PIN_ENABLE 56
#define Y_M0 59
#define Y_M1 58

#define PAPER_PIN_STP 36
#define PAPER_PIN_DIR 34
#define PAPER_SWITCH1_PIN 18
#define PAPER_PIN_ENABLE 30
#define PAPER_M0 4
#define PAPER_M1 57

#define SHUTTER_PIN_STP 26
#define SHUTTER_PIN_DIR 28
#define SHUTTER_ENDSTOP_PIN 14
#define SHUTTER_PIN_ENABLE 24
#define SHUTTER_M0 64
#define SHUTTER_M1 63

#define SCISSOR_PIN_STP 46
#define SCISSOR_PIN_DIR 48
#define SCISSOR_ENDSTOP_PIN 15
#define SCISSOR_PIN_ENABLE 62
#define SCISSOR_M0 22
#define SCISSOR_M1 39

#define LED_MATRIX_SDI_PIN 52  //12 // SDI = DIN
#define LED_MATRIX_CS_PIN 51   //11 // CS
#define LED_MATRIX_SCL_PIN 50  //10 // SCL = CLOCK

#define FLASH_PIN A15
#define START_BTN_PIN 19

#define SERVO_PIN 11
#define SERVO_POWER_PIN 10

#define EXIT_PIN 8

#define LED_PIN 7
#define LEDSELFI_PIN 9
//#define LEDSELFIBIS_PIN 10

#define LCD_PINS_RS 16
#define LCD_PINS_ENABLE 17
#define LCD_PINS_D4 23
#define LCD_PINS_D5 25
#define LCD_PINS_D6 27
#define LCD_PINS_D7 29
#define LCD_HEIGHT 4
#define LCD_WIDTH 20

// Encoder
#define BTN_EN1 31
#define BTN_EN2 33
#define BTN_ENC 35

//CONSTANTS
#ifdef ISPROTO
#define DRYER_PIN A11
#define SERVO_POS1 27
#define SERVO_POS2 160
#define SERVO_POS3 90

#define Y_MIDDLE_POS 0
#define Y_AGITATE_POS -2700
#define Y_BOTTOM_POS -2899

#define CAMERA_POS -270
#define TANK1_POS -3923
#define TANK2_POS -2700
#define TANK3_POS -1450
#define TANK4_POS -100
#define TANK5_POS -100
#define TANK6_POS -1450
#define TANK7_POS -2700
#define TANK8_POS -3923
#define EXIT_POS -3923
#define SERVO_ROTATE_POS -2700

#define X_SPEED 1000
#define X_ACCEL 2000

#define Y_SPEED 1000
#define Y_ACCEL 2000

#define SHUTTER_SPEED 1000
#define SHUTTER_ACCEL 1450       // 1450 => 1s, 5500 => 1/2s, 22000 => 1/4s, 30000 => max, 191ms less than 1/8s
#define SHUTTER_STEP_REVOL -200  // Number of step for a full rotation of the shutter

#define SCISSOR_SPEED 3000
#define SCISSOR_ACCEL 8000
#define SCISSOR_STEP_OPENED 300  // Number of step to fully open the scissor.

#define NB_STEP_PAPER_ONE_SHOT -606  // Number of step to move to another shot.
#define NB_STEP_PAPER_OUT -2700      // Number of step to move out paper.Previous:1285
#define PAPER_SPEED 400
#define PAPER_ACCEL 200
#define DELTA_FIRST_SHOT 440  //Delta in step to do after paper reach opto 1. Previous: -80
#endif

#ifndef ISPROTO

#define DRYER_PIN 12

#define SERVO_POS1 12
#define SERVO_POS2 147
#define SERVO_POS3 90

#define Y_MIDDLE_POS -450
#define Y_AGITATE_POS -2700
#define Y_BOTTOM_POS -3350

#define CAMERA_POS -1350
#define TANK1_POS -1250
#define TANK2_POS -2600
#define TANK3_POS -4000
#define TANK4_POS -5300
#define TANK5_POS -5600
#define TANK6_POS -4300
#define TANK7_POS -3000
#define TANK8_POS -1600
#define EXIT_POS 0
#define SERVO_ROTATE_POS -1600

#define X_SPEED 1000
#define X_ACCEL 2000

#define Y_SPEED 1000
#define Y_ACCEL 2000

#define SHUTTER_SPEED 1000
#define SHUTTER_ACCEL 1450       // 1450 => 1s, 5500 => 1/2s, 22000 => 1/4s, 30000 => max, 191ms less than 1/8s
#define SHUTTER_STEP_REVOL -200  // Number of step for a full rotation of the shutter

#define SCISSOR_SPEED 1000
#define SCISSOR_ACCEL 2000
#define SCISSOR_STEP_OPENED 260  // Number of step to fully open the scissor.

#define NB_STEP_PAPER_ONE_SHOT -606  // Number of step to move to another shot.
#define NB_STEP_PAPER_OUT -3100      // Number of step to move out paper.Previous:1285
#define PAPER_SPEED 400
#define PAPER_ACCEL 200
#define DELTA_FIRST_SHOT 500  //Delta in step to do after paper reach opto 1. Previous: -80

#endif

#define INIT_SPEED 1000
#define INIT_ACCEL 500

#define WAIT_BETWEEN_SHOT 5000  // Wait between shot in ms.
#define DRYER_TIME 10000

#define START_LIGHT 3
#define STOP_LIGHT 0

const int expTimes[3] = { 6000, 2000, 700 };

// EEPROM data & work variables
#define EEPROM_ADRESS 0
struct storage {
  byte checkCode = 0;
  int totStrip = 0;
  int userCount1 = 0;
  int userCount2 = 0;
  int tankTimes[8] = { 35, 10, 20, 10, 30, 15, 10, 15 };
  int dripTimes[8] = { 5, 5, 5, 5, 5, 5, 5, 15 };

  int timeDrip1 = 5;
  int timeDrip2 = 5;
  int timeDrip3 = 5;
  int timeDrip4 = 5;
  int timeDrip5 = 5;
  int timeDrip6 = 5;
  int timeDrip7 = 5;
  int timeDrip8 = 10;

  int timeDryer = 15;

  int tankPos[8] = { TANK1_POS, TANK2_POS, TANK3_POS, TANK4_POS, TANK5_POS, TANK6_POS, TANK7_POS, TANK8_POS };
  int cameraPos = CAMERA_POS;
  int exitPos = EXIT_POS;
  int servoRotatePos = SERVO_ROTATE_POS;

  int nbStepOneShot = NB_STEP_PAPER_ONE_SHOT;
  int nbStepPaperOut = NB_STEP_PAPER_OUT;
  int deltaFirstShot = DELTA_FIRST_SHOT;

  int middlePos = Y_MIDDLE_POS;
  int agitateTopPos = Y_AGITATE_POS;
  int bottomPos = Y_BOTTOM_POS;
  byte servoPos1 = SERVO_POS1;
  byte servoPos2 = SERVO_POS2;
  byte servoPos3 = SERVO_POS3;

  bool userMode1 = false;

  int expTime = 1;
  int bulbTime = 1;

  bool bflashOn = true;
  bool bDefineEachShot = false;
  byte nbExp = 1;

  int shotExpTimes[4] = { 1, 1, 1, 1 };
  int shotBulbTimes[4] = { 1, 1, 1, 1 };
  bool shotFlashOn[4] = { true, true, true, true };
  int shotNbExps[4] = { 1, 1, 1, 1 };

  byte startLight = 3;
  byte stopLight = 0;
};


#endif
