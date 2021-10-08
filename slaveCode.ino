//For serial receive.
const byte numChars = 30;
char receivedChars[numChars]; // an array to store the received data
String received; //The data as a string
boolean newData = false;

// MOTOR A (right side)
int in1 = 13;
int in2 = 12;

// MOTOR B (left side)
int in3 = 11;
int in4 = 10;

void setup()
{
  Serial.begin(9600); // Starts the serial communication

  // Sets up all motor pins as output
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  //pinMode(3, OUTPUT);
}

void loop()
{
  //Serial.println("hello from simon");
  delay(1000);
  recvWithEndMarker();
   if (newData == true)
   {
    String instruction = received.substring(0,5);
    Serial.println(instruction);
    if(instruction == "fords")
    {
      moveForward(); // Moves both motors forwards
      //digitalWrite(3, HIGH); // turns on green LED
    }
    if(instruction == "stops")
    {
      moveStop(); // Turns off all motors
      //digitalWrite(3, LOW); // turns on green LED
    }
    if(instruction == "lefts")
    {
      moveLeft(); // Moves left motor forwards
    }
    if(instruction == "right")
    {
      moveRight(); // Moves right motor forwards
    }
    newData = false;
   }
}

void recvWithEndMarker() 
{
 static byte ndx = 0;
 char endMarker = '\n';
 char rc;
 
 while (Serial.available() > 0 && newData == false) 
 {
  rc = Serial.read();

  if (rc != endMarker) 
  {
    receivedChars[ndx] = rc;
    ndx++;
    if (ndx >= numChars) 
    {
      ndx = numChars - 1;
    }
 }
 else 
  {
  receivedChars[ndx] = '\0'; // terminate the string
  received = String(receivedChars);
  ndx = 0;
  newData = true;
  }
 }
}

// Moves both motors forwards
void moveForward()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// Moves left motor forwards
void moveLeft()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

// Moves right motor forwards
void moveRight()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// Turn off all motors
void moveStop()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
