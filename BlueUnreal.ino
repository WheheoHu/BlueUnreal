
#include <M5StickC.h>

#include <BlueMagic32.h>

#define LED_PIN 10

int buttonState;           // the current reading from the input pin
int lastButtonState = LOW; // the previous reading from the input pin

unsigned long lastDebounceTime = 0; // the last time the output pin was toggled 最后一次切换输出引脚
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
    Serial.setTimeout(5);
    delay(1000);
    pinMode(LED_PIN,OUTPUT);
    digitalWrite(LED_PIN, HIGH);

}

void loop()
{
    //Serial.println("TEST Serial");

    //按键录制
    buttonRecording();

    //参数显示
    setOnScreen();

    if (Serial.available())
    {
        String str = Serial.readString();
        if (str="Aperture")
        {
            control_aperture();
        }
        
    }
    
}
void control_aperture(){
    float faperture_value=BMDControl->getAperture();
    write_float(faperture_value);
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
            printOnScreen(2, 0, "IRIS : F" + String(BMDControl->getAperture(), 1));
            printOnScreen(2, 16, "SHUTTER : " + String(BMDControl->getShutter()) + "°");
            printOnScreen(2, 32, "ISO : " + String(BMDControl->getIso()));
            printOnScreen(2, 48, "WB : " + String(BMDControl->getWhiteBalance()) + "K");
            printOnScreen(2, 64, "TINT : " + String(BMDControl->getTint()));
        }
    }
}

//屏幕显示
void printOnScreen(int x, int y, String text)
{
    M5.Lcd.setCursor(x, y, 2);
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(1);
    M5.Lcd.println(text);
}

void write_float(float fVal){
    byte *fBuffer = reinterpret_cast<byte *>(&fVal);
    Serial.write(fBuffer, 4);
}