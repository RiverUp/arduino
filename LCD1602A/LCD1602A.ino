int DI=12;//数据/命令选择端
int RW=11;//读/写选择端
int DB[]{3,4,5,6,7,8,9,10};
int Enable=2;//使能端

void LcdCommandWrite(int value){
  int i=0;
  /*按D7~D0即arduinoDB[0]~DB[7]由高位到低位赋值*/
  for(i=DB[0];i<=DI;i++){
    digitalWrite(i,value&01);
    value>>=1;
  }
  digitalWrite(Enable,LOW);
  delayMicroseconds(1);
  digitalWrite(Enable,HIGH);
  delayMicroseconds(1);
  digitalWrite(Enable,LOW);
  delayMicroseconds(1);

}
void LcdDataWrite(int value){
  int i=0;
  digitalWrite(DI,HIGH);
  digitalWrite(RW,LOW);
  for(i=DB[0];i<=DB[7];i++){
    digitalWrite(i,value&01);
    value>>=1;
  }  
  digitalWrite(Enable,LOW);
  delayMicroseconds(1);
  digitalWrite(Enable,HIGH);
  delayMicroseconds(1);
  digitalWrite(Enable,LOW);
  delayMicroseconds(1);
}
void setup(){
  int i=0;
  for(i=Enable;i<=DI;i++){
    pinMode(i,OUTPUT);
  }
  delay(100);
  LcdCommandWrite(0x38);//设置为8位接口，2行显示，5*7文字大小
  delay(64);
  LcdCommandWrite(0x38);
  delay(50);
  LcdCommandWrite(0x38);
  delay(20);
  LcdCommandWrite(0x06);//自动增量，不显示移位
  delay(20);
  LcdCommandWrite(0x0E);//开启显示屏，光标显示，无闪烁
  delay(20);
  LcdCommandWrite(0x01);//屏幕清空，光标位置归零
  delay(100);
  LcdCommandWrite(0x80);//设置地址第一行头（80）（尾是A7）
  delay(20);

}
void loop(){
  LcdCommandWrite(0x01);
  delay(10);
  LcdCommandWrite(0x80+4);//从头移四位
  delay(10);
  LcdDataWrite('W');
  LcdDataWrite('e');
  LcdDataWrite('l');
  LcdDataWrite('c');
  LcdDataWrite('o');
  LcdDataWrite('m');
  LcdDataWrite('e');
  LcdDataWrite('!');
  delay(1000);
  LcdCommandWrite(0x01);
  delay(10);
  LcdCommandWrite(0xc0);//设置地址为第二行头（c0）（尾是E7）
  delay(10);
  LcdDataWrite('I');
  LcdDataWrite(' ');
  LcdDataWrite('L');
  LcdDataWrite('o');
  LcdDataWrite('v');
  LcdDataWrite('e');
  LcdDataWrite(' ');
  LcdDataWrite('A');
  LcdDataWrite('r');
  LcdDataWrite('d');
  LcdDataWrite('u');
  LcdDataWrite('i');
  LcdDataWrite('n');
  LcdDataWrite('o');
  LcdDataWrite('!');
  delay(5000);

}
