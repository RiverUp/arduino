#include<LiquidCrystal.h>
const int inputPin =A1;
const int powerPinlcd=13;
LiquidCrystal lcd(12,11,10,9,8,7,6,5,4,3,2);
void setup()
{
    lcd.begin(16,2);    
    lcd.noCursor();
    lcd.noBlink();
    lcd.clear();
    digitalWrite(powerPinlcd,HIGH);
    Serial.begin(9600);
}
void loop()
{
    lcd.clear();
    lcd.print("Arduino!");
    lcd.setCursor(0,2);
    lcd.print("Welcome!");
    judgeLight();    
    delay(1000);

}
void judgeLight()
{
    delay(10);
    int reading=analogRead(inputPin);
    Serial.println(reading);
    if (reading<=5)
    {
        digitalWrite(powerPinlcd, LOW);
    }
    else
    {
        digitalWrite(powerPinlcd,HIGH);
    }
    
}