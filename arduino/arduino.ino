// Motor Pins
const int FR_INR = 8;
const int FR_INL = 9;
const int FL_INR = 7;
const int FL_INL = 6;
const int BR_INR = 4;
const int BR_INL = 5;
const int BL_INR = 3;
const int BL_INL = 2;

// Always HIGH pins for IBT-2 motor drivers
const int controlPins[] = {22, 23, 24, 25, 26, 27, 28, 29, 30};

void setup() {
  int motorPins[] = {FR_INR, FR_INL, FL_INR, FL_INL, BR_INR, BR_INL, BL_INR, BL_INL};
  for (int i = 0; i < 8; i++) {
    pinMode(motorPins[i], OUTPUT);
  }

  for (int i = 0; i < sizeof(controlPins) / sizeof(controlPins[0]); i++) {
    pinMode(controlPins[i], OUTPUT);
    digitalWrite(controlPins[i], HIGH);
  }

  Serial.begin(9600);
}

// Motor control function
void setWheel(int inR, int inL, int speed) {
  if (speed > 0) {
    analogWrite(inR, speed);
    analogWrite(inL, 0);
  } else if (speed < 0) {
    analogWrite(inR, 0);
    analogWrite(inL, -speed);
  } else {
    analogWrite(inR, 0);
    analogWrite(inL, 0);
  }
}

// Set all wheels
void driveWheels(int fr, int fl, int br, int bl) {
  setWheel(FR_INR, FR_INL, fr);
  setWheel(FL_INR, FL_INL, fl);
  setWheel(BR_INR, BR_INL, br);
  setWheel(BL_INR, BL_INL, bl);
}

// Stop all wheels
void stopWheels() {
  driveWheels(0, 0, 0, 0);
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    // Split the input
    int firstSpace = input.indexOf(' ');
    int secondSpace = input.indexOf(' ', firstSpace + 1);

    if (firstSpace == -1 || secondSpace == -1) return;

    String motionType = input.substring(0, firstSpace);
    String direction = input.substring(firstSpace + 1, secondSpace);
    int speed = input.substring(secondSpace + 1).toInt();
    speed = constrain(speed, 0, 255);

    if (motionType == "straight") {
      if (direction == "forward") driveWheels(speed, speed, speed, speed);
      else if (direction == "backward") driveWheels(-speed, -speed, -speed, -speed);

    } else if (motionType == "horizontal") {
      if (direction == "right") driveWheels(-speed, speed, speed, -speed);
      else if (direction == "left") driveWheels(speed, -speed, -speed, speed);

    } else if (motionType == "diagonal") {
      if (direction == "forward_right") driveWheels(0, speed, speed, 0);
      else if (direction == "forward_left") driveWheels(speed, 0, 0, speed);
      else if (direction == "backward_right") driveWheels(-speed, 0, 0, -speed);
      else if (direction == "backward_left") driveWheels(0, -speed, -speed, 0);

    } else if (motionType == "rotate") {
      if (direction == "left") driveWheels(-speed, speed, -speed, speed);
      else if (direction == "right") driveWheels(speed, -speed, speed, -speed);
    }

    delay(10);  // Optional pause
  }
}
