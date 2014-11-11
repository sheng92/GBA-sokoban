#include "text.h"
#include "mylib.h"

void drawChar(int row, int col, char ch, unsigned short color)
{
	int r, c;
	for(r=0; r<8; r++)
	{
		for(c=0; c<6; c++)
		{
			if(fontdata_6x8[OFFSET(r, c, 6)+ch*48])
			{
				setPixel4(row+r, col+c, color);
			}
		}
	}
}

/*
 *
 * I didn't code this in class but I will go over it next lecture
 *
 * You can call it like this:
 *
 * drawString(10, 10, "Hello!", YELLOW);
 *
 * or like this:
 * 
 * char *message = "This is a message.";
 * drawString(20, 5, message, RED);
 *
 * or like this:
 *
 * char buffer[41] = "This is a char array!";
 * drawString(30, 5, buffer, GREEN);
 * 
 */
void drawString(int row, int col, char *str, unsigned short color)
{
	while(*str)
	{
		drawChar(row, col, *str++, color);
		col +=6;

	}
}
