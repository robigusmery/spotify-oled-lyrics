/**
 * Spotify Real-time Lyrics Streamer - Embedded Firmware
 * Author: Robi Gusmery
 * License: Mozilla Public License 2.0 (MPL 2.0)
 * Description: Implements a serial input buffer parser over a 115200 baud link
 *              to orchestrate data visualization on a 16x2 I2C Character LCD.
 */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Initialize LCD driver subsystem mapping to slave address 0x27 
// Configured for a physical matrix dimension profile of 16 columns by 2 rows.
LiquidCrystal_I2C lcd(0x27, 16, 2);  

void setup() {
  // Open hardware serial communication bus channel at high velocity baud rate
  Serial.begin(115200);
  
  // Power up display hardware logic controller
  lcd.init();          
  lcd.backlight();     // Activate physical LED background array illumination
  
  // Render initial bootstrap verification message
  lcd.setCursor(0, 0);
  lcd.print("Hardware Ready!");
  lcd.setCursor(0, 1);
  lcd.print("Awaiting Python..");
}

void loop() {
  // Evaluates if structural string byte packets are pending in the Serial Ring Buffer
  if (Serial.available() > 0) {
    // Read stream up until the designated Unix line termination token '\n'
    String incoming_lyric_line = Serial.readStringUntil('\n');
    incoming_lyric_line.trim(); // Wipe potential trailing carriage return artifacts
    
    // Refresh visual memory layer
    lcd.clear();
    lcd.setCursor(0, 0);
    
    // Dynamic Text-Wrapping Layout Subsystem Engine
    // Determines if data array size spills past the physical 16-character row margin
    if (incoming_lyric_line.length() > 16) {
      // Isolate and project first 16 character elements to the top line matrix
      lcd.print(incoming_lyric_line.substring(0, 16));
      
      // Shift structural cursor target index to the lower line index
      lcd.setCursor(0, 1);
      
      // Capture remainder buffer and render down onto the second matrix row
      lcd.print(incoming_lyric_line.substring(16, 32));
    } 
    else {
      // Data payload falls within hardware limits; render natively inside row 1
      lcd.print(incoming_lyric_line);
    }
  }
}
