/**
 * AutoBadger v1.1.0
 * @author Stefano Taillefert
 * https://github.com/Steeven9/AutoBadger
 */

#include <Servo.h>

#define SERVO_PORT 2
#define RELAY_PORT 3
#define BUTTON_PORT 4

//Servo starting angle in degrees
#define INITIAL_POS 0

//Strobe blinking interval in ms
#define STROBE_INTERVAL 500

//Uncomment to blink manually
//(switches the relay on and off in intervals)
//#define MANUAL_BLINK

Servo servo;

void setup() {
  pinMode(RELAY_PORT, OUTPUT);
  pinMode(BUTTON_PORT, INPUT);
  servo.attach(SERVO_PORT);
  digitalWrite(RELAY_PORT, HIGH); //default is off
  servo.write(INITIAL_POS); //start position - up
  delay(1000);
}

/**
 * Makes the strobe manually blink for the given duration.
 */
void manualBlink(int interval) {
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
    #ifdef MANUAL_BLINK
      servo.write(INITIAL_POS + 180);
      manualBlink(1500);
      servo.write(INITIAL_POS);
      manualBlink(500);
    #else
      digitalWrite(RELAY_PORT, LOW);  //on
      servo.write(INITIAL_POS + 180);
      delay(1500);
      servo.write(INITIAL_POS);
      delay(500);
      digitalWrite(RELAY_PORT, HIGH);  //off
    #endif
    delay(1000);
  }
}
