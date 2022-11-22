// add the needed C libraries below
#include <stdbool.h> // bool, true, false
#include <stdlib.h> // rand
#include <math.h>
#include <stdio.h>

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

bool checkghostN(char **,int,int);          //this module check if there is a ghost in a case
bool checkghostE(char **,int,int);          //this module check if there is a ghost in a case
bool checkghostS(char **,int,int);          //this module check if there is a ghost in a case
bool checkghostW(char **,int,int);          //this module check if there is a ghost in a case
bool checkdiag1(char**,int,int);
bool checkdiag2(char**,int,int);
bool checkdiag3(char**,int,int);
bool checkdiag4(char**,int,int);

//char coordghosts(int*,int*,int*,int*,int**,char * *,int,int);       //this module find the ghosts and return their coordonates
direction randomDirection(bool,bool,bool,bool,bool);
//int MIN(int,int);

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
  //int q;
  int p=0;
  int dir1[4];  //for keeping the authorized direction after checking
  bool dir[4]; //for verifying where we can go and how many possibilities we have (which are saved in dir1)
  dir[0]=north;
  dir[1]=east;
  dir[2]=south;
  dir[3]=west;
  //int coordGhost1[2]; //Coordonates of ghost1
  //int coordGhost2[2]; //Coordonates of ghost2
  //int coordGhost3[2]; //Coordonates of ghost3
  //int coordGhost4[2]; //Coordonates of ghost4
  //int * posghost[4];   // tab with all the previous coordinates, modified by the coordghosts module

//Vectors for calculus relatives positions with coordghost

 // int v1[2];
  //int v2[2];
  //int v3[2];
  //int v4[2];

  //int vectpositions[8];

/*-------------------------------------------------------------------------*/
//dealing with top left door to transfer pacman to top right door
if(x==0 && y==9){
	map[x][y]=PATH;
	x=17;
	y=9;
}

//dealing with bottom left door
if(x==0 && y==11){
	map[x][y]=PATH;
	x=17;
	y=11;
}

//Top right door
if(x==17 && y==9){
	map[x][y]=PATH;
	x=0;
	y=9;
}

//Bottom left door
if(x==17 && y==11){
	map[x][y]=PATH;
	x=0;
	y=11;
}

/*--------------------------------------------------------------------------*/
/*Il faut que tu revois la stratégie pour les déplacement*/



/*--------------------------------------------------------------------------*/

	if(y==0 || (y>0 && map[y-1][x]!=WALL && map[y-1][x]!=DOOR)){  //We check if pacman can go north (no wall or anything else)  
			//printf("il rentre nord \n");
			if(checkghostN(map,x,y)==true && checkdiag1(map,x,y)==true && checkdiag2(map,x,y)==true){                // we check that there are no ghost in this cases
				north=false;                                     //if there is a ghost, you can't go north
			} else north=true;
			//printf("nord : %d\n",north); 
	}

	if(x==xsize-1 || (x<xsize-1 && map[y][x+1]!=WALL && map[y][x+1]!=DOOR)){  //We check if pacman can go east (no wall or anything else)
	//printf("il rentre east \n");    
		for (i=1;i<4;i++){                                        //we check the 3 positions up east
			if(checkghostE(map,x,y)==true && checkdiag2(map,x,y)==true && checkdiag3(map,x,y)==true){                              // we check that there are no ghost in this cases
				east=false;                                      //if there is a ghost, you can't go east
			} else east=true;
			//printf("est : %d\n",east);
		}
	}

	if(y==ysize-1 || (y<ysize-1 && map[y+1][x]!=WALL && map[y+1][x]!=DOOR)){  //We check if pacman can go south (no wall or anything else)
	//printf("il rentre sud \n");
		for (i=1;i<4;i++){                                        //we check the 3 positions up south
			if(checkghostS(map,x,y)==true && checkdiag4(map,x,y)==true && checkdiag3(map,x,y)==true){                              // we check that there are no ghost in this cases
				south=false;                                      //if there is a ghost, you can't go south
			} else south=true;
			//printf("sud : %d\n",south);
		}
	}

	if(x==0 || (x>0 && map[y][x-1]!=WALL && map[y][x-1]!=DOOR)){  //We check if pacman can go west (no wall or anything else)
	//printf("il rentre ouest \n");
		for (i=1;i<4;i++){                                        //we check the 3 positions up west
			if(checkghostW(map,x,y)==true && checkdiag4(map,x,y)==true && checkdiag1(map,x,y)==true){                              // we check that there are no ghost in this cases
				west=false;                                      //if there is a ghost, you can't go west
			} else west=true;
			//printf("ouest : %d\n",west);
		}
	}

