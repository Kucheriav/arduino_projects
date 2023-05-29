// Подключаем библиотеку FastLED.
#include "FastLED.h"
 
// Указываем, какое количество пикселей у нашей ленты.
#define LED_COUNT 240
 
// Указываем, к какому порту подключен вход ленты DIN.
#define LED_PIN 6
 
// Создаем переменную strip для управления нашей лентой.
CRGB strip[LED_COUNT];
int k = 0;
void setup()
{
  FastLED.addLeds<WS2812B, LED_PIN, RGB>(strip, LED_COUNT);
}
 
void loop()
{
  for (int i = 0; i < LED_COUNT; i++)
  { if ((i + k) % 12 == 0){
      strip[i].setRGB(20, 0, 0);}
    if ((i + k) % 12 == 1){
      strip[i].setRGB(255, 0, 0);}
    if ((i + k) % 12 == 2){
      strip[i].setRGB(20, 0, 0);}
    if ((i + k) % 12 == 3){
      strip[i].setRGB(0, 0, 0);}
    if ((i + k) % 12 == 4){
      strip[i].setRGB(0, 20, 0);}
    if ((i + k) % 12 == 5){
      strip[i].setRGB(0, 255, 0);}
    if ((i + k) % 12 == 6){
      strip[i].setRGB(0, 20, 0);}
    if ((i + k) % 12 == 7){
      strip[i].setRGB(0, 0, 0);}
    if ((i + k) % 12 == 8){
      strip[i].setRGB(0, 0, 20);}
    if ((i + k) % 12 == 9){
      strip[i].setRGB(0, 0, 255);}
    if ((i + k) % 12 == 10){
      strip[i].setRGB(0, 0, 20);}
    if ((i + k) % 12 == 11){
      strip[i].setRGB(0, 0, 0);}  
  }
  k += 1;
  FastLED.show();
  delay(100);

  FastLED.show();


}