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
    DDRC|=_BV(DHT11_PIN);//设置为输入
    PORTC|=_BV(DHT11_PIN);//输入置一
    Serial.begin(19200);
    Serial.println("ready");
}

void loop()
{
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
        Serial.println("get_error1");
        return;
    }
    delayMicroseconds(80);
    dht11_in=PINC&=_BV(DHT11_PIN);
    if (!dht11_in)
    {
        Serial.println("gett_error2");
        return;
    }
    delayMicroseconds(80);
    for ( i = 0; i < 5; i++)
    {
        dht11_dat[i]=read_dht11_dat();
    }
    DDRC|=_BV(DHT11_PIN);
    PORTC|=_BV(DHT11_PIN);
    byte dht11_check_sum=dht11_dat[0]+dht11_dat[1]+dht11_dat[2]+dht11_dat[3]  ;
    if(dht11_check_sum!=dht11_dat[4])  
    {
        Serial.println("check_error");
    }
    Serial.print("湿度为：");
    Serial.print(dht11_dat[0],DEC);
    Serial.print(".");
    Serial.print(dht11_dat[1],DEC);
    Serial.print("%");
    Serial.print("温度为：");
    Serial.print(dht11_dat[2],DEC);
    Serial.print(".");
    Serial.print(dht11_dat[3],DEC);
    Serial.print("C");
    Serial.print("\n");

    delay(2000);
}
