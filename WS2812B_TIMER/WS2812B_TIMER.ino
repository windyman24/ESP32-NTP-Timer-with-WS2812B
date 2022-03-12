#include <WS2812FX.h>
#include <WiFi.h>
#include <time.h>
const char* ssid = "Your Wifi SSID";
const char* password = "Your Wifi PASSWORD";
//NTP Time
int timezone = 8 * 3600;//Set Time zone ,In Taiwan is +8, so Time zone is 8 * 3600
int dst = 0;
time_t now = time(nullptr);
struct tm* p_tm = localtime(&now);
//WS2812B define
#define LED_COUNT 30
#define LED_PIN 4
#define OFF 0x000000
#define TIMER_MS 5000

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

unsigned long LightColor = 0x006633;
int Def_min = 0;
int Def_Second = 0;
int Second = 0;
int minu = 0;
int hour = 0;

//Set blink time without delay
unsigned long previousMillis = 0;
const long interval = 1000;
int DotState = false;// Dot State

bool GotTime = false;//Got NTP TIME Flag
/*
 * Control Dot ON or OFF
 */
void ShowDots(int EN)
{
  if (EN == true)
  {
    ws2812fx.setPixelColor(14, LightColor);
    ws2812fx.setPixelColor(15, LightColor);
  }
  else
  {
    ws2812fx.setPixelColor(14, OFF);
    ws2812fx.setPixelColor(15, OFF);
  }
}
/*
 * Set Number,Input which Seg and its number
 */
void ShowNumber(int SegNum, int num)
{
  int ShowSegNum = SegNum * 7;
  if (SegNum > 1)ShowSegNum += 2;
  switch (num)
  {
    case 0:
      ws2812fx.setPixelColor(0 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(1 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(2 + ShowSegNum, OFF);
      ws2812fx.setPixelColor(3 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(4 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(5 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(6 + ShowSegNum, LightColor);
      break;
    case 1:
      ws2812fx.setPixelColor(0 + ShowSegNum, OFF);
      ws2812fx.setPixelColor(1 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(2 + ShowSegNum, OFF);
      ws2812fx.setPixelColor(3 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(4 + ShowSegNum, OFF);
      ws2812fx.setPixelColor(5 + ShowSegNum, OFF);
      ws2812fx.setPixelColor(6 + ShowSegNum, OFF);
      break;
    case 2:
      ws2812fx.setPixelColor(0 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(1 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(2 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(3 + ShowSegNum, OFF);
      ws2812fx.setPixelColor(4 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(5 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(6 + ShowSegNum, OFF);
      break;
    case 3:
      ws2812fx.setPixelColor(0 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(1 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(2 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(3 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(4 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(5 + ShowSegNum, OFF);
      ws2812fx.setPixelColor(6 + ShowSegNum, OFF);
      break;
    case 4:
      ws2812fx.setPixelColor(0 + ShowSegNum, OFF);
      ws2812fx.setPixelColor(1 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(2 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(3 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(4 + ShowSegNum, OFF);
      ws2812fx.setPixelColor(5 + ShowSegNum, OFF);
      ws2812fx.setPixelColor(6 + ShowSegNum, LightColor);
      break;
    case 5:
      ws2812fx.setPixelColor(0 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(1 + ShowSegNum, OFF);
      ws2812fx.setPixelColor(2 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(3 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(4 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(5 + ShowSegNum, OFF);
      ws2812fx.setPixelColor(6 + ShowSegNum, LightColor);
      break;
    case 6:
      ws2812fx.setPixelColor(0 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(1 + ShowSegNum, OFF);
      ws2812fx.setPixelColor(2 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(3 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(4 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(5 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(6 + ShowSegNum, LightColor);
      break;
    case 7:
      ws2812fx.setPixelColor(0 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(1 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(2 + ShowSegNum, OFF);
      ws2812fx.setPixelColor(3 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(4 + ShowSegNum, OFF);
      ws2812fx.setPixelColor(5 + ShowSegNum, OFF);
      ws2812fx.setPixelColor(6 + ShowSegNum, OFF);
      break;
    case 8:
      ws2812fx.setPixelColor(0 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(1 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(2 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(3 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(4 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(5 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(6 + ShowSegNum, LightColor);
      break;
    case 9:
      ws2812fx.setPixelColor(0 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(1 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(2 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(3 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(4 + ShowSegNum, LightColor);
      ws2812fx.setPixelColor(5 + ShowSegNum, OFF);
      ws2812fx.setPixelColor(6 + ShowSegNum, LightColor);
      break;
  }
}
/*
 * Set hour and minute ,and set to Seg
 */
int TimeConvert(int hour, int minu)
{
  int hour_H = hour / 10;
  int hour_L = hour % 10;
  int min_H = minu / 10;
  int min_L = minu % 10;

  ShowNumber(3, hour_H);
  ShowNumber(2, hour_L);
  ShowNumber(1, min_H);
  ShowNumber(0, min_L);

  ws2812fx.show();
}
void setup() {

  Serial.begin(115200);
  //Wifi setting and connect
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wifi Connected Success!");
  Serial.print("NodeMCU IP Address : ");
  Serial.println(WiFi.localIP() );
  
  
  ws2812fx.init();
  ws2812fx.setBrightness(1000);
  ws2812fx.setSpeed(SPEED_MIN);
  ws2812fx.setColor(LightColor);
  ws2812fx.setMode(FX_MODE_BREATH);
  ws2812fx.start();

  //Get the NTP time
  configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");
  Serial.println("\nWaiting for Internet time");

  Def_Second = p_tm->tm_sec;
  Def_min = p_tm->tm_min;
  Serial.print("Def_Second:");
  Serial.println(Def_Second);
  Serial.print("Def_min:");
  Serial.println(p_tm->tm_min);

  while (!GotTime) {
    configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");
    now = time(nullptr);
    p_tm = localtime(&now);
    Second = p_tm->tm_sec;
    minu = p_tm->tm_min;
    Serial.print("Second:");
    Serial.println(Second);
    Serial.print("min:");
    Serial.println(p_tm->tm_min);
    if (Def_min != minu)  GotTime = true;
    else Serial.print("*");
    demo();
  }
  
  Serial.println("\nTime response....OK");

  minu = p_tm->tm_min;
  hour = p_tm->tm_hour;
  Serial.print(hour);
  Serial.print(":");
  Serial.println(minu);
  TimeConvert(hour, minu);
}
/*
 * Use to reconnet the NTP time
 */
void CheckTime()
{
  configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");
  now = time(nullptr);
  p_tm = localtime(&now);
  Second = p_tm->tm_sec;
  minu = p_tm->tm_min;
}
/*
 * Use to demo show 0~9
 */
void demo()
{
  for (int i = 0; i < 10; i++)
  {
    ShowNumber(0, i);
    ShowNumber(1, i);
    ShowNumber(2, i);
    ShowNumber(3, i);
    ws2812fx.show();
    delay(300);
  }
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    Second++;
    if (Second > 59)
    {
      minu++;
      Second = 0;
    }
    if (minu > 59)
    {
      hour++;
      minu = 0;
      CheckTime();//every hour regulate the time
    }
    if (hour > 23)
    {
      hour = 0;
      minu = 0;
    }
    TimeConvert(hour, minu);
    ShowDots(DotState = !DotState);
    ws2812fx.setColor(LightColor++);
  }  
  yield();
}
