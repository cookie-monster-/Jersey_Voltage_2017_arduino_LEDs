// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#include <Wire.h>
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
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


int delayval = 500; // delay for half a second
int incomingByte = 0;
uint32_t yellow = pixels.Color(255,150,0);
uint32_t blue = pixels.Color(0,0,255);
uint32_t green = pixels.Color(0,255,0);
uint32_t red = pixels.Color(255,0,0);
uint32_t color = pixels.Color(0,0,255);
uint32_t altColor = pixels.Color(150,255,0);
uint32_t off = pixels.Color(0,0,0);
uint32_t white = pixels.Color(255,255,255);
byte aimingTarget = 64;
byte haveGearDown = 65;
byte haveGearUpNoTarget = 66;
byte noGearDownMotorOff = 67;
byte noGearDownMotorOn = 68;
byte noGearUp = 69;
byte partyMode = 70;
int istep = 0;

String lastMode = "noGearUp";
String prevMode = "noGearUp";
void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(255);
  pixels.show();
  Wire.begin(84);
  //Serial.begin(9600);
}
void loop() {
  Serial.println("it works");
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  prevMode = lastMode;
  while (Serial.available())
  {
    incomingByte = Serial.read();
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
    if (incomingByte == aimingTarget)
    {
      lastMode = "aimingTarget";
    }
    else if (incomingByte == haveGearDown)
    {
      lastMode = "haveGearDown";
    }
    else if (incomingByte == haveGearUpNoTarget)
    {
      lastMode = "haveGearUpNoTarget";
    }
    else if (incomingByte == noGearDownMotorOff)
    {
      lastMode = "noGearDownMotorOff";
     }
    else if (incomingByte == noGearDownMotorOn)
    {
      lastMode = "noGearDownMotorOn";
    }
    else if (incomingByte == noGearUp)
    {
      lastMode = "noGearUp";
    }
    else if (incomingByte == partyMode)
    {
      lastMode = "partyMode";
    }
  }
  
  if(prevMode != lastMode) {
    istep = 0;
  }
  if(lastMode == "aimingTarget"){
    //chaseBounceIncremental(red, yellow, &istep);
    //stuff
  }else if(lastMode == "haveGearDown"){
    //flashAltOffIncremental(white, 20, &istep);
    flash(white,20); 
  }else if(lastMode == "haveGearUpNoTarget"){
    flash(green,400);
  }else if(lastMode == "noGearDownMotorOff"){
    solid(yellow,&istep);
  }else if(lastMode == "noGearDownMotorOn"){
    flashAltOffIncremental(yellow, 200, &istep);
  }else if(lastMode == "noGearUp"){
    chaseBounceIncremental(yellow,blue, &istep);
  }else if(lastMode == "partyMode"){
    //Flame();
    Fire(35,100,60);
  }

  
  
    /*else{
      //idleMode(red, green);   
        //chase(yellow, red); 
        //chaseBounce(yellow, white);
        //yellowFlame();
       // Fire(35,170,60);
       //Flame();
       // blackAndYellow();
        blackAndYellowBounce(10);
        //flashAltOff(blue, 200);
        //flashAltColors(yellow, white, 20);
        //flashAltOffColors(yellow, white, 20);
       //flash(white, 20);
       //bounce(red,30);
       //bounce(blue,10);
       //bounce(green,10);
       //bounce(yellow,20);
    }*/
  //}
  //idleMode(yellow, blue);
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

void receiveEvent(int howMany)
{
  while(Wire.available() > 0)
  {
    incomingByte = Wire.read();
    if (incomingByte == aimingTarget)
    {
      lastMode = "aimingTarget";
    }
    else if (incomingByte == haveGearDown)
    {
      lastMode = "haveGearDown";
    }
    else if (incomingByte == haveGearUpNoTarget)
    {
      lastMode = "haveGearUpNoTarget";
    }
    else if (incomingByte == noGearDownMotorOff)
    {
      lastMode = "noGearDownMotorOff";
     }
    else if (incomingByte == noGearDownMotorOn)
    {
      lastMode = "noGearDownMotorOn";
    }
    else if (incomingByte == noGearUp)
    {
      lastMode = "noGearUp";
    }
    else if (incomingByte == partyMode)
    {
      lastMode = "partyMode";
    }
  }
}

void solid(uint32_t color,int *istep){
  if ( (*istep) == 0 ) {
    for (uint16_t i=0; i<pixels.numPixels(); ++i)
    {
       pixels.setPixelColor(i,color);
       pixels.show();
    }
  }
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

void chaseIncremental(uint32_t color, uint32_t chaseColor, int *istep){
  if ( (*istep) == 0 ) {
    for (uint16_t i=0; i<pixels.numPixels(); ++i)
    {
       pixels.setPixelColor(i,color);
       pixels.show();
    }
  }
  if ( (*istep) < pixels.numPixels() ) {
     int i = (*istep);
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
     delay(40);
  }
  (*istep) = ((*istep) + 1) % (pixels.numPixels());
}

void chaseBounce(uint32_t color, uint32_t chaseColor){
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
    for (uint16_t i=pixels.numPixels(); i>0; --i)
    {
       int otherI = i - pixels.numPixels()/2;
       if (otherI > pixels.numPixels())
       {
        otherI = i + pixels.numPixels()/2;
       }
       pixels.setPixelColor(i,chaseColor);
       pixels.setPixelColor(i+1,color);
       pixels.setPixelColor(otherI,chaseColor);
       pixels.setPixelColor(otherI+1,color);
       pixels.show();
       delay(30);
    }
}

void chaseBounceIncremental(uint32_t color, uint32_t chaseColor, int *istep){
  if ( (*istep) == 0 ) {
    for (uint16_t i=0; i<pixels.numPixels(); ++i)
    {
       pixels.setPixelColor(i,color);
       pixels.show();
    }
  }
  if ( (*istep) < pixels.numPixels() ) {
     int i = (*istep);
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
  } else {
    int i = (*istep) - pixels.numPixels();
    i = pixels.numPixels() - i;
    int otherI = i - pixels.numPixels()/2;
    if (otherI > pixels.numPixels())
    {
    otherI = i + pixels.numPixels()/2;
    }
    pixels.setPixelColor(i,chaseColor);
    pixels.setPixelColor(i+1,color);
    pixels.setPixelColor(otherI,chaseColor);
    pixels.setPixelColor(otherI+1,color);
    pixels.show();
    delay(30);
  }
  (*istep) = ((*istep) + 1) % (2 * pixels.numPixels());
}

void blackAndYellow(int delayTime){
  uint32_t black = pixels.Color(0,0,0);
  uint32_t yellow = pixels.Color(255,150,0);
  for (uint16_t i=0; i<pixels.numPixels(); ++i)
  {
     pixels.setPixelColor(i,yellow);
     pixels.show();
  }
    for (uint16_t i=0; i<pixels.numPixels(); ++i)
    {
       int secondI = i + 2;
       int thirdI = secondI + 2;
       if (secondI > pixels.numPixels())
       {
        secondI = 0;
        thirdI = 2;
       }
       else if (thirdI > pixels.numPixels())
       {
        thirdI = 0;
       }
       pixels.setPixelColor(i,black);
       pixels.setPixelColor(i-1,yellow);
       pixels.setPixelColor(secondI,black);
       pixels.setPixelColor(secondI-1,yellow);
       pixels.setPixelColor(thirdI,black);
       pixels.setPixelColor(thirdI-1,yellow);
       pixels.show();
       delay(delayTime);
    }
}

void idleMode(uint32_t color, uint32_t color1){
    delay(50);
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

void flash(uint32_t color, int delayTime){
  for (uint16_t i=0; i<pixels.numPixels(); ++i)
  {
     pixels.setPixelColor(i,color);
     pixels.show();
  }
  delay(delayTime);
  for (uint16_t i=0; i<pixels.numPixels(); ++i)
  {
     pixels.setPixelColor(i,pixels.Color(0,0,0));
     pixels.show();
  }
  delay(delayTime);
}

void flashAltColors(uint32_t color, uint32_t altColor, int delayTime){
  for (uint16_t i=0; i<pixels.numPixels(); ++i)
  {
     pixels.setPixelColor(i,color);
     pixels.show();
  }
  delay(delayTime);
  for (uint16_t i=0; i<pixels.numPixels(); ++i)
  {
     pixels.setPixelColor(i,pixels.Color(0,0,0));
     pixels.show();
  }
  delay(delayTime);
  for (uint16_t i=0; i<pixels.numPixels(); ++i)
  {
     pixels.setPixelColor(i,altColor);
     pixels.show();
  }
  delay(delayTime);
  for (uint16_t i=0; i<pixels.numPixels(); ++i)
  {
     pixels.setPixelColor(i,pixels.Color(0,0,0));
     pixels.show();
  }
  delay(delayTime);
}

void flashAltOff(uint32_t color, int delayTime){
  for (uint16_t i=0; i<pixels.numPixels(); ++i)
  {
    if(i%2==0)
    {
     pixels.setPixelColor(i,color);
     pixels.show();
    }
    else
    {
     pixels.setPixelColor(i,pixels.Color(0,0,0));
     pixels.show();
    }
  }
  delay(delayTime);
  for (uint16_t i=0; i<pixels.numPixels(); ++i)
  {
    if(i%2==1)
    {
     pixels.setPixelColor(i,color);
     pixels.show();
    }
    else
    {
     pixels.setPixelColor(i,pixels.Color(0,0,0));
     pixels.show();
    }
  }
  delay(delayTime);
}
void flashAltOffIncremental(uint32_t color, int delayTime, int *istep){
  int even_odd = ((*istep) == 0) ? 0 : 1;
  for (uint16_t i=0; i<pixels.numPixels(); ++i)
  {
    if(i%2==even_odd)
    {
     pixels.setPixelColor(i,color);
     pixels.show();
    }
    else
    {
     pixels.setPixelColor(i,pixels.Color(0,0,0));
     pixels.show();
    }
  }
  delay(delayTime);
  (*istep) = ((*istep) + 1) % 2;
}
void flashAltOffColors(uint32_t color, uint32_t altColor, int delayTime)
{
  flashAltOff(color, delayTime);
  flashAltOff(altColor, delayTime);
}

void bounce(uint32_t color, int delayTime){
  for (uint16_t i=0; i<pixels.numPixels(); ++i)
  {
     pixels.setPixelColor(i,color);
     pixels.setPixelColor(i-1,pixels.Color(0,0,0));
     pixels.show();
     delay(delayTime);
  }
  for (uint16_t i=pixels.numPixels(); i>0; --i)
  {
     pixels.setPixelColor(i,color);
     pixels.setPixelColor(i+1,pixels.Color(0,0,0));
     pixels.show();
     delay(delayTime);
  }
}


void blackAndYellowBounce(int delayTime){
  uint32_t black = pixels.Color(0,0,0);
  uint32_t yellow = pixels.Color(255,150,0);
  for (uint16_t i=0; i<pixels.numPixels(); ++i)
  {
     pixels.setPixelColor(i,yellow);
     pixels.show();
  }
    for (uint16_t i=0; i<pixels.numPixels(); ++i)
    {
       int secondI = i + 2;
       int thirdI = secondI + 2;
       pixels.setPixelColor(i,black);
       pixels.setPixelColor(i-1,yellow);
       pixels.setPixelColor(secondI,black);
       pixels.setPixelColor(secondI-1,yellow);
       pixels.setPixelColor(thirdI,black);
       pixels.setPixelColor(thirdI-1,yellow);
       pixels.show();
       delay(delayTime);
    }
    
    for (uint16_t i=pixels.numPixels(); i>0; --i)
    {
       int secondI = i - 2;
       int thirdI = secondI - 2;
       pixels.setPixelColor(i,black);
       pixels.setPixelColor(i+1,yellow);
       pixels.setPixelColor(secondI,black);
       pixels.setPixelColor(secondI+1,yellow);
       pixels.setPixelColor(thirdI,black);
       pixels.setPixelColor(thirdI+1,yellow);
       pixels.show();
       delay(delayTime);
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
void Fire(int Cooling, int Sparking, int SpeedDelay) {
  
  static byte heat[20];
  int cooldown;
  
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < pixels.numPixels(); i++) {
    cooldown = random(0, ((Cooling * 10) / pixels.numPixels()) + 2);
    
    if(cooldown>heat[i]) {
      heat[i]=0;
    } else {
      heat[i]=heat[i]-cooldown;
    }
  }
  
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= pixels.numPixels() - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
    
  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160,255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for( int j = 0; j < pixels.numPixels(); j++) {
    setPixelHeatColor(j, heat[j] );
  }

  pixels.show();
  delay(SpeedDelay);
}

void setPixelHeatColor (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);
 
  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) {                     // hottest
    pixels.setPixelColor(Pixel, 255, 255, heatramp);
  } else if( t192 > 0x40 ) {             // middle
    pixels.setPixelColor(Pixel, 255, heatramp, 0);
  } else {                               // coolest
    pixels.setPixelColor(Pixel, heatramp, 0, 0);
  }
}


void Flame(){
  int r = 255;
  int g = r-120;
  int b = 40;
  
  for(int x = 0; x <99; x++)
  {
  int flicker = random(0,150);
  int r1 = r-flicker;
  int g1 = g-flicker;
  int b1 = b-flicker;
  if(g1<0) g1=0;
  if(r1<0) r1=0;
  if(b1<0) b1=0;
  pixels.setPixelColor(x,r1,g1, b1);
  }
  pixels.show();
  delay(random(50,150));
}

