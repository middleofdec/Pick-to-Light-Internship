#include <SPI.h>
int clockPin_Card1 = 2; // SH_CP
int latchPin_Card1 = 3; // ST_CP
int dataPin_Card1 = 4; // DS
int clockPin_Card2 = 5; // SH_CP
int latchPin_Card2 = 6; // ST_CP
int dataPin_Card2 = 7; // DS
int clockPin_Card3 = 8; // SH_CP
int latchPin_Card3 = 9; // ST_CP
int dataPin_Card3 = 10; // DS

byte num;
byte amt;
byte plr;
String inputString;
bool newDataKeybd = false; 
byte Ic595_11,Ic595_12,Ic595_13,Ic595_14,Ic595_15,Ic595_16,Ic595_17,Ic595_18,Ic595_19,Ic595_110;
byte Ic595_21,Ic595_22,Ic595_23,Ic595_24,Ic595_25,Ic595_26,Ic595_27,Ic595_28,Ic595_29,Ic595_210;
byte Ic595_31,Ic595_32,Ic595_33,Ic595_34,Ic595_35,Ic595_36,Ic595_37,Ic595_38,Ic595_39,Ic595_310;
byte Card595_1,Card595_2,Card595_3;
byte LedPattern[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80} ; 
String bin,Prior_bin;
String amount;
String polar;


String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void serialEventto595(){
  if      ( num>= 1  && num <= 8 ){Ic595_11 = LedPattern[num-1] ;}
  else if ( num>= 9  && num <= 16){Ic595_12 = LedPattern[num-9] ;}
  else if ( num>= 17 && num <= 24){Ic595_13 = LedPattern[num-17];}
  else if ( num>= 25 && num <= 32){Ic595_14 = LedPattern[num-25];}
  else if ( num>= 33 && num <= 40){Ic595_15 = LedPattern[num-33];}
  else if ( num>= 41 && num <= 48){Ic595_16 = LedPattern[num-41];}
  else if ( num>= 49 && num <= 56){Ic595_17 = LedPattern[num-49];}
  else if ( num>= 57 && num <= 64){Ic595_18 = LedPattern[num-57];}
  else if ( num>= 65 && num <= 72){Ic595_19 = LedPattern[num-65];}
  else if ( num>= 73 && num <= 80){Ic595_110 = LedPattern[num-73];}

  if      ( num>= 81 && num <= 88){Ic595_21 = LedPattern[num-81];}
  else if ( num>= 89 && num <= 96){Ic595_22 = LedPattern[num-89];}
  else if ( num>= 97 && num <= 104){Ic595_23 = LedPattern[num-97];}
  else if ( num>= 105 && num <= 112){Ic595_24 = LedPattern[num-105];}
  else if ( num>= 113 && num <= 120){Ic595_25 = LedPattern[num-113];}
  else if ( num>= 121 && num <= 128){Ic595_26 = LedPattern[num-121];}
  else if ( num>= 129 && num <= 136){Ic595_27 = LedPattern[num-129];}
  else if ( num>= 137 && num <= 144){Ic595_28 = LedPattern[num-137];}
  else if ( num>= 145 && num <= 152){Ic595_29 = LedPattern[num-145];}
  else if ( num>= 153 && num <= 160){Ic595_210 = LedPattern[num-153];}

  if      ( num>= 161 && num <= 168){Ic595_31 = LedPattern[num-161];}
  else if ( num>= 169 && num <= 176){Ic595_32 = LedPattern[num-169];}
  else if ( num>= 177 && num <= 184){Ic595_33 = LedPattern[num-177];}
  else if ( num>= 185 && num <= 192){Ic595_34 = LedPattern[num-185];}
  else if ( num>= 193 && num <= 200){Ic595_35 = LedPattern[num-193];}

}

