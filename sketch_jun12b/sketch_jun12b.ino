#include <Stepper.h>

const int stepsPerRevolution = 400;
const int buttonPin = 2;
const int ledPin = 7;
bool running = false;

// the step angle is 0.9 degrees so that comes to 400 steps in one revolution, for some reason the actual number of steps is 3200
Stepper StepperOnline(stepsPerRevolution, 9, 10);

void turn() {
  StepperOnline.step(123);
}

void setup() {
  StepperOnline.setSpeed(50);
  Serial.begin(9600);
}

void loop() {
  
  // delay for opentron start up
  delay(42000);
  turn();

  // dropcast samples 2,3,4
  for(int i = 0; i < 3; i++){
    delay(30000);
    turn();
  }
  
  // first mix and dropcast sample 5
  delay(160000);
  turn();

  // dropcast 6, 7, 8
  for(int i = 0; i < 3; i++){
    delay(30000);
    turn();
  }

  // second mix and dropcast sample 9
  delay(180000);
  turn();

  // dropcast 10, 11, 12
  for(int i = 0; i < 3; i++){
    delay(30000);
    turn();
  }

  // dropcast samples 13,14,15,16
  for(int i = 0; i < 4; i++){
    delay(30000);
    turn();
  }

  // third mix and dropcast sample 17
  delay(160000);
  turn();

  // dropcast 18, 19, 20
  for(int i = 0; i < 3; i++){
    delay(30000);
    turn();
  }

  // fourth mix and dropcast sample 21
  delay(180000);
  turn();

  // dropcast 22, 23, 24
  for(int i = 0; i < 3; i++){
    delay(30000);
    turn();
  }
  
  
}
