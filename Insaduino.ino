 
#define DEBUG 1
#define COMMAND_BUFFER_SIZE 100

byte mode=0;

//RGB-LED 1
int  L1_Red    = 3;
int  L1_Blue   = 5;
int  L1_Green  = 6;

//RGB-LED 2
int  L2_Red    = 9;
int  L2_Blue   = 10;
int  L2_Green  = 11;

//White-LED 1
int L1_White   = 2;

//White-LED 2
int L2_White   = A6;

//Photoresistor
int S1_Light = A0;

int red = 3;
int green = 6;
int blue = 5;
int white = 9;

byte pink[] = {255,20,147}; 

byte redLed1 = 0;
byte greenLed1 = 0;
byte blueLed1 = 0;

byte rndRed;
byte rndGreen;
byte rndBlue;

void setup() {                
  // initialize the digital pin as an output.
  pinMode(L2_White, OUTPUT);
  //pinMode(green, OUTPUT);
  //pinMode(blue, OUTPUT);
  //pinMode(white, OUTPUT);
  
  Serial.begin(9600);
  randomSeed(analogRead(0));
  digitalWrite(L2_White, HIGH);
  
}

// the loop routine runs over and over again forever:
void loop() {
  
  //analogWrite(L1_Blue, analogRead(S1_Light));
  analogWrite(L1_Red, analogRead(S1_Light));
/*
  if (Serial.available() > 0) {
    
    Serial.println("received serial data");
    mode = Serial.read();
    Serial.println(mode);
    if(mode == 'm')
    {
      mode = Serial.read();
      if(mode == 1) 
      { 
        newMessage();
        Serial.println("Status->new message");
      }
      if(mode == 2) 
      { 
        newMessage();
        Serial.println("Status->unread mails");
      }
      
      if(mode == 0) 
      {
        blueLight();
        Serial.println("Status->idle");
      }   
    }
  } else if (mode == 0) {
    Serial.println("no serial data");
    blueLight();
    Serial.println("Status->idle");
  }
  */
}


char* readCommand()
{
  char commandBuffer[COMMAND_BUFFER_SIZE];     //CommandBuffer
  int i=0;                     //Counter
  
  if(Serial.available()){
     delay(10);
     while( Serial.available() && i< (COMMAND_BUFFER_SIZE - 1)) {
        commandBuffer[i++] = Serial.read();
     }
     commandBuffer[i++]='\0';
  }

#ifdef DEBUG
  Serial.println("Command received:");
  Serial.println((char*)commandBuffer);
#endif

  return commandBuffer;
}







boolean setMode()
{
  byte input[5];     //
  int i;             //counter
  if (Serial.available() > 0) 
  {
    while(Serial.available())
    {
      input[i] = Serial.read();
    }
    
    
  } else {
    return false;
  }
}

void redLight() 
{
  analogWrite(red, 255);
  analogWrite(green, 0);
  analogWrite(blue, 0);
  analogWrite(white, 0);
}
void greenLight() 
{
  analogWrite(red, 0);
  analogWrite(green, 255);
  analogWrite(blue, 0);
  analogWrite(white, 0);
}
void blueLight() 
{
  analogWrite(red, 0);
  analogWrite(green, 0);
  analogWrite(blue, 255);
  analogWrite(white, 0);
}

void idle()
{
  rndRed = random(-10,10);
  rndGreen = random(-10,10);
  rndBlue = random(-10,10);
  
  redLed1 = redLed1 + rndRed;
  greenLed1 = greenLed1 + rndGreen;
  blueLed1 = blueLed1 + rndGreen;
  
  analogWrite(red, redLed1);
  analogWrite(green, greenLed1);
  analogWrite(blue, blueLed1);
  analogWrite(white, 128);
  
  delay(10);
}

void newMessage() 
{
    analogWrite(white, 0);
    analogWrite(red, pink[0]);
    analogWrite(green, pink[1]);
    analogWrite(blue, pink[2]);
    delay(100);
}
