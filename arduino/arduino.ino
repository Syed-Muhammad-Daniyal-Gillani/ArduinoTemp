// Updated PWM Motor Pins
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
  // Initialize motor pins
  int motorPins[] = {FR_INR, FR_INL, FL_INR, FL_INL, BR_INR, BR_INL, BL_INR, BL_INL};
  for (int i = 0; i < 8; i++) {
    pinMode(motorPins[i], OUTPUT);
  }

  // Set control pins HIGH
  for (int i = 0; i < sizeof(controlPins) / sizeof(controlPins[0]); i++) {
    pinMode(controlPins[i], OUTPUT);
    digitalWrite(controlPins[i], HIGH);
  }

  Serial.begin(9600);
}

// Individual wheel control
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

//Front right, positive forward
//Front left,  positive backward


// Drive all 4 wheels with individual control
void driveWheels(int fr, int fl, int br, int bl) {
  setWheel(FR_INR, FR_INL, fr);
  setWheel(FL_INR, FL_INL, fl);
  setWheel(BR_INR, BR_INL, br);
  setWheel(BL_INR, BL_INL, bl);
}

void loop() {
  // Forward
  driveWheels(135, 70, 70, 70);
  delay(5000);

  driveWheels(0, 0, 0, 0);
  delay(2000);
  // Backward
  driveWheels(-135, -70, -70, -70);
  delay(5000);

  driveWheels(0, 0, 0, 0);
  delay(2000);
  // Strafe Left
  driveWheels(-135, 70, 70, -70);
  delay(2000);

  driveWheels(0, 0, 0, 0);
  delay(2000);
  // Strafe Right
  driveWheels(135, -70, -70, 70);
  delay(2000);

  driveWheels(0, 0, 0, 0);
  delay(2000);

  // Diagonal Forward Left
  driveWheels(0, 70, 70, 0);
  delay(5000);

  driveWheels(0, 0, 0, 0);
  delay(2000);

  // Diagonal Backward Right
  driveWheels(-135, 0, 0, -70);
  delay(5000);

    driveWheels(0, 0, 0, 0);
  delay(2000);

  // Rotate Clockwise
  driveWheels(135, -70, 70, -70);
  delay(5000);

  driveWheels(0, 0, 0, 0);
  delay(2000);

  // Rotate Counter-Clockwise
  driveWheels(-135, 70, -70, 70);
  delay(5000);


  // Stop
  driveWheels(0, 0, 0, 0);
  delay(2000);
}