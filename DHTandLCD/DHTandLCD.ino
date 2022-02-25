int DI=12;//数据/命令选择端
int RW=11;//读/写选择端
int DB[]{3,4,5,6,7,8,9,10};
int Enable=2;//使能端
#define DHT11_PIN 0
byte read_dht11_dat()
{
    byte i=0;
    byte result=0;
    for ( i = 0; i < 8; i++)
    {
        while (!(PINC&_BV(DHT11_PIN)));
        delayMicroseconds(30);
        if (PINC&_BV(DHT11_PIN))
        {
            result|=(1<<(7-i));
        }
        while((PINC&_BV(DHT11_PIN)));
        
    }
    return result;
}
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
void LcdDataWriteString(String value){
    for (byte i = 0; i < value.length(); i++)
    {
        LcdDataWrite(value.charAt(i));
    }
    
}
String BinaryToDecimal(byte bin)
{
  byte res=0;
  for (int i = 0; i < 8; i++)
  {  
    byte bas=bin&_BV(i);
    for (; i > 0; i--)
    {
      bas*=2;
    }
    res+=bas;
  }
  return String(res);
}
void setup(){
  Serial.begin(19200);
  int i;
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

  DDRC|=_BV(DHT11_PIN);//设置为输入
  PORTC|=_BV(DHT11_PIN);//输入置一


}

void loop()
{
    LcdCommandWrite(0x01);
    delay(10);
    byte dht11_dat[5];
    byte dht11_in;
    byte i;
    PORTC&=~_BV(DHT11_PIN);//输入置零
    delay(18);
    PORTC|=_BV(DHT11_PIN);
    delayMicroseconds(40);
    DDRC&=~_BV(DHT11_PIN);
    delayMicroseconds(40);
    dht11_in=PINC&_BV(DHT11_PIN);
    if (dht11_in)//如果是高电平
    {
        LcdDataWriteString("get_error1");
        delay(2000);
        return;
    }
    delayMicroseconds(80);
    dht11_in=PINC&=_BV(DHT11_PIN);
    if (!dht11_in)
    {
        LcdDataWriteString("gett_error2");
        return;
    }
    delayMicroseconds(80);
    for ( i = 0; i < 5; i++)//读取数据
    {
        dht11_dat[i]=read_dht11_dat();
    }
    DDRC|=_BV(DHT11_PIN);
    PORTC|=_BV(DHT11_PIN);
    byte dht11_check_sum=dht11_dat[0]+dht11_dat[1]+dht11_dat[2]+dht11_dat[3]  ;
    if(dht11_check_sum!=dht11_dat[4])  
    {
        LcdDataWriteString("check_error");
    }
    LcdDataWriteString("humi is ");
    LcdDataWriteString(BinaryToDecimal(dht11_dat[0]));
    LcdDataWriteString("%");
    LcdCommandWrite(0xc0);
    LcdDataWriteString("temp is ");
    LcdDataWriteString(BinaryToDecimal(dht11_dat[3]));
    LcdDataWriteString("C");   
    
    delay(5000);
}
