
#include <M5StickC.h>

#include <BlueMagic32.h>

#define BUTTON_PIN 37

int buttonState;           // the current reading from the input pin
int lastButtonState = LOW; // the previous reading from the input pin


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
   // BMDConnection.clearPairing();
    BMDConnection.begin("AA");

    BLEAddress pccadd = BLEAddress("90:FD:9F:C4:5F:C2");
    BMDControl = BMDConnection.connect(pccadd);

    M5.Lcd.setCursor(10, 30);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.print("Connected");
    delay(1000);
    pinMode(BUTTON_PIN, INPUT);
}

void loop()
{

   
    //Serial.println("TEST Serial");

    //state of button
    int reading = digitalRead(BUTTON_PIN);

    // If the switch changed, due to noise or pressing:
    if (reading != lastButtonState)
    {
        lastDebounceTime = millis();
        Serial.println(lastDebounceTime);
    }

    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        if (reading != buttonState)
        {
            buttonState = reading;

            // only toggle the LED if the new button state is HIGH
            if (buttonState == HIGH)
            {
                Serial.println("Rec");
                if (BMDConnection.available())
                {
                    BMDControl->toggleRecording();
                }
            }
        }
    }
    lastButtonState = reading;
}
