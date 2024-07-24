#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

char arriba[16];
char abajo[16];

void setup()
{
    lcd.init();
    lcd.backlight();
    for (int i = 0; i < 8; i++)
    {
      arriba[2*i] = '/';
      abajo[2*i + 1] = '/';
      arriba[2*i + 1] = 0xa4;
      abajo[2*i] = 164;
    }
    lcd.setCursor(0, 0);
    lcd.print(arriba);
    lcd.setCursor(0, 1);
    lcd.print(abajo);
}

void loop()
{ 
}


