#include<LiquidCrystal.h>

LiquidCrystal lcd(12,11,2,3,4,5,6,7,8,9,10);
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
void setup()
{
    lcd.begin(16,2);    
    lcd.noCursor();
    lcd.noBlink();
    lcd.clear();
    DDRC|=_BV(DHT11_PIN);//设置为输入
    PORTC|=_BV(DHT11_PIN);//输入置一    
}
void loop()
{
    lcd.clear();
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
        lcd.print("get_error1");
        delay(2000);
        return;
    }
    delayMicroseconds(80);
    dht11_in=PINC&=_BV(DHT11_PIN);
    if (!dht11_in)
    {
       lcd.print("gett_error2");
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
        lcd.print("check_error");
        return;
    }
    lcd.print("humi is ");
    lcd.print(dht11_dat[0],DEC);
    lcd.print("%");
    lcd.setCursor(0,2);
    lcd.print("temp is ");
    lcd.print(dht11_dat[2],DEC);
    lcd.print("C");
    delay(5000);
}
