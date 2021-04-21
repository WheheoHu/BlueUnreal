
#include <M5StickC.h>
#define LED_PIN 10


int buttonread = 0;
void setup()
{
    M5.begin();
    M5.IMU.Init();

    M5.Lcd.setRotation(1);

    M5.Lcd.setTextColor(TFT_WHITE); // Adding a background colour erases previous text automatically

    M5.Lcd.setCursor(10, 30);
    M5.Lcd.setTextSize(2);
    M5.Lcd.print("Boot");
    Serial.setTimeout(5);
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{

    // if (!Serial.available())
    //     return;
    // String str = Serial.readString();

    // if (buttonread)
    // {
    //     digitalWrite(LED_PIN, 1);
    // }
    // else
    // {
    //     digitalWrite(LED_PIN, 0);

    //     // int len=12;
    //     // Serial.println(len);
    //     float fVal = 12.34f;
    //     byte *fBuffer = reinterpret_cast<byte *>(&fVal);
    //     Serial.write(fBuffer, 4);
    // }
    if (Serial.available())
    {
        String str = Serial.readString();
        if (str = "lines")
        {
            float fVal = 12.34f;
            byte *fBuffer = reinterpret_cast<byte *>(&fVal);
            Serial.write(fBuffer, 4);
            digitalWrite(LED_PIN,HIGH);
            M5.Lcd.fillScreen(TFT_BLACK);
            M5.Lcd.setCursor(10, 30);
            M5.Lcd.setTextSize(2);
            M5.Lcd.print("Lines");
        }
        else
        {
            /* code */
        }
        
    }
}