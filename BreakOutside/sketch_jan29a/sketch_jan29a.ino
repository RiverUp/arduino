const int inputPin=A0;
const int powerPin=12;
void setup()
{
    pinMode(powerPin,OUTPUT);
    Serial.begin(9600);
}
void loop()
{
    Serial.println(takeReading());
    delay(500);
}
int takeReading()
{
    digitalWrite(powerPin, HIGH);
    delay(10);
    int reading=analogRead(inputPin);
    digitalWrite(powerPin, LOW);
    return reading;
}
