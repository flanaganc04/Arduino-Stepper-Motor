const int buttonPin = 2;
const int ledPin = 7;
int state = HIGH;
int read_button,read_led;
int previous = LOW;

unsigned long time = 0;
unsigned long debounce = 200;

const int dirPin = 10;
const int stepPin = 9;
const int stepsPerRevolution = 1000;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
}
