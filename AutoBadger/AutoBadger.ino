/**
 * AutoBadger v1.0.0
 * @author Stefano Taillefert
 * https://github.com/Steeven9/AutoBadger
 */

#include <Servo.h>

Servo servo;
const int SERVO_PORT = 2;
const int RELAY_PORT = 3;
const int BUTTON_PORT = 4;

//Servo starting angle in degrees
const int INITIAL_POS = 0;

//Strobe blinking interval in ms
const int STROBE_INTERVAL = 500;

void setup() {
  pinMode(RELAY_PORT, OUTPUT);
  pinMode(BUTTON_PORT, INPUT);
  servo.attach(SERVO_PORT);
  digitalWrite(RELAY_PORT, HIGH); //default is off
  servo.write(INITIAL_POS); //start position - up
  delay(2000);
}


/**
 * Makes the strobe blink for the given duration
 * in intervals specified by STROBE_INTERVAL.
 */
void blink(int interval) {
  for (int i = 0; i < interval; ++i) {
    digitalWrite(RELAY_PORT, LOW);  //on
    delay(STROBE_INTERVAL);
    digitalWrite(RELAY_PORT, HIGH); //off
    delay(STROBE_INTERVAL);
    i = i + 2 * STROBE_INTERVAL;
  }
}


void loop() {
  if (digitalRead(BUTTON_PORT) == 1) {
    servo.write(INITIAL_POS + 180);
    blink(3000);
    servo.write(INITIAL_POS);
    blink(2000);
    delay(1000);
  }
}
