/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * Arduino Mega with RAMPS v1.4 adjusted pin assignments
 *
 *  MKS v1.4  (Extruder, Fan, Bed)
 *  MKS v1.4  (Extruder, Extruder, Fan, Bed)
 */

#if !defined(__AVR_ATmega1280__) && !defined(__AVR_ATmega2560__)
  #error "Oops!  Make sure you have 'Arduino Mega' selected from the 'Tools -> Boards' menu."
#endif

#if HOTENDS > 2 || E_STEPPERS > 2
  #error "MKS BASE 1.4 supports up to 2 hotends / E-steppers. Comment out this line to continue."
#endif

#define BOARD_NAME "MKS BASE v1.4"

// Servos
#define SERVO0_PIN         11 //PWM11 PB5
#define SERVO1_PIN          6 //PWM6  PH3
#define SERVO2_PIN          5 //PWM5  PE3
#ifndef SERVO3_PIN
  #define SERVO3_PIN        4 //PWM4  PG5
#endif

// Limit Switches
#define X_MIN_PIN           3  //Confirmed Labeled X- //PWM3 PE5
#if ENABLED(FILAMENT_RUNOUT_SENSOR)    
  #undef X_MAX_PIN             //Confirmed Labeled X+ //PWM2 PE4 
  #undef FIL_RUNOUT_PIN
  #define FIL_RUNOUT_PIN    2
#else
  #define X_MAX_PIN         2  //Confirmed Labeled X+ //PWM2 PE4
#endif
#define Y_MIN_PIN          14  //Confirmed Labeled Y- //USART3_TX PJ1
#undef Y_MAX_PIN
//#define Y_MAX_PIN          15  //Confirmed Labeled Y+ //USART3_RX PJ0
#define Z_MIN_PIN          18  //Confirmed Labeled Z- //USART1_TX PD3
#undef Z_MAX_PIN
//#define Z_MAX_PIN          19  //Confirmed Labeled Z+ //USART1_RX PD2

// Z Probe (when not Z_MIN_PIN)
#ifndef Z_MIN_PROBE_PIN
  #define Z_MIN_PROBE_PIN  32
#endif

// Steppers
#define X_STEP_PIN         54  //Confirmed Labeled X  //A0
#define X_DIR_PIN          55  //Confirmed            //A1
#define X_ENABLE_PIN       38  //Confirmed            //D38
#define X_CS_PIN           53  //Confirmed            //SPI_SS

#define Y_STEP_PIN         60  //Confirmed Labeled Y  //A6
#define Y_DIR_PIN          61  //Confirmed            //A7
#define Y_ENABLE_PIN       56  //Confirmed            //A2
#define Y_CS_PIN           49  //Confirmed            //D49

#define Z_STEP_PIN         46  //Confirmed Labeled Z  //D46
#define Z_DIR_PIN          48  //Confirmed            //D48
#define Z_ENABLE_PIN       62  //Confirmed            //A8
#define Z_CS_PIN           40  //Confirmed            //D40

#define E0_STEP_PIN        26  //Confirmed Labeled E0 //D26
#define E0_DIR_PIN         28  //Confirmed            //D28
#define E0_ENABLE_PIN      24  //Confirmed            //D24
#define E0_CS_PIN          42  //Confirmed            //D42

#define E1_STEP_PIN        36  //Confirmed Labeled E1 //D36
#define E1_DIR_PIN         34  //Confirmed            //D34
#define E1_ENABLE_PIN      30  //Confirmed            //D30
#define E1_CS_PIN          44  //Confirmed            //D44

// Temperature Sensors
#define TEMP_0_PIN         13   // Analog Input  //Confirmed Labeled A13  //PWM13 PB7
#define TEMP_1_PIN         15   // Analog Input  //Confirmed Labeled A14  //USART3_TX PJ1
#define TEMP_BED_PIN       14   // Analog Input  //Confirmed Labeled A15  //USART3_RX PJ0

// SPI for Max6675 or Max31855 Thermocouple
#define MAX6675_SS         66  //A12 PK4

// Augmentation for auto-assigning RAMPS plugs
#if DISABLED(IS_RAMPS_EEB) && DISABLED(IS_RAMPS_EEF) && DISABLED(IS_RAMPS_EFB) && DISABLED(IS_RAMPS_EFF) && DISABLED(IS_RAMPS_SF) && !PIN_EXISTS(MOSFET_D)
  #if HOTENDS > 1
    #if TEMP_SENSOR_BED
      #define IS_RAMPS_EEB
    #else
      #define IS_RAMPS_EEF
    #endif
  #elif TEMP_SENSOR_BED
    #define IS_RAMPS_EFB
  #else
    #define IS_RAMPS_EFF
  #endif
