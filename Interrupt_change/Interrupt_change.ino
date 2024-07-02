// =======================================================
// ENGG1000 - Computing Techincal Stream
// Interrupt and Log data
// Written by Andy Tran Octerber 2022
// Implements an Interupt0 for any change in state
// and record the data
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
  Serial.println("Log begins");

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
      Serial.print(interruptTime[i] - interruptTime[i-1]);
      Serial.print(" - ");
      Serial.println(interruptState[i]);
    }
    Serial.println("Log ends");
  }  
}
