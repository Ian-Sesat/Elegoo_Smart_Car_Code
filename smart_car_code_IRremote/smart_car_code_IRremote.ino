
//Including the IRremote library 
#include <IRremote.h>
int IRpin=12;
IRrecv IR(IRpin);
decode_results cmd;
//Declaring the pins on the arduino:
int ENA=5;
int ENB=6;
int IN1=7;
int IN2=8;
int IN3=9;
int IN4=11;
int d=1;      //distance to be travelled by the car
int degRot=90;
int left,right;
float v=1.5;
int wv;
int rv;

void setup() {
//setting up the IRremote:
IR.enableIRIn();
//initialising the Serial monitor
Serial.begin(9600);
// setting up the pins
 pinMode(ENA,OUTPUT);
 pinMode(ENB,OUTPUT);
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);

//enabling the channels A and B for them to always stay enabled:
digitalWrite(ENA,HIGH);
digitalWrite(ENB,HIGH);

}

void loop()
{
wv=(v-0.35)/0.0075;
left=wv;
right=wv;
setspeed(left,right);

while (IR.decode(&cmd)==0){
  }
Serial.println(cmd.value,HEX);
 
if (cmd.value == 0x511DBB){
  Serial.println("Moving Forward...");
  forward(d,v);
  }
if (cmd.value == 0xA3C8EDDB){
  Serial.println("Moving Backwards...");
  backward(d,v);
  }
 if (cmd.value == 0x52A3D41F){
  Serial.println("Turning Left...");
  leftTurn(degRot,wv);
  }
 if (cmd.value == 0x20FE4DBB){
  Serial.println("Turning Right...");
  rightTurn(degRot,wv);
  }
  IR.resume();

   //Setting the distance the smart car travels using a remote
   //On press of *
if (cmd.value==0x32C6FDF7
){
  Serial.println("Set Distance");
  delay(500);
  IR.resume();
  while(IR.decode(&cmd)==0){
    }
  Serial.println(cmd.value,HEX);
  if (cmd.value==0x1BC0157B){
    d=0;
    Serial.println("Distance=0");
    delay(100);
    }
  if (cmd.value==0xC101E57B){
    d=1;
    Serial.println("Distance=1");
    delay(100);
    }
  if (cmd.value==0x97483BFB){
    d=2;
    Serial.println("Distance=2");
    delay(100);
    }
  if (cmd.value==0xF0C41643){
    d=3;
    Serial.println("Distance=3");
    delay(100);
    }
  if (cmd.value==0x9716BE3F){
    d=4;
    Serial.println("Distance=4");
    delay(100);
    }
  if (cmd.value==0x3D9AE3F7){
    d=5;
    Serial.println("Distance=5");
    delay(100);
    }
  if (cmd.value==0x6182021B){
    d=6;
    Serial.println("Distance=6");
    delay(100);
    }
  if (cmd.value==0x8C22657B){
    d=7;
    Serial.println("Distance=7");
    delay(100);
    }
  if (cmd.value==0x488F3CBB){
    d=8;
    Serial.println("Distance=8");
    delay(100);
    }
   if (cmd.value==0x449E79F){
    d=9;
    Serial.println("Distance=9");
    delay(100);
    }
    
  }
 IR.resume();

 //Setting speed of the smart car via the IRremote
 //on press of #
if(cmd.value==0x3EC3FC1B){
  Serial.println("Set Speed");
  delay(500);
  IR.resume();
  while (IR.decode(&cmd)==0){
    }
   Serial.println(cmd.value,HEX);
   if(cmd.value==0x1BC0157B){
    rv=0;
    Serial.println("rv is 0");
    delay(100);
    }
   if(cmd.value==0xC101E57B){
    rv=1;
    Serial.println("rv is 1");
    delay(100);
    }
   if(cmd.value==0x97483BFB){
    rv-2;
    Serial.println("rv is 2");
    delay(100);
    }
   if(cmd.value==0xF0C41643){
    rv-3;
    Serial.println("rv is 3");
    delay(100);
    }
    if(cmd.value==0x9716BE3F){
    rv-4;
    Serial.println("rv is 4");
    delay(100);
    }
   if(cmd.value==0x3D9AE3F7){
    rv=5;
    Serial.println("rv is 5");
    delay(100);
    }
   if(cmd.value==0x6182021B){
    rv=6;
    Serial.println("rv is 6");
     delay(100);
    }
   if(cmd.value==0x8C22657B){
    rv=7;
    Serial.println("rv is 7");
    delay(100);
    }
   if(cmd.value==0x488F3CBB){
    rv=8;
    Serial.println("rv is 8");
    delay(100);
    }
    if(cmd.value==0x449E79F){
    rv=9;
    Serial.println("rv is 9");
    delay(100);
    }
    v=(1.16/9.)*rv+1.1;
  }
  IR.resume();
 
}  
void setspeed(int l,int r){
 analogWrite(ENA,l);
 analogWrite(ENB,r);
  }
//forward motion function
void forward(float d, float v){
 float t;
digitalWrite(IN1,HIGH);
digitalWrite(IN2,LOW);
digitalWrite(IN3,LOW);
digitalWrite(IN4,HIGH);
t=(d/v)*1000;
delay(t);
stopCar();
  }
 //backward motion function
void backward(float d,float v){
 float t;
digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
t=(d/v)*1000;
delay(t);
stopCar();
  }
//left turn function
void leftTurn(int deg,float wv ){
float t;
stopCar();
analogWrite(ENA,125);
analogWrite(ENB,125);
delay(100);
digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);
digitalWrite(IN3,LOW);
digitalWrite(IN4,HIGH);
t=(deg+6)/136.29*1000.;
delay(t);
analogWrite(ENA,wv);
analogWrite(ENB,wv);

stopCar();
 }
//right turn function
void rightTurn(int deg,float wv){
 float t;
 stopCar();
analogWrite(ENA,125);
analogWrite(ENB,125);
delay(100);
digitalWrite(IN1,HIGH);
digitalWrite(IN2,LOW);
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
t=(deg+6)/136.29*1000.;
delay(t);
analogWrite(ENA,wv);
analogWrite(ENB,wv);
stopCar();
  }
 void stopCar(){
 digitalWrite(IN1,LOW);
digitalWrite(IN2,LOW);
digitalWrite(IN3,LOW);
digitalWrite(IN4,LOW);

  }
//calibrating in the forward direction
  void calForward(){
digitalWrite(IN1,HIGH);
digitalWrite(IN2,LOW);
digitalWrite(IN3,LOW);
digitalWrite(IN4,HIGH);
delay(2500);
stopCar();
  }
 //calibrating in the backward direction
 void calBackward(){
digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
delay(2500);
stopCar(); 
  }
 //calibrating in the left direction
 void calLeft(int wv){
  analogWrite(ENA,125);
  analogWrite(ENB,125);
digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);
digitalWrite(IN3,LOW);
digitalWrite(IN4,HIGH);
delay(500);
analogWrite(ENA,wv);
analogWrite(ENB,wv);

stopCar();
 }
 //calibrating in the right direction
 void calRight(int wv){
    analogWrite(ENA,125);
  analogWrite(ENB,125);
digitalWrite(IN1,HIGH);
digitalWrite(IN2,LOW);
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
delay(3000);
analogWrite(ENA,wv);
analogWrite(ENB,wv);
stopCar();
 }
 
