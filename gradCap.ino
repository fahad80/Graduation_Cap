/**
  ******************************************************************************
  * @file       main.c 
  * @author     Fahad Mirza
  * @version    V1.0
  * @date       09-July-2016
  * @modified   11-September-2016
  * @brief      Main program body
  ******************************************************************************
  */


#include <Adafruit_NeoPixel.h>
#define CONTROL_PIN 6


/****************************** Global Variables ******************************/
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(40, CONTROL_PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

uint32_t greenShade[15];  // For 15 different preset shades

/* Ignore the 'led' variable. I wanted to start all the animation from a specific 
 * pixel for the 16 LED ring. If you are a perfectionist freak like me I guess 
 * then you will evemtually figure out what you want and what to do. But for now
 * just ignore.
 */
uint16_t led[16]={26,25,24,39,38,37,36,35,34,33,32,31,30,29,28,27};


/****************************** Setup function ******************************/
void setup() 
{
  //Serial.begin(115200);
  strip.begin();
  strip.show();             // Initialize all pixels to 'off'
  strip.setBrightness(60);  // Limit overall brightness to 60% in order to lengethen the battery life 
  
  // Creating the green shades started from Zero to 150 with a stepping value of 10
  int index=0;
  for(int i = 0; i <= 150; i = i+10)
  {
      greenShade[index++]= strip.Color(0, i, 0);
  }
  
  pinMode(13, OUTPUT);
  digitalWrite(13,0);   // For debug. This will indicate the board indeed is working!
}


void loop() 
{
  int16_t x; // 'for' loop variables
  int16_t i;

  
/************ Animation 1: Fill the Pixels one after the other ************/
  colorWipe(strip.Color(0, 150, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 0), 50);   // off
  delay(1000);



/****************************** Animation 2 ******************************/
  glowingCircles(2,50)
  delay(1000);
  

  for(i=0; i<151;i=i+10)
  {
      theaterChase(strip.Color(0, i, 0), 50); // GREEN
  }
  for(i=150; i>=0;i=i-10)
  {
    //Serial.println(i);
    theaterChase(strip.Color(0, i, 0), 50); // GREEN
  }
  delay(1000);
  for(int k=0; k<2;k++)
  {
        for(int j=0; j<151;j=j+10)
        {
          for (i=0; i < strip.numPixels(); i++) 
          {
            strip.setPixelColor(i, strip.Color(0, j, 0));    //turn every third pixel on
          }
          strip.show();
    
          delay(50);
        }
        
        for(int j=150; j>=0; j=j-10)
        {
          for (i=0; i < strip.numPixels(); i++) 
          {
            strip.setPixelColor(i, strip.Color(0, j, 0));        //turn every third pixel off
          }
          strip.show();
          delay(50);
        }
  }
  delay(1000);

    
}


/*
 * @brief  Fill the Pixels(LEDs) one after the other with a color
 * @param  color_: 32bit color type, 
 *         wait  : delay in ms
 * @retval none
 */
void colorWipe(uint32_t color_, uint8_t wait)
{
  for(uint16_t i=0; i<24; i++) 
  {
    strip.setPixelColor(i, color_);
    strip.show();
    delay(wait);
  }
  
  // If you are ignoring 'led' variable then use the commented out code and comment out the other 'for' loop
 
  // for(uint16_t i=24; i<40; i++) 
  // {
  //    strip.setPixelColor(i, color_);
  //    strip.show();
  //    delay(wait);
  // }  
  
  for(uint16_t i=0; i<16; i++) 
  {
    strip.setPixelColor(led[i], color_);
    strip.show();
    delay(wait);
  }
}


/*
 * @brief  Glow the rings one after the other
 * @param  times: how many times you want to play the animation, 
 *         wait : delay in ms
 * @retval none
 */
void glowingCircles(uint8_t times, uint8_t wait)
{
  uint8_t x;
  uint8_t i;
  for(uint8_t k = 0; k < times; k++)
  {
      // Start to glow the outer circle half way
      for(x=0; x<=7;x++)
      {
          for (i=0; i <= 23; i++) 
          {
            strip.setPixelColor(i, greenShade[x]);    //turn every  pixel on
          }
          strip.show();
          delay(wait);
      }

      // Now complete full cycle for the outer circle and start to glow inner cicle half way
      for(x=8; x<=15;x++)
      {
          for (i=0; i <= 23; i++) 
          {
            strip.setPixelColor(i, greenShade[x]);    //turn every  pixel on
          }
          for (i=24; i <= 39; i++) 
          {
            strip.setPixelColor(i, greenShade[x-8]);
          }
          strip.show();    
          delay(wait);
      }  

      // Now complete full cycle for the inner circle
      for(x=8; x<=15;x++)
      {
          for (i=24; i <= 39; i++) 
          {
            strip.setPixelColor(i, greenShade[x]);    
          }
          strip.show();
          delay(wait);
      }

      // Now reverse the whole thing
      for(x=15; x>=8;x--)
      {
          for (i=24; i <= 39; i++) 
          {
            strip.setPixelColor(i, greenShade[x]); 
          }
          strip.show();
          delay(wait);
      }
      for(x=7; x>=0;x--)
      {
          for (i=0; i < 24; i++) 
          {
            strip.setPixelColor(i, greenShade[x+8]);    //turn every  pixel on
          }
          for (i=24; i < 40; i++) 
          {
            strip.setPixelColor(i, greenShade[x]);
          }
          strip.show();
          delay(wait);
      }
      for(x=7; x>=0;x--)
      {
          for (i=0; i < 24; i++) 
          {
            strip.setPixelColor(i, greenShade[x]);    //turn every  pixel on
          }
          strip.show();     
          delay(wait);
      }
  }
}







/*
 * @brief  Fill the Pixels(LEDs) one after the other with a color
 * @param  color_: 32bit color type, 
 *         wait  : delay in ms
 * @retval none
 */
void rainbow(uint8_t wait) 
{
  uint16_t i, j;

  for(j=0; j<256; j++) 
  {
    for(i=0; i<strip.numPixels(); i++) 
    {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) 
{
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint16_t wait) 
{
  for (int j=0; j<1; j++) 
  {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) 
    {
      for (uint16_t m=0; m < strip.numPixels(); m=m+3) 
      {
        strip.setPixelColor(m+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t m=0; m < strip.numPixels(); m=m+3) 
      {
        strip.setPixelColor(m+q, 0);        //turn every third pixel off
      }
      strip.show();
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) 
{
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) 
  {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) 
  {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
