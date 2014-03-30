// This program is intended as a simple test that data is being properly recieved from the controller.
// Data is recieved as a 6 byte packet. Bytes 3 & 5 are read and used to drive a 2 servo tank robot.
// by Adam Kemp, 2012 http://code.google.com/p/smduino/

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
    Serial.println("Reading First Byte...");
    startByte = Serial1.read();
    Serial.print("starByte = ");
    Serial.println(startByte);
    if (startByte == (255)){
      Serial.print("StartByte Verified as ");
      Serial.println(startByte);
      buttons = Serial1.read(); //reads byte 1
      dPads = Serial1.read(); //reads byte 2
      LY = Serial1.read(); //reads byte 3
      LX = Serial1.read(); //reads byte 4
      RY = Serial1.read(); //reads byte 5
      RX = Serial1.read(); //reads byte 6
    }
    
    if (LY <= 115){
      leftMotorSpeedF = map(LY, 0, 115, 255, 0); //converts the thumbstick value to 0 - 255 for PWM
      analogWrite (leftMotorReverse, 0);
      analogWrite (leftMotorForward, leftMotorSpeedF);
    }
    else if (LY >= 155){
      leftMotorSpeedR = map(LY, 155, 254, 0, 255);
      analogWrite (leftMotorForward, 0);
      analogWrite (leftMotorReverse, leftMotorSpeedR);
    }
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
 /*   
    Serial.print("buttons = ");
    Serial.println(buttons);
    Serial.print("dPads = ");
    Serial.println(dPads);
    Serial.print("LY = ");
    Serial.println(LY);
    Serial.print("LX = ");
    Serial.println(LX);
    Serial.print("RY = ");
    Serial.println(RY);
    Serial.print("RX = ");
    Serial.println(RX);
    Serial.println();
 */
    delay(15);
  }
}

