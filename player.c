// add the needed C libraries below
#include <stdbool.h> // bool, true, false
#include <stdlib.h> // rand

// look at the file below for the definition of the direction type
// pacman.h must not be modified!
#include "pacman.h"

// ascii characters used for drawing levels
extern const char PACMAN; // ascii used for pacman
extern const char WALL; // ascii used for the walls
extern const char PATH; // ascii used for the explored paths
extern const char DOOR; // ascii used for the ghosts' door
extern const char VIRGIN_PATH; // ascii used for the unexplored paths
extern const char ENERGY; // ascii used for the energizers
extern const char GHOST1; // ascii used for the ghost 1
extern const char GHOST2; // ascii used for the ghost 2
extern const char GHOST3; // ascii used for the ghost 3
extern const char GHOST4; // ascii used for the ghost 4

/*---------------------------------------------------------------------------------------------*/


// reward (in points) when eating dots/energizers 
extern const int VIRGIN_PATH_SCORE; // reward for eating a dot
extern const int ENERGY_SCORE; // reward for eating an energizer

/*---------------------------------------------------------------------------------------------*/


// put the student names below (mandatory)
const char * binome="CordonGigandet";

/*---------------------------------------------------------------------------------------------*/

// put the prototypes of your additional functions/procedures below

bool checkghost(int,char * *,int,int);          //this module check if there is a ghost in a case
char coordghosts(int **, int **, int **, int **,char *,char * *,int,int);       //this module find the ghosts and return their coordonates
direction randomDirection(bool,bool,bool,bool);

/*---------------------------------------------------------------------------------------------*/

// change the pacman function below to build your own player
// your new pacman function can use as many additional functions/procedures as needed; put the code of these functions/procedures *AFTER* the pacman function

/*---------------------------------------------------------------------------------------------*/


