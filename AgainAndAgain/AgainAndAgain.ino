#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

String inputString;
byte num;
byte amt;
byte plr;
bool newDataKeybd = false;
String bin;
String amount;
String polar; 
String prior_inputString;
void setup() {
   mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  inputString.reserve(200);
  Serial.println();
  Serial.println("DFRobot DFPlayer Mini Demo");
  Serial.println("Initializing DFPlayer ... (May take 3~5 seconds)");

  if (!myDFPlayer.begin(mySoftwareSerial)) {Serial.println(F("Unable to begin:"));
                                            Serial.println(F("1.Please recheck the connection!"));
                                            Serial.println(F("2.Please insert the SD card!"));
                                            while(true);}
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.setTimeOut(500);
  myDFPlayer.volume(30);
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
}

String getValue(String data, char separator, int index)
{ int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){ found++; strIndex[0] = strIndex[1]+1;
                                                           strIndex[1] = (i == maxIndex) ? i+1 : i;}
    }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void serialEvent(){while (Serial.available()) {inputString = Serial.readString();
                                               {bin = getValue(inputString,'l',0);
                                                amount = getValue(inputString,'l',1);
                                                polar = getValue(inputString,'l',2);
                                                newDataKeybd = true;
                                                num = bin.toInt();
                                                amt = amount.toInt();
                                                plr = polar.toInt();
                                                Serial.println(num);
                                                Serial.println(amount);
                                                Serial.println(polar);
                                               }
                                              }  
}

void serialEventtoSpeaker_BIN(){myDFPlayer.playFolder(01,num);}
void serialEventtoSpeaker_AMOUNT(){myDFPlayer.playFolder(02,amt);}
void serialEventtoSpeaker_POLAR(){myDFPlayer.playFolder(03,plr);}
void serialEventtoSpeaker(){serialEventtoSpeaker_BIN(); delay(2300);
                            serialEventtoSpeaker_AMOUNT(); delay(1800);
                            serialEventtoSpeaker_POLAR();
                            } 
                                                               
void loop() {
  if (newDataKeybd) {if (prior_inputString != inputString){ prior_inputString = inputString;
                                                            serialEventtoSpeaker();
                                                            inputString = ""; 
                                                            newDataKeybd = false;}
                     }
}