#endif

// Heaters / Fans
#define HEATER_0_PIN       10  //Confirmed Labeled E0 //PWM10 PB4

// Non-specific are "EFB" (i.e., "EFBF" or "EFBE")
#define FAN_PIN             9  //Confirmed    //PWM9 PH6
#define HEATER_BED_PIN      8  //Confirmed    //PWM8 PH5
#if HOTENDS == 1
  #define FAN1_PIN          7  //Confirmed Labeled E1  //PWM7 PH4
#else
  #define HEATER_1_PIN      7  //Confirmed Labeled E1  //PWM7 PH4
#endif

// Misc. Functions
#define SDSS               53  //Confirmed on EXP1  //SPI_SS PB0
#define LED_PIN            13  //PWM13 PB7

#ifndef FILWIDTH_PIN
  #define FILWIDTH_PIN      5  //PWM5 PE3
#endif

#define PS_ON_PIN          12  //PWM12 PB6

#if ENABLED(CASE_LIGHT_ENABLE) && !PIN_EXISTS(CASE_LIGHT) && !defined(SPINDLE_LASER_ENABLE_PIN)
  #if !defined(NUM_SERVOS) || NUM_SERVOS == 0 // try to use servo connector first
    #define CASE_LIGHT_PIN  11  //6      //PWM6 PH3
  #elif !(ENABLED(ULTRA_LCD) && ENABLED(NEWPANEL) \
      && (ENABLED(PANEL_ONE) || ENABLED(VIKI2) || ENABLED(miniVIKI) || ENABLED(MINIPANEL) || ENABLED(REPRAPWORLD_KEYPAD)))  // try to use AUX 2
    #define CASE_LIGHT_PIN 11  //44     // MUST BE HARDWARE PWM
  #endif
#endif

// M3/M4/M5 - Spindle/Laser Control
#if ENABLED(SPINDLE_LASER_ENABLE) && !PIN_EXISTS(SPINDLE_LASER_ENABLE)
  #if !defined(NUM_SERVOS) || NUM_SERVOS == 0 // try to use servo connector first
    #define SPINDLE_LASER_ENABLE_PIN  4  // Pin should have a pullup/pulldown!  //PWM4 PG5
    #define SPINDLE_LASER_PWM_PIN     6  // MUST BE HARDWARE PWM   //PWM6 PH3
    #define SPINDLE_DIR_PIN           5  //PWM5 PE3
  #elif !(ENABLED(ULTRA_LCD) && ENABLED(NEWPANEL) \
      && (ENABLED(PANEL_ONE) || ENABLED(VIKI2) || ENABLED(miniVIKI) || ENABLED(MINIPANEL) || ENABLED(REPRAPWORLD_KEYPAD)))  // try to use AUX 2
    #define SPINDLE_LASER_ENABLE_PIN 40  // Pin should have a pullup/pulldown! //D40 PG1
    #define SPINDLE_LASER_PWM_PIN    44  // MUST BE HARDWARE PWM  //D44 PL5
    #define SPINDLE_DIR_PIN          65  //A11 PK3
  #endif
#endif

// Průša i3 MK2 Multiplexer Support
#ifndef E_MUX0_PIN
  #define E_MUX0_PIN 40   // Z_CS_PIN  //D40 PG1
#endif
#ifndef E_MUX1_PIN
  #define E_MUX1_PIN 42   // E0_CS_PIN  //D42 PL7
#endif
#ifndef E_MUX2_PIN
  #define E_MUX2_PIN 44   // E1_CS_PIN  //D44 PL5
#endif

//////////////////////////
// LCDs and Controllers //
//////////////////////////

