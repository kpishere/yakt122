
#include "usb_hid_112.hpp"
#include "keyboard_terminal_122.hpp"
#include "Keyboard.h"

//#define DEBUG  
  
// For ProMicro - Atmega32U4
const int numbits = 11; // Bits in each PS2 Keyboard event
const int clockPin = 3;
const int dataPin = 2; 
const int debugPin = 4; 

//
// Incoming PS/2 signals
//
static bool incoming_ready = false;
static unsigned char bitcount = 0;
static unsigned char incoming = 0;
void clkRising() {
  #define MAX_PS2MSG_TIME_MICROSEC 900 /* 900e-6 seconds */
  static unsigned long startBitCount = 0;
  static unsigned long currentBitCount = 0;
  unsigned char val, n;

  val = digitalRead(dataPin);
  currentBitCount = millis();
  n = bitcount - 1;
  if( val == 0x00 && bitcount == 0 ) { // Start bit
    digitalWrite(debugPin, 1);
    startBitCount = millis();
    incoming = 0x00;
    bitcount++;
  } else if( n <= 7 ) {
    incoming |= (val << n );
    bitcount++;
  } else if( n == 8 ) { // Parity bit
    bitcount++;
  } else if( n >= 9 /* Stop bit */
    ||(currentBitCount > startBitCount /* Msg Timeout */
        && (currentBitCount - startBitCount) > MAX_PS2MSG_TIME_MICROSEC
      )
  ) {
    digitalWrite(debugPin, 0);
    incoming_ready = true;
    bitcount = 0x00;
  }
}

//
// Outgoing USB packets
//
void sendUSBKey(usbKey key) {
  KeyReport report = {(uint8_t)key.mod,0,(uint8_t)key.key};
#ifdef DEBUG
  Serial.print(" usb "); Serial.print(report.keys[0], HEX);    
  Serial.print(" mod "); Serial.println(report.modifiers, HEX);    
#endif
  Keyboard.sendReport(&report);
}
void procTaskPS2KeyUp()
{
  KeyReport report = {(uint8_t)usbModFromPS2State(ps2kbState),0,(uint8_t)Reserved0};
#ifdef DEBUG
  Serial.print(" usb "); Serial.print(report.keys[0], HEX);    
  Serial.print(" mod "); Serial.println(report.modifiers, HEX);    
#endif
  Keyboard.sendReport(&report); 
}

//
// Configuration
//
void setup_ps2(){
  attachInterrupt( digitalPinToInterrupt(clockPin) , clkRising, RISING);
  pinMode(clockPin, INPUT_PULLUP);
  pinMode(dataPin, INPUT_PULLUP);
  ps2kbState = (int)ps2none;
}

void setup() {
  while (! Serial);
#ifdef DEBUG
  Serial.begin(115200);
#endif
  delay(500);
  Keyboard.begin();

  setup_ps2();
  
#ifdef DEBUG
  Serial.println("started");
#endif
}

//
// Main event loop
//
void loop() {
  // put your main code here, to run repeatedly:
  if(incoming_ready) {
    unsigned char valc = (unsigned char)incoming;
    
#ifdef DEBUG
    Serial.print("ps2 "); Serial.println(incoming, HEX);    
#endif

    if(nextKeyIsOut) {
      outKeyState(valc);
    } else {
      keyHandler keyFound = keyHandler_map_find(valc);
      if(keyFound != NULL) {
        keyFound( ((ps2key){valc, ps2kbState}) );
        procTaskPS2KeyUp();
      }
    }
        
    incoming_ready = false;
  }
}
