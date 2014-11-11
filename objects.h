#ifndef OBJECTS_H
#define OBJECTS_H

// player structure
typedef struct user{
	int x;
	int y;
	int direction;
	int moving;
	int pushing;
	int inhole;
	int outhole;
	int frame;
	int finished;
	int moves;
	int busy;
	int map[150];
	int boulders[150];
} User;

// boulder structure
typedef struct boulder{
	int x;
	int y;
	int direction;
	int moving;
	int inhole;
	int outhole;
	int frame;
} Boulder;


// defines
#define FRAMEDELAY 2
#define QUERY(x,y) (((y)<<4)-(y)+(x))

// function prototypes
void init_user(User *user, int x, int y);
void init_boulder(Boulder *boulter, int x, int y);
void init_map(User *user, const unsigned int *map);
int init_objects(User *user, Boulder *boulder, const unsigned int *objects, int objsize);
#endif
