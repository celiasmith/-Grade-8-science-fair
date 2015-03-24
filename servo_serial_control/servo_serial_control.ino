
/*
 * NewSerialServo
 * --------------
 * Servo control from the Serial port
 *
 * Alteration of the control interface to use  keys
 * to slew the servo horn left and right.  Works best with
 * the Linux/Mac terminal "screen" program.
 *
 * Created 10 December 2007
 * copyleft 2007 Brian D. Wendt
 * http://principialabs.com/
 *
 * Adapted from code by Tom Igoe
 * http://itp.nyu.edu/physcomp/Labs/Servo
 */

/** Adjust these values for your servo and setup, if necessary **/
int servoPin     =  8;    // control pin for servo motor
int minPulse     =  1000;  // minimum servo position
int maxPulse     =  2000; // maximum servo position
int turnRate     =  1;  // servo turn rate increment (larger value, faster rate)
int refreshTime  =  20;   // time (ms) between pulses (50Hz)

/** The Arduino will calculate these values for you **/
int centerServo;         // center servo position
int pulseWidth;          // servo pulse width
int moveServo;           // raw user input
long currentTime = 0;         // counting time since the last pulse
long lastPulse   = 0;    // recorded time (ms) of the last pulse


void setup() {
  pinMode(servoPin, OUTPUT);  // Set servo pin as an output pin
  centerServo = maxPulse - ((maxPulse - minPulse)/2);
  pulseWidth = centerServo;   // Give the servo a starting point (or it floats)
  Serial.begin(115200);
  //Serial.println("      Arduino Serial Servo Control");
  //Serial.println("Press  to move, spacebar to center");
  //Serial.println();
}

void loop() {
// wait for serial input
  if (Serial.available() > 0) {
    // read the incoming byte:
    moveServo = Serial.read();
    //Serial.println(pulseWidth);
    // ASCII ” is 46 (comma and period, really)
    if (moveServo == 44) { pulseWidth = pulseWidth - turnRate; }
    if (moveServo == 46) { pulseWidth = pulseWidth + turnRate; }
    if (moveServo == 32) { pulseWidth = centerServo; }
    Serial.println(pulseWidth);
  // stop servo pulse at min and max
    if (pulseWidth > maxPulse) { pulseWidth = maxPulse; }
    if (pulseWidth < minPulse) { pulseWidth = minPulse; }
    //Serial.println(pulseWidth);
  }
  if ( (currentTime-lastPulse) >= refreshTime) {
    digitalWrite(servoPin, HIGH); // start the pulse
    delayMicroseconds(pulseWidth); // pulse width
    digitalWrite(servoPin, LOW); // stop the pulse
    lastPulse = millis(); // save the time of the last pulse
  }
currentTime = millis();
}