void ShiftLED_Card1(){ 
  digitalWrite(latchPin_Card1,  LOW);    
  shiftOut(dataPin_Card1, clockPin_Card1, MSBFIRST, Ic595_110 );
  shiftOut(dataPin_Card1, clockPin_Card1, MSBFIRST, Ic595_19 );
  shiftOut(dataPin_Card1, clockPin_Card1, MSBFIRST, Ic595_18 );
  shiftOut(dataPin_Card1, clockPin_Card1, MSBFIRST, Ic595_17 );
  shiftOut(dataPin_Card1, clockPin_Card1, MSBFIRST, Ic595_16 );
  shiftOut(dataPin_Card1, clockPin_Card1, MSBFIRST, Ic595_15 );
  shiftOut(dataPin_Card1, clockPin_Card1, MSBFIRST, Ic595_14 );
  shiftOut(dataPin_Card1, clockPin_Card1, MSBFIRST, Ic595_13 );
  shiftOut(dataPin_Card1, clockPin_Card1, MSBFIRST, Ic595_12 );
  shiftOut(dataPin_Card1, clockPin_Card1, MSBFIRST, Ic595_11 );
  digitalWrite(latchPin_Card1,  HIGH);
         
   Ic595_11=0;   Ic595_12=0;   Ic595_13=0;  Ic595_14=0; Ic595_15=0; 
   Ic595_16=0;   Ic595_17=0;   Ic595_18=0;  Ic595_19=0; Ic595_110=0;    
}

void ShiftLED_Card2(){
  digitalWrite(latchPin_Card2,  LOW);
  shiftOut(dataPin_Card2, clockPin_Card2, MSBFIRST, Ic595_210 );
  shiftOut(dataPin_Card2, clockPin_Card2, MSBFIRST, Ic595_29 );
  shiftOut(dataPin_Card2, clockPin_Card2, MSBFIRST, Ic595_28 );
  shiftOut(dataPin_Card2, clockPin_Card2, MSBFIRST, Ic595_27 );
  shiftOut(dataPin_Card2, clockPin_Card2, MSBFIRST, Ic595_26 );
  shiftOut(dataPin_Card2, clockPin_Card2, MSBFIRST, Ic595_25 );
  shiftOut(dataPin_Card2, clockPin_Card2, MSBFIRST, Ic595_24 );
  shiftOut(dataPin_Card2, clockPin_Card2, MSBFIRST, Ic595_23 );
  shiftOut(dataPin_Card2, clockPin_Card2, MSBFIRST, Ic595_22 );
  shiftOut(dataPin_Card2, clockPin_Card2, MSBFIRST, Ic595_21 );
  digitalWrite(latchPin_Card2,  HIGH);
  Ic595_21=0;   Ic595_22=0;   Ic595_23=0;  Ic595_24=0; Ic595_25=0; 
  Ic595_26=0;   Ic595_27=0;   Ic595_28=0;  Ic595_29=0; Ic595_210=0;  
}

void ShiftLED_Card3(){
  digitalWrite(latchPin_Card3,  LOW);
  shiftOut(dataPin_Card3, clockPin_Card3, MSBFIRST, Ic595_35 );
  shiftOut(dataPin_Card3, clockPin_Card3, MSBFIRST, Ic595_34 );
  shiftOut(dataPin_Card3, clockPin_Card3, MSBFIRST, Ic595_33 );
  shiftOut(dataPin_Card3, clockPin_Card3, MSBFIRST, Ic595_32 );
  shiftOut(dataPin_Card3, clockPin_Card3, MSBFIRST, Ic595_31 );
  digitalWrite(latchPin_Card3,  HIGH);
  Ic595_31=0;   Ic595_32=0;   Ic595_33=0;  Ic595_34=0; Ic595_35=0; 
}

