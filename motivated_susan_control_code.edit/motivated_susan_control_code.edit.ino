// Define pin connections & motor's steps per revolution
// do not modify this section unless you need to re-wire for some reason, then ensure pins are correctly
// matched with outputs as listed.

const int buttonPin = 2;  // the number of the pushbutton pin
const int dirPin = 10;
const int stepPin = 9;
const int ledPin = 7;
const int stepsPerRevolution = 1000;
bool isRunning = true;
int buttonState = 0;  // variable for reading the pushbutton status

void turnMotor() {
  for(int i = 0; i < 15; i++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(500000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(5000);
      Serial.print("i: ");
      Serial.println(i);
    }
}
// 700 is ~ 30 seconds 
void standBy(int time) {
  for(int j = 0; j < time; j++)
      {
        buttonState = digitalRead(buttonPin);
        Serial.print(buttonState);
        Serial.print(" On: waiting for next drop: ");
        Serial.println(j);
        

        if (buttonState == 1)
        {
          isRunning = false;
        }
      
      }
}


void setup()
{
  // Declare pins as Outputs

  bool isRunning = true; // variable for iterating loop during operation pause
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  
  Serial.begin(9600);
}

////////////////////////  this is an infinite loop and will run the motor program continuously   /////////////////////////
void loop()
{
  // Set motor direction: LOW for CCW, HIGH for CW
  digitalWrite(dirPin, LOW);

  if (isRunning == true)
  {
    digitalWrite(ledPin, HIGH);
    
    // initial delay for opentrons to ready itself
    standBy(140);

    // drops 2,3,4
    for(int i = 0; i < 3; i++)
    {
      turnMotor();
      standBy(70);
    }
    
    // mixing and dropping of the drops 5-12
    for(int n = 0; n < 2; n++)
    {
      turnMotor();
      //delay for mix
      standBy(210);

      for(int i = 0; i < 3; i++)
      {
      turnMotor();
      standBy(70);
      }
    }

    
    
    
  }
  else if(isRunning == false)
  {
     digitalWrite(ledPin, LOW);
      for(int k = 0; k <100; k++)
      {
        buttonState = digitalRead(buttonPin);
        Serial.print(buttonState);
        Serial.print(" Off: ");
        Serial.println(k);
        if (buttonState == 1)
        {
          isRunning = true;
        }
      }
  }
}
