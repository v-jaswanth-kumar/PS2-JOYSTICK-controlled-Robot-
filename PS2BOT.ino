#include <PS2X_lib.h>


PS2X ps2x;
#define ENA 2        //ENA
#define MOTORA_A1 3  //IN3
#define MOTORA_A2 4  //IN4
#define MOTORB_B1 6  //IN1
#define MOTORB_B2 7  //IN2
#define ENB 8
int error = 0;
byte type = 0;
byte vibrate = 0;
int speed = 1024;


void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(MOTORA_A1, OUTPUT);
  pinMode(MOTORA_A2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(MOTORB_B1, OUTPUT);
  pinMode(MOTORB_B2, OUTPUT);
  Serial.begin(57600);

  error = ps2x.config_gamepad(13, 11, 10, 12, true, true);  //(clock, command, attention, data)
}

void loop() {
  int temp;
  ps2x.read_gamepad(false, vibrate);
 

  int leftStickX = ps2x.Analog(PSS_RX);
  int leftStickY = ps2x.Analog(PSS_RY);

  // Map analog joystick values to control the motors
  int motorA_speed = map(leftStickY, 0, 255, -255, 255);
  int motorB_speed = map(leftStickX, 0, 255, -255, 255);

  // Calculate motor speeds for differential drive
  int motorLeft = motorA_speed + motorB_speed;
  int motorRight = motorA_speed - motorB_speed;

  // Motor control
  analogWrite(ENA, abs(motorLeft));
  analogWrite(ENB, abs(motorRight));

  // Set motor direction based on joystick position
  digitalWrite(MOTORA_A1, motorLeft > 0 ? HIGH : LOW);
  digitalWrite(MOTORA_A2, motorLeft < 0 ? HIGH : LOW);
  digitalWrite(MOTORB_B1, motorRight > 0 ? HIGH : LOW);
  digitalWrite(MOTORB_B2, motorRight < 0 ? HIGH : LOW);

  delay(50);

  if (ps2x.Button(PSB_TRIANGLE)) {
    temp = ps2x.Analog(PSB_TRIANGLE), DEC;

    digitalWrite(MOTORA_A1, HIGH);
    digitalWrite(MOTORA_A2, LOW);
    digitalWrite(MOTORB_B1, HIGH);
    digitalWrite(MOTORB_B2, LOW);
    analogWrite(ENB, speed);
    analogWrite(ENA, speed);
    Serial.println("Front");
  }

  else if (ps2x.Button(PSB_CIRCLE)) {
    temp = ps2x.Analog(PSB_CIRCLE), DEC;
    digitalWrite(MOTORA_A1, HIGH);
    digitalWrite(MOTORA_A2, LOW);
    digitalWrite(MOTORB_B1, LOW);
    digitalWrite(MOTORB_B2, HIGH);
    analogWrite(ENB, speed);
    analogWrite(ENA, speed);
    Serial.println("Right");

  }

  else if (ps2x.Button(PSB_SQUARE)) {
    temp = ps2x.Analog(PSB_SQUARE), DEC;
    digitalWrite(MOTORA_A1, LOW);
    digitalWrite(MOTORA_A2, HIGH);
    digitalWrite(MOTORB_B1, HIGH);
    digitalWrite(MOTORB_B2, LOW);
    analogWrite(ENB, speed);
    analogWrite(ENA, speed);
    Serial.println("Left");


  }

  else if (ps2x.Button(PSB_CROSS)) {
    temp = ps2x.Analog(PSB_CROSS), DEC;
    digitalWrite(MOTORA_A1, LOW);
    digitalWrite(MOTORA_A2, HIGH);
    digitalWrite(MOTORB_B1, LOW);
    digitalWrite(MOTORB_B2, HIGH);
    analogWrite(ENB, speed);
    analogWrite(ENA, speed);
    Serial.println("Back");

  }

  else {

    digitalWrite(MOTORA_A1, LOW);
    digitalWrite(MOTORA_A2, LOW);
    digitalWrite(MOTORB_B1, LOW);
    digitalWrite(MOTORB_B2, LOW);
    analogWrite(ENB, 0);
    analogWrite(ENA, 0);
    Serial.println("Move stop");
  }

  delay(50);
}