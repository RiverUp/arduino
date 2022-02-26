#include<Wire.h>
void setup()
{
    Wire.begin(4);
    Wire.onReceive(receiveEvent);
}

void loop()
{
    delay(100);
}

void receiveEvent()
{
    while (1<Wire.available())
    {
        char c=Wire.read();
        Serial.print(c);
    }
    int x=Wire.read();
    Serial.println(x);
    
}
