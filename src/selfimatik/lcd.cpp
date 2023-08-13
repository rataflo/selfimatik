#include "lcd.h"

using namespace Menu;
LiquidCrystal lcd(LCD_PINS_RS, LCD_PINS_ENABLE, LCD_PINS_D4, LCD_PINS_D5, LCD_PINS_D6, LCD_PINS_D7);

ClickEncoder clickEncoder(BTN_EN2, BTN_EN1, BTN_ENC,4);

ClickEncoderStream encStream(clickEncoder,1);
MENU_INPUTS(in, &encStream);
void timerIsr() {clickEncoder.service();}

result doAlert(eventMask e, prompt &item);

result saveParams(eventMask e, prompt &item){
  updateParameters();
  return proceed;
}

result showEvent(eventMask e,navNode& nav,prompt& item) {
  /*Serial.print("event: ");
  Serial.println(e);*/
  return proceed;
}

result eraseCounter1(eventMask e, prompt &item){
  parametres.userCount1 = 0;
  updateParameters();
  return proceed;
}

result eraseCounter2(eventMask e, prompt &item){
  parametres.userCount2 = 0;
  updateParameters();
  return proceed;
}

MENU(menuData,"Data",showEvent,anyEvent,noStyle
  ,FIELD(parametres.totStrip,"Total"," ",0,0,0,0, doNothing ,noEvent, noStyle)
  ,FIELD(parametres.userCount1,"Counter 1","",0,0,0,0, doNothing ,noEvent, noStyle)
  ,OP("Erase counter 1", eraseCounter1, enterEvent)
  ,FIELD(parametres.userCount2,"Counter 2","",0,0,0,0, doNothing ,noEvent, noStyle)
  ,OP("Erase counter 2", eraseCounter2, enterEvent)
  ,EXIT("<Back")
);

MENU(menuTanks, "Tanks", doNothing ,noEvent, noStyle
  ,FIELD(parametres.tankTimes[0],"Tank 1(Dev)","s",0,480,1,0,saveParams ,exitEvent , noStyle)
  ,FIELD(parametres.tankTimes[1],"Tank 2(H2o)","s",0,480,1,0,saveParams ,exitEvent , noStyle)
  ,FIELD(parametres.tankTimes[2],"Tank 3(Blch)","s",0,480,1,0,saveParams ,exitEvent , noStyle)
  ,FIELD(parametres.tankTimes[3],"Tank 4(H2o)","s",0,480,1,0,saveParams ,exitEvent , noStyle)
  ,FIELD(parametres.tankTimes[4],"Tank 5(Clar)","s",0,480,1,0,saveParams ,exitEvent , noStyle)
  ,FIELD(parametres.tankTimes[5],"Tank 6(Toner)","s",0,480,1,0,saveParams ,exitEvent , noStyle)
  ,FIELD(parametres.tankTimes[6],"Tank 7(H2o)","s",0,480,1,0,saveParams ,exitEvent , noStyle)
  ,FIELD(parametres.tankTimes[7],"Tank 8(H2o)","s",0,480,1,0,saveParams ,exitEvent , noStyle)
  ,EXIT("<Back")
);

MENU(menuDrips, "Drips", doNothing ,noEvent, noStyle
  ,FIELD(parametres.dripTimes[0],"Drip 1","s",0,480,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.dripTimes[1],"Drip 2","s",0,480,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.dripTimes[2],"Drip 3","s",0,480,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.dripTimes[3],"Drip 4","s",0,480,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.dripTimes[4],"Drip 5","s",0,480,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.dripTimes[5],"Drip 6","s",0,480,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.dripTimes[6],"Drip 7","s",0,480,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.dripTimes[7],"Final drip","s",0,480,1,0,saveParams ,exitEvent, noStyle)
  ,EXIT("<Back")
);

MENU(menuTimes, "Times", doNothing ,noEvent, noStyle
  ,SUBMENU(menuTanks)
  ,SUBMENU(menuDrips)
  ,FIELD(parametres.timeDryer,"Dryer","s",-1,480,1,0,saveParams ,exitEvent, noStyle)
  ,EXIT("<Back")
);

