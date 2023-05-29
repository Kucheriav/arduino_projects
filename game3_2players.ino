#include "GyverOLED.h"
#include "FastLED.h"
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

#define max_level 5



GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
CRGB strip[LED_COUNT];
int map1D[LED_COUNT];
int pl1_pos = 2;
int pl2_pos = LED_COUNT - 2;
int pl1_vector = 1;
int pl2_vector = -1;
int draw1 = LOW;
int draw2 = LOW;
int score1 = 0;
int score2 = 0;
int level_color = 0;
int colors[4] = {level_color, level_color, 96, 160};
float my_delay;

int level_n;
uint32_t btnTimer = 0;
uint32_t game_loop_timer = 0;
extern uint8_t TinyFont[];

void setup()
{ oled.init();        // инициализация
  oled.clear();       // очистка
  oled.setScale(3);   // масштаб текста (1..4)
  oled.home();
  pinMode(pl1_pin, INPUT);
  pinMode(pl2_pin, INPUT); 
  FastLED.addLeds<WS2812B, LED_PIN, RGB>(strip, LED_COUNT);
  level_n = 1; 
  generate();
  Serial.begin(9600);
  
}
 
void loop()
{
  draw1 = digitalRead(pl1_pin);
  draw2 = digitalRead(pl2_pin);
  check_buttons();
  
  if (millis() - game_loop_timer > my_delay){
    game_loop_timer = millis();
    pl1_pos += pl1_vector;
    if (pl1_pos == 1 or pl1_pos == LED_COUNT - 1){
      pl1_vector *= -1;
    }
  
    pl2_pos += pl2_vector;
    if (pl2_pos == 1 or pl2_pos == LED_COUNT - 1){
      pl2_vector *= -1;
    }
    
    update_map();
    strip[pl1_pos].setHSV(colors[pl1_tile], sat, 255);
    strip[pl2_pos].setHSV(colors[pl2_tile], sat, 255);
    FastLED.show();
    oled.setCursor(0, 2);
    oled.print(score2);
    oled.setCursor(100, 2);
    oled.print(score1);
  }
  
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

void check_buttons(){
  if (millis() - btnTimer > my_delay){
    btnTimer = millis();
    if (draw1 == HIGH){
      for (int i = -1; i < 2; i ++){
          if (map1D[pl1_pos + i] == gap_tile){
              map1D[pl1_pos + i] = pl1_tile;
              score1 += 1;
          }else if (map1D[pl1_pos + i] == pl1_tile){
              map1D[pl1_pos + i] = gap_tile;
              score1 -= 1;
          }
      }  
    }

    if (draw2 == HIGH){
      for (int i = -1; i < 2; i ++){
        if (map1D[pl2_pos + i] == gap_tile){
            map1D[pl2_pos + i] = pl2_tile;
            score2 += 1;
        }else if (map1D[pl2_pos + i] == pl2_tile){
            map1D[pl2_pos + i] = gap_tile;
            score2 -= 1;
        }
      }
    }
  }
}

void update_map(){
for (int i = 0; i < LED_COUNT; i++)  { 
    strip[i].setHSV(colors[map1D[i]], sat, val * min(1, map1D[i])) ; 
  }
}