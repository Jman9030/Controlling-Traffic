// Project 5 controlling traffic by Julian Bong

#define westButton 3 // Defines the slot used for the pins
#define eastButton 13
#define westRed 2
#define westYellow 1
#define westGreen 0
#define eastRed 12
#define eastYellow 11
#define eastGreen 10
#define yellowBlinkTime 500 // Value set for the delay

boolean trafficWest = true; // west = true, east = false, sets true false statement
int flowTime = 10000; 
int changeDelay = 2000;



void setup()
{
  pinMode(westButton, INPUT); // Defines pins as input or output
  pinMode(eastButton, INPUT);
  pinMode(westRed, OUTPUT);
  pinMode(westYellow, OUTPUT);
  pinMode(westGreen, OUTPUT);
  pinMode(eastRed, OUTPUT);
  pinMode(eastYellow, OUTPUT);
  pinMode(eastGreen, OUTPUT);

  digitalWrite(westRed, LOW); // Sets LED's either on or off. West= low. East = high
  digitalWrite(westYellow, LOW);
  digitalWrite(westGreen, HIGH);
  digitalWrite(eastRed, HIGH);
  digitalWrite(eastYellow, LOW);
  digitalWrite(eastGreen, LOW);
}

void loop()
{
  if ( digitalRead(westButton) == HIGH) // Turns east traffic off going from green to yellow to red
  {
    if ( trafficWest != true) // Sets the flowing side of traffic to turn red
    {
      trafficWest = true;
      delay(flowTime);
      digitalWrite(eastGreen, LOW);

      digitalWrite(eastYellow, HIGH);
      delay(changeDelay);
      digitalWrite(eastYellow, LOW);
      digitalWrite(eastRed, HIGH);
      delay(changeDelay);
      
      for ( int a = 0; a < 5; a++) // Incraments five times for a total of 5 seconds. Blinks west yellow LED
      {
        digitalWrite(westYellow, LOW); 
        delay(yellowBlinkTime);
        digitalWrite(westYellow, HIGH);
        delay(yellowBlinkTime);
      }
      // Allows west traffic to flow
      digitalWrite(westYellow, LOW);
      digitalWrite(westRed, LOW);
      digitalWrite(westGreen, HIGH);
    }
  }

  if ( digitalRead(eastButton) == HIGH) // Turns west traffic off going from green to yellow to red
  {
    if ( trafficWest == true) // Sets the flowing side of traffic to turn red
    {
      trafficWest = false;
      delay(flowTime);
      digitalWrite(westGreen, LOW);
      digitalWrite(westYellow, HIGH);
      delay(changeDelay);
      digitalWrite(westYellow, LOW);
      digitalWrite(westRed, HIGH);
      delay(changeDelay);

      for ( int a = 0; a < 5; a++) // Incramnets five time for a total of 5 sec. Blinks east yellow LED
      {
        digitalWrite(eastYellow, LOW);
        delay(yellowBlinkTime);
        digitalWrite(eastYellow, HIGH);
        delay(yellowBlinkTime);
      }
      // Allows east trafic to flow
      digitalWrite(eastYellow, LOW);
      digitalWrite(eastRed, LOW);
      digitalWrite(eastGreen, HIGH);
    }
  }
}


