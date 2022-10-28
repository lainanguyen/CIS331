// C++ code
//

int distanceThreshold = 0;
int cm = 0;
int pushCondition = 0;
const unsigned int pushButton = 8;  


//This code section was taken from https://www.tinkercad.com/things/j0k4YgzXoDF
//I got this source from sources included in elearning
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

//This function sets up the ports and the connection of the button to the machine
void setup()
{
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(pushButton, INPUT_PULLUP);  
}

//This function runs the entire system
//Loop through 
void loop()
{
  //Ping time in cm
  cm = 0.01723 * readUltrasonicDistance(7, 6);
  
  //Alert the machine to condition of button
  //The condition of the button connects to the if statements for action
  pushCondition = digitalRead(pushButton);

 //If the distance of the person within the door is higher than the distance of sensor
 if (cm < distanceThreshold) {
  analogWrite(10,0);
  analogWrite(11,250);
  
 //This if statement activates when the button is pushed
 //Which indicates that there is a person within the distance threshold of the door
 while (pushButton == HIGH) {
  analogWrite(10,0);
  analogWrite(11,0);
  delay(300);
  analogWrite(10,250);
  analogWrite(11,0);
  delay(300);
  analogWrite(10,0);
  analogWrite(11,0);
  delay(300);   
break;
  analogWrite(10,0);
  analogWrite(11,255);
  delay(300);
  }
   
  }
  //This if statement activates when the button is pushed again, turning it off
  //Turns off the motor
  else if (cm > distanceThreshold)
  {
  analogWrite(10,250);
  analogWrite(11,0);
  analogWrite(10,0);
  analogWrite(11,0);
  }
}
