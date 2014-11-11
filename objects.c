#include "objects.h"
#include "spritesheet.h"
#include "mylib.h"
#include "plot.h"

// a function that initializes a user struct
void init_user(User *user, int x, int y){
	user->x = x;
	user->y = y;
	user->direction = 0; // [0,1,2,3] > [up, right, down, left]
	user->moving = 0;
	user->pushing = 0;
	user->outhole = 0;
	user->inhole = 0;
	user->frame = 0;
	user->finished = 0;
	user->moves = 0;
	user->busy = 0;
}

// a function that initializes a boulder struct
void init_boulder(Boulder *boulder, int x, int y){
	boulder->x = x;
	boulder->y = y;
	boulder->direction = 0;
	boulder->moving = 0;
	boulder->outhole = 0;
	boulder->inhole = 0;
	boulder->frame = 0;
}

// a function that gets a premade map and imports it into the user struct 
void init_map(User *user, const u32* map){
	for (int i = 0; i < 15; i ++){
		for (int j = 0; j < 10; j ++){
			user->map[QUERY(i,j)] = map[QUERY(i,j)];
		}
	}

}

// a function that imports user and boulder locations from a premade map into the user and boulder structs
int init_objects(User *user, Boulder *boulder, const unsigned int *objects, int objsize){
	int first = 1;
	int j = 0;
	for (int i = 0; i < objsize; i += 2){
		if (first){
			init_user(user, objects[i], objects[i+1]);
			first = 0;
		}
		else{
			j = (i-2)<<2;
			boulder[j].x = objects[i];
			boulder[j].y = objects[i+1];
			boulder[j].direction = 0;
			boulder[j].moving = 0;
			boulder[j].outhole = 0;
			boulder[j].inhole = 0;
			boulder[j].frame = 0;
			user->boulders[QUERY(objects[i],objects[i+1])] = 1;
		}
	}
	return j+1;
}

