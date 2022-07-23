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
char cmd;
int LTRight=10;
int LTLeft=2;
int LTMiddle=4;
int middleRead;
int rightRead;
int leftRead;
int rv;
int deg;

void setup() {
//initialising the Serial monitor
Serial.begin(9600);
// setting up the pins for the motor
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

while(Serial.available()==0){
  
  }
cmd=Serial.read();
 
if (cmd == 'f'){
  Serial.println("Moving Forward...");
  forward(d,v);
  }
if (cmd == 'b'){
  Serial.println("Moving Backwards...");
  backward(d,v);
  }
 if (cmd == 'l'){
  Serial.println("Turning Left...");
  leftTurn(degRot,wv);
  }
 if (cmd == 'r'){
  Serial.println("Turning Right...");
  rightTurn(degRot,wv);
  }


   //Setting the distance the smart car travels using BLE
if (cmd == 'd'){
  Serial.println("Set Distance");
  delay(100);
  while (Serial.available()==0){
    
    }
  cmd=Serial.read();
  delay(100);
  if (cmd =='1'){
    d=1;
    Serial.println("Distance=1");
    }
  if (cmd =='2'){
    d=2;
    Serial.println("Distance=2");
    }
  if (cmd =='3'){
    d=3;
    Serial.println("Distance=3");
   
    }
  if (cmd == '4'){
    d=4;
    Serial.println("Distance=4");
   
    }
  if (cmd == '5'){
    d=5;
    Serial.println("Distance=5");
    }
  if (cmd == '6'){
    d=6;
    Serial.println("Distance=6");
    }
  if (cmd == '7'){
    d=7;
    Serial.println("Distance=7");
    }
  if (cmd == '8'){
    d=8;
    Serial.println("Distance=8");
    }
   if (cmd == '9'){
    d=9;
    Serial.println("Distance=9");
    }
    
  }

 //Setting speed of the samrt car via the BLE
if(cmd=='s'){
  Serial.println("Set Speed");
  delay(100);
  while (Serial.available()==0){
    
    }
  cmd=Serial.read();
  delay(100);
  
   if(cmd=='1'){
    rv=1;
    Serial.println("rv is 1");
    }
   if(cmd=='2'){
    rv=2;
    Serial.println("rv is 2");
    }
   if(cmd=='3'){
    rv=3;
    Serial.println("rv is 3");
    delay(100);
    }
    if(cmd=='4'){
    rv=4;
    Serial.println("rv is 4");
    }
   if(cmd=='5'){
    rv=5;
    Serial.println("rv is 5");
    }
   if(cmd=='6'){
    rv=6;
    Serial.println("rv is 6");
    }
   if(cmd=='7'){
    rv=7;
    Serial.println("rv is 7");

    }
   if(cmd=='8'){
    rv=8;
    Serial.println("rv is 8");
    }
    if(cmd=='9'){
    rv=9;
    Serial.println("rv is 9");

    }
    v=(1.16/9.)*rv+1.1;
  }
if (cmd == 'q'){
  Serial.println("10 degrees to the left");
  leftTurn(10,wv);
  }
  if (cmd == 'u'){
  Serial.println("10 degrees to the right");
  rightTurn(10,wv);
  }
  if(cmd== 'v'){
    Serial.println("180 degree turn");
    rightTurn(180,wv);
    }
 middleRead=!digitalRead(LTMiddle);
 rightRead=!digitalRead(LTRight);
 leftRead=!digitalRead(LTLeft);
 Serial.println(middleRead);
 if (middleRead=="HIGH"){
  forward(d,v);
  }
 else if (leftRead=="HIGH"){
  leftTurn(deg,wv);
  while(leftRead==1);
  }
  else if (rightRead=="HIGH"){
  rightTurn(deg,wv);
  while(rightRead==1);
  }
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
t=d/v*1000;
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
