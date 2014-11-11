#ifndef MYLIB_H
#define MYLIB_H

typedef unsigned char	u8;
typedef unsigned short	u16;
typedef unsigned int	u32;

typedef volatile unsigned char vu8;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

typedef volatile signed char vs8;
typedef volatile signed short vs16;
typedef volatile signed int vs32;

// gba macros
#define REG_DISPCNT *(u16 *) 0x4000000
#define RGB(r,g,b) ((r)|((g)<<5)|((b)<<10))
#define OFFSET(r, c, rowlen)  ((r)*(rowlen)+(c))
#define SCANLINECOUNTER ((unsigned short *) 0x4000006)
#define MODE3 3
#define MODE4 4
#define BG2_ENABLE 1<<10
#define WIDTH 240
#define HEIGHT 160

// button macros
#define BUTTONS (*(unsigned int *) 0x4000130)
#define BUTTON_A      (1<<0)
#define BUTTON_B      (1<<1)
#define BUTTON_SELECT (1<<2)
#define BUTTON_START  (1<<3)
#define BUTTON_RIGHT  (1<<4)
#define BUTTON_LEFT   (1<<5)
#define BUTTON_UP     (1<<6)
#define BUTTON_DOWN   (1<<7)
#define BUTTON_R      (1<<8)
#define BUTTON_L      (1<<9)
#define PRESSED(button) (~(BUTTONS)&button)

// color macros
#define RED RGB(31,0,0)
#define ORANGE RGB(31,12,0)
#define YELLOW RGB(31,31,0)
#define GREEN RGB(0,31,0)
#define CYAN RGB(0,31,31)
#define BLUE RGB(0,0,31)
#define BLACK RGB(0,0,0)
#define WHITE RGB(31,31,31)

extern u16 *videoBuffer;

/* DMA channel 0 register definitions*/
#define REG_DMA0SAD         *(vu32*)0x40000B0  /* source address*/
#define REG_DMA0DAD         *(vu32*)0x40000B4  /* destination address*/
#define REG_DMA0CNT         *(vu32*)0x40000B8  /* control register*/

/* DMA channel 1 register definitions*/
#define REG_DMA1SAD         *(vu32*)0x40000BC  /* source address*/
#define REG_DMA1DAD         *(vu32*)0x40000C0  /* destination address*/
#define REG_DMA1CNT         *(vu32*)0x40000C4  /* control register*/

/* DMA channel 2 register definitions*/
#define REG_DMA2SAD         *(vu32*)0x40000C8  /* source address*/
#define REG_DMA2DAD         *(vu32*)0x40000CC  /* destination address*/
#define REG_DMA2CNT         *(vu32*)0x40000D0  /* control register*/

/* DMA channel 3 register definitions */
#define REG_DMA3SAD         *(vu32*)0x40000D4   /* source address*/
#define REG_DMA3DAD         *(vu32*)0x40000D8  /* destination address*/
#define REG_DMA3CNT         *(vu32*)0x40000DC  /* control register*/

/* Defines*/
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

/* Destination address flags */
#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

/* Source address flags */
#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)
#define DMA_REPEAT (1 << 25)

/* How much to copy flags */
#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

/* When to DMA flags */
#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)
#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)
#define START_ON_FIFO_EMPTY 0x30000000

// Buffer defines
#define BUFFER0 ((u16 *) 0x06000000)
#define BUFFER1 ((u16 *) 0x0600A000)
#define PALETTE ((u16 *) 0x05000000)
#define BUFFER1FLAG 0x10 

// function prototypes
void wait_for_vblank();
void drawImage4(int r, int c, int width, int height, const u16* image);
void fill_palette(const short unsigned int *palette);
void drawSprite4(int dr, int dc, int sr, int sc, int sheight, int swidth, const u16* image, int iwidth);
void setPixel4(int dr, int dc, const u8 color);
void flip_page();

#endif
