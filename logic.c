#include "objects.h"
#include "spritesheet.h"
#include "mylib.h"
#include "plot.h"
#include "logic.h"

// this function takes in inputs and decides whether or not they'll affect the player
void send_input(User *user, int direction, int push){
	if (!user->busy){
		if (push){
			user->pushing = 1;
			user->frame = 0;
		}
		else{
			if (user->direction == direction){
				user->moving = 1;
				user->frame = 0;
			}
			else{
				user->direction = direction;
				user->frame = 0;
			}
		}
	}
}

// this function iterates through the game
void iterate_user(User *user, Boulder *boulder, int numboulders){
	if (user->pushing){
		plot_user(user);
		user->frame++;
		if (user->frame==(3<<FRAMEDELAY)){
			push(user, boulder, numboulders);
		}
		if (user->frame>=(5<<FRAMEDELAY)){
			user->busy = 0;
			user->frame = 0;
			user->moving = 0;
			user->pushing = 0;
		}
	}
	else if (user->moving){
		if (user->frame == 0){
			user->inhole = 0;
			user->outhole = 0;
			int taken = 0;
			int rock = 0;
			int prev = 0;
			int dx = 0;
			int dy = 0;
			switch (user->direction){
				case 0:
					dy = -1;
					break;
				case 1:
					dx = 1;
					break;
				case 2:
					dy = 1;
					break;
				case 3:
					dx = -1;
					break;
				default:
					break;
			}
			taken = user->map[QUERY(user->x+dx,user->y+dy)];
			rock = user->boulders[QUERY(user->x+dx,user->y+dy)];
			prev = user->map[QUERY(user->x,user->y)];
			if (taken>2 || rock){
				user->moving = 0;
				user->busy = 0;
				user->pushing = 0;
				user->frame = -1;
				if (taken == 2){
					user->inhole = 1;
				}
				if (prev == 2){
					user->outhole = 1;
				}
			}
			else{
				user->moves++;
				user->x += dx;
				user->y += dy;
				if (taken == 2){
					user->inhole = 1;
				}
				if (prev == 2){
					user->outhole = 1;
				}
			}
		}
		plot_user(user);
		user->frame++;
		if (user->frame >= (5<<FRAMEDELAY)){
			user->moving = 0;
			user->busy = 0;
			user->pushing = 0;
			user->frame = 0;
		}
	}
	if (!user->busy){
		user->moving = 0;
		user->pushing = 0;
		plot_user(user);
	}
	plot_boulders(boulder, numboulders);
	int finished = 1;
	for (int i = 0; i < numboulders; i += 1){
		int prev = user->map[QUERY(boulder[i].x,boulder[i].y)];
		if (boulder[i].moving){
			boulder[i].frame++;
			if (boulder[i].frame >= (5<<FRAMEDELAY)){
				boulder[i].moving = 0;
				boulder[i].frame = 0;
			}
			finished = 0;
		}
		if (!boulder[i].moving && prev != 2){
			finished = 0;
		}
	}
	user->finished = finished;
	for (int i = 0; i < 15; i ++){
		for (int j = 0; j < 10; j ++){
			if (user->map[QUERY(i,j)]==3)
				plot_tile(user->map[QUERY(i,j)],i,j);
		}
	}
}

// this function sees if there's a boulder to push at the location the user is pushing at
void push(User *user, Boulder *boulder, int numboulders){
	int x = user->x;
	int y = user->y;
	int dx = 0;
	int dy = 0;
	switch (user->direction){
		case 0:
			dy = -1;
			break;
		case 1:
			dx = 1;
			break;
		case 2:
			dy = 1;
			break;
		case 3:
			dx = -1;
			break;
		default:
			break;
	}
	int present = 0;
	int i = 0;
	for (i = 0; i < numboulders; i += 1){
		if (boulder[i].x == x+dx && boulder[i].y == y+dy){
			present = 1;
			break;
		}
	}
	if (present){
		int taken = user->map[QUERY(user->x+dx+dx,user->y+dy+dy)];
		int prev = user->map[QUERY(user->x+dx,user->y+dy)];
		int rock = user->boulders[QUERY(user->x+dx+dx,user->y+dy+dy)];
		if (taken>2 || rock){
			boulder[i].moving = 0;
			boulder[i].frame = 0;
			if (prev == 2){
				boulder[i].inhole = 1;
			}
		}
		else{
			user->moves++;
			boulder[i].moving = 1;
			boulder[i].direction = user->direction;
			user->boulders[QUERY(boulder[i].x,boulder[i].y)] = 0;
			boulder[i].x += dx;
			boulder[i].y += dy;
			user->boulders[QUERY(boulder[i].x,boulder[i].y)] = 1;
			if (taken == 2){
				boulder[i].inhole = 1;
			}
			if (prev == 2){
				boulder[i].outhole = 1;
			}
		}
	}
}
