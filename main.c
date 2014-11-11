// Sheng Jiang
#include "mylib.h"
#include "spritesheet.h"
#include "objects.h"
#include "plot.h"
#include "logic.h"
#include "levels.h"
#include "text.h"
#include<stdio.h>
#include <string.h>


// function prototype
void intro(void);

// main function
int main(void){
	// set GBA parameters
	REG_DISPCNT = MODE4 | BG2_ENABLE;
	
	// intro sequence (start screen)
	intro();

	// init variables
	int loop = 1;
	char buffer1[20];

	User user;
	Boulder boulder[150];
	int bouldernum = init_objects(&user, boulder, level1obj, LEVEL1SIZE);
	init_map(&user, level1);
	int maxmoves = LEVEL1MOVES;
	
	// reset pages
	fill_palette(spritesheet_palette);
	drawImage4(0,0,160,240,bg);
	plot_map(&user);
	
	flip_page();
	fill_palette(spritesheet_palette);
	drawImage4(0,0,160,240,bg);
	plot_map(&user);
	
	
	// main game loop
	while (loop){
		wait_for_vblank();
		flip_page();
		iterate_user(&user, boulder, bouldernum);
		
		//reset loop
		if (PRESSED(BUTTON_SELECT)){
			intro();
			User newuser;
			Boulder newboulder[150];
			memcpy(newboulder, boulder, 150);
			memcpy(newuser.map,user.map, 150);
			memcpy(newuser.boulders,user.boulders, 150);
			bouldernum = init_objects(&user, boulder, level1obj, LEVEL1SIZE);
			fill_palette(spritesheet_palette);
			drawImage4(0,0,160,240,bg);
			plot_map(&user);
			
			flip_page();
			fill_palette(spritesheet_palette);
			drawImage4(0,0,160,240,bg);
			plot_map(&user);
		}
		else if (PRESSED(BUTTON_A)){
			send_input(&user, 0, 1);
		}
		else if (PRESSED(BUTTON_UP)){
			send_input(&user, 0, 0);
		}
		else if (PRESSED(BUTTON_RIGHT)){
			send_input(&user, 1, 0);
		}
		else if (PRESSED(BUTTON_DOWN)){
			send_input(&user, 2, 0);
		}
		else if (PRESSED(BUTTON_LEFT)){
			send_input(&user, 3, 0);
		}
		sprintf (buffer1, "Moves: %4d/%4d", user.moves, maxmoves);
		drawImage4(2,2,8,238,bg);
		drawString(2,2,buffer1,5);
		
		// game over loop
		if (user.finished || user.moves > maxmoves){
			int wait = 1;
			if (user.finished){
				drawImage4(0,0,160,240,gamewin);
			}
			else{
				drawImage4(0,0,160,240,gameover);
			}
			flip_page();
			while(wait){
				wait_for_vblank();
				if (PRESSED(BUTTON_START) || PRESSED(BUTTON_A)){
					while(PRESSED(BUTTON_START) || PRESSED(BUTTON_A)){;}
					wait = 0;
				}
			}
			User newuser;
			Boulder newboulder[150];
			memcpy(newboulder, boulder, 150);
			memcpy(newuser.map,user.map, 150);
			memcpy(newuser.boulders,user.boulders, 150);
			bouldernum = init_objects(&user, boulder, level1obj, LEVEL1SIZE);
			fill_palette(spritesheet_palette);
			drawImage4(0,0,160,240,bg);
			plot_map(&user);
			
			flip_page();
			fill_palette(spritesheet_palette);
			drawImage4(0,0,160,240,bg);
			plot_map(&user);
		}
	}// end main game loop
	flip_page();
}// end main

// intro sequence
void intro(void){
	int loop = 1;
	fill_palette(spritesheet_palette);
	drawImage4(0,0,160,240,startscreen);
	flip_page();
	fill_palette(spritesheet_palette);
	drawImage4(0,0,160,240,startscreen);
	flip_page();
	while(loop){
		wait_for_vblank();
		if (PRESSED(BUTTON_START) || PRESSED(BUTTON_A)){
			while(PRESSED(BUTTON_START) || PRESSED(BUTTON_A)){;}
			loop = 0;
		}
	}
}// end intro
