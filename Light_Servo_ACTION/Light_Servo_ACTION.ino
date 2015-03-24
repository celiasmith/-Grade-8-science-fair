  #define C4 10   // defining rows and columns as pin numbers                                                                                   digitalWrite(C1, HIGH);
#define C3 11   
#define C2 12  
#define C1 13
#define R1 2
#define R2 3
#define R3 4
#define R4 5

//Column and row variables
int co1 = 0;
int co2 = 0;
int co3 = 0;
int co4 = 0;
int ro = 0;

// Definitions for servo
int servoPin     =  6;    // control pin for servo motor
int minPulse     =  1295;  // minimum servo position
int maxPulse     =  1695; // maximum servo position
int turnRate     =  1;  // servo turn rate increment (larger value, faster rate)
int refreshTime  =  20;   // time (ms) between pulses (50Hz)
int centerServo;         // center servo position
int pulseWidth;          // servo pulse width
int moveServo;           // raw user input
long currentTime = 0;         // counting time since the last pulse
long lastPulse   = 0;    // recorded time (ms) of the last pulse
int conumber;

//loop setup
void setup() {
  pinmode();  //Sets input/output pins, below
  centerServo = maxPulse - ((maxPulse - minPulse)/2);
  pulseWidth = centerServo;   // Give the servo a starting point
  Serial.begin(115200);
}

void loop(){    //main loop
  if (Serial.available() > 0) {
    // read the incoming byte:
    moveServo = Serial.read();
    // Comma and period, for servo control
    if (moveServo == 44) { pulseWidth = pulseWidth - turnRate; }
    else if (moveServo == 46) { pulseWidth = pulseWidth + turnRate; }
    else if (moveServo == 32) { pulseWidth = centerServo; }
    else { //a number to tell which light to turn on
      ro = moveServo % 4 + 1;
      conumber = int(moveServo/4);
      if (conumber == 1) { co1 = 1; } 
      else if (conumber == 2) { co2 = 1; } 
      else if (conumber == 3) { co3 = 1; } 
      else { co4 = 1; }
      LEDcontrol(); //turn lights on and off
    }
    
    Serial.println(pulseWidth);

  // stop servo pulse at min and max
    if (pulseWidth > maxPulse) { pulseWidth = maxPulse; }
    if (pulseWidth < minPulse) { pulseWidth = minPulse; }
  }

  if ( (currentTime-lastPulse) >= refreshTime) {
    digitalWrite(servoPin, HIGH); // start the pulse
    delayMicroseconds(pulseWidth); // pulse width
    digitalWrite(servoPin, LOW); // stop the pulse
    lastPulse = millis(); // save the time of the last pulse
  }
  currentTime = millis();  
}

void pinmode(){
  pinMode(servoPin, OUTPUT);  // Set servo pin as an output pin
  pinMode(C1, OUTPUT);      //  set 8 pins for LED outputs.
  pinMode(C2, OUTPUT);
  pinMode(C3, OUTPUT);
  pinMode(C4, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
}

void LEDcontrol(){
  digitalWrite(C1, LOW);      // Turns off all of the LED column pins
  digitalWrite(C2, LOW);
  digitalWrite(C3, LOW);
  digitalWrite(C4, LOW);

  digitalWrite(R1, LOW);      // Turns off all of the LED row pins
  digitalWrite(R2, LOW);
  digitalWrite(R3, LOW);
  digitalWrite(R4, LOW);

  if (co1 == 1){                  // Tests the "LED column" variables.
  digitalWrite(C1, HIGH);       //  Corresponding column is turned on
  }
  if (co2 == 1){
    digitalWrite(C2, HIGH);
  }
  if (co3 == 1){
    digitalWrite(C3, HIGH);
  }
  if (co4 == 1){
    digitalWrite(C4, HIGH);
  }
  
  co1 = 0;   // reset column numbers
  co2 = 0;
  co3 = 0;
  co4 = 0;
  
  if (ro == 1){                  //  Tests the "row LED" variable
    digitalWrite(R1, HIGH);      //  If variable = 2, turn row 2 on... (etc.)
  }
  if (ro == 2){
    digitalWrite(R2, HIGH);
  }
  if (ro == 3){
    digitalWrite(R3, HIGH);
  }
  if (ro == 4){
    digitalWrite(R4, HIGH);
  }
}
  

