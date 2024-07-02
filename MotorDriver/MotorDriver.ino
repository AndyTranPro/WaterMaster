// =======================================================
// ENGG1000 - Computing Technical Stream
// Motor Controller
// Written by Andy Tran Oct 2022
// Controls motors via an H Bridge 
// ======================================================= 

// -------------------------------------------------------
// Global Variables
// -------------------------------------------------------
int rightMotorLogicPin1 = 3;    
int rightMotorLogicPin2 = 5;  
int leftMotorLogicPin1 = 10;    
int leftMotorLogicPin2 = 11; 
int pwmDutyCycle = 255;
char currentDirection = 0;

// -------------------------------------------------------
// The setup() method runs once, when the sketch starts
// -------------------------------------------------------
void setup(){ 
 
  // Initialize the serial communications
  Serial.begin(9600);

  // Print the program details
  Serial.println("-------------------------------------");
  Serial.println("Program: MotorDriver"); 
  Serial.println("Initializing ...");

  // Configuration the motor pins

  pinMode(rightMotorLogicPin1, OUTPUT);
  pinMode(rightMotorLogicPin2, OUTPUT);
  pinMode(leftMotorLogicPin1, OUTPUT);
  pinMode(leftMotorLogicPin2, OUTPUT);   

  // Print the motor pin configuration for wiring

  Serial.print("Right Motor Pin 1 = ");
  Serial.println(rightMotorLogicPin1);
  
  Serial.print("Right Motor Pin 2 = ");
  Serial.println(rightMotorLogicPin2);
  
  Serial.print("Left Motor Pin 1 = ");
  Serial.println(leftMotorLogicPin1);
  
  Serial.print("Left Motor Pin 2 = ");
  Serial.println(leftMotorLogicPin2);

  // Initialization completed successfully
  Serial.println("Initialization complete");
  
}

// -------------------------------------------------------
// The loop() method runs over and over again
// -------------------------------------------------------
void loop(){
  
  char incomingByte = 0;
  
  // See if there's incoming serial data:
  if (Serial.available() > 0) { 

    // Read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    currentDirection = incomingByte;

    // Checking direction; 'f' 'b' 'l' 'r'
    // Moving forward
    if (incomingByte == 'f') {
      Serial.println("Forwards");
      analogWrite(leftMotorLogicPin1, 0);
      analogWrite(leftMotorLogicPin2, pwmDutyCycle);
      analogWrite(rightMotorLogicPin1, 0);
      analogWrite(rightMotorLogicPin2, pwmDutyCycle);   
    }
  
    // Moving backwards
    if (incomingByte == 'b') {
      Serial.println("Backwards");
      analogWrite(leftMotorLogicPin1, pwmDutyCycle);
      analogWrite(leftMotorLogicPin2, 0);
      analogWrite(rightMotorLogicPin1, pwmDutyCycle);
      analogWrite(rightMotorLogicPin2, 0);   
    }   
    
    // Turning left
    if (incomingByte == 'l') {
      Serial.println("Turn Left");
      analogWrite(leftMotorLogicPin1, pwmDutyCycle);
      analogWrite(leftMotorLogicPin2, 0);
      analogWrite(rightMotorLogicPin1, 0);
      analogWrite(rightMotorLogicPin2, pwmDutyCycle);   
    }
    
    // Turning right
    if (incomingByte == 'r') {
      Serial.println("Turn Right");
      analogWrite(leftMotorLogicPin1, 0);
      analogWrite(leftMotorLogicPin2, pwmDutyCycle);
      analogWrite(rightMotorLogicPin1, pwmDutyCycle);
      analogWrite(rightMotorLogicPin2, 0);  
    }
    
    // Setting a motor speed '0' - '5'
    // Set the speed to 0
    if (incomingByte == '0') {
      pwmDutyCycle = 0;
      Serial.println("Stop");
    }
    
    // Modifying the motor speed
    if (isDigit(incomingByte) && incomingByte != '0') {
      // calculate new duty cycle
      pwmDutyCycle = ((incomingByte - '0')*255)/10;
      // Display the changed speed;
      Serial.print("speed = ");
      Serial.print(incomingByte);
      Serial.println("0%");
    }
    
  }
  
  // Small delay for a character to arrive
  delay(100); 

}
