// This program is intended as a simple test that data is being properly recieved from the controller.
// Data is recieved as a 6 byte packet. Bytes 3 & 5 are read and used to drive a 2 servo tank robot.
// by Adam Kemp, 2012 http://code.google.com/p/smduino/
// modified by Tomdf for RC car control v11

byte buttons = 0; //button byte
byte dPads = 0; //dpads byte
byte LY = 128; //neutral value for servo position (in byte form)
byte LX = 128;
byte RY = 128;
byte RX = 128;

byte startByte; //storage for frame start identifier

byte rightMotorSpeedF; //byte to store right motor forward speed value
byte rightMotorSpeedR; //byte to store right motor reverse speed value
byte leftMotorSpeedF;
byte leftMotorSpeedR;

int leftMotorForward = 3; //right motor forward pin connects to PWM D3
int leftMotorReverse = 5;
int rightMotorForward = 6;
int rightMotorReverse = 10;

void setup() {
  Serial.begin(57600);
  Serial1.begin(57600);
  pinMode(leftMotorForward, OUTPUT);
  pinMode(leftMotorReverse, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(rightMotorReverse, OUTPUT);
}

void loop() {
  if (Serial1.available() >=7) { //waits until the 7 bytes are read into buffer
    startByte = Serial1.read();
    if (startByte == (255)){
      buttons = Serial1.read(); //reads byte 1
      dPads = Serial1.read(); //reads byte 2
      LY = Serial1.read(); //reads byte 3
      LX = Serial1.read(); //reads byte 4
      RY = Serial1.read(); //reads byte 5
      RX = Serial1.read(); //reads byte 6
    }

    // if left stick is pushed forward pass the deadzone turn on left
    // motor at a forward speed relative to how far the stick is pushed
    if (LY <= 115){
      leftMotorSpeedF = map(LY, 0, 115, 255, 0); //converts the thumbstick value to 0 - 255 for PWM
      analogWrite (leftMotorReverse, 0);
      analogWrite (leftMotorForward, leftMotorSpeedF);
    }
    // if the left stick is pushed back pass the deadzone turn on left
    // motor at a reverse speed relative to how far the stick is pushed
    else if (LY >= 155){
      leftMotorSpeedR = map(LY, 155, 254, 0, 255);
      analogWrite (leftMotorForward, 0);
      analogWrite (leftMotorReverse, leftMotorSpeedR);
    }
    // if the left stick is not pushed at all then turn off the left motor
    else {
      analogWrite (leftMotorForward,0);
      analogWrite (leftMotorReverse,0);
    }
    
    if (RY <= 105){
      rightMotorSpeedF = map(RY, 0, 105, 255, 0); //converts the thumbstick value to 0 - 255 for PWM
      analogWrite (rightMotorReverse, 0);
      analogWrite (rightMotorForward, rightMotorSpeedF);
    }
    else if (RY >= 135){
      rightMotorSpeedR = map(RY, 135, 254, 0, 255);
      analogWrite (rightMotorForward,0);
      analogWrite (rightMotorReverse, rightMotorSpeedR);
    }
    else {
      analogWrite (rightMotorForward,0);
      analogWrite (rightMotorReverse,0);
    }
    delay(15);
  }
}
