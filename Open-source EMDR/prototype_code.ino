  //Do NOT use this code, this is not the current version with WIFI interface, convenient settings and everything, just a bare proof of concept.
  
  #include <FastLED.h>
    #define LED_PIN     7
    #define NUM_LEDS    30
    CRGB leds[NUM_LEDS];
    
    int num = 0; 
    int num1 = 0; 
    int freq = 100;
    int tick = 1000 / freq;
    void setup() {
      FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
      
    }
    void loop() { 
      if (num < 30){
      num1 = num - 1;
      leds[num] = CRGB(0, 255, 0);
      leds[num1] = CRGB(0, 0, 0);
      FastLED.show();
      num++;
      delay(tick);
    }
      else{
        
       while(num > 0){ 
        num1 = num - 1;
        leds[num] = CRGB(0, 0, 0);
        leds[num1] = CRGB(0, 255, 0);
        FastLED.show();
        num--;
        delay(tick);
      }
    }
    }