/*---------------------------------------------------------------------------------------------------------------------------*/


	for(j=0;j<4;j++){
		if(dir[j]==true){             //can we go north,east,south,west ?
			dir1[p]=true;  
			p+=1;              //if yes then we store the value of the direction in dir1. For instance if we can only go north then dir1 = [0]
		} else dir1[p]=false;
		
	}
	switch(p){
		case 0: d=randomDirection(north, east, south,west,ok);      //If we can go nowhere, do a bold move
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

		case 2: 

				if(dir1[0]==0){
					if(map[y-1][x]==VIRGIN_PATH || map[y-1][x]==ENERGY){
					d=NORTH;
					}
				}
				
				if(dir1[0]==1){
					if(map[y][x+1]==VIRGIN_PATH || map[y][x+1]==ENERGY){
					d=EAST;
					}					}

				if(dir1[0]==2){
					if(map[y+1][x]==VIRGIN_PATH || map[y+1][x]==ENERGY){
						d=SOUTH;
					}
				}
				
				if(dir1[0]==3){
					if(map[y][x-1]==VIRGIN_PATH || map[y][x-1]==ENERGY){
						d=WEST;
					}
				}

				if(d!=NORTH || d!=EAST || d!=SOUTH || d!=WEST){
					if(map[x][y-1]==PATH){
						d=NORTH;
					}

						if(map[x+1][y]==PATH){
							d=EAST;
						}

						if(map[x][y+1]==PATH){
							d=SOUTH;
						}

						if(map[x-1][y]==PATH){
							d=WEST;
						}
					}
			
		case 3: if(north && (map[y-1][x]==VIRGIN_PATH || map[y-1][x]==ENERGY)){
			d=NORTH;
		}
		if(east && (map[y][x+1]==VIRGIN_PATH || map[y][x+1]==ENERGY)){
			d=EAST;
		}
		if(south && (map[y+1][x]==VIRGIN_PATH || map[y+1][x]==ENERGY)){
			d=SOUTH;
		}
		if(west && (map[y][x-1]==VIRGIN_PATH || map[y][x-1]==ENERGY)){
			d=WEST;
		}
		if(d!=NORTH || d!=EAST || d!=SOUTH || d!=WEST){
						if(map[x][y-1]==PATH){
							d=NORTH;
						}

						if(map[x+1][y]==PATH){
							d=EAST;
						}

						if(map[x][y+1]==PATH){
							d=SOUTH;
						}

						if(map[x-1][y]==PATH){
							d=WEST;
						}
					}



		case 4:  if(north && map[y-1][x]==VIRGIN_PATH){
			d=NORTH;
		}
		if(east && map[y][x+1]==VIRGIN_PATH){
			d=EAST;
		}
		if(south && map[y+1][x]==VIRGIN_PATH){
			d=SOUTH;
		}
		if(west && map[y][x-1]==VIRGIN_PATH){
			d=WEST;
		}
		if(d!=NORTH || d!=EAST || d!=SOUTH || d!=WEST){
						if(map[x][y-1]==PATH){
							d=NORTH;
						}

						if(map[x+1][y]==PATH){
							d=EAST;
						}

						if(map[x][y+1]==PATH){
							d=SOUTH;
						}

						if(map[x-1][y]==PATH){
							d=WEST;
						}
					}
	}

   
  return d; // answer to the game engine
}

/*---------------------------------------------------------------------------------------------*/

// the code of your additional functions/procedures must be put below

