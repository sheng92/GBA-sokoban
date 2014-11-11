// Sheng Jiang
#include "mylib.h"

// video buffer
u16 *videoBuffer = (u16 *) 0x6000000;

// a function that waits for scanline blank to prevent tearing
void wait_for_vblank() {
  u16 *X = SCANLINECOUNTER;

  while (*X >= 160) {;} // in vblank, wait to exit
  while (*X < 160) {;} // wait for beginning of next vblank
}

// a function that uses mode4 to draw an image
void drawImage4(int r, int c, int height, int width, const u16* image) {
	width /= 2;
	REG_DMA3CNT = 0;
	for (u16 i=0; i < height; i++) {
		REG_DMA3SAD = (vu32) (image + (width*i)); // Source
		REG_DMA3DAD = (vu32) (videoBuffer + (240*(r+i)+c)/2); // Destination
		REG_DMA3CNT = width|DMA_ON; // Count and start
	}
}

// a function that uses mode4 to draw a sprite
void drawSprite4(int dr, int dc, int sr, int sc, int sheight, int swidth, const u16* image, int iwidth){
	int plot = 1;
	if (sheight <= 0 || swidth <= 0){
		plot = 0;
	}
	if (dc < 0){
		if (swidth+dc > 0){
			sc += 0-dc;
			swidth += dc;
			dc = 0;
		}
		else{
			plot = 0;
		}
	}
	if (dc+swidth > WIDTH){
		if (dc >= WIDTH){
			plot = 0;
		}
		else{
			swidth += WIDTH-(dc+swidth);
		}
	}
	if (dr < 0){
		if (sheight+dr > 0){
			sr += 0-dr;
			sheight += dr;
			dr = 0;
		}
		else{
			plot = 0;
		}
	}
	if (dr+sheight > HEIGHT){
		if (dr >= HEIGHT){
			plot = 0;
		}
		else{
			sheight += HEIGHT-(dr+sheight);
		}
	}
	if (plot){
		/*iwidth /= 2;
		swidth /= 2;
		dc /= 2;*/
		
		for (int i = dr; i < sheight+dr; i++){
			REG_DMA3CNT = 0;
			REG_DMA3SAD = (vu32) (image+((i-dr+sr)*iwidth+sc)/2);
			REG_DMA3DAD = (vu32) (videoBuffer+(dc+i*240)/2);
			REG_DMA3CNT = swidth/2|DMA_ON;
		}
	}

}

// a function that sets a pixel a certain color in mode4
void setPixel4(int r, int c, const u8 color){
	if(c & 1) {
		videoBuffer[((240*r+c)/2)] = (videoBuffer[((240*r+c)/2)] & 0x00ff) |  (color<<8);
	} else {
		videoBuffer[((240*r+c)/2)] = (videoBuffer[((240*r+c)/2)] & 0xff00) |  (color);
	}
}

// a function that fills the palette with a saved palette
void fill_palette(const short unsigned int *palette) {
	for (int i=0; i<255; i++) {
		PALETTE[i] = palette[i];
	}
}

// a function that flips the page
void flip_page() {
  if(REG_DISPCNT & BUFFER1FLAG) {
    REG_DISPCNT &= ~BUFFER1FLAG;
    videoBuffer = BUFFER1;
  } else {
    REG_DISPCNT |= BUFFER1FLAG;
    videoBuffer = BUFFER0;
  }
}
