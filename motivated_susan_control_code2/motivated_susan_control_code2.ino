// Define pin connections & motor's steps per revolution
// do not modify this section unless you need to re-wire for some reason, then ensure pins are correctly
// matched with outputs as listed.

const int buttonPin = 2;  // the number of the pushbutton pin
const int dirPin = 10;
const int stepPin = 9;
const int ledPin = 7;
const int stepsPerRevolution = 400;
boolean isRunning = true;
int buttonState = 0;  // variable for reading the pushbutton status

void setup()
{
  // Declare pins as Outputs

  boolean isRunning = true; // variable for iterating loop during operation pause
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


    // this for loop is the delay before the first drop
    for(int j = 0; j <1200; j++)
        {
          buttonState = digitalRead(buttonPin);
          Serial.print(buttonState);
          Serial.print(" On:waiting for drop number ");
          Serial.print(1);
          Serial.print(":");
          Serial.println(j);

          if (buttonState == 1)
          {
            isRunning = false;
          }
        }


    // this for loop is the rotations for the proceeding 3 drops
    for(int w = 2; w <5; w++)
    {
      digitalWrite(ledPin, HIGH);
      for(int i = 0; i < 50; i++)
      {
        // each step is achieved by sending a voltage pulse to the motor, i.e. a high signal and then a low signal.
        // changing the delay between high and low determines the speed of rotation. Lower values will result in faster rotation.
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(5000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(5000);
        Serial.print("i: ");
        Serial.println(i);
      }
      // introduces a pause between movements. The "time" of pause is controlled by the j counter, with larger j resulting in a
      // longer pause. Unfortunately, this is the only way I could come up with to do this while still checking the status of
      // the button.
      // as best I can tell  second but will depend on the computer running the code.

        // this is the pause between drops 2,3,4
        for(int j = 0; j <816; j++)
        {
          buttonState = digitalRead(buttonPin);
          Serial.print(buttonState);
          Serial.print(" On:waiting for drop number ");
          Serial.print(w);
          Serial.print(":");
          Serial.println(j);

          if (buttonState == 1)
          {
            isRunning = false;
          }
        }
    } 
    for(int i = 1; i < 3; i++)
      {
        // this for loop is the delay for mixing 
        for(int j = 0; j <4000; j++)
          {
            buttonState = digitalRead(buttonPin);
            Serial.print(buttonState);
            Serial.print(" On:mixing:");
            Serial.println(j);

            if (buttonState == 1)
            {
              isRunning = false;
            }
          }
        digitalWrite(ledPin, HIGH);
      for(int i = 0; i < 50; i++)
      {
        // each step is achieved by sending a voltage pulse to the motor, i.e. a high signal and then a low signal.
        // changing the delay between high and low determines the speed of rotation. Lower values will result in faster rotation.
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(5000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(5000);
        Serial.print("i: ");
        Serial.println(i);
      }
        for(int w = 2; w <5; w++)
        {
          // this is the pause between drops 2,3,4 after each mix
          for(int j = 0; j <816; j++)
          {
            buttonState = digitalRead(buttonPin);
            Serial.print(buttonState);
            Serial.print(" On:waiting for drop number ");
            Serial.print(w);
            Serial.print(":");
            Serial.println(j);

            if (buttonState == 1)
            {
              isRunning = false;
            }
          }
        }
      } 
  }
   else if (isRunning == false)
   {
      digitalWrite(ledPin, LOW);
      for(int k = 0; k <100; k++)
      {
        buttonState = digitalRead(buttonPin);
        Serial.print(buttonState);
        Serial.print("k: ");
        Serial.println(k);
        if (buttonState == 1)
        {
          isRunning = true;
        }
      }
    }
}
