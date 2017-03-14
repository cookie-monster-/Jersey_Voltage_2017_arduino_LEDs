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
uint32_t yellow = pixels.Color(150,255,0);
uint32_t blue = pixels.Color(0,0,255);
uint32_t red = pixels.Color(0,255,0);
uint32_t green = pixels.Color(255,0,0);
uint32_t color = pixels.Color(0,0,255);
uint32_t altColor = pixels.Color(150,255,0);
int searching = 64;
int haveGear = 65;
int haveGearTarget = 66;
int idle = 67;
int partyMode = 68;

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
    if (incomingByte == searching)
    {
      chase(red, yellow);
    }
    else if (incomingByte == haveGear)
    {
      chase(blue, yellow);
    }
    else if (incomingByte == haveGearTarget)
    {
      chase(green, blue);
    }
    else if (incomingByte == idle)
    {
      chase(green, blue);
    }
    else if (incomingByte == partyMode)
    {
      chase(green, blue);
    }
  }
  idleMode(yellow, blue);
  //chase(red, yellow);
  Serial.println(color, DEC);
  /*while(true){
    for (uint16_t i=0; i<pixels.numPixels(); ++i)
    {
      if (i%2==0)
      {
        pixels.setPixelColor(i,color);
        pixels.show();
      }
      else
      {
        pixels.setPixelColor(i,altColor);
        pixels.show();
      }
      //delay(10);
      //Serial.println(i);
    }
    delay(1000);*/
    /*for (uint16_t i=0; i<pixels.numPixels(); ++i)
    {
      if (i%2==1)
      {
        pixels.setPixelColor(i,color);
        pixels.show();
      }
      else
      {
        pixels.setPixelColor(i,altColor);
        pixels.show();
      }
      //delay(10);
      //Serial.println(i);
    }
    delay(1000);*/
  
  //murica();
 
}

void chase(uint32_t color, uint32_t chaseColor){
  for (uint16_t i=0; i<pixels.numPixels(); ++i)
  {
     pixels.setPixelColor(i,color);
     pixels.show();
  }
    for (uint16_t i=0; i<pixels.numPixels(); ++i)
    {
       int otherI = i + pixels.numPixels()/2;
       if (otherI > pixels.numPixels())
       {
        otherI = i - pixels.numPixels()/2;
       }
       pixels.setPixelColor(i,chaseColor);
       pixels.setPixelColor(i-1,color);
       pixels.setPixelColor(otherI,chaseColor);
       pixels.setPixelColor(otherI-1,color);
       pixels.show();
       delay(30);
    }
}

void idleMode(uint32_t color, uint32_t color1){
  for (uint16_t i=0; i<pixels.numPixels(); ++i)
  {
    pixels.setPixelColor(i, color);
    pixels.show();
  }
  for (uint16_t i=0; i<pixels.numPixels(); ++i)
  {
    int otherI = i + pixels.numPixels()/2;
    if (otherI > pixels.numPixels())
    {
      otherI = i - pixels.numPixels()/2;
    }
    pixels.setPixelColor(i, color1);
    pixels.setPixelColor(otherI, color);
    pixels.show();
    delay(30);
  }
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
