#include <SPI.h>
#include "Adafruit_BLE_UART.h"
#include <Adafruit_NeoPixel.h>

// bluetooth constants

// Connect CLK/MISO/MOSI to hardware SPI
// e.g. On UNO & compatible: CLK = 13, MISO = 12, MOSI = 11
#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2     // This should be an interrupt pin, on Uno thats #2 or #3
#define ADAFRUITBLE_RST 9
Adafruit_BLE_UART BTLEserial = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);

// Neopixels constants
#define PIN 5
int numPixels = 24;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPixels, PIN, NEO_GRB + NEO_KHZ800);
uint32_t ironManLightBlue = strip.Color(70,199,241);
uint32_t ironManDarkBlue = strip.Color(1,38,66);
uint32_t ironManMedBlue = strip.Color(0,112,155);
uint32_t white = strip.Color(255,255,255);
uint32_t off = strip.Color(0,0,0);
uint32_t colred = strip.Color(255,0,0);
uint32_t colgreen = strip.Color(0,255,0);
uint32_t colblue = strip.Color(0,0,255);


void setup() {
  // bluetooth init
  Serial.begin(9600);
  while(!Serial); // Leonardo/Micro should wait for serial init

  BTLEserial.begin();
  
  // Neopixels init
  strip.begin();
  
  strip.setBrightness(80);
  
  strip.show(); // Initialize all pixels to 'off'
  
  
  
}

/**************************************************************************/
/*!
    Constantly checks for new events on the nRF8001
*/
/**************************************************************************/
aci_evt_opcode_t laststatus = ACI_EVT_DISCONNECTED;

void loop() {
  
   // Tell the nRF8001 to do whatever it should be working on.
   BTLEserial.pollACI();
   
   // Ask what is our current status
  aci_evt_opcode_t status = BTLEserial.getState();
  // If the status changed....
  if (status != laststatus) {
    // print it out!
     if (status == ACI_EVT_DEVICE_STARTED) {
        Serial.println(F("* Bluetooth is on and ready"));
    }
    
    if (status == ACI_EVT_CONNECTED) {
        Serial.println(F("* iPhone connected!"));
    }
    
    if (status == ACI_EVT_DISCONNECTED) {
        Serial.println(F("* Connection lost"));
    }
    
    // OK set the last status change to this one
    laststatus = status;
  }
  
  if (status == ACI_EVT_CONNECTED) {
    // Lets see if there's any data for us!
     while (BTLEserial.available()) {
      char c = BTLEserial.read();
      Serial.print(c);
      String mystring = String(c);
      Serial.println(mystring);
      
      if (mystring == "1") {
         blue(); 
      }
      
      if (mystring == "2") {
        green();
      }
      
      if (mystring == "3") {
        red();
      }
      
      
     
    }
  }  
  
}

void blue() {
  Serial.println("Blue");
  for(int s = 0; s < numPixels; s++) {
    strip.setPixelColor(s, colblue);
     strip.show();
  }
   
}

void green() {
  Serial.println("Green");
  for(int t = 0; t < numPixels; t++) {
    strip.setPixelColor(t, colgreen);
     strip.show();
  }
   
}

void red() {
  Serial.println("Red");
  for(int u = 0; u < numPixels; u++) {
    strip.setPixelColor(u, colred);
     strip.show();
  }
   
}