bool checkghostN(char * * map, int x,int y){
	int i=1;
	for(i=1;i<4;i++){
		if(map[y-i][x]==GHOST1 || map[y-i][x]==GHOST2 || map[y-i][x]==GHOST3 || map[y-i][x]==GHOST4 ){
			//printf("ya un fantome nord \n");
			return true;                   //we check if the considered case is a ghost and return a bool
			break;
		}
		else {
			//printf("ya pas fantome nord\n");
		} 
	}
	return false; 
}

bool checkghostE(char * * map, int x,int y){
	int i=1;
	for(i=1;i<4;i++){
		if(map[y][x+i]==GHOST1 || map[y][x+i]==GHOST2 || map[y][x+i]==GHOST3 || map[y][x+i]==GHOST4 ){
			//printf("ya un fantome est \n");
			return true;                   //we check if the considered case is a ghost and return a bool
			break;
		}
		else {
			//printf("ya pas fantome est\n");
		} 
	}
	return false;
}

bool checkghostS(char * * map, int x,int y){
	int i=1;
	for(i=1;i<4;i++){
		if(map[y+i][x]==GHOST1 || map[y+i][x]==GHOST2 || map[y+i][x]==GHOST3 || map[y+i][x]==GHOST4 ){
			//printf("ya un fantome sud \n");
			return true;                   //we check if the considered case is a ghost and return a bool
			break;
		}
		else {
			//printf("ya pas fantome sud\n");
		} 
	}
	return false;
}

bool checkghostW(char * * map, int x,int y){
	int i=1;
	for(i=1;i<4;i++){
		if(map[y][x-i]==GHOST1 || map[y][x-i]==GHOST2 || map[y][x-i]==GHOST3 || map[y][x-i]==GHOST4 ){
			//printf("ya un fantome ouest \n");
			return true;                   //we check if the considered case is a ghost and return a bool
			break;
		}
		else {
			//printf("ya pas fantome ouest\n");
		} 
	}
	return false;
}






bool checkdiag1(char ** map, int x,int y){
	if(map[y-1][x-1]==GHOST1 || map[y-1][x-1]==GHOST2 || map[y-1][x-1]==GHOST3 || map[y-1][x-1]==GHOST4){
		return true;
	} else return false;
}

bool checkdiag2(char ** map, int x,int y){
	if(map[y-1][x+1]==GHOST1 || map[y-1][x+1]==GHOST2 || map[y-1][x+1]==GHOST3 || map[y-1][x+1]==GHOST4){
		return true;
	} else return false;
}

bool checkdiag3(char ** map, int x,int y){
	if(map[y+1][x+1]==GHOST1 || map[y+1][x+1]==GHOST2 || map[y+1][x+1]==GHOST3 || map[y+1][x+1]==GHOST4){
		return true;
	} else return false;
}

bool checkdiag4(char ** map, int x,int y){
	if(map[y+1][x-1]==GHOST1 || map[y+1][x-1]==GHOST2 || map[y+1][x-1]==GHOST3 || map[y+1][x-1]==GHOST4){
		return true;
	} else return false;
}


/*char coordghosts(int * coordGhost1, int * coordGhost2, int * coordGhost3, int * coordGhost4,int * * posghost,char * * map,int xsize,int ysize){
	int i; 
	int j;
	for(i=0;i<ysize+1;i++){      //Lines
		for(j=0;j<xsize+1;j++){  //colomns
			if(map[i][j]==GHOST1){
				coordGhost1[0]=i;
				coordGhost1[1]=j;
				posghost[0]=coordGhost1;
			}
			if(map[i][j]==GHOST2){
				coordGhost2[0]=i;
				coordGhost2[1]=j;
				posghost[1]=coordGhost2;
			}
			if(map[i][j]==GHOST3){
				coordGhost3[0]=i;
				coordGhost3[1]=j;
				posghost[2]=coordGhost3;
			}
			if(map[i][j]==GHOST4){
				coordGhost4[0]=i;
				coordGhost4[1]=j;
				posghost[3]=coordGhost4;
			}
		}
	}
} */

direction randomDirection(bool north,bool east,bool south, bool west, bool ok){
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

/* int MIN(int x,int y){
	if(x>=y){
		return y;
	}
	else return x;
}
*/