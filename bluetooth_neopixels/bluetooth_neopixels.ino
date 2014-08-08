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


void setup() {
  // bluetooth init
  Serial.begin(9600);
  while(!Serial); // Leonardo/Micro should wait for serial init
  Serial.println(F("Adafruit Bluefruit Low Energy nRF8001 Print echo demo"));

  
  // Neopixels init
  strip.begin();
  
  strip.setBrightness(80);
  
  for(int y = 0; y < numPixels; y++) {
    strip.setPixelColor(y, ironManDarkBlue);
  }
   
  strip.show(); // Initialize all pixels to 'off'
  
  
  
  BTLEserial.begin();
  
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
      

      
      if (c == '1') {
         one(); 
      }
      
      if (c == '2') {
        two();
      }
      
      if (c == '3') {
        three();
      }
     
    }
  }  
  
}

void one() {
  Serial.println("Test 1");
}

void two() {
  Serial.println("Test 2");
}

void three() {
  Serial.println("Test 3");
}
