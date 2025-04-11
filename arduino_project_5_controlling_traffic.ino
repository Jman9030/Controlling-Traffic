// Project 5 controlling traffic by Julian Bong

#define westButton 3  // Defines the slot used for the pins
#define eastButton 10
#define westRed 0
#define westYellow 1
#define westGreen 2
#define eastRed 11
#define eastYellow 12
#define eastGreen 13
#define yellowBlinkTime 500  // Value set for the delay

boolean trafficWest = true;  // west = true, east = false, sets true false statement
int flowTime = 10000;
int changeDelay = 2000;



void setup() {
  pinMode(westButton, INPUT);  // Defines pins as input or output
  pinMode(eastButton, INPUT);
  pinMode(westRed, OUTPUT);
  pinMode(westYellow, OUTPUT);
  pinMode(westGreen, OUTPUT);
  pinMode(eastRed, OUTPUT);
  pinMode(eastYellow, OUTPUT);
  pinMode(eastGreen, OUTPUT);

  digitalWrite(westRed, LOW);  // Sets LED's either on or off. West= low. East = high
  digitalWrite(westYellow, LOW);
  digitalWrite(westGreen, HIGH);
  digitalWrite(eastRed, HIGH);
  digitalWrite(eastYellow, LOW);
  digitalWrite(eastGreen, LOW);
}

void loop() {
  if (digitalRead(westButton) == HIGH)  // Turns east traffic off going from green to yellow to red
  {
    if (trafficWest != true)  // Sets the flowing side of traffic to turn red
    {
      trafficWest = true;
      delay(flowTime);
      changeGreenToRed(eastGreen, eastYellow, eastRed);

      changeYellow(eastYellow);

      allowTrafficFlow(eastYellow, eastRed, eastGreen);
    }
  }

  if (digitalRead(eastButton) == HIGH)  // Turns west traffic off going from green to yellow to red
  {
    if (trafficWest == true)  // Sets the flowing side of traffic to turn red
    {
      trafficWest = false;
      delay(flowTime);
      changeGreenToRed(westGreen, westYellow, westRed);

      changeYellow(eastYellow);

      allowTrafficFlow(eastYellow, eastRed, eastGreen);
    }
  }
}

// Blinks yellow light
void changeYellow(int yellow) {
  for (int a = 0; a < 5; a++)  // Incramnets five time for a total of 5 sec.
  {
    digitalWrite(yellow, LOW);
    delay(yellowBlinkTime);
    digitalWrite(yellow, HIGH);
    delay(yellowBlinkTime);
  }
}

// Stops traffic from flowing
void changeGreenToRed(int green, int yellow, int red) {
  digitalWrite(green, LOW);
  digitalWrite(yellow, HIGH);
  delay(changeDelay);
  digitalWrite(yellow, LOW);
  digitalWrite(red, HIGH);
  delay(changeDelay);
}

// Allows trafic to flow
void allowTrafficFlow(int yellow, int red, int green) {
  digitalWrite(yellow, LOW);
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
}
