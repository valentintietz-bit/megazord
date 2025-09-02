#include <Servo.h>
#include <SoftwareSerial.h>
Servo MAxeX, MAxeY, MAxeZ, MAxePince;

int ValX, ValY, ValZ, ValPince;
int BluetoothTX = 10;
int BluetoothRX = 11;
int FrontLeft = 4;
int BackLeft = 5;
int FrontRight = 9;
int BackRight = 8;
int LeftMotorOn = 3;
int RightMotorOn = 7;

SoftwareSerial Bluetooth(BluetoothTX, BluetoothRX);

void setup() {
  // put your setup code here, to run once:
  MAxeX.attach(2);
  MAxeY.attach(3);
  MAxeZ.attach(4);
  MAxePince.attach(5);
  pinMode(FrontLeft, OUTPUT);
  pinMode(BackLeft, OUTPUT);
  pinMode(FrontRight, OUTPUT);
  pinMode(BackRight, OUTPUT);
  pinMode(LeftMotorOn, OUTPUT);
  pinMode(RightMotorOn, OUTPUT);

  Serial.begin(9600);
  Bluetooth.begin(9600);
}

void moveForward() {
  digitalWrite(FrontLeft, HIGH);
  digitalWrite(BackLeft, LOW);
  digitalWrite(FrontRight, HIGH);
  digitalWrite(BackRight, LOW);
  digitalWrite(LeftMotorOn, HIGH);
  digitalWrite(RightMotorOn, HIGH);
}

void moveBackward() {
  digitalWrite(FrontLeft, LOW);
  digitalWrite(BackLeft, HIGH);
  digitalWrite(FrontRight, LOW);
  digitalWrite(BackRight, HIGH);
  digitalWrite(LeftMotorOn, HIGH);
  digitalWrite(RightMotorOn, HIGH);
}

void turnLeft() {
  digitalWrite(FrontLeft, LOW);
  digitalWrite(BackLeft, HIGH);
  digitalWrite(FrontRight, HIGH);
  digitalWrite(BackRight, LOW);
  digitalWrite(LeftMotorOn, HIGH);
  digitalWrite(RightMotorOn, HIGH);
}

void turnRight() {
  digitalWrite(FrontLeft, HIGH);
  digitalWrite(BackLeft, LOW);
  digitalWrite(FrontRight, LOW);
  digitalWrite(BackRight, HIGH);
  digitalWrite(LeftMotorOn, HIGH);
  digitalWrite(RightMotorOn, HIGH);
}

void stopMoving() {
  digitalWrite(FrontLeft, LOW);
  digitalWrite(BackLeft, LOW);
  digitalWrite(FrontRight, LOW);
  digitalWrite(BackRight, LOW);
  digitalWrite(LeftMotorOn, LOW);
  digitalWrite(RightMotorOn, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Bluetooth.available() >= 2) {
    int ValPos = Bluetooth.read();
    int ValPos1 = Bluetooth.read();
    int Val = (ValPos1 * 256) + ValPos;
    Serial.println(Val);

    if (Val >= 1000 && Val < 1180) {
      ValX = map(Val, 1000, 1180, 0, 180);
      MAxeX.write(ValX);
    }

    if (Val >= 2000 && Val < 2180) {
      ValY = map(Val, 2000, 2180, 0, 180);
      MAxeY.write(ValY);
    }

    if (Val >= 3000 && Val < 3180) {
      ValZ = map(Val, 3000, 3180, 0, 180);
      MAxeZ.write(ValZ);
    }

    if (Val >= 4000 && Val < 4180) {
      ValPince = map(Val, 4000, 4180, 0, 180);
      MAxePince.write(ValPince);
    }
  }

  char remoteControl;

  if (Bluetooth.available() <= 2) {
    remoteControl = Bluetooth.read();
    Serial.println(remoteControl);
  }

  if (remoteControl == 'z')
    moveForward();
  else if (remoteControl == 's')
    moveBackward();
  else if (remoteControl == 'q')
    turnLeft();
  else if (remoteControl == 'd')
    turnRight();
  else if (remoteControl == 'a')
    stopMoving();
}
