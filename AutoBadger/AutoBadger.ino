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
  delay(2000);
}

/**
 * Makes the strobe blink for the given duration.
 * If manual blinking is needed, flashes manually
 * in intervals specified by STROBE_INTERVAL.
 */
void blink(int interval) {
  #ifdef MANUAL_BLINK
    for (int i = 0; i < interval; ++i) {
      digitalWrite(RELAY_PORT, LOW);  //on
      delay(STROBE_INTERVAL);
      digitalWrite(RELAY_PORT, HIGH); //off
      delay(STROBE_INTERVAL);
      i = i + 2 * STROBE_INTERVAL;
    }
  #else
    digitalWrite(RELAY_PORT, LOW);  //on
    delay(interval);
    digitalWrite(RELAY_PORT, HIGH); //off
  #endif
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