MENU(menuPositions, "Positions", doNothing ,noEvent, noStyle
  ,FIELD(parametres.cameraPos,"Camera","",-5300,0,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.exitPos,"Exit","",-5300,0,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.servoRotatePos,"Arm Rotation","",-5300,0,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.tankPos[0],"Tank 1","",-5300,0,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.tankPos[1],"Tank 2","",-5300,0,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.tankPos[2],"Tank 3","",-5300,0,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.tankPos[3],"Tank 4","",-5300,0,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.tankPos[4],"Tank 5","",-5300,0,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.tankPos[5],"Tank 6","",-5300,0,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.tankPos[6],"Tank 7","",-5300,0,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.tankPos[7],"Tank 8","",-5300,0,1,0,saveParams ,exitEvent, noStyle)
  ,EXIT("<Back")
);

MENU(menuPaper, "Paper", doNothing ,noEvent, noStyle
  ,FIELD(parametres.nbStepOneShot,"One shot","",-5000,0,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.nbStepPaperOut,"Paper out","",-6000,0,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.deltaFirstShot,"Delta first","",0,1000,1,0,saveParams ,exitEvent, noStyle)
  ,EXIT("<Back")
);

MENU(menuArm, "Arm", doNothing ,noEvent, noStyle
  ,FIELD(parametres.middlePos,"Middle","",-3350,0,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.agitateTopPos,"Agitate top","",-3350,0,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.bottomPos,"Bottom pos","",-3350,0,1,0,saveParams ,exitEvent, noStyle)
  ,EXIT("<Back")
);

MENU(menuServo, "Servo", doNothing ,noEvent, noStyle
  ,FIELD(parametres.servoPos1,"Pos 1","",0,200,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.servoPos2,"Pos 2","",0,200,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.servoPos3,"Pos 3 (proto)","",0,200,1,0,saveParams ,exitEvent, noStyle)
  ,EXIT("<Back")
);

MENU(menuSetup,"Setup",showEvent,anyEvent,noStyle
  ,SUBMENU(menuPositions)
  ,SUBMENU(menuPaper)
  ,SUBMENU(menuArm)
  ,SUBMENU(menuServo)
  ,EXIT("<Back")
);

TOGGLE(parametres.userMode1,userMode1,"Dble exp 1: ",doNothing,noEvent,noStyle
  ,VALUE("On", true, saveParams, noEvent)
  ,VALUE("Off", false, saveParams, noEvent)
);


SELECT(parametres.expTime, selExpTimes, "Exp time", saveParams, exitEvent, noStyle
  ,VALUE("1/4", 0, doNothing, noEvent)
  ,VALUE("1/2", 1, doNothing, noEvent)
  ,VALUE("1s", 2, doNothing, noEvent)
  ,VALUE("Bulb", 3, doNothing, noEvent)
);

MENU(menuModes,"User modes",showEvent,anyEvent,noStyle
  ,SUBMENU(userMode1)
  ,EXIT("<Back")
);

TOGGLE(parametres.bflashOn,flashOnOff,"Flashs: ",doNothing,noEvent,noStyle
  ,VALUE("On", true, saveParams, noEvent)
  ,VALUE("Off", false, saveParams, noEvent)
);

TOGGLE(parametres.bDefineEachShot, defineOnOff, "Activate: ", doNothing, noEvent, noStyle
  ,VALUE("On", true, saveParams, noEvent)
  ,VALUE("Off", false, saveParams, noEvent)
);


SELECT(parametres.shotExpTimes[0], selExpTimes1, "Exp time", saveParams, exitEvent, noStyle
  ,VALUE("1/4", 0, doNothing, noEvent)
  ,VALUE("1/2", 1, doNothing, noEvent)
  ,VALUE("1s", 2, doNothing, noEvent)
  ,VALUE("Bulb", 3, doNothing, noEvent)
);

TOGGLE(parametres.shotFlashOn[0],flashOnOff1,"Flashs: ",doNothing,noEvent,noStyle
  ,VALUE("On", true, saveParams, noEvent)
  ,VALUE("Off", false, saveParams, noEvent)
);

