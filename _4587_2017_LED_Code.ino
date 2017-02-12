// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            2

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      20

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

int delayval = 500; // delay for half a second
int incomingByte = 0;
uint32_t color = pixels.Color(255,0,0);

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(255);
  pixels.show();
  Serial.begin(9600);
}
void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  if (Serial.available() > 0)
  {
    incomingByte = Serial.read();
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
    if (incomingByte == 64)
    {
      color = pixels.Color(0,0,255);
    }
    else if (incomingByte == 65)
    {
    
      color = pixels.Color(0,255,0);
    }
    else if (incomingByte == 66)
    {
      color = pixels.Color(255,0,0);
    }
  }
  Serial.println(color, DEC);
  for (uint16_t i=0; i<pixels.numPixels(); ++i)
  {
    pixels.setPixelColor(i,color);
    pixels.show();
    //delay(50);
    //Serial.println(i);
  }

  //murica();
 
}

/*void murica(){
  unsigned int pos = 0;
  int timeDelay = 5;
  int blueSize =5;
  int whiteSize = 5;
  int numStars = 5;
  int redWhiteSize = 5;
  int numStripes = 5;
  
  int totalLength = (numStars+1)*blueSize+numStars*whiteSize+(numStripes*2+1)*redWhiteSize;
  int currentPos = 0; //position in current refresh

      Serial.println("hello");
  
  while(true) {
    Serial.println("hello");
    currentPos = pos;
    for(int i = 0; i < blueSize; i++){
      pixels.setPixelColor(currentPos, pixels.Color(0,0,127));
      pixels.show();
      Serial.println("0,0,127" + currentPos);
      currentPos++;
      if(currentPos >= pixels.numPixels()){
        currentPos-=totalLength;//////////////////////////////////////////////////////////////////////////
      }
    }
    for(int i = 0; i < numStars; i++){
      for(int j = 0; j < whiteSize; j++){
        pixels.setPixelColor(currentPos, pixels.Color(127,127,127));
        pixels.show();
        Serial.println("127,127,127" + currentPos);
        currentPos++;
      }
      for(int j = 0; j < blueSize; j++){
        pixels.setPixelColor(currentPos, pixels.Color(0,0,127));
        pixels.show();
        Serial.println("0,0,127" + currentPos);
        currentPos++;
      }
    }//stars
    for(int i = 0; i < redWhiteSize; i++){
      pixels.setPixelColor(currentPos, pixels.Color(0,127,0));
      pixels.show();
      Serial.println("127,0,0");
      currentPos++;
    }
    for(int i = 0; i < numStripes; i++){
      for(int j = 0; j < redWhiteSize; j++){
        pixels.setPixelColor(currentPos, pixels.Color(127,127,127));
        pixels.show();
        Serial.println("127,127,127");
        currentPos++;
      }
      for(int j = 0; j < redWhiteSize; j++){
        pixels.setPixelColor(currentPos, pixels.Color(127,0,0));
        pixels.show();
        Serial.println("127,0,0");
        currentPos++;
      }
    }//stripes
    pos++;
    if(pos >= pixels.numPixels())
      pos = 0; 
  }
}*/
