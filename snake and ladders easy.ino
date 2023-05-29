
#include "FastLED.h"
#define LED_COUNT 240
 

#define LED_PIN 6
#define sat 255
#define val 100
enum {ROAD_B=30, PLAYER_B=150, ENTER_B=70, EXIT_B=} brightness;
enum {ROAD_C, PLAYER1_C, PLAYER2_C, PLAYER3_C, PLAYER4_C, PLAYER5_C, SNAKE_START_C, SNAKE_FINISH_C, LADDER_START_C=130, LADDER_FINISH_C} colors;

struct Pixel{
  int color;
  int saturation;
  int brightness;
};
struct Tyle{
  int type_type;
  Pixel pixel;
};


CRGB strip[LED_COUNT];
Tyle level[LED_COUNT];

int n_players;
void setup()
{
  FastLED.addLeds<WS2812B, LED_PIN, RGB>(strip, LED_COUNT);
  Serial.begin(9600);
  n_players = get_players();
  // инициализация пустого уровня
  for (int i = 0; i < LED_COUNT ; i++){
    Pixel p = {0, sat, val};
    tyle_type = EMPTY; 
    Tyle t = {tyle_type, p};
    level[i] = t;
  }
  // ladders
  for (int i = 0; i < 4 ; i++){
    Pixel p = {0, sat, val};
    tyle_type = EMPTY; 
    Tyle t = {tyle_type, p};
    level[i] = t;
  }
}
 
void loop()
{
  for (int i = 0; i < LED_COUNT ; i++)
  { int pos = (i + k) % wave_len;
    strip[i].setHSV(pos * step, sat, val) ; }
  
  k += 1;
  FastLED.show();
  delay(10);

}
int get_players(){
  return 2
}