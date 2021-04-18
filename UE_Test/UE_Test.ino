
#include <M5StickC.h>
#define LED_PIN 10
#define BUTTON_PIN 37

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

    pinMode(BUTTON_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    buttonread = digitalRead(BUTTON_PIN);
    // if (!Serial.available())
    //     return;
    // String str = Serial.readString();

    if (buttonread)
    {
        digitalWrite(LED_PIN, 1);
    }
    else
    {
        digitalWrite(LED_PIN, 0);

        // int len=12;
        // Serial.println(len);
        float fVal = 12.34f;
        byte *fBuffer = reinterpret_cast<byte *>(&fVal);
        Serial.write(fBuffer, 4);

        delay(100);
    }
}