void offLED(){
  
  digitalWrite(latchPin_Card1, LOW);
  shiftOut(dataPin_Card1, clockPin_Card1, MSBFIRST, B00000000);
  shiftOut(dataPin_Card1, clockPin_Card1, MSBFIRST, B00000000);
  shiftOut(dataPin_Card1, clockPin_Card1, MSBFIRST, B00000000);
  shiftOut(dataPin_Card1, clockPin_Card1, MSBFIRST, B00000000);
  shiftOut(dataPin_Card1, clockPin_Card1, MSBFIRST, B00000000);
  shiftOut(dataPin_Card1, clockPin_Card1, MSBFIRST, B00000000);
  shiftOut(dataPin_Card1, clockPin_Card1, MSBFIRST, B00000000);
  shiftOut(dataPin_Card1, clockPin_Card1, MSBFIRST, B00000000);
  shiftOut(dataPin_Card1, clockPin_Card1, MSBFIRST, B00000000);
  shiftOut(dataPin_Card1, clockPin_Card1, MSBFIRST, B00000000);
  digitalWrite(latchPin_Card1,  HIGH);

  digitalWrite(latchPin_Card2, LOW);
  shiftOut(dataPin_Card2, clockPin_Card2, MSBFIRST, B00000000);
  shiftOut(dataPin_Card2, clockPin_Card2, MSBFIRST, B00000000);
  shiftOut(dataPin_Card2, clockPin_Card2, MSBFIRST, B00000000);
  shiftOut(dataPin_Card2, clockPin_Card2, MSBFIRST, B00000000);
  shiftOut(dataPin_Card2, clockPin_Card2, MSBFIRST, B00000000);
  shiftOut(dataPin_Card2, clockPin_Card2, MSBFIRST, B00000000);
  shiftOut(dataPin_Card2, clockPin_Card2, MSBFIRST, B00000000);
  shiftOut(dataPin_Card2, clockPin_Card2, MSBFIRST, B00000000);
  shiftOut(dataPin_Card2, clockPin_Card2, MSBFIRST, B00000000);
  shiftOut(dataPin_Card2, clockPin_Card2, MSBFIRST, B00000000);
  digitalWrite(latchPin_Card2,  HIGH);

  digitalWrite(latchPin_Card3, LOW);
  shiftOut(dataPin_Card3, clockPin_Card3, MSBFIRST, B00000000);
  shiftOut(dataPin_Card3, clockPin_Card3, MSBFIRST, B00000000);
  shiftOut(dataPin_Card3, clockPin_Card3, MSBFIRST, B00000000);
  shiftOut(dataPin_Card3, clockPin_Card3, MSBFIRST, B00000000);
  shiftOut(dataPin_Card3, clockPin_Card3, MSBFIRST, B00000000);
  digitalWrite(latchPin_Card3,  HIGH);
}

void setup() {
  IC595_Initial();
  SPI_Initial();
  Serial_Initial();
  offLED();
}

void Serial_Initial(){Serial.begin(115200);inputString.reserve(200); Serial.print("Hi");}
void SPI_Initial(){SPI.begin(); SPI.setBitOrder(MSBFIRST);}
void IC595_Initial(){pinMode(latchPin_Card1, OUTPUT); pinMode(clockPin_Card1, OUTPUT); pinMode(dataPin_Card1, OUTPUT); digitalWrite(latchPin_Card1, HIGH);
                     pinMode(latchPin_Card2, OUTPUT); pinMode(clockPin_Card2, OUTPUT); pinMode(dataPin_Card2, OUTPUT); digitalWrite(latchPin_Card2, HIGH);
                     pinMode(latchPin_Card3, OUTPUT); pinMode(clockPin_Card3, OUTPUT); pinMode(dataPin_Card3, OUTPUT); digitalWrite(latchPin_Card3, HIGH);}

void serialEvent(){while (Serial.available()) {inputString = Serial.readString(); //Serial.println(inputString);
                                               {bin = getValue(inputString,'l',0);
                                                
                                                //Serial.println(bin);
                                                amount = getValue(inputString,'l',1);
                                                polar = getValue(inputString,'l',2);

                                                if (Prior_bin == bin){}
                                                else {newDataKeybd = true;
                                                num = bin.toInt();
                                                amt = amount.toInt();
                                                plr = polar.toInt();
                                                Serial.print(num);
                                                Serial.print("l");
                                                Serial.print(amount);
                                                Serial.print("l");
                                                Serial.println(polar);}

                                                
                                                
                                                Prior_bin = bin;
                                               }
                                              }  
}

void loop() {
  if (newDataKeybd) {offLED(); serialEventto595();
   if (num == 0){offLED();}
   if (num >= 1 && num <= 80) {ShiftLED_Card1();}
   if (num >= 81 && num <= 160) {ShiftLED_Card2();}
   if (num >= 161 && num <= 200) {ShiftLED_Card3();}
   inputString = ""; newDataKeybd = false;
}
}
