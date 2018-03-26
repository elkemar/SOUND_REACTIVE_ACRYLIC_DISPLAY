#define MIC_IN A0                   // This renames pin A0 to MIC_IN
#define RED 3                       // This renames pin 3 to RED
#define BLUE 5
#define GREEN 6
#define BUTTON 2

#define TOTAL_STATES 8              // I use this to keep track of the total number of modes/states
#define RED_SOLID 0                 // This assigns mode RED to number 0
#define GREEN_SOLID 1
#define BLUE_SOLID 2
#define YELLOW_SOLID 3
#define PURPLE_SOLID 4
#define CYAN_SOLID 5
#define WHITE_SOLID 6
#define RANDOM 7

int r,g,b;                          // I declare variable r, g, and b to be of type integer

int currentState = 7;               // This variable will keep track of which mode/state the program is currently in

void setup() {
  pinMode(MIC_IN, INPUT);           // Typical pinMode setup when using arduino
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);

  pinMode(BUTTON, INPUT_PULLUP);

  r=0;                              // This is not neccessary but I like to make sure that all variables are set to zero
  g=0;
  b=0;
  
  setLed(r,g,b);                    // This calls the function setLed with argument r, g, and b passed in (0,0,0) in this case
}

void loop() {
  if(digitalRead(BUTTON)==LOW) {    // This constantly check when the button is pressed, which will complete the circuit from pin 2 (defined above) to ground (==LOW)
    currentState++;                 // Jump to next state when button is pressed
    updateLeds();                   // Update the LEDs to the color of the new mode
    if(currentState>=TOTAL_STATES||currentState<0) {     // The next 2 lines of code makes sure that currentState cannot go out of bound and stays within 0 and the total
      currentState = 0;                                  // number of modes defined above
    }
    delay(400);                     // This is a quick and dirty way to debounce the button, preventing the fast program from jumping multiple mode with one button-press
  }
  
  if(analogRead(MIC_IN)>1000) {     // If the signal from the sound module is greater than 1000, blink the light. I picked the value 1000 here based on my testing. You should pick your own
    setLed(255,255,255);            // Turn the LEDs off. Because the LEDs are common anode, a value of 255 which translates to 5V will turn them off
    delay(32);                      // Stay off for 32 microseconds. This is also tweaked to my own liking
    updateLeds();                   // Turn the LEDs back on through the updateLEDs function
  }
  setLed(r,g,b);                    // If the signal from the sound module is not high enough, keep the LEDs in their current state with their current rgb color values
  delay(32);                        // This delay prevents the code from constantly updating, making the LEDs flashes too fash for eye comfort
}

void updateLeds() {
  switch(currentState) {            // This switch set the rgb color of the display depending on the mode/state the program is in (from the variable currentState)
      case RANDOM:                  // Random mode will generates a random number from 0 to 255 for each r, g, and b
        r=random(256);
        g=random(256);
        b=random(256);
        break;
      case RED_SOLID:               // Red will keep the red LEDs on at all time
        r=0;
        g=255;
        b=255;
        break;
      case BLUE_SOLID:
        r=255;
        g=255;
        b=0;
        break;
      case GREEN_SOLID:
        r=255;
        g=0;
        b=255;
        break;
      case YELLOW_SOLID:
        r=0;
        g=0;
        b=255;
        break;
      case PURPLE_SOLID:
        r=0;
        g=255;
        b=0;
        break;
      case CYAN_SOLID:
        r=255;
        g=0;
        b=0;
        break;
      case WHITE_SOLID:
        r=0;
        g=0;
        b=0;
        break;
      default:                      // by default, the rgb values will be random as well. This code will not be reached for a normal operation, but it serves as a safe backup to prevent an error
        r=random(256);
        g=random(256);
        b=random(256);
    }
}

void setLed(int r, int g, int b) {  // this function generates 3 PWM (Pulse Width Modulation) signals to pins RED, GREEN, and BLUE respectively with values from r, g, and b
  analogWrite(RED, r);
  analogWrite(GREEN, g);
  analogWrite(BLUE, b);
}
