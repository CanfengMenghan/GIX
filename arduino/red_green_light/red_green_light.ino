#include <IRremote.h>
int control=0;
int RECV_PIN = 13;//定义红外接收器的引脚为11
IRrecv irrecv(RECV_PIN);
decode_results results;
#define Red_light 7
#define Yellow_light 8
#define Green_light 9
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);  //定义脚位
int timing;
float elapse;
int timing0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); //设置波特率
irrecv.enableIRIn();
pinMode(Red_light, OUTPUT);
pinMode(Yellow_light, OUTPUT); 
pinMode(Green_light, OUTPUT);
lcd.begin(16,2); //设置LCD显示的数目。16 X 2：16格2行。
lcd.print("hello,world!"); //将hello,world!显示在LCD上
analogWrite(6,150);
}

void loop() {

  // put your main code here, to run repeatedly:
if (irrecv.decode(&results)) {
    Serial.println(results.value,HEX);
    if(results.value==0xFF6897) //此处的32位值与发射部分发射的值要保持一致
{
  if (control==0)
  {timing0=millis();
  control=1;}

}
}
if (control==1)
{
timing=millis()-timing0;
elapse=int(timing%13000);
if (elapse<5000)
{
digitalWrite(Red_light,LOW);
digitalWrite(Yellow_light,LOW);
digitalWrite(Green_light,HIGH);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Green to ");
lcd.print(int((5000-elapse)/1000)+1);
delay(1000);
}

else if(elapse<8000)
{
digitalWrite(Red_light,LOW);
digitalWrite(Yellow_light,HIGH);
digitalWrite(Green_light,LOW);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Yellow");
delay(3000);
}
else
{
digitalWrite(Red_light,HIGH);
digitalWrite(Yellow_light,LOW);
digitalWrite(Green_light,LOW);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Red to ");
lcd.print(int((13000-elapse)/1000)+1);
delay(1000);
}
}
}