MENU(defineShot1,"Shot 1",showEvent,anyEvent,noStyle
  ,SUBMENU(selExpTimes1)
  ,FIELD(parametres.shotBulbTimes[0],"Bulb time","s",0,600,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.shotNbExps[0],"Nb exp","",1,10,1,0,saveParams ,exitEvent, noStyle)
  ,SUBMENU(flashOnOff1)
  ,EXIT("<Back")
);

SELECT(parametres.shotExpTimes[1], selExpTimes2, "Exp time", saveParams, exitEvent, noStyle
  ,VALUE("1/4", 0, doNothing, noEvent)
  ,VALUE("1/2", 1, doNothing, noEvent)
  ,VALUE("1s", 2, doNothing, noEvent)
  ,VALUE("Bulb", 3, doNothing, noEvent)
);

TOGGLE(parametres.shotFlashOn[1],flashOnOff2,"Flashs: ",doNothing,noEvent,noStyle
  ,VALUE("On", true, saveParams, noEvent)
  ,VALUE("Off", false, saveParams, noEvent)
);

MENU(defineShot2,"Shot 2",showEvent,anyEvent,noStyle
  ,SUBMENU(selExpTimes2)
  ,FIELD(parametres.shotBulbTimes[1],"Bulb time","s",0,600,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.shotNbExps[1],"Nb exp","",1,10,1,0,saveParams ,exitEvent, noStyle)
  ,SUBMENU(flashOnOff2)
  ,EXIT("<Back")
);

SELECT(parametres.shotExpTimes[2], selExpTimes3, "Exp time", saveParams, exitEvent, noStyle
  ,VALUE("1/4", 0, doNothing, noEvent)
  ,VALUE("1/2", 1, doNothing, noEvent)
  ,VALUE("1s", 2, doNothing, noEvent)
  ,VALUE("Bulb", 3, doNothing, noEvent)
);

TOGGLE(parametres.shotFlashOn[2],flashOnOff3,"Flashs: ",doNothing,noEvent,noStyle
  ,VALUE("On", true, saveParams, noEvent)
  ,VALUE("Off", false, saveParams, noEvent)
);

MENU(defineShot3,"Shot 3",showEvent,anyEvent,noStyle
  ,SUBMENU(selExpTimes3)
  ,FIELD(parametres.shotBulbTimes[2],"Bulb time","s",0,600,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.shotNbExps[2],"Nb exp","",1,10,1,0,saveParams ,exitEvent, noStyle)
  ,SUBMENU(flashOnOff3)
  ,EXIT("<Back")
);

SELECT(parametres.shotExpTimes[3], selExpTimes4, "Exp time", saveParams, exitEvent, noStyle
  ,VALUE("1/4", 0, doNothing, noEvent)
  ,VALUE("1/2", 1, doNothing, noEvent)
  ,VALUE("1s", 2, doNothing, noEvent)
  ,VALUE("Bulb", 3, doNothing, noEvent)
);

TOGGLE(parametres.shotFlashOn[3],flashOnOff4,"Flashs: ",doNothing,noEvent,noStyle
  ,VALUE("On", true, saveParams, noEvent)
  ,VALUE("Off", false, saveParams, noEvent)
);

MENU(defineShot4,"Shot 4",showEvent,anyEvent,noStyle
  ,SUBMENU(selExpTimes4)
  ,FIELD(parametres.shotBulbTimes[3],"Bulb time","s",0,600,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.shotNbExps[3],"Nb exp","",1,10,1,0,saveParams ,exitEvent, noStyle)
  ,SUBMENU(flashOnOff4)
  ,EXIT("<Back")
);

MENU(menuDefineEachShot,"Define each shot",showEvent,anyEvent,noStyle
  ,SUBMENU(defineOnOff)
  ,SUBMENU(defineShot1)
  ,SUBMENU(defineShot2)
  ,SUBMENU(defineShot3)
  ,SUBMENU(defineShot4)
  ,EXIT("<Back")
);