#if ENABLED(ULTRA_LCD)
  // LCD Display output pins
  #if ENABLED(REPRAPWORLD_GRAPHICAL_LCD)
    #define LCD_PINS_RS         49   //Confirmed EXP2 // CS chip select /SS chip slave select   //D49 PL0
    #define LCD_PINS_ENABLE     51   //Confirmed EXP2 // SID (MOSI)  //SPI_MOSI PB2
    #define LCD_PINS_D4         52   //Confirmed EXP2 // SCK (CLK) clock  //SPI_SCK PB1

  #elif ENABLED(NEWPANEL) && ENABLED(PANEL_ONE)
    #define LCD_PINS_RS         40
    #define LCD_PINS_ENABLE     42
    #define LCD_PINS_D4         65
    #define LCD_PINS_D5         66
    #define LCD_PINS_D6         44
    #define LCD_PINS_D7         64

  #else
    #if ENABLED(CR10_STOCKDISPLAY)
      #define LCD_PINS_RS       27  //Confirmed EXP1
      #define LCD_PINS_ENABLE   29  //Confirmed EXP1
      #define LCD_PINS_D4       25  //Confirmed EXP1

      #if DISABLED(NEWPANEL)
        #define BEEPER_PIN      37  //Confirmed EXP1
      #endif

    #else

      #if ENABLED(MKS_12864OLED) || ENABLED(MKS_12864OLED_SSD1306)
        #define LCD_PINS_DC     25   //Confirmed EXP1  // Set as output on init
        #define LCD_PINS_RS     27   //Confirmed EXP1  // Pull low for 1s to init
        // DOGM SPI LCD Support
        #define DOGLCD_CS       16   //Confirmed EXP1
        #define DOGLCD_MOSI     17   //Confirmed EXP1
        #define DOGLCD_SCK      23   //Confirmed EXP1
        #define DOGLCD_A0       LCD_PINS_DC
      #else
        #define LCD_PINS_RS     16  //Confirmed EXP1
        #define LCD_PINS_ENABLE 17  //Confirmed EXP1
        #define LCD_PINS_D4     23  //Confirmed EXP1
        #define LCD_PINS_D5     25  //Confirmed EXP1
        #define LCD_PINS_D6     27  //Confirmed EXP1
      #endif

      #define LCD_PINS_D7       29  //Confirmed EXP1

      #if DISABLED(NEWPANEL)
        #define BEEPER_PIN      33  //Confirmed EXP2
      #endif
    #endif
  #endif

  // LCD Display input pins
  #if ENABLED(NEWPANEL)
    #if ENABLED(REPRAP_DISCOUNT_SMART_CONTROLLER)
      #define BEEPER_PIN        37  //Confirmed EXP1

      #if ENABLED(CR10_STOCKDISPLAY)
        #define BTN_EN1         17  //Confirmed EXP1
        #define BTN_EN2         23  //Confirmed EXP1
      #else
        #define BTN_EN1         31  //Confirmed EXP2
        #define BTN_EN2         33  //Confirmed EXP2
      #endif

      #define BTN_ENC           35  //Confirmed EXP1
      #define SD_DETECT_PIN     49  //Confirmed EXP2
      #define KILL_PIN          41  //Confirmed EXP2

      #if ENABLED(BQ_LCD_SMART_CONTROLLER)
        #define LCD_BACKLIGHT_PIN 39
      #endif

    #elif ENABLED(REPRAPWORLD_GRAPHICAL_LCD)
      #define BTN_EN1           64
      #define BTN_EN2           59
      #define BTN_ENC           63
      #define SD_DETECT_PIN     42

    #elif ENABLED(LCD_I2C_PANELOLU2)
      #define BTN_EN1           47
      #define BTN_EN2           43
      #define BTN_ENC           32
      #define LCD_SDSS          53  //Confirmed EXP2
      #define KILL_PIN          41  //Confirmed EXP2

    #elif ENABLED(LCD_I2C_VIKI)
      #define BTN_EN1           22 // http://files.panucatt.com/datasheets/viki_wiring_diagram.pdf explains 40/42.
      #define BTN_EN2            7 // 22/7 are unused on RAMPS_14. 22 is unused and 7 the SERVO0_PIN on RAMPS_13.
      #define BTN_ENC           -1
      #define LCD_SDSS          53  //Confirmed EXP2
      #define SD_DETECT_PIN     49  //Confirmed EXP2

    #elif ENABLED(VIKI2) || ENABLED(miniVIKI)
  /**
   * VIKI2 Has two groups of wires with...
   *
   * +Vin     + Input supply, requires 120ma for LCD and mSD card
   * GND      Ground Pin
   * MOSI     Data input for LCD and SD
   * MISO     Data output for SD
   * SCK      Clock for LCD and SD
   * AO       Reg. Sel for LCD
   * LCS      Chip Select for LCD
   * SDCS     Chip Select for SD
   * SDCD     Card Detect pin for SD
   * ENCA     Encoder output A
   * ENCB     Encoder output B
   * ENCBTN   Encoder button switch
   *
   * BTN      Panel mounted button switch
   * BUZZER   Piezo buzzer
   * BLUE-LED Blue LED ring pin (3 to 5v, mosfet buffered)
   * RED-LED  Red LED ring pin (3 to 5v, mosfet buffered)
   *
   * This configuration uses the following arrangement:
   *
   * EXP1 D37 = EN2   D35 = EN1     EXP2 D50 = MISO  D52 = SCK
   *      D17 = BLUE  D16 = RED          D31 = ENC   D53 = SDCS
   *      D23 = KILL  D25 = BUZZ         D33 = ---   D51 = MOSI
   *      D27 = A0    D29 = LCS          D49 = SDCD  RST = ---
   *      GND = GND   5V  = 5V           GND = ---   D41 = ---
   */

  #define LCD_SCREEN_ROT_180

  // VIKI2 12-wire lead
  #define SD_DETECT_PIN   49       // orange/white         SDCD
  #define BTN_EN1         35       // white                ENCA
  #define BTN_EN2         37       // green                ENCB
  #define BTN_ENC         31       // purple               ENCBTN
  #define DOGLCD_A0       27       // brown                A0
  #define DOGLCD_CS       29       // green/white          LCS
                       // 50          gray                 MISO
                       // 51          yellow               MOSI
                       // 52          orange               SCK
  //#define SDSS          53       // blue                 SDCS

  // VIKI2 4-wire lead
  #define KILL_PIN        23       // blue                 BTN
  #define BEEPER_PIN      25       // green                BUZZER
  #define STAT_LED_RED_PIN 16      // yellow               RED-LED
  #define STAT_LED_BLUE_PIN 17     // white                BLUE-LED

    #elif ENABLED(ELB_FULL_GRAPHIC_CONTROLLER)
      #define DOGLCD_CS         29
      #define DOGLCD_A0         27
      #define BEEPER_PIN        23
      #define LCD_BACKLIGHT_PIN 33
      #define BTN_EN1           35
      #define BTN_EN2           37
      #define BTN_ENC           31
      #define LCD_SDSS          53
      #define SD_DETECT_PIN     49
      #define KILL_PIN          41

    #elif ENABLED(MKS_MINI_12864)  // Added in Marlin 1.1.6
      #define DOGLCD_A0         27
      #define DOGLCD_CS         25
      // GLCD features
      //#define LCD_CONTRAST   190
      // Uncomment screen orientation
      //#define LCD_SCREEN_ROT_90
      //#define LCD_SCREEN_ROT_180
      //#define LCD_SCREEN_ROT_270
      #define BEEPER_PIN        37
      // not connected to a pin
      #define LCD_BACKLIGHT_PIN 65 // backlight LED on A11/D65
      #define BTN_EN1           31
      #define BTN_EN2           33
      #define BTN_ENC           35
