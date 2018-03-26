#define MIC_IN A0
#define RED 3
#define BLUE 5
#define GREEN 6
#define BUTTON 2

#define TOTAL_STATES 8
#define RED_SOLID 0
#define GREEN_SOLID 1
#define BLUE_SOLID 2
#define YELLOW_SOLID 3
#define PURPLE_SOLID 4
#define CYAN_SOLID 5
#define WHITE_SOLID 6
#define RANDOM 7

int r,g,b;

int currentState = 7;

void setup() {
  pinMode(MIC_IN, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);

  pinMode(BUTTON, INPUT_PULLUP);

  r=0;
  g=0;
  b=0;
  
  setLed(r,g,b);
}

void loop() {
  if(digitalRead(BUTTON)==LOW) {
    currentState++;
    updateLeds();
    if(currentState>=TOTAL_STATES||currentState<0) {
      currentState = 0;
    }
    delay(400);
  }
  
  if(analogRead(MIC_IN)>1000) {
    setLed(255,255,255);
    delay(32);
    updateLeds();
  }
  setLed(r,g,b);
  delay(32);
}

void updateLeds() {
  switch(currentState) {
      case RANDOM:
        r=random(256);
        g=random(256);
        b=random(256);
        break;
      case RED_SOLID:
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
      default:
        r=random(256);
        g=random(256);
        b=random(256);
    }
}

void setLed(int r, int g, int b) {
  analogWrite(RED, r);
  analogWrite(GREEN, g);
  analogWrite(BLUE, b);
}