MENU(menuShot,"Shot",showEvent,anyEvent,noStyle
  ,SUBMENU(selExpTimes)
  ,FIELD(parametres.bulbTime,"Bulb time","s",0,600,1,0,saveParams ,exitEvent, noStyle)
  ,FIELD(parametres.nbExp,"Nb exp","",1,10,1,0,saveParams ,exitEvent, noStyle)
  ,SUBMENU(flashOnOff)
  ,SUBMENU(menuDefineEachShot)
  ,SUBMENU(menuModes)
  ,EXIT("<Back")
);

MENU(mainMenu,"Main menu",doNothing,noEvent,wrapStyle
  ,SUBMENU(menuShot)
  ,SUBMENU(menuTimes)
  ,SUBMENU(menuData)
  ,SUBMENU(menuSetup)
);

#define MAX_DEPTH 5

MENU_OUTPUTS(out, MAX_DEPTH
  ,LIQUIDCRYSTAL_OUT(lcd,{0,0,20,4})
  ,NONE
);
NAVROOT(nav,mainMenu,MAX_DEPTH,in,out);//the navigation root object

/*result idle(menuOut& o,idleEvent e) {
  o.setCursor(0,0);
  o.print(F("suspended..."));
  return proceed;
}*/

void initLCD() {
  Serial.begin(115200);
  while(!Serial);
  Serial.flush();
  //encoder.begin();
  lcd.begin(20,4);
  //nav.idleTask=idle;
  //nav.showTitle = false;
  menuData[0].enabled=disabledStatus;
  menuData[1].enabled=disabledStatus;
  menuData[3].enabled=disabledStatus;
  menuShot[1].enabled = parametres.expTime != 3 ? disabledStatus : enabledStatus; 

  menuDefineEachShot[1].enabled = parametres.bDefineEachShot ? enabledStatus : disabledStatus; 
  menuDefineEachShot[2].enabled = parametres.bDefineEachShot ? enabledStatus : disabledStatus; 
  menuDefineEachShot[3].enabled = parametres.bDefineEachShot ? enabledStatus : disabledStatus; 
  menuDefineEachShot[4].enabled = parametres.bDefineEachShot ? enabledStatus : disabledStatus; 

  defineShot1[1].enabled = parametres.shotExpTimes[0] != 3 ? disabledStatus : enabledStatus; 
  defineShot2[1].enabled = parametres.shotExpTimes[1] != 3 ? disabledStatus : enabledStatus; 
  defineShot3[1].enabled = parametres.shotExpTimes[2] != 3 ? disabledStatus : enabledStatus; 
  defineShot4[1].enabled = parametres.shotExpTimes[3] != 3 ? disabledStatus : enabledStatus; 

  lcd.setCursor(0, 0);
  lcd.print("Mini 14 system");
  lcd.setCursor(0, 1);
  lcd.print("V0.1");
  lcd.setCursor(0, 2);
  lcd.print("Startup...");
  Timer3.initialize(1000);
  Timer3.attachInterrupt(timerIsr);
  clickEncoder.setAccelerationEnabled(true);
}

void idleOnLCD(){
  nav.idleOn();
}
void idleOffLCD(){
  nav.idleOff();
}

void checkMenu(){
  menuShot[1].enabled = parametres.expTime != 3 ? disabledStatus : enabledStatus; 

  menuDefineEachShot[1].enabled = parametres.bDefineEachShot ? enabledStatus : disabledStatus; 
  menuDefineEachShot[2].enabled = parametres.bDefineEachShot ? enabledStatus : disabledStatus; 
  menuDefineEachShot[3].enabled = parametres.bDefineEachShot ? enabledStatus : disabledStatus; 
  menuDefineEachShot[4].enabled = parametres.bDefineEachShot ? enabledStatus : disabledStatus; 

  defineShot1[1].enabled = parametres.shotExpTimes[0] != 3 ? disabledStatus : enabledStatus; 
  defineShot2[1].enabled = parametres.shotExpTimes[1] != 3 ? disabledStatus : enabledStatus; 
  defineShot3[1].enabled = parametres.shotExpTimes[2] != 3 ? disabledStatus : enabledStatus; 
  defineShot4[1].enabled = parametres.shotExpTimes[3] != 3 ? disabledStatus : enabledStatus; 

  nav.poll();
}
