#include <usbhid.h>
#include <usbhub.h>
#include <hiduniversal.h>
#include <hidboot.h>
#include <SPI.h>
#define OutputLED 2
#include <SoftwareSerial.h>

int SameBin;
SoftwareSerial SoftSN1 (19, 18);  // Rx, Tx
SoftwareSerial SoftSN2 (17, 16);  // Rx, Tx
String Readbuf[100],PriorReadbuf[100];
int Rb,i;
class MyParser : public HIDReportParser {
  public:
    MyParser();
    void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
  protected:
    uint8_t KeyToAscii(bool upper, uint8_t mod, uint8_t key);
    virtual void OnKeyScanned(bool upper, uint8_t mod, uint8_t key);
    virtual void OnScanFinished();
};

MyParser::MyParser() {}

void MyParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
  // If error or empty, return
  if (buf[2] == 1 || buf[2] == 0) return;

  for (uint8_t i = 7; i >= 2; i--) {
    // If empty, skip
    if (buf[i] == 0) continue;

    // If enter signal emitted, scan finished
    if (buf[i] == UHS_HID_BOOT_KEY_ENTER) {
      OnScanFinished();
    }

    // If not, continue normally
    else {
      // If bit position not in 2, it's uppercase words
      OnKeyScanned(i > 2, buf, buf[i]);
    }

    return;
  }
}

uint8_t MyParser::KeyToAscii(bool upper, uint8_t mod, uint8_t key) {
  // Letters
  if (VALUE_WITHIN(key, 0x04, 0x1d)) {
    if (upper) return (key - 4 + 'A');
    else return (key - 4 + 'a');
  }

  // Numbers
  else if (VALUE_WITHIN(key, 0x1e, 0x27)) {
    return ((key == UHS_HID_BOOT_KEY_ZERO) ? '0' : key - 0x1e + '1');
  }

  return 0;
}

void MyParser::OnKeyScanned(bool upper, uint8_t mod, uint8_t key) {
  uint8_t ascii = KeyToAscii(upper, mod, key);
  //Serial.print((char)ascii);
  Readbuf[Rb] = (char)ascii;
  Rb=Rb+1;

}
void EndScaning_LED() {
  SameBin=0;
  for (i = 0; i < 3; i++) {  
    if (PriorReadbuf[i]==Readbuf[i]) { SameBin = SameBin+1;} 
    }

    if (SameBin==3) {}
    else { 
                  //for (i = 0; i < Rb; i++) {    
              //  SoftSN2.print(Readbuf[i]);
              //  }
              //SoftSN2.print('\n');

                  for (i = 0; i < Rb; i++) {
                  Serial.print(Readbuf[i]);
                  SoftSN2.print(Readbuf[i]);    
                  SoftSN1.print(Readbuf[i]);    
                  }
              Serial.print('\n');
              SoftSN2.print('\n'); 
              SoftSN1.print('\n');
    }
///  
  for (i = 0; i < 3; i++) {  
    PriorReadbuf[i]=Readbuf[i]; 
    }

  }
  
void MyParser::OnScanFinished() {EndScaning_LED();
  //Serial.println(" - Finished");
  Rb=0;
  
}

USB          Usb;
USBHub       Hub(&Usb);
HIDUniversal Hid(&Usb);
MyParser     Parser;
//
void setup() {Rb=0;
  pinMode(OutputLED,OUTPUT);
  EndScaning_LED();
  Serial.begin( 115200 );
  Serial.println("Start");
  SoftSN1.begin( 115200 );
  SoftSN1.println("Start");
  SoftSN2.begin( 115200 );
  SoftSN2.println("Start");
  
  if (Usb.Init() == -1) {
    Serial.println("OSC did not start.");
  }

  delay( 200 );

  Hid.SetReportParser(0, &Parser);
}

void loop() {
  Usb.Task();
}
