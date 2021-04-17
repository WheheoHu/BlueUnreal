
#include <M5StickC.h>

#include <BlueMagic32.h>

#define BUTTON_PIN 0

int buttonState;           // the current reading from the input pin
int lastButtonState = LOW; // the previous reading from the input pin
int loopcount = 0;

unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 50;   // the debounce time; increase if the output flickers

void setup()
{
    M5.begin();
    M5.IMU.Init();

    M5.Lcd.setRotation(1);

    M5.Lcd.setTextColor(TFT_WHITE); // Adding a background colour erases previous text automatically

    M5.Lcd.setCursor(10, 30);
    M5.Lcd.setTextSize(2);
    M5.Lcd.print("TRY CONNECT");

    BMDConnection.begin("AA");

   // BMDControl = BMDConnection.connect();

    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.print("TEST");

    pinMode(BUTTON_PIN, INPUT);
}

void loop()
{
    
    M5.Lcd.setCursor(10, 30);
    M5.Lcd.setTextSize(3);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.print(loopcount);
    Serial.println("TEST Serial");
    loopcount++;
    delay(1000);
    // int reading = digitalRead(BUTTON_PIN);

    // // If the switch changed, due to noise or pressing:
    // if (reading != lastButtonState)
    // {
    //     lastDebounceTime = millis();
    // }

    // if ((millis() - lastDebounceTime) > debounceDelay)
    // {
    //     if (reading != buttonState)
    //     {
    //         buttonState = reading;

    //         // only toggle the LED if the new button state is HIGH
    //         if (buttonState == HIGH)
    //         {
    //             if (BMDConnection.available())
    //             {
    //                 BMDControl->toggleRecording();
    //             }
    //         }
    //     }
    // }
    // lastButtonState = reading;
}
