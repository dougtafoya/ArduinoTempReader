#include <math.h>

double getTemp(int RawADC) 
{
    double Temp;
    Temp = log(10000.0*((1024.0/RawADC-1))); 
    Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
    Temp = Temp - 273.15;            // Convert Kelvin to Celcius
    Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
    return Temp;
}

void setup() 
{
    Serial.begin(9600);
    int temp = int(getTemp(analogRead(0)));
    Serial.print(String(temp));
}

void loop() 
{
    int temp = int(getTemp(analogRead(0)));
    Serial.print(String(temp));
    
    delay(750);
}
