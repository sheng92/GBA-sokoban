#include "objects.h"
#include "spritesheet.h"
#include "mylib.h"
#include "plot.h"
#include "logic.h"

// a function that plots the user. looks out for the action the user is doing as well as if the user is crossing over holes
void plot_user(User *user){
	int dr = user->y << 4;
	int dc = user->x << 4;
	int sr = 0;
	int sc = 0;
	int width = 0;
	int height = 0;
	const u16* image = player;
	int iwidth = 0;
	if (user->moving){
		sc = 0;
		user->busy = 1;
		switch (user->direction){
			case 0:
				if (user->inhole && user->outhole){
					sr = ((user->frame >> FRAMEDELAY) << 5);
					image = playerup11hole;
				}
				else if (user->inhole){
					sr = ((user->frame >> FRAMEDELAY) << 5);
					image = playerup01hole;
				}
				else if (user->outhole){
					sr = ((user->frame >> FRAMEDELAY) << 5);
					image = playerup10hole;
				}
				else {
					sr = ((user->frame >> FRAMEDELAY) << 5);
					image = playerup;
				}
				width = 16;
				height = 32;
				iwidth = PLAYERUP_WIDTH;
				break;
			case 1:
				if (user->inhole && user->outhole){
					sr = ((user->frame >> FRAMEDELAY) << 4);
					image = playerright11hole;
				}
				else if (user->inhole){
					sr = ((user->frame >> FRAMEDELAY) << 4);
					image = playerright01hole;
				}
				else if (user->outhole){
					sr = ((user->frame >> FRAMEDELAY) << 4);
					image = playerright10hole;
				}
				else {
					sr = ((user->frame >> FRAMEDELAY) << 4);
					image = playerright;
				}
				dc -= 16;
				width = 32;
				height = 16;
				iwidth = PLAYERRIGHT_WIDTH;
				break;
			case 2:
				dr -= 16;
				if (user->inhole && user->outhole){
					sr = ((user->frame >> FRAMEDELAY) << 5);
					image = playerdown11hole;
				}
				else if (user->inhole){
					sr = ((user->frame >> FRAMEDELAY) << 5);
					image = playerdown01hole;
				}
				else if (user->outhole){
					sr = ((user->frame >> FRAMEDELAY) << 5);
					image = playerdown10hole;
				}
				else {
					sr = ((user->frame >> FRAMEDELAY) << 5);
					image = playerdown;
				}
				width = 16;
				height = 32;
				iwidth = PLAYERDOWN_WIDTH;
				break;
			case 3:
				if (user->inhole && user->outhole){
					sr = ((user->frame >> FRAMEDELAY) << 4);
					image = playerleft11hole;
				}
				else if (user->inhole){
					sr = ((user->frame >> FRAMEDELAY) << 4);
					image = playerleft01hole;
				}
				else if (user->outhole){
					sr = ((user->frame >> FRAMEDELAY) << 4);
					image = playerleft10hole;
				}
				else {
					sr = ((user->frame >> FRAMEDELAY) << 4);
					image = playerleft;
				}
				width = 32;
				height = 16;
				iwidth = PLAYERLEFT_WIDTH;
				break;
			default:
				break;
		}
	}
	else if (user->pushing){
		user->busy = 1;
		sr = user->direction << 4;
		sc = ((user->frame >> FRAMEDELAY) << 4) + 64;
		width = 16;
		height = 16;
		image = player;
		iwidth = PLAYER_WIDTH;
	}
	else{
		user->busy = 0;
		sr = user->direction << 4;
		sc = (user->frame >> FRAMEDELAY) << 4;
		width = 16;
		height = 16;
		image = player;
		iwidth = PLAYER_WIDTH;
	}
	drawSprite4(dr,dc,sr,sc,height,width,image,iwidth);
}

