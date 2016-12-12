//author: Alex Perez, Aug. 2016

// Our motor pins
int leftMotorPin = 3;
int rightMotorPin = 6;

// We've specified these values based on empirical testing
int sensorMax = 700;
int mapThresh = 10;
int threshold = mapThresh / 3;

// These are the outputs to the motors, range 0-255
int crawlSpeed = 100;
int accelSpeed = 150; 

// This value is set to "overshoot" a turn
// so that we don't hug walls.
// Make this smaller to overshoot more,
// but ***never set to 1!***
int overshootScaler = 5; 
int overshoot = mapThresh / overshootScaler;

void setup() {
  randomSeed(analogRead(0));
  pinMode(leftMotorPin, OUTPUT);
  pinMode(rightMotorPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A0);
  int sensorValueScaled = map(sensorValue, 0, sensorMax, 0, mapThresh);
  sensorValueScaled = constrain(sensorValueScaled, 0, mapThresh);

  // for debugging
  Serial.print(sensorValue);
  Serial.print("\t");
  Serial.println(sensorValueScaled);
  delay(100);

  if (sensorValueScaled > threshold) {
    // the moment we sense something is coming up, 
    // make a decision to turn left or right
    int directionDecision = random(2);
    
    while(sensorValueScaled + overshoot > threshold) {
      Serial.print("In the while loop \t");
      Serial.print(sensorValue);
      Serial.print("\t");
      Serial.print(sensorValueScaled);
      Serial.print("\t");
      Serial.println(directionDecision);
      delay(100);
      
      if (directionDecision == 1) { // we'll say 1 is to turn right
        Right(accelSpeed);  
        Left(0);
      }
      else {
        Left(accelSpeed);
        Right(0);
      }
      sensorValue = analogRead(A0);
      sensorValueScaled = map(sensorValue, 0, sensorMax, 0, mapThresh);
      sensorValueScaled = constrain(sensorValueScaled, 0, mapThresh);
    }
  }      
  else {
    Right(crawlSpeed);
    Left(crawlSpeed); 
  }
}

void Right( int speed ) {
  analogWrite(leftMotorPin, speed);
}

void Left( int speed ) {
  analogWrite(rightMotorPin, speed);
}

