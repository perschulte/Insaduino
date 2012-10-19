
byte mode=0;

//RGB-LED 1
int  L1_Red    = 6;
int  L1_Blue   = 5;
int  L1_Green  = 3;

//RGB-LED 2
int  L2_Red    = 11;
int  L2_Blue   = 10;
int  L2_Green  = 9;

//White-LED 1
int L1_White   = 2;

//White-LED 2
int L2_White   = A5;

//Photoresistor
int S1_Light = A0;

//preset colors
byte color1[] = {255, 19, 0}; 
byte color2[] = {255, 133, 0}; 
byte color3[] = {201, 0, 133};
byte color4[] = {0, 195, 34};

// color targets
byte L1_Red_Target     = 0;
byte L1_Green_Target   = 0; 
byte L1_Blue_Target    = 0;

byte L2_Red_Target     = 0;
byte L2_Green_Target   = 0; 
byte L2_Blue_Target    = 0;

byte L1_White_Target     = 0;
byte L2_White_Target     = 0; 

//color states
byte L1_Red_State     = 0;
byte L1_Green_State   = 0; 
byte L1_Blue_State    = 0;

byte L2_Red_State     = 0;
byte L2_Green_State   = 0; 
byte L2_Blue_State    = 0;

byte L1_White_State     = 0;
byte L2_White_State     = 0;

int millisSinceLastMesssage=0;

void setup() {                
  // initialize the digital pin as an output.
  pinMode(L2_White, OUTPUT);
  pinMode(L1_Red, OUTPUT);
  pinMode(L1_Blue, OUTPUT);
  pinMode(L1_Green, OUTPUT);
  pinMode(L2_Red, OUTPUT);
  pinMode(L2_Blue, OUTPUT);
  pinMode(L2_Green, OUTPUT);
  pinMode(L1_White, OUTPUT);
  
  Serial.begin(9600);
  randomSeed(analogRead(0));
 
  //digitalWrite(L2_White, HIGH);
  //digitalWrite(L1_Red, HIGH);
  //digitalWrite(L1_Blue, HIGH);
  //digitalWrite(L1_Green, HIGH);
  //digitalWrite(L2_Red, HIGH);
  //digitalWrite(L2_Blue, HIGH);
  //digitalWrite(L2_Green, HIGH);
  //digitalWrite(L1_White, HIGH);
}

// the loop routine runs over and over again forever:
void loop() {


  if (Serial.available() > 0) {
    millisSinceLastMesssage = millis();
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
        idle();
        Serial.println("Status->idle");
      }   
    }
  } else {
    Serial.println("no serial data");
    Serial.println("Status->idle");
    
  }
  
  if ((millis() - millisSinceLastMesssage) > 10000) 
  {
    idle();
  }
    
  //changeColors
  
}

void idle()
{
  //setTargetColors
  L1_Red_Target     = color1[0];
  L1_Green_Target   = color1[1]; 
  L1_Blue_Target    = color1[2];

  L2_Red_Target     = color1[0];
  L2_Green_Target   = color1[1]; 
  L2_Blue_Target    = color1[2];

  L1_White_Target     = 255;
  L2_White_Target     = 255;
  
  if (checkLightSensor
  
  /*
  analogWrite(L1_Red, color1[0]);
  analogWrite(L1_Green, color1[1]);
  analogWrite(L1_Blue, color1[2]);
    
  analogWrite(L2_Red, color1[0]);
  analogWrite(L2_Green, color1[1]);
  analogWrite(L2_Blue, color1[2]);
  */
}

void noSignal()
{ 
  //check light sensor
  
  //setTargetColors
  L1_Red_Target     = 0;
  L1_Green_Target   = 0; 
  L1_Blue_Target    = 0;

  L2_Red_Target     = 0;
  L2_Green_Target   = 0; 
  L2_Blue_Target    = 0;

  L1_White_Target     = 0;
  L2_White_Target     = 0;
  
  analogWrite(L1_Red, color1[0]);
   analogWrite(L1_Green, color1[1]);
   analogWrite(L1_Blue, color1[2]);
    
   analogWrite(L2_Red, color1[0]);
   analogWrite(L2_Green, color1[1]);
   analogWrite(L2_Blue, color1[2]);
   
}

void newMessage() 
{
    analogWrite(L1_Red, color4[0]);
    analogWrite(L1_Green, color4[1]);
    analogWrite(L1_Blue, color4[2]);
    
    analogWrite(L2_Red, color4[0]);
    analogWrite(L2_Green, color4[1]);
    analogWrite(L2_Blue, color4[2]);
}

byte checkLightSensor()
{
  //set LEDs to zero for 10ms
  analogWrite(L1_Red, 0);
  analogWrite(L1_Green, 0);
  analogWrite(L1_Blue, 0);
  analogWrite(L2_Red, 0);
  analogWrite(L2_Green, 0);
  analogWrite(L2_Blue, 0);
  analogWrite(L1_White, 0);
  analogWrite(L2_White, 0);
  
  byte result = analogRead(S1_Light);
  
  //set LEDs back to previous state
  analogWrite(L1_Red, L1_Red_State);
  analogWrite(L1_Green, L1_Green_State);
  analogWrite(L1_Blue, L1_Blue_State);
  analogWrite(L2_Red, L1_Red_State);
  analogWrite(L2_Green, L1_Green_State);
  analogWrite(L2_Blue, L1_Blue_State);
  analogWrite(L1_White, L1_White_State);
  analogWrite(L2_White, L2_White_State);
}