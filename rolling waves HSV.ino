// Подключаем библиотеку FastLED.
#include "FastLED.h"
// Указываем, какое количество пикселей у нашей ленты.
#define LED_COUNT 240
 
// Указываем, к какому порту подключен вход ленты DIN.
#define LED_PIN 6
#define sat 255
#define val 100
#define wave_len 15 

// Создаем переменную strip для управления нашей лентой.
CRGB strip[LED_COUNT];
int k = 0;
int step;
void setup()
{
  FastLED.addLeds<WS2812B, LED_PIN, RGB>(strip, LED_COUNT);
  step = 255 / wave_len;
  Serial.begin(9600);
}
 
void loop()
{
  int my_delay =  analogRead(A3);
  Serial.println(my_delay);
  for (int i = 0; i < LED_COUNT ; i++)
  { int pos = (i + k) % wave_len;
    strip[i].setHSV(pos * step, sat, val) ; }
  
  k += 1;
  FastLED.show();
  delay(map(my_delay, 0, 1000, 10, 1000));

}