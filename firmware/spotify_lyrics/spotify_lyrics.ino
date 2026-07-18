#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

String inputString = "";         
bool stringComplete = false;     

void setup() {
  Serial.begin(115200);          
  inputString.reserve(200);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    for(;;); // Halt execution if display hardware initialization fails
  }
  
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  display.clearDisplay();
  display.setCursor(10, 24);
  display.print("Awaiting Spotify...");
  display.display();
}

void loop() {
  if (stringComplete) {
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println(inputString);
    display.display();
    
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') { 
      stringComplete = true;
    } else {
      inputString += inChar;
    }
  }
}