direction pacman(
		 char * * map, // the map as a dynamic array of strings, ie of arrays of chars
		 int xsize, // number of columns of the map
		 int ysize, // number of lines of the map
		 int x, // x-position of pacman in the map 
		 int y, // y-position of pacman in the map
		 direction lastdirection, // last move made by pacman (see pacman.h for the direction type; lastdirection value is -1 at the beginning of the game
		 bool energy, // is pacman in energy mode? 
		 int remainingenergymoderounds // number of remaining rounds in energy mode, if energy mode is true
		 ) {
  direction d; // the direction to return

  bool north=false; // indicate whether pacman can go north; no by default
  bool east=false; // indicate whether pacman can go east; no by default
  bool south=false; // indicate whether pacman can go south; no by default
  bool west=false; // indicate whether pacman can go west; no by default
  bool ok=false; // turn true when a valid direction is randomly chosen

  int i;   //for the checking of the cases ahead
  int j;
  int p=0;
  int dir1[4];  //for keeping the authorized direction after checking
  bool dir[4]; //for verifying where we can go and how many possibilities we have (which are saved in dir1)
  dir[0]=north;
  dir[1]=east;
  dir[2]=south;
  dir[3]=west;
  int ** coordGhost1[2]; //Coordonates of ghost1
  int **coordGhost2[2]; //Coordonates of ghost2
  int **coordGhost3[2]; //Coordonates of ghost3
  int **coordGhost4[2]; //Coordonates of ghost4
  char *posghost[4];   // tab with all the previous coordinates, modified by the coordghosts module




	if(y==0 || (y>0 && map[y-1][x]!=WALL && map[y-1][x]!=DOOR)){  //We check if pacman can go north (no wall or anything else)
		for (i=1;i<3;i++){                                        //we check the 3 positions up north
			if(checkghost(i,map[x][y],x,y)==true){                              // we check that there are no ghost in this cases
				north=false;                                      //if there is a ghost, you can't go north
			}
		}
	}

	if(x==xsize-1 || (x<xsize-1 && map[y][x+1]!=WALL && map[y][x+1]!=DOOR)){  //We check if pacman can go east (no wall or anything else)
		for (i=1;i<3;i++){                                        //we check the 3 positions up east
			if(checkghost(i,map[x][y],x,y)==true){                              // we check that there are no ghost in this cases
				east=false;                                      //if there is a ghost, you can't go east
			}
		}
	}

	if(y==ysize-1 || (y<ysize-1 && map[y+1][x]!=WALL && map[y+1][x]!=DOOR)){  //We check if pacman can go south (no wall or anything else)
		for (i=1;i<3;i++){                                        //we check the 3 positions up south
			if(checkghost(i,map[x][y],x,y)==true){                              // we check that there are no ghost in this cases
				south=false;                                      //if there is a ghost, you can't go south
			}
		}
	}

	if(x==0 || (x>0 && map[y][x-1]!=WALL && map[y][x-1]!=DOOR)){  //We check if pacman can go west (no wall or anything else)
		for (i=1;i<3;i++){                                        //we check the 3 positions up west
			if(checkghost(i,map[x][y],x,y)==true){                              // we check that there are no ghost in this cases
				west=false;                                      //if there is a ghost, you can't go west
			}
		}
	}

	for(j=0;j<4;j++){
		if(dir[j]==true){             //can we go north,east,south,west ?
			dir1[p]=j;                //if yes then we store the value of the direction in dir1. For instance if we can only go north then dir1 = [0]
			p+=1;
		}
	}
	switch(p){
		case 0: randomDirection;      //If we can go nowhere, do a bold move
		case 1: if(dir1[0]==0){		  //If we can only go in 1 direction then we find it and go
			d=NORTH;
		}
				if(dir1[0]==1){
			d=EAST;
		}

				if(dir1[0]==2){
			d=SOUTH;
		}

				if(dir1[0]==3){
			d=WEST;
		}

		case 2: coordghosts(*coordGhost1,*coordGhost2,*coordGhost3,*coordGhost4,*posghost,* *map,xsize,ysize); //If we can go in 2 directions, we retrieve the ghost's coordonates and find which way bring you to the farest point from the ghosts
		case 3: ; //Same idea than case 2
	}

   
  return d; // answer to the game engine
}

/*---------------------------------------------------------------------------------------------*/

// the code of your additional functions/procedures must be put below

bool checkghost(int i, char * * map, int x,int y){
	if(map[y-i][x]=="GHOST1" || map[y-i][x]=="GHOST2" || map[y-i][x]=="GHOST3" || map[y-i][x]=="GHOST4"){
		return true;                       //we check if the considered case is a ghost and return a bool
	}
	else return false;
}

char coordghosts(int * * coordGhost1, int * * coordGhost2, int * * coordGhost3, int * * coordGhost4,char * posghost,char * * map,int xsize,int ysize){
	int i; 
	int j;
	for(i=0;i<ysize+1;i++){      //Lines
		for(j=0;j<xsize+1;j++){  //colomns
			if(map[i][j]==GHOST1){
				*coordGhost1[0]=i;
				*coordGhost1[1]=j;
				posghost[0]=coordGhost1;
			}
			if(map[i][j]==GHOST2){
				*coordGhost2[0]=i;
				*coordGhost2[1]=j;
				posghost[1]=coordGhost1;
			}
			if(map[i][j]==GHOST3){
				*coordGhost3[0]=i;
				*coordGhost3[1]=j;
				posghost[2]=coordGhost1;
			}
			if(map[i][j]==GHOST4){
				*coordGhost4[0]=i;
				*coordGhost4[1]=j;
				posghost[3]=coordGhost1;
			}
		}
	}
}

direction randomDirection(bool north,bool east,bool south, bool west){
	bool ok=false;
	int d;
	do {
    d=rand()%4;
    if((d==NORTH && north)
       || (d==EAST && east)
       || (d==SOUTH && south)
       || (d==WEST && west)) {
      ok=true;
    }  
  } while(!ok);
  return d;
}
