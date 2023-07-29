#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#include "common_nyan.h"
#include "pics.h"
#include "pins.h"


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

uint16_t nextInt;

uint8_t starsSize [6] = {1, 5, 7, 7, 5, 3};
uint8_t nyanPosY[4];
uint8_t nyanState, nyanStateX, rainbowStateX;
uint8_t starsStep;

bool rainbowState;

int previous_frame_time = 0;

star_t allStars[MAX_STARS];


//===================

uint16_t keyRand(void)
{
  nextInt = (((nextInt * 214013 + 2531011)>> 8)& 0x7fff);
  return nextInt;
}


void initStars(void)
{  
  for(auto &singleStar : allStars)
  {
    singleStar.state = keyRand() % 6;
    singleStar.posX = keyRand() % (SCREEN_WIDTH - 1);   // 0-128   ((127 + 1) - 0) + 0;
    singleStar.posY = keyRand() % (SCREEN_HEIGHT - 1);  // 0-64  ((63 + 1) - 0) + 0;
  }
}


void moveStars(void)
{
  for(auto &singleStar : allStars)
  {
    singleStar.posX -= starsStep;
    if(singleStar.posX > (SCREEN_WIDTH - 1)) {
      singleStar.posX =  (SCREEN_WIDTH - 1);
      singleStar.posY = keyRand() % (SCREEN_HEIGHT - 1);  // 0-64  ((63 + 1) - 0) + 0;
      singleStar.state = keyRand() % 6;
    }
    
    ++singleStar.state;
    if(singleStar.state >= 6) {
      singleStar.state = 0;
    }
  }
}


void initUser(void)
{
  nyanState = 0;
  nyanStateX = 24;
  rainbowStateX = 0;
  rainbowState = false;
  starsStep = 8;
  
  for(size_t i=0; i < 5; i++) {
    nyanPosY[i] = i + 9; // 9 - zero state
  }

  // yes, it real "semi-random"!
  randomSeed(analogRead(ENTROPY_SOURCE_PIN));
  nextInt += rand();
}


void drawNyan(void)
{
  // Draw stars and blow your mind
  for(auto &singleStar : allStars) {
  
    // x and y coordinates, where we start draw pic
    // width and higth of pic depend of number of state of number star struct;
    // number of star state is index for starsSize[] array, where we get sizes :)
    display.drawXBitmap(singleStar.posX, singleStar.posY,
                        starPointers[singleStar.state],
                        starsSize[singleStar.state], starsSize[singleStar.state],
                        COLOR_WHITE);
  }

  // Draw rainbow (yes, monochrome rainbow!)
  display.drawXBitmap(rainbowStateX, 18,
                      (rainbowState) ? rainbow1 : rainbow2,
                      rinbow_w, rinbow_h,
                      COLOR_WHITE);
  
  // Draw nyan
  // Move up and down aka jump on Y coordinate is draw by:  number of state(0,1,2,3) + 9;
  display.drawXBitmap(nyanStateX, nyanPosY[nyanState],
                    picsPointers[nyanState],
                    nyan_pic_w, nyan_pic_h,
                    COLOR_WHITE);
}


void setup()
{
  Serial.begin(115200);
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer after initialisation
  display.clearDisplay();

  initUser();
  initStars();
}


void loop()
{
  if ((millis() - previous_frame_time) > (1000 / 18)) {
    previous_frame_time = millis();

    display.clearDisplay();

    drawNyan();
  
    // Here we change all
    nyanState = (nyanState + 1) & 0x03;
    ++nyanStateX;
    ++rainbowStateX;
    rainbowState = !rainbowState;
    moveStars();
  
    display.display();
  }
}
