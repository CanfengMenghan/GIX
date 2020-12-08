//本例来自于红外接收模块的IRremote自带范例
//已经作出了修改
//改为当有遥控器的按键按下时,接在数字引脚4上的发光LED就会点亮，再按一下按键，led熄灭
/*电路连接
 *红外接收器的VOUT接在数字引脚11上,GND接控制板的GND,VCC接控制板上+5V
*发光二极管引脚接在数字引脚4上,通过220欧姆电阻回到控制板的GND
*效果,当遥控器按下按键时,发光二极管就会闪烁,同时电脑的串口会出现按键的命令编码.
*/
 
#include <IRremote.h>
  
int RECV_PIN = 11;//定义红外接收器的引脚为11
int LED_PIN=4;//定义发光LED引脚数字4
int a=0;
IRrecv irrecv(RECV_PIN);
  
decode_results results;
  
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // 初始化红外接收器
  pinMode(LED_PIN,OUTPUT);//设置发光LED引脚数字4
}
  
void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value,HEX);
if(results.value==0xFF6897 &a==0) //此处的32位值与发射部分发射的值要保持一致
{
    digitalWrite(LED_PIN,HIGH);//LED点亮
    
a=1;
Serial.println(a);
}
else if(results.value==0xFF6897 &a==1)
{
digitalWrite(LED_PIN,LOW);//LED熄灭
a=0;
}
    irrecv.resume(); // 接收下一个值
  }
}