// a function that plots a boulder. looks out for boulder movement as well as if the boulder is crossing over holes, or over a hole
void plot_boulder(Boulder *boulder){
	int dr = boulder->y << 4;
	int dc = boulder->x << 4;
	int sr = 0;
	int sc = 0;
	int width = 0;
	int height = 0;
	const u16* image = player;
	int iwidth = 0;
	if (boulder->moving){
		sc = 0;
		switch (boulder->direction){
			case 0:
				if (boulder->inhole && boulder->outhole){
					sr = 128 - ((boulder->frame >> FRAMEDELAY) << 5);
					image = ballvertholes;
				}
				else if (boulder->inhole){
					sr = ((boulder->frame >> FRAMEDELAY) << 5);
					image = balluphole;
				}
				else if (boulder->outhole){
					sr = 128 - ((boulder->frame >> FRAMEDELAY) << 5);
					image = balldownhole;
				}
				else {
					sr = ((boulder->frame >> FRAMEDELAY) << 5);
					image = ballup;
				}
				width = 16;
				height = 32;
				iwidth = BALLUP_WIDTH;
				break;
			case 1:
				dc -= 16;
				if (boulder->inhole && boulder->outhole){
					sr = ((boulder->frame >> FRAMEDELAY) << 4);
					image = ballhorizholes;
				}
				else if (boulder->inhole){
					sr = ((boulder->frame >> FRAMEDELAY) << 4);
					image = ballrighthole;
				}
				else if (boulder->outhole){
					sr = 64 - ((boulder->frame >> FRAMEDELAY) << 4);
					image = balllefthole;
				}
				else {
					sr = ((boulder->frame >> FRAMEDELAY) << 4);
					image = ballright;
				}
				width = 32;
				height = 16;
				iwidth = BALLRIGHT_WIDTH;
				break;
			case 2:
				dr -= 16;
				if (boulder->inhole && boulder->outhole){
					sr = ((boulder->frame >> FRAMEDELAY) << 5);
					image = ballvertholes;
				}
				else if (boulder->inhole){
					sr = ((boulder->frame >> FRAMEDELAY) << 5);
					image = balldownhole;
				}
				else if (boulder->outhole){
					sr = 128 - ((boulder->frame >> FRAMEDELAY) << 5);
					image = balluphole;
				}
				else {
					sr = ((boulder->frame >> FRAMEDELAY) << 5);
					image = balldown;
				}
				width = 16;
				height = 32;
				iwidth = BALLDOWN_WIDTH;
				break;
			case 3:
				if (boulder->inhole && boulder->outhole){
					sr = 64 - ((boulder->frame >> FRAMEDELAY) << 4);
					image = ballhorizholes;
				}
				else if (boulder->inhole){
					sr = ((boulder->frame >> FRAMEDELAY) << 4);
					image = balllefthole;
				}
				else if (boulder->outhole){
					sr = 64 - ((boulder->frame >> FRAMEDELAY) << 4);
					image = ballrighthole;
				}
				else {
					sr = ((boulder->frame >> FRAMEDELAY) << 4);
					image = ballleft;
				}
				width = 32;
				height = 16;
				iwidth = BALLLEFT_WIDTH;
				break;
			default:
				break;
		}
	}
	else{
		sr = 0;
		sc = 0;
		width = 16;
		height = 16;
		if (boulder->inhole)
			image = ballhole;
		else
			image = ball;
		iwidth = BALL_WIDTH;
	}
	drawSprite4(dr,dc,sr,sc,height,width,image,iwidth);
}

// plots a tile (wall, hole, or tile)
void plot_tile(int id, int x, int y){
	int dr = y << 4;
	int dc = x << 4;
	int sr = 0;
	int sc = 0;
	int width = 0;
	int height = 0;
	const u16* image = ground;
	int iwidth = 0;
	switch (id){
		case 1:
			width = 16;
			height = 17;
			iwidth = 16;
			image = ground;
			break;
		case 2:
			width = 16;
			height = 16;
			iwidth = 16;
			image = hole;
			break;
		case 3:
			dr -= 5;
			width = 16;
			height = 21;
			iwidth = 16;
			image = wall;
			break;
		default:
			break;
	}
	drawSprite4(dr,dc,sr,sc,height,width,image,iwidth);
}

// plots the map (calls plot_tile)
void plot_map(User *user){
	for (int i = 0; i < 15; i ++){
		for (int j = 0; j < 10; j ++){
			if (i == user->x && j == user->y){
				plot_user(user);
			}
			else{
				plot_tile(user->map[QUERY(i,j)],i,j);
			}
		}
	}
}

// plots all boulders (calls plot_boulder)
void plot_boulders(Boulder *boulder, int numboulders){
	for (int i = 0; i < numboulders; i += 1){
		plot_boulder(&boulder[i]);
	}
}
