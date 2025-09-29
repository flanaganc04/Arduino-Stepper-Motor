#include <Stepper.h>

const int buttonPin = 2;
const int ledPin = 7;
const int stepsPerRevolution = 400;

bool running = false;

int buttonStatus = 0;
int ledStatus = 0;
int state = LOW;
int previous = LOW;

unsigned long time = 0;
unsigned long debounce = 200;

int mix [] = {66, 81, 81, 89, 108, 108, 89, 108, 108};

Stepper StepperOnline(stepsPerRevolution, 9, 10);

// function for checking the status of the button
void updateButton() {
  buttonStatus = digitalRead(buttonPin);
}

/* this function checks the status of the button and the toggles the LED on or off while also printing data to the serial monitor*/
void toggle() {
  updateButton();
  if (buttonStatus == HIGH && previous == LOW && millis() - time > debounce)
  {
    if (state == HIGH)
      state = LOW;
    else
      state = HIGH;

    time = millis();
  }

  digitalWrite(ledPin, state);
  ledStatus = digitalRead(ledPin);
  previous = buttonStatus;
  Serial.print("button: ");
  Serial.print(buttonStatus);
  Serial.print("led: ");
  Serial.println(ledStatus);
}

/* this function is nearly identical to toggle() except it returns "IDLE" in the serial monitor. This method is just for the off position of the motor*/
void toggleIdle() {
  updateButton();
  if (buttonStatus == HIGH && previous == LOW && millis() - time > debounce)
  {
    if (state == HIGH)
      state = LOW;
    else
      state = HIGH;

    time = millis();
  }
  digitalWrite(ledPin, state);
  ledStatus = digitalRead(ledPin);
  previous = buttonStatus;
  Serial.print("IDLE:");
  Serial.print("button: ");
  Serial.print(buttonStatus);
  Serial.print("led: ");
  Serial.println(ledStatus);
}

/* here is where you can adjust the distance susan rotates, it will also run an additional toggle() to check if you pressed the button during the rotation*/
void turn() {
  StepperOnline.step(123);
  toggle();
}

/*Takes int seconds as an argument. This method works by using a for loop and the prebuily delay method. The delay causes a pause for 250 milliseconds or the delay argument. Then the for loops interates 4 times the number of seconds so that the times is correct for the delay. The shorter the delay time the more times the loop is able to check the toggle method for turning the led on an off.*/
void wait(int seconds) {
  for(int i = 0; i < 4*seconds;i++){
    if(ledStatus == LOW) {
      break;
    }
    Serial.println((i + 1)*0.25);
    toggle();
    delay(250);
    
  }
}
/*Set speed of stepper motor, button pin allocation, led pin allocation, serial output at 9600 bits per second*/
void setup() {
  StepperOnline.setSpeed(50);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);



}

void loop()
{
  // running position
  if(ledStatus == HIGH) {
   
    for(int b = 0; b < 9; b ++) {
      wait(mix[b]);
      turn();
      for(int s = 0; s < 3; s++)
        wait(27);
        turn();
    }
   

  }
  // idle position
  else {
    toggleIdle();
  }
}

