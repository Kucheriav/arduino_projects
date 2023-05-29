#include "GyverOLED.h"
#include "math.h"
 

#define LED_COUNT 40
#define LED_PIN 6

#define sat 255
#define val 100
#define pl1_pin 4
#define pl2_pin 5

#define gap_tile 0
#define level_tile 1
#define pl1_tile 2
#define pl2_tile 3
int level_color = 0;
int colors[4] = {level_color, level_color, 96, 160};
#define max_level 5

class Player{
  public:
    byte _color;
    byte _pos;
    byte _score;
    Player(byte pin, byte pos, byte vector, byte color);
    void update();

  private:
    byte _pin;
    int _isClicked;
    byte _vector;
    uint32_t _btnTimer;
    void move();
    void checkClick();
    

};


GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
Player player1(pl1_pin, 2, 1, 96);
Player player2(pl2_pin, LED_COUNT-2, -1, 160);
CRGB strip[LED_COUNT];
int map1D[LED_COUNT];
float my_delay;

int level_n;
uint32_t game_loop_timer = 0;
extern uint8_t TinyFont[];

void setup()
{ oled.init();        // инициализация
  oled.clear();       // очистка
  oled.setScale(3);   // масштаб текста (1..4)
  oled.home();
  FastLED.addLeds<WS2812B, LED_PIN, RGB>(strip, LED_COUNT);
  level_n = 1; 
  generate();
  Serial.begin(9600);
}
 
void loop()
{
    update_map();
    strip[player1._pos].setHSV(player1._color, sat, 255);
    strip[player2._pos].setHSV(player2._color, sat, 255);
    FastLED.show();
    oled.setCursor(0, 2);
    oled.print(player2._score);
    oled.setCursor(100, 2);
    oled.print(player1._score);
  
  
  if (win_check() == true){
    level_n += 1;
    generate();
  };

}
bool win_check(){
  int is_finish = 1;
  int win_color;
  for (int i = 0; i < LED_COUNT; i++)
  { 
    if (map1D[i] == 0){
      is_finish = 0;
    }
  }
  if (is_finish == 1){
    if (score1 > score2){
      win_color = pl1_tile;
     }else if (score1 < score2){
      win_color = pl2_tile;
    } else {
      win_color = level_tile;
    }
    for (int j = 0; j < 3; j++){
        for (int i = 0; i < LED_COUNT; i++)
          { 
            strip[i].setHSV(colors[win_color], sat, 255) ; 
          }
        FastLED.show();
        delay(100);
        FastLED.clear();
        FastLED.show();
        delay(100);
      }
  return true;}
      else{
    return false;
        }
}
void generate(){
  my_delay = 500 - log10(level_n) / 2 * 1000;
  level_color = (level_n - 1) * (255 / max_level);
  colors[1] = level_color;
  for (int i = 0; i < LED_COUNT; i++){
    map1D[i] = 1;
  }
  int counter = 0;
  while (counter < (LED_COUNT / 3 / max_level * level_n)){
    int x = random(1, LED_COUNT -1);
    if (map1D[x] == 1){
      map1D[x - 1] = 0;
      map1D[x] = 0;
      map1D[x + 1] = 0;
      counter += 1;
    }
  }
}



void update_map(){
for (int i = 0; i < LED_COUNT; i++)  { 
    strip[i].setHSV(colors[map1D[i]], sat, val * min(1, map1D[i])) ; 
  }
}

Player::Player(byte pin, byte pos, byte vector, byte color){
  _pin = pin;
  pinMode(_pin, INPUT);
  _isClicked = LOW;
  _pos = pos;
  _vector = vector;
  _score = 0;
  _color = color;
  _btnTimer = 0;
}


void Player::update(){
  _isClicked = digitalRead(_pin);
  void move();
  void checkClick();
}
void Player::move(){
  if (millis() - game_loop_timer > my_delay){
    game_loop_timer = millis();
    _pos += _vector;
    if (_pos == 1 or _pos == LED_COUNT - 1){
      _vector *= -1;
    } 
  }
}

void Player::checkClick(){
  if (millis() - _btnTimer > my_delay){
    _btnTimer = millis();
    if (_isClicked == HIGH){
      for (int i = -1; i < 2; i ++){
          if (map1D[_pos + i] == gap_tile){
              map1D[_pos + i] = pl1_tile;
              _score += 1;
          }else if (map1D[_pos + i] == pl1_tile){
              map1D[_pos + i] = gap_tile;
              _score -= 1;
          }
      }  
    }
  }
}