//    #define SDSS              53
      #define SD_DETECT_PIN     49
      #define KILL_PIN          64

    #elif ENABLED(MINIPANEL)
      #define BEEPER_PIN        42
      // not connected to a pin
      #define LCD_BACKLIGHT_PIN 65 // backlight LED on A11/D65
      #define DOGLCD_A0         44
      #define DOGLCD_CS         66
      // GLCD features
      //#define LCD_CONTRAST   190
      // Uncomment screen orientation
      //#define LCD_SCREEN_ROT_90
      //#define LCD_SCREEN_ROT_180
      //#define LCD_SCREEN_ROT_270
      #define BTN_EN1           40
      #define BTN_EN2           63
      #define BTN_ENC           59
//    #define SDSS              53
      #define SD_DETECT_PIN     49
      #define KILL_PIN          64

    #else
      #define BEEPER_PIN        33

      // Buttons are directly attached using AUX-2
      #if ENABLED(REPRAPWORLD_KEYPAD)
        #define SHIFT_OUT       40
        #define SHIFT_CLK       44
        #define SHIFT_LD        42
        #define BTN_EN1         64
        #define BTN_EN2         59
        #define BTN_ENC         63
      #elif ENABLED(PANEL_ONE)
        #define BTN_EN1         59
        #define BTN_EN2         63
        #define BTN_ENC         49
      #else
        #define BTN_EN1         37
        #define BTN_EN2         35
        #define BTN_ENC         31
      #endif

      #if ENABLED(G3D_PANEL)
        #define SD_DETECT_PIN   49
        #define KILL_PIN        41
      #endif

    #endif
  #endif // NEWPANEL

#endif // ULTRA_LCD

#if ENABLED(ZONESTAR_LCD)
  #define LCD_PINS_RS        64
  #define LCD_PINS_ENABLE    44
  #define LCD_PINS_D4        63
  #define LCD_PINS_D5        40
  #define LCD_PINS_D6        42
  #define LCD_PINS_D7        65
  #define ADC_KEYPAD_PIN     12
  #define BTN_EN1            -1
  #define BTN_EN2            -1
  #define BTN_ENC            -1
  // pin 29 N/C
#endif // ZONESTAR_LCD
