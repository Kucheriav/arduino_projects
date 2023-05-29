
#include "FastLED.h"
#define LED_COUNT 240
 

#define LED_PIN 6
#define sat 255
#define val 100
#define wave_len 15 
enum {EMPTY, PLAYER, SNAKE_START, SNAKE_FINISH, LADDER_START, LADDER_FINISH} tyle_type;
struct Pixel{
  int color;
  int saturation;
  int brightness;
}
struct Tyle{
  int type_type;
  Pixel pixel;
  
}
class Level{
  public:
    byte level_number;
    byte[] snake_start_pos;
    byte[] snake_end_pos;
    byte[] ladder_start_pos;
    byte[] ladder_end_pos;
    Level(byte _number, int _pixels_n);
    void update_map();
    void move_player(byte pos, byte color)
  private:
    int pixels_n;
    int level_color_map[];
    byte snake_color;
    byte ladder_color;
    byte level_color;

  }

Level::Level(byte _number, int _pixels_n){
  level_number = _number;
  pixels_n = _pixels_n;

  int level_color_map[pixels_n];


}
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
  for (int i = 0; i < LED_COUNT ; i++)
  { int pos = (i + k) % wave_len;
    strip[i].setHSV(pos * step, sat, val) ; }
  
  k += 1;
  FastLED.show();
  delay(10);

}