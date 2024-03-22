#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h> 
#define NUM_LEDS 24
#define DATA_PIN 2
#define SCORE_PIN 6
#define SCORE_LEDS 4

Adafruit_NeoPixel leds(NUM_LEDS, DATA_PIN, NEO_GRB);
Adafruit_NeoPixel sleds(SCORE_LEDS, SCORE_PIN, NEO_GRB);
LiquidCrystal_I2C lcd(0x27, 16, 2); 
bool reachedEnd = false;
byte gameState = 0;
//byte ledSpeed = 0;
int period = 1000;
unsigned long time_now = 0;
byte Position = 0;
byte level = 0;

const byte ledSpeed[4] = {60, 60, 60, 60}; //led speed

//Debounce
bool findRandom = false;
byte spot = 0;

void setup()
{
    // put your setup code here, to run once:
    leds.begin();
    sleds.begin();
    pinMode(4, INPUT_PULLUP);
    Serial.begin(9600);
    Serial.println("Reset");
}

void loop()
{
    if (gameState == 0)
    {
        // Your initialization code
        for (int i = 0; i < NUM_LEDS; i++)
        {//fill rainbow
            leds.setPixelColor(i, leds.ColorHSV(map(i, 0, NUM_LEDS, 0, 65535), 255, 255)); // Fill rainbow colors
        }
        leds.show();

        for (int i = 0; i < SCORE_LEDS; i++)
        {
            sleds.setPixelColor(i, sleds.ColorHSV(map(i, 0, SCORE_LEDS, 0, 65535), 255, 255)); // Fill rainbow colors
        }
        sleds.show();

        if (digitalRead(4) == LOW)
        {
            Position = 0;
            findRandom = true;
            delay(500);
            for (byte i = 0; i < NUM_LEDS; i++)
            {
                leds.setPixelColor(i, 0); // Turn off all LEDs
            }
            leds.show();
            for (byte i = 0; i < SCORE_LEDS; i++)
            {
                sleds.setPixelColor(i, 0); // Turn off all LEDs
            }
            sleds.show();
            gameState = 1;
        }            //leds.show();

    }

    if (gameState == 1)
    {
        period = ledSpeed[0];
        if (millis() > time_now + period)
        {
            time_now = millis();
            if (findRandom)
            {
                spot = random(5) + 6;
                findRandom = false;
            }
            leds.setPixelColor(spot - 1, leds.Color(255, 140, 0));
            leds.setPixelColor(spot, leds.Color(0, 255, 0));
            leds.setPixelColor(spot + 1, leds.Color(255, 110, 0));
            sleds.setPixelColor(0, sleds.Color(0, 255, 0));
            PlayGame(spot - 1, spot + 1); // You need to define PlayGame function
            leds.show();
            sleds.show();
        }

        if (digitalRead(4) == LOW)
        {
            delay(300);
            findRandom = false;
            if (Position > spot - 1 && Position < spot + 3)
            {      
                blinkLED(0, 255, 0); // Green color
                level = gameState;
                gameState ++;
            }
            else
            {
              //Wrong button press, blink LED red
                blinkLED(255, 0, 0); // Red color
                gameState = 0;
            }
        }
    }
  if (gameState == 2) {
    period = ledSpeed[1];
    if (millis() > time_now + period) {
        time_now = millis();
        if (findRandom) {
            spot = random(6) + 6;
            findRandom = false;
        }
        leds.setPixelColor(spot - 1, leds.Color(255, 190, 0));
        leds.setPixelColor(spot, leds.Color(0, 255, 0));
        leds.setPixelColor(spot + 1, leds.Color(255, 190, 0));
        sleds.setPixelColor(1, sleds.Color(128, 255, 0));
        PlayGame(spot - 1, spot + 1);
        leds.show();
        sleds.show();
    }
    if (digitalRead(4) == LOW) {
        delay(300);
        if (Position > spot - 1 && Position < spot + 3) {
          blinkLED(0, 255, 0);
            level = gameState;
            gameState  ++;
        } else {blinkLED(255, 0, 0);
            gameState =0;
        }
    }
}
// add every state from here=>
  if (gameState == 3) {
    period = ledSpeed[2];
    if (millis() > time_now + period) {
        time_now = millis();
        if (findRandom) {
            spot = random(2) + 12;
            findRandom = false;
        }
        // leds[spot-1].setRGB(255, 190, 0);
        leds.setPixelColor(spot, leds.Color(0, 255, 0));
        leds.setPixelColor(spot + 1, leds.Color(1, 255, 0));
        sleds.setPixelColor(2, sleds.Color(0, 0, 255));
        PlayGame(spot, spot + 1);
        leds.show();
        sleds.show();
    }
    if (digitalRead(4) == LOW) {
        delay(300);
        if (Position > spot && Position < spot + 3) {
          blinkLED(0, 255, 0); // Green colo
            level = gameState;
            gameState ++;
        } else {//Wrong button press, blink LED red
                blinkLED(255, 0, 0); // Red color
            gameState = 0;
        }
    }
}
if (gameState == 4) {
    period = ledSpeed[3];
    if (millis() > time_now + period) {
        time_now = millis();
        if (findRandom) {
            spot = random(5) + 5;
            findRandom = false;
        }
        leds.setPixelColor(spot, leds.Color(0, 255, 0));
        sleds.setPixelColor(3, sleds.Color(255, 146, 3));
        PlayGame(spot, spot);
        leds.show();
        sleds.show();
    }
    if (digitalRead(4) == LOW) {
        delay(300);
        if (Position == spot + 1) {
          blinkLED(0, 255, 0);
            level = gameState;
            gameState ++; winner();
        } else {blinkLED(255, 0, 0);
            gameState = 1;loser();
        }
    }
}

}


