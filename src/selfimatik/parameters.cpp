#include "parameters.h"

storage parametres;

storage getParameters()
{
    return parametres;
}

void loadParameters(){
  EEPROM.readBlock(EEPROM_ADRESS, parametres);
  //parametres.checkCode = 0;
  // Check verif code, if not correct init eeprom.
  if(parametres.checkCode < 1){
    parametres.checkCode = 1;
    parametres.totStrip = 0;
    parametres.tankTimes[0] = 35;
    parametres.tankTimes[1] = 10;
    parametres.tankTimes[2] = 20;
    parametres.tankTimes[3] = 10;
    parametres.tankTimes[4] = 30;
    parametres.tankTimes[5] = 15;
    parametres.tankTimes[6] = 15;
    parametres.tankTimes[7] = 20;
    parametres.dripTimes[0] = 5;
    parametres.dripTimes[1] = 5;
    parametres.dripTimes[2] = 5;
    parametres.dripTimes[3] = 5;
    parametres.dripTimes[4] = 5;
    parametres.dripTimes[5] = 5;
    parametres.dripTimes[6] = 5;
    parametres.dripTimes[7] = 15;
    EEPROM.writeBlock(EEPROM_ADRESS, parametres);
  }
  
  if(parametres.checkCode < 2){
    parametres.checkCode = 2;
    parametres.userCount1 = 10;
    parametres.userCount2 = 0;
    parametres.timeDryer = 15;
    EEPROM.writeBlock(EEPROM_ADRESS, parametres);
  }

  if(parametres.checkCode < 3){
    parametres.checkCode = 3;
    /*parametres.tankPos[0]=-1250;
    parametres.tankPos[1]=-2600;
    parametres.tankPos[2]=-4000;
    parametres.tankPos[3]=-5300;
    parametres.tankPos[4]=-5600;
    parametres.tankPos[5]=-4300;
    parametres.tankPos[6]=-3000;
    parametres.tankPos[7]=-1600;*/
    parametres.tankPos[0]=TANK1_POS;
    parametres.tankPos[1]=TANK2_POS;
    parametres.tankPos[2]=TANK3_POS;
    parametres.tankPos[3]=TANK4_POS;
    parametres.tankPos[4]=TANK5_POS;
    parametres.tankPos[5]=TANK6_POS;
    parametres.tankPos[6]=TANK7_POS;
    parametres.tankPos[7]=TANK8_POS;
    parametres.cameraPos = CAMERA_POS;
    parametres.exitPos = EXIT_POS;
    parametres.servoRotatePos = SERVO_ROTATE_POS;
  }
  
  if(parametres.checkCode < 4){
    parametres.checkCode = 4;
    parametres.nbStepOneShot = NB_STEP_PAPER_ONE_SHOT;
    parametres.nbStepPaperOut = NB_STEP_PAPER_OUT;
    parametres.deltaFirstShot = DELTA_FIRST_SHOT;
    parametres.middlePos = Y_MIDDLE_POS;
    parametres.agitateTopPos = Y_AGITATE_POS;
    parametres.bottomPos = Y_BOTTOM_POS;
  }
  
  if(parametres.checkCode < 5){
    parametres.checkCode = 5;
    parametres.servoPos1 = SERVO_POS1;
    parametres.servoPos2 = SERVO_POS2;
    parametres.servoPos3 = SERVO_POS3;
  }

  if(parametres.checkCode < 6){
    parametres.checkCode = 6;
    parametres.userMode1 = false;
  }

  if(parametres.checkCode < 7){
    parametres.checkCode = 7;
    parametres.expTime = 1;
    parametres.bulbTime = 1;
  }

  if(parametres.checkCode < 8){
    parametres.checkCode = 8;
    parametres.bflashOn = true;
    parametres.nbExp = 1;
    parametres.bDefineEachShot = false;

    parametres.shotExpTimes[0] = 1;
    parametres.shotBulbTimes[0] = 1;
    parametres.shotFlashOn[0] = true;
    parametres.shotNbExps[0] = 1;

    parametres.shotExpTimes[1] = 1;
    parametres.shotBulbTimes[1] = 1;
    parametres.shotFlashOn[1] = true;
    parametres.shotNbExps[1] = 1;

    parametres.shotExpTimes[2] = 1;
    parametres.shotBulbTimes[2] = 1;
    parametres.shotFlashOn[2] = true;
    parametres.shotNbExps[2] = 1;

    parametres.shotExpTimes[3] = 1;
    parametres.shotBulbTimes[3] = 1;
    parametres.shotFlashOn[3] = true;
    parametres.shotNbExps[3] = 1;
  
  }

  if(parametres.checkCode < 9){
    parametres.checkCode = 9;
    parametres.startLight = 3;
    parametres.stopLight = 0;
  }

  EEPROM.writeBlock(EEPROM_ADRESS, parametres);
}
void updateParameters(){
  EEPROM.updateBlock(EEPROM_ADRESS, parametres);
}
