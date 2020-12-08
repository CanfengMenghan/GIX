  
/*
* 发射红外线讯号
*     注意! 红外线发射器(IR LED)必须接到 pin 3, 不能接其它脚位，头文件已经定义，所以下面不用设置pin3口的状态
*/
#include <IRremote.h>                  // 引用 IRRemote 函式库
                            
const int buttonPin = 4;                 // 按键(pushbutton)接在 pin 4
int buttonState = 0;                     // 按键状态
                            
IRsend irsend;                          // 定义 IRsend 物件来发射红外线讯号
                            
void setup()
{
  Serial.begin(9600);
pinMode(buttonPin, INPUT);             // 把 buttonPin 设置成 输入
}
                            
void loop()
{
  /*
// 读取按键状态
buttonState = digitalRead(buttonPin);
                    
// 检查按键是否被按下
// 有的话 buttonState 会是高电平输出
if (buttonState == HIGH) 
// 发射红外线讯号
*/
irsend.sendNEC(0x00FF6897, 32);   // 这个编码即你按的键（接pin4）的编码，可以随意更改，如果要控制其他设备，只需将此编码改为相应编码就行
Serial.println("a");
delay(500);

}
