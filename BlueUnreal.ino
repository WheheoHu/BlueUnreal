
#include <M5StickC.h>

#include <BlueMagic32.h>

#define LED_PIN 10

int buttonState;           // the current reading from the input pin
int lastButtonState = LOW; // the previous reading from the input pin

unsigned long debounceDelay = 50;   // the debounce time; increase if the output flickers

float fAperture_value = 0;
float fShutter_value = 0;
int32_t iISO_value = 0;
int16_t iWhiteBalance_value = 0;
int16_t iTint_value = 0;

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
    Serial.setTimeout(5);
    delay(1000);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
}

void loop()
{
    collect_data();
    //按键录制
    buttonRecording();

    //参数显示
    setOnScreen();

    if (!Serial.available())
        return;

    String str = Serial.readString();
    if (str == "Aperture")
    {
        write_float(fAperture_value);
    }
    else if (str == "Shutter")
    {
        write_float(shutter_angle_to_speed(24.0f, fShutter_value));
    }
    else if (str == "ISO")
    {
        write_int32(iISO_value);
    }
    else if (str == "WB")
    {
        write_int16(iWhiteBalance_value);
    }
    else if (str == "TINT")
    {
        write_int16(iTint_value);
    }
}

//按键录制
void buttonRecording()
{
    if (BMDConnection.available())
    {
        if (M5.BtnA.wasPressed())
        {
            BMDControl->toggleRecording();
        }
        if (BMDControl->isRecording())
        {
            M5.Lcd.setTextColor(RED);
            digitalWrite(LED_PIN, LOW);
        }
        else
        {
            M5.Lcd.setTextColor(TFT_WHITE);
            digitalWrite(LED_PIN, HIGH);
        }
    }
}

//参数显示
void setOnScreen()
{
    M5.update();

    if (M5.BtnB.wasPressed())
    {
        ESP.restart();
    }

    if (BMDConnection.available())
    {

        if (BMDControl->changed())
        {

            M5.Lcd.fillScreen(TFT_BLACK);
            printOnScreen(2, 0, "IRIS : F" + String(fAperture_value, 1));
            printOnScreen(2, 16, "SHUTTER : " + String(fShutter_value) + "°");
            printOnScreen(2, 32, "ISO : " + String(iISO_value));
            printOnScreen(2, 48, "WB : " + String(iWhiteBalance_value) + "K");
            printOnScreen(2, 64, "TINT : " + String(iTint_value));
        }
    }
}
//collect camera data 
void collect_data()
{
    fAperture_value = BMDControl->getAperture();
    fShutter_value = BMDControl->getShutter();
    iISO_value = BMDControl->getIso();
    iWhiteBalance_value = BMDControl->getWhiteBalance();
    iTint_value = BMDControl->getTint();
}

//屏幕显示
void printOnScreen(int x, int y, String text)
{
    M5.Lcd.setCursor(x, y, 2);
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(1);
    M5.Lcd.println(text);
}

//write a float value to Serial
void write_float(float fVal)
{
    byte *fBuffer = reinterpret_cast<byte *>(&fVal);
    Serial.write(fBuffer, 4);
}

//convert shutter angle value (degree) to shutter speed value (1/s)
float shutter_angle_to_speed(float fFrameRate, float fShutter_Angle_value)
{
    return 360.0f * fFrameRate / fShutter_Angle_value;
}

//write a int 32 value to serial
void write_int32(int32_t iVal)
{
    byte iBuffer[] = {
        byte(iVal & 0xff),
        byte(iVal >> 8 & 0xff),
        byte(iVal >> 16 & 0xff),
        byte(iVal >> 24 & 0xff)};
    Serial.write(iBuffer, 4);
}

//wirte a int 16 value to serial
void write_int16(int16_t iVal)
{
    byte iBuffer[] = {
        byte(iVal & 0xff),
        byte(iVal >> 8 & 0xff)};
    Serial.write(iBuffer, 2);
}