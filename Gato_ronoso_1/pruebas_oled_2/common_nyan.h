#ifndef _COMMON_NYAN_H
#define _COMMON_NYAN_H

#define nyan_pic_w (64)
#define nyan_pic_h (40)

//#define tail_w (12)
//#define tail_h (18)

#define rinbow_w (34)
#define rinbow_h (30)

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define MAX_STARS (6)  // how much stars we seen on screen

/// See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define SCREEN_ADDRESS 0x3c

#define COLOR_BLACK (SSD1306_BLACK)
#define COLOR_WHITE (SSD1306_WHITE)

//=======================
typedef struct {
  uint8_t state;
  uint8_t posX;
  uint8_t posY;
} star_t;

//=======================

void initUser(void);
void moveStars(void);
void initStars(void);
void drawNyan(void);
float getTemp(void);
uint16_t keyRand(void);

//=======================

#endif // _COMMON_NYAN_H
