// =======================================================
// ENGG1000 - Computing Techincal Stream
// Interrupt and Data log
// Written by Andy Tran October 2022
// Implements an Interupt0 for any change in state
// and using graph representation
// ======================================================= 

// -------------------------------------------------------
// Global Variables
// -------------------------------------------------------
int interruptPin = 2; 
int interruptNo = 0;
long interruptTime[100];
int interruptState[100];
int dataLength = 0;

// -------------------------------------------------------
// Interrupt Event Handler
// -------------------------------------------------------
void interruptPinChange(){
  
  // Switch off interrupts to avoid a conflict in code execution
  noInterrupts();

  // Log the time of the interrupt
  interruptTime[dataLength] = micros();
  
  // Record the pin state
  interruptState[dataLength] = (digitalRead(interruptPin) == HIGH);
  
  // Increment the length of the data log
  if (dataLength < 99) dataLength++;
  
  // Switch interrupts back on
  interrupts();
  
}

// -------------------------------------------------------
// The setup() method runs once, when the sketch starts
// -------------------------------------------------------
void setup(){  
  
  // Set up the interupt
  pinMode(interruptPin, INPUT);
  attachInterrupt(interruptNo, interruptPinChange, CHANGE);
  Serial.begin(9600);
  Serial.println("Initialise");

}

// -------------------------------------------------------
// The loop() method runs over and over again
// -------------------------------------------------------
void loop(){
  
  // Normal process code
  delay(100);
  if (Serial.available() > 0) {
    while (Serial.available() > 0) Serial.read();
    
    for (int i = 1; i < dataLength; i++) {
      // Calculate the time elapsed since the previous state change of the pin
      int pulseWidth = (interruptTime[i] - interruptTime[i-1] + 52) / 104;
      // Print some dashes for the pulse
      for (int j = 0; j < pulseWidth; j++) {
        // Was it a positive or negative pulse
        if (interruptState[i-1] == 1) {
          Serial.print("-");
        } else {
          Serial.print("_");
        }
      }
    }
  }  
}
