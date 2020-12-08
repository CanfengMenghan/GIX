#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor
const int TrigPin = 13; //发出超声波
//const int EchoPin = A1; //收到反射回来的超声波
#define EchoPin A1
float cm1; //因为测得的距离是浮点型的
float cm2; //因为测得的距离是浮点型的
float time1;
float time2;
float velocity;
float delta_velocity;
float rpm;
int timing0;
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 7, 8, 9, 10);

#include <IRremote.h>
int control=0;
int RECV_PIN = 4;//定义红外接收器的引脚为11
#define RECV_PIN A2
IRrecv irrecv(RECV_PIN);
decode_results results;
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);  //定义脚位
int timing;
float elapse;

#include <math.h>


void setup() {
  lcd.begin(16,2); //设置LCD显示的数目。16 X 2：16格2行。
lcd.setCursor(0,0);
lcd.print("hello,world!"); //将hello,world!显示在LCD上
analogWrite(6,150);//contrast
  // set the speed at 60 rpm:
  myStepper.setSpeed(0);
  irrecv.enableIRIn(); // Start the receiver
  // initialize the serial port:
  Serial.begin(9600);
    pinMode(TrigPin, OUTPUT); 
  pinMode(EchoPin, INPUT);

digitalWrite(TrigPin, LOW); //低高低电平发一个短时间脉冲去TrigPin 
  delayMicroseconds(2);       // delayMicroseconds在更小的时间内延时准确
  digitalWrite(TrigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TrigPin, LOW); //通过这里控制超声波的发射
  
  cm2 = pulseIn(EchoPin, HIGH) / 58.0; //将回波时间换算成cm 
  Serial.print("Distance:"); 
  Serial.print(cm2); 
  Serial.print("cm"); 
  Serial.println(); 
  time2=millis();
  delay(50); 

}

void loop() {

  if (irrecv.decode(&results)) {
    //Serial.println(results.value,HEX);
    if(results.value==0xFF30CF) //此处的32位值与发射部分发射的值要保持一致
{
  if (control==0)

{control=1;
timing0=millis();
}
}
}

if (control==1)
{
  analogWrite(6,150);
  timing=millis()-timing0;
elapse=int(timing%13000);
if (elapse<5000)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Green to ");
lcd.print(int((5000-elapse)/1000)+1);
//delay(1000);
}

else if(elapse<8000)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Yellow");
//delay(3000);
}
else
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Red to ");
lcd.print(int((13000-elapse)/1000)+1);
//delay(1000);
}
  // step one revolution  in one direction:
  cm1=cm2;
  digitalWrite(TrigPin, LOW); //低高低电平发一个短时间脉冲去TrigPin 
  delayMicroseconds(2);       // delayMicroseconds在更小的时间内延时准确
  digitalWrite(TrigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TrigPin, LOW); //通过这里控制超声波的发射
  
  cm2 = pulseIn(EchoPin, HIGH) / 58.0; //将回波时间换算成cm 
  Serial.print("Distance:"); 
  Serial.print(cm2); 
  Serial.print("cm"); 
  Serial.println(); 
  time1=time2;
  time2=millis();
  delta_velocity=(cm2-cm1)/(time2-time1);
  velocity=velocity+delta_velocity;
  rpm=30*velocity/2/3.1415/0.03;
  //rpm=25/(1+powf(2.71828, -velocity))+75;
    Serial.println(rpm); 
    if (rpm<0)
    {rpm=0;
    }
   rpm=10*rpm;
    myStepper.setSpeed(rpm);
    myStepper.step(rpm);
   }
    
  if (control==1) 
  { 
if (irrecv.decode(&results)) {
    Serial.println(results.value,HEX);
    if(results.value==0xFF30CF) //此处的32位值与发射部分发射的值要保持一致
    {
  control=0;
    }
}
  }
}