//// blink led

void blinkLED(byte r, byte g, byte b) {
    for (int i = 0; i < 3; i++) {
        // Set all LEDs to the specified color
        for (byte j = 0; j < NUM_LEDS; j++) {
            leds.setPixelColor(j, leds.Color(r, g, b));
        }
        leds.show(); // Update the LED strip
        delay(500); // Wait for 500 milliseconds
        
        // Clear all LEDs
        clearLEDS();
        leds.show(); // Update the LED strip to turn off all LEDs
        delay(500); // Wait for 500 milliseconds
    }
}

///////////////////////////////////////
void PlayGame(byte bound1, byte bound2) {
  leds.setPixelColor(Position, leds.Color(255, 0, 0)); // Set current LED to red

  // Turn off the previous LED if it's outside the bounds
  if (Position > 0 && (Position - 1 < bound1 || Position - 1 > bound2)) {
    leds.setPixelColor(Position - 1, leds.Color(0, 0, 0));
  }

  leds.show(); // Update the LED strip
  Position++; // Move to the next position

  if (Position >= NUM_LEDS) { // If the position exceeds the number of LEDs
    leds.setPixelColor(Position - 1, leds.Color(0, 0, 0)); // Turn off the last LED
    Position = 0; // Reset position to start
  }
}

////////////////////////////
void winner() {
  for (byte i = 0; i < 3; i++) {
    // Set all LEDs to green
    for (byte j = 0; j < NUM_LEDS; j++) {
      leds.setPixelColor(j, leds.Color(0, 255, 0));
    }
    leds.show(); // Update the LED strip
    delay(500); // Wait for 500 milliseconds
    
    // Clear all LEDs
    clearLEDS();
    leds.show(); // Update the LED strip to turn off all LEDs
    delay(500); // Wait for 500 milliseconds
  }
  
  // Reset game state and position
  findRandom = true;
  Position = 0;

  // Move to the next game state
  gameState = level + 1;
  if (gameState > 6) {
    gameState = 0;
  }
}
////////////////////
void loser() {
  for (byte i = 0; i < 3; i++) {
    // Set all LEDs to red
    for (byte j = 0; j < NUM_LEDS; j++) {
      leds.setPixelColor(j, leds.Color(255, 0, 0));
    }
    leds.show(); // Update the LED strip
    delay(500); // Wait for 500 milliseconds
    
    // Clear all LEDs
    clearLEDS();
    leds.show(); // Update the LED strip to turn off all LEDs
    delay(500); // Wait for 500 milliseconds
  }
  
  // Reset game state to 0
  gameState = 0;
}
//////////
void clearLEDS() {
  for (byte i = 0; i < NUM_LEDS; i++) {
    leds.setPixelColor(i, 0); // Set the color of each LED to off (black)
  }
  leds.show(); // Update the LED strip
}

///////////////////////
void displayData()
{
    // Example: Display additional data on LCD
    lcd.clear(); // Clear the LCD display
    lcd.setCursor(0, 0); // Set cursor to first column, first row
    lcd.print("Data goes here"); // Print data on LCD
}











