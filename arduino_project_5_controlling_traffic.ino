// Project 5 controlling traffic by Julian Bong

#define westButton 3  // Defines the slot used for the pins
#define eastButton 10
#define eastPedestrianButton 5
#define westPedestrianButton 4
#define eastPedestrian 7
#define westPedestrian 6
#define westRed 0
#define westYellow 1
#define westGreen 2
#define eastRed 11
#define eastYellow 12
#define eastGreen 13
#define yellowBlinkTime 500  // Value set for the delay
#define eastAmbulance 8
#define westAmbulance 9

boolean trafficWest = true;  // west = true, east = false, sets true false statement
int flowTime = 10000;
int changeDelay = 2000;

void setup() {
  pinMode(westButton, INPUT);  // Defines pins as input or output
  pinMode(eastButton, INPUT);
  pinMode(eastPedestrianButton, INPUT);
  pinMode(westPedestrianButton, INPUT);
  pinMode(westRed, OUTPUT);
  pinMode(westYellow, OUTPUT);
  pinMode(westGreen, OUTPUT);
  pinMode(westPedestrian, OUTPUT);
  pinMode(eastRed, OUTPUT);
  pinMode(eastYellow, OUTPUT);
  pinMode(eastGreen, OUTPUT);
  pinMode(eastPedestrian, OUTPUT);
  pinMode(westAmbulance, INPUT);
  pinMode(eastAmbulance, INPUT);

  digitalWrite(westRed, LOW);  // Sets LED's either on or off. West= low. East = high
  digitalWrite(westYellow, LOW);
  digitalWrite(westGreen, HIGH);
  digitalWrite(eastPedestrian, LOW);
  digitalWrite(eastRed, HIGH);
  digitalWrite(eastYellow, LOW);
  digitalWrite(eastGreen, LOW);
  digitalWrite(westPedestrian, LOW);
}

void loop() {
  if (digitalRead(westButton) == HIGH)  // Turns east traffic off going from green to yellow to red
  {
    if (trafficWest != true)  // Sets the flowing side of traffic to turn red
    {
      trafficWest = true;
      delay(flowTime);

      if (digitalRead(westPedestrian) == LOW) { // Turns green light to red if pedestrian lights are not active
        changeGreenToRed(eastGreen, eastYellow, eastRed);
      }
      changeYellow(westYellow, westPedestrian, eastPedestrian);

      allowTrafficFlow(westYellow, westRed, westGreen);
    }
  }

  allowPedestrianToCross(eastPedestrianButton, westPedestrianButton, westPedestrian, eastPedestrian);
  
  allowAmbulanceToDrive(eastAmbulance, eastYellow, eastGreen, eastRed, eastPedestrian, westPedestrian, westYellow, westGreen, westRed, westAmbulance);

  if (digitalRead(eastButton) == HIGH)  // Turns west traffic off going from green to yellow to red
  {
    if (trafficWest == true)  // Sets the flowing side of traffic to turn red
    {
      trafficWest = false;
      delay(flowTime);

      if (digitalRead(westPedestrian) == LOW) {
        changeGreenToRed(westGreen, westYellow, westRed);
      }

      changeYellow(eastYellow, westPedestrian, eastPedestrian);

      allowTrafficFlow(eastYellow, eastRed, eastGreen);
    }
  }
}

// Blinks yellow and pedstrian lights
void changeYellow(int yellow, int WPedestrian, int EPedestrian) {
  if (digitalRead(westPedestrian) == HIGH) { // Pedestrian light is high
    for (int a = 0; a < 5; a++)  // Incramnets five time for a total of 5 sec.
    {
      digitalWrite(yellow, HIGH);
      digitalWrite(westPedestrian, HIGH);
      digitalWrite(eastPedestrian, HIGH);
      delay(yellowBlinkTime);
      digitalWrite(yellow, LOW);
      digitalWrite(westPedestrian, LOW);
      digitalWrite(eastPedestrian, LOW);
      delay(yellowBlinkTime);
    }
  }

  else { // Pedestrian light is low
    for (int a = 0; a < 5; a++)  // Incramnets five time for a total of 5 sec.
    {
      digitalWrite(yellow, HIGH);
      delay(yellowBlinkTime);
      digitalWrite(yellow, LOW);
      delay(yellowBlinkTime);
    }
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

// Allows pedestrians to cross
void allowPedestrianToCross(int EButton, int WButton, int WPedestrian, int EPedestrian) { // Turns green LEDs low, Red LEDs high, and Pedestrian LEDs high if a pedestrian button was pressed 
  if (digitalRead(EButton) == HIGH || digitalRead(WButton) == HIGH) {
    digitalWrite(eastGreen, LOW);
    digitalWrite(eastRed, HIGH);
    digitalWrite(westGreen, LOW);
    digitalWrite(westRed, HIGH);
    delay(2500);
    digitalWrite(WPedestrian, HIGH);
    digitalWrite(EPedestrian, HIGH);
  }
}

// Changes the direction of traffic to allow the ambulance to drive through the intersection
void allowAmbulanceToDrive (int EAmbulance, int Wyellow, int Egreen, int ERed, int EPedestrian, int WPedestrian, int Eyellow, int WGreen, int WRed, int WAmbulance) {
  if (digitalRead(eastAmbulance) == HIGH) { // Allows east traffic to flow 
     // Blinks yellow LED twice
    digitalWrite(westYellow, HIGH); 
    delay(500);
    digitalWrite(westYellow, LOW);
    delay(500);
    digitalWrite(westYellow, HIGH);
    delay(500);
    digitalWrite(westYellow, LOW); // Turns yellow LED low to end blinking
    digitalWrite(eastGreen, HIGH);
    digitalWrite(eastRed, LOW);
    digitalWrite(eastPedestrian, LOW); // Makes sure no pedestrians cross the intersection
    digitalWrite(westPedestrian, LOW);
    digitalWrite(westGreen, LOW);
    digitalWrite(westRed, HIGH);
  }

  if (digitalRead(westAmbulance) == HIGH) {  // Allows west traffic to flow 
    digitalWrite(eastYellow, HIGH);
    delay(500);
    digitalWrite(eastYellow, LOW);
    delay(500);
    digitalWrite(eastYellow, HIGH);
    delay(500);
    digitalWrite(eastYellow, LOW); 
    digitalWrite(eastGreen, LOW);
    digitalWrite(eastRed, HIGH);
    digitalWrite(eastPedestrian, LOW);
    digitalWrite(westPedestrian, LOW);
    digitalWrite(westGreen, HIGH);
    digitalWrite(westRed, LOW);
  }
}
