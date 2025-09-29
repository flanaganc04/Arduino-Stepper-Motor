// Define pin connections & motor's steps per revolution
// do not modify this section unless you need to re-wire for some reason, then ensure pins are correctly
// matched with outputs as listed.

const int buttonPin = 2;  // the number of the pushbutton pin
const int dirPin = 10;
const int stepPin = 9;
const int ledPin = 7;
const int stepsPerRevolution = 400;
bool isRunning = true;
int buttonState = 0;  // variable for reading the pushbutton status

void turnMotor(int i, int delay) {
  for(i; i < 15; i++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(delay);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(5000);
      Serial.print("i: ");
      Serial.println(i);
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

void loop()
{
  digitalWrite(dirPin, LOW);
  if (isRunning == true)
  {
    digitalWrite(ledPin, HIGH);

    // delay for opentrons and first drop
    for(int j = 0; j <900; j++)
    {
      buttonState = digitalRead(buttonPin);
      Serial.print("Button: ");
        Serial.print(buttonState);
        Serial.print(": j: ");
        Serial.print(j);
        Serial.print(": Waiting for drop number ");
        Serial.println(1);

      if (buttonState == 1)
      {
        isRunning = false;
      }
    }

    // first roation
    for(int i = 0; i < 15; i++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(5000000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(5000);
      Serial.print("i: ");
      Serial.println(i);
    }

    // for loop to iterate over number of drops before mixing
    for(int w = 2; w <5; w++)
    {
      // delay between drops
      for(int j = 0; j <700; j++)
      {
        buttonState = digitalRead(buttonPin);
        Serial.print("Button: ");
        Serial.print(buttonState);
        Serial.print(": j: ");
        Serial.print(j);
        Serial.print(": Waiting for drop number ");
        Serial.println(w);

        if (buttonState == 1)
        {
          isRunning = false;
        }
      }

      // rotation for 2,3,4
      for(int i = 0; i < 15; i++)
      {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(5000000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(5000);
        Serial.print("Rotating: ");
        Serial.println(i);
      }

    }

    // loop to iterate over two mixes
    for(int w = 1; w < 3;w++)
    {
      // waiting for mixing
      for(int j = 0; j <2685; j++)
      {
        buttonState = digitalRead(buttonPin);
        Serial.print("Button: ");
        Serial.print(buttonState);
        Serial.print(": j: ");
        Serial.print(j);
        Serial.print(":Mixing");
        Serial.print(w);
        Serial.println(" Waiting for next drop");
        

        if (buttonState == 1)
        {
         isRunning = false;
        }
      }
      // iterate over the 3 drops after the mix
      for (int m = 2; m < 5; m++)
      {
        // rotate b/w 6,7,8,10,11,12
        for(int i = 0; i < 15; i++)
        {
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(5000000);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(5000);
          Serial.print("Rotating: ");
          Serial.println(i);
          buttonState = digitalRead(buttonPin);
        }

        // delay b/w 6,7,8,10,11,12
        for(int j = 0; j < 700; j++)
        {
          buttonState = digitalRead(buttonPin);
          Serial.print("Button: ");
          Serial.print(buttonState);
          Serial.print(": j: ");
          Serial.print(j);
          Serial.println(":Mixed: Waiting for next drop ");
          if (buttonState == 1)
          {
            isRunning = false;
          }
        }


      }
      

    }

  }
  else if(isRunning == false);
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
