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
bool checkghostE(char **,int,int,int);          //this module check if there is a ghost in a case
bool checkghostS(char **,int,int,int);          //this module check if there is a ghost in a case
bool checkghostW(char **,int,int);          //this module check if there is a ghost in a case
bool checkdiagSupGauche(char**,int,int);    //this module check if there is a ghost in the top lef diagonal
bool checkdiagSupDroite(char**,int,int,int);
bool checkdiagInfDroite(char**,int,int,int,int);
bool checkdiagInfGauche(char**,int,int,int);
void pacmanNoFear(int,int,int,int,char**,bool,bool,bool,bool,direction *,direction); //in order (x,y,xsize,ysize,map,north,east,south,west,&d)
void pacmanFear(int,int,int,int,char**,bool,bool,bool,bool,direction *,direction);
bool IsDoor(int ,int , int, int,direction *, direction); //In order (&x, &y ,xsize, ysize, d,lastdir),teleporting pacman in case of a door
void CanGoButNoPoint(int,int,char**,bool,bool,bool,bool,direction*,direction);
void CanGoPointOrGhost(int,int,char**,bool,bool,bool,bool,direction*);
void CanGoPoint(int,int,char**,bool,bool,bool,bool,direction*);


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
		 ) { //Beginning of main cod
  direction d; // the direction to return

  bool north=false; // indicate whether pacman can go north; no by default
  bool east=false; // indicate whether pacman can go east; no by default
  bool south=false; // indicate whether pacman can go south; no by default
  bool west=false; // indicate whether pacman can go west; no by default

/*-------------------------------------------------------------------------*/

if(energy && remainingenergymoderounds>=15){  //Beginning of IfEnergy

	if(IsDoor(x,y,xsize,ysize,&d,lastdirection)){	//teleporting pacman if he's standing in a door
		goto DoorTaken;
		}
	else {
		pacmanNoFear(x,y,xsize,ysize,map,north,east,south,west,&d, lastdirection);
		}

}	//End of Energy
else { //Beginning if else (No energy)
	
	if(IsDoor(x,y,xsize,ysize,&d,lastdirection)){
		goto DoorTaken;
		}
	else {
	pacmanFear(x,y,xsize,ysize,map,north,east,south,west,&d,lastdirection);
		}

}		//End of NoEnergy

	DoorTaken:;
	return d; // answer to the game engine
}  //End of main code


/*---------------------------------------------------------------------------------------------*/

// the code of your additional functions/procedures must be put below

bool checkghostN(char * * map, int x,int y){
	int i=1;
	if(y!=0){
		if(y<=2){
			if(map[y-1][x]==GHOST1 || map[y-1][x]==GHOST2 || map[y-1][x]==GHOST3 || map[y-1][x]==GHOST4 ){
				return true;
			} else return false;
		}
		for(i=1;i<4;i++){
			if(map[y-i][x]==GHOST1 || map[y-i][x]==GHOST2 || map[y-i][x]==GHOST3 || map[y-i][x]==GHOST4 ){
				//printf("ya un fantome nord \n");
				return true;                   //we check if the considered case is a ghost and return a bool
				break;
			}
		}
		return false;
	} else return false;
}

bool checkghostE(char * * map, int x,int y,int xsize){
	int i=1;

	if(x!=xsize-1){
	if(x<=xsize-2){
		if(map[y][x+1]==GHOST1 || map[y][x+1]==GHOST2 || map[y][x+1]==GHOST3 || map[y][x+1]==GHOST4){
			return true;
		} else return false;
	}
	for(i=1;i<4;i++){
		if(map[y][x+i]==GHOST1 || map[y][x+i]==GHOST2 || map[y][x+i]==GHOST3 || map[y][x+i]==GHOST4){
			return true;                   //we check if the considered case is a ghost and return a bool
			break;
		}
		else {
			//printf("ya pas fantome est\n");
		} 
	}
	return false;
	} else return false;
}

bool checkghostS(char * * map, int x,int y, int ysize){
	int i=1;

	if(y!=ysize-1){
	if(y>=ysize-3 && y!=ysize-1){	//if pacman is in the lower lines
		if(map[y+1][x]==GHOST1 || map[y+1][x]==GHOST2 || map[y+1][x]==GHOST3 || map[y+1][x]==GHOST4){
			return true;
		} else return false;
	}
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
	} else return false;
}

bool checkghostW(char * * map, int x,int y){
	int i=1;

	if(x!=0){
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
	} else return false;
}

bool checkdiagSupGauche(char * * map, int x,int y){
	if(x!=0 && y!=0){
	if(map[y-1][x-1]==GHOST1 || map[y-1][x-1]==GHOST2 || map[y-1][x-1]==GHOST3 || map[y-1][x-1]==GHOST4){
		return true;
	} else return false;
	} else return false;
}

bool checkdiagSupDroite(char ** map, int x,int y, int xsize){
	if(x!=xsize-1 && y!=0){
	if(map[y-1][x+1]==GHOST1 || map[y-1][x+1]==GHOST2 || map[y-1][x+1]==GHOST3 || map[y-1][x+1]==GHOST4){
		return true;
	} else return false;
	} return false;
}

bool checkdiagInfDroite(char ** map, int x,int y, int ysize, int xsize){
	if(y!=ysize-1 && x!=xsize-1){
	if(map[y+1][x+1]==GHOST1 || map[y+1][x+1]==GHOST2 || map[y+1][x+1]==GHOST3 || map[y+1][x+1]==GHOST4){
		return true;
	} else return false;
	} else return false;
}

bool checkdiagInfGauche(char ** map, int x,int y, int ysize){
	if(y!=ysize-1 && x!=0){
	if(map[y+1][x-1]==GHOST1 || map[y+1][x-1]==GHOST2 || map[y+1][x-1]==GHOST3 || map[y+1][x-1]==GHOST4){
		return true;
	} else return false;
	} else return false;
}

void pacmanNoFear(int x,int y,int xsize,int ysize,char ** map,bool north,bool east,bool south,bool west,direction * d, direction lastdirection){

		if(y>0 && map[y-1][x]!=WALL && map[y-1][x]!=DOOR){  //We check if pacman can go north (no wall or anything else)      
				north=true;                                    
			} else north=false;
	
		if(x<xsize-1 && map[y][x+1]!=WALL && map[y][x+1]!=DOOR){  //We check if pacman can go east (no wall or anything else)
			east=true;
			} else east=false;

		if(y<ysize-1 && map[y+1][x]!=WALL && map[y+1][x]!=DOOR){   //We check if pacman can go south (no wall or anything else)
			south=true;
			} else south=false;

		if(x>0 && map[y][x-1]!=WALL && map[y][x-1]!=DOOR){  //We check if pacman can go west (no wall or anything else)
			west=true;
			} else west=false;

	/*---------------------------------------------*/
	//Debug permettant de savoir quelles directions sont dispo
	// printf("lastdir : %d\n", lastdirection);
	// printf("x = %d, y = %d \n",x,y);
	// printf("ysize = %d\n", ysize);
	// printf("nord : %d\n",north);
	// printf("est : %d\n",east);
	// printf("sud : %d\n",south);
	// printf("ouest : %d\n",west);
	/*---------------------------------------------------------------------------------------------------------------------------*/

	if((north && map[y-1][x]!=PATH) || (east && map[y][x+1]!=PATH) || (south && map[y+1][x]!=PATH)|| (west && map[y][x-1]!=PATH)){  //If princ
		CanGoPointOrGhost(x,y,map,north,south,east,west,&d);
		goto outIF1;
	} //End if princ

	else { //Begin else 
		if(north || south || east || west){ //Begin if( n || s || e || w )
			CanGoButNoPoint(y,x,map,north,south,east,west,&d,lastdirection);
		} //end if( n || s || e || w )
	} // End else
	outIF1:;
} // End PacmanNoFear

void pacmanFear(int x,int y,int xsize,int ysize ,char** map,bool north,bool east,bool south,bool west,direction * d, direction lastdirection){

	if(y>0 && map[y-1][x]!=WALL && map[y-1][x]!=DOOR){  //We check if pacman can go north (no wall or anything else)  
			if(checkghostN(map,x,y)==true || checkdiagSupGauche(map,x,y)==true || checkdiagSupDroite(map,x,y,xsize)==true){                // we check that there are no ghost in this cases
				north=false;                                     //if there is a ghost, you can't go north
			} else north=true;

			if(map[y-1][x]==ENERGY){
				north=true;
			} 
			
	}

	if(x<xsize-1 && map[y][x+1]!=WALL && map[y][x+1]!=DOOR){  //We check if pacman can go east (no wall or anything else)
			if(checkghostE(map,x,y,xsize)==true || checkdiagSupDroite(map,x,y,xsize)==true || checkdiagInfDroite(map,x,y,ysize,xsize)==true){                              // we check that there are no ghost in this cases
				east=false;            //if there is a ghost, you can't go east
			}else east=true;
			if(map[y][x+1]==ENERGY){
				east=true;
				}
			
		
	}

	if(y<ysize-1 && map[y+1][x]!=WALL && map[y+1][x]!=DOOR){  //We check if pacman can go south (no wall or anything else)
		if(checkghostS(map,x,y,ysize)==true || checkdiagInfGauche(map,x,y,ysize)==true || checkdiagInfDroite(map,x,y,ysize,xsize)==true){                              // we check that there are no ghost in this cases
			south=false;                                      //if there is a ghost, you can't go south
		}else south=true;
		if(map[y+1][x]==ENERGY){
				south=true;
				}
		
	}

	if(x>0 && map[y][x-1]!=WALL && map[y][x-1]!=DOOR){  //We check if pacman can go west (no wall or anything else)
				if(checkghostW(map,x,y)==true || checkdiagInfGauche(map,x,y,ysize)==true || checkdiagSupGauche(map,x,y)==true){     // we check that there are no ghost in this cases
				west=false;                                      //if there is a ghost, you can't go west
			}else west=true;
			if(map[y][x-1]==ENERGY){
				west=true;
				} 
			
	}


	/*---------------------------------------------*/
	//Debug permettant de savoir quelles directions sont dispo

	// printf("lastdir :%d\n", lastdirection);
	// printf("nord : %d\n",north);
	// printf("est : %d\n",east);
	// printf("sud : %d\n",south);
	// printf("ouest : %d\n",west);

	/*---------------------------------------------------------------------------------------------------------------------------*/

	if((north && map[y-1][x]!=PATH) || (east && map[y][x+1]!=PATH) || (south && map[y+1][x]!=PATH)|| (west && map[y][x-1]!=PATH)){  //If princ
	CanGoPoint(x,y,map,north,south,east,west,&d);
	goto outIF2;
	} //End if princ

	else {
	if(north || south || east || west){

		CanGoButNoPoint(y,x,** map,north,south,east,west,&d,lastdirection);

	   } //end if after else

	} //End else
	outIF2:;
} //End else no energy

bool IsDoor(int x, int y ,int xsize, int ysize, direction * d, direction lastdirection){
	if(y==0 && lastdirection==0){
		*d=NORTH;
		return true;
	}
	if(y==ysize-1 && lastdirection==2){
		*d=SOUTH;
		return true;	
	}
	if(x==0 && lastdirection==3){
		*d=WEST;
		return true;
	}
	if(x==xsize-1 && lastdirection==1){
		*d=EAST;
		return true;
	}
	return false;
	}

void CanGoButNoPoint(int y,int x,char ** map, bool north, bool south, bool east, bool west, direction * d, direction lastdirection){
	if(north && map[y-1][x]==PATH){
		if(lastdirection==0){
			*d=NORTH;
			goto outCGBNP;
		} else *d=NORTH;

		if(lastdirection==2 && east){
			*d=EAST;
			goto outCGBNP;
		}
		if(lastdirection==2 && west){
			*d=WEST;
			goto outCGBNP;
		}
	} 

	if(east && map[y][x+1]==PATH){
		if(lastdirection==1){
			*d=EAST;
			goto outCGBNP;
		} else *d=EAST;

		if(lastdirection==3 && south){
			*d=SOUTH;
			goto outCGBNP;
		}

		if(lastdirection==3 && north){
			*d=NORTH;
			goto outCGBNP;
		}
	}

	if(south && map[y+1][x]==PATH){
		if(lastdirection==2){
			*d=SOUTH;
			goto outCGBNP;
			} else *d=SOUTH;

		if(lastdirection==0 && east){
			*d=EAST;
			goto outCGBNP;
			}
				
		if(lastdirection==0 && west){
			*d=WEST;
			goto outCGBNP;
		}
	}

	if(west && map[y][x-1]==PATH){
		if(y==11 && x==13 && north && west && east){
			*d=NORTH;
			goto outCGBNP;
			}
				
		if(lastdirection==3){
			*d=WEST;
			goto outCGBNP;
			} else *d=WEST;

		if(lastdirection==1 && south){
			*d=SOUTH;
			goto outCGBNP;
			}

		if(lastdirection==1 && north){
			*d=NORTH;
			goto outCGBNP;
		}
	}
	outCGBNP:;
}

void CanGoPointOrGhost(int x,int y,char**map,bool north,bool south,bool east,bool west,direction*d){
	if(north && (map[y-1][x]==VIRGIN_PATH || map[y-1][x]==ENERGY || map[y-1][x]==GHOST1 || map[y-1][x]==GHOST2 || map[y-1][x]==GHOST3 || map[y-1][x]==GHOST4)){
			*d=NORTH;
			goto outCGPOG;	
		}

		if(east && (map[y][x+1]==VIRGIN_PATH || map[y][x+1]==ENERGY || map[y][x+1]==GHOST1 || map[y][x+1]==GHOST2 || map[y][x+1]==GHOST3 || map[y][x+1]==GHOST4)){
			*d=EAST;
			goto outCGPOG;
		}

		if(south && (map[y+1][x]==VIRGIN_PATH || map[y+1][x]==ENERGY || map[y+1][x]==GHOST1 || map[y+1][x]==GHOST2 || map[y+1][x]==GHOST3 || map[y+1][x]==GHOST4)){
			*d=SOUTH;
			goto outCGPOG;
		}

		if(west && (map[y][x-1]==VIRGIN_PATH || map[y][x-1]==ENERGY || map[y][x-1]==GHOST1 || map[y][x-1]==GHOST2 || map[y][x-1]==GHOST3 || map[y][x-1]==GHOST4)){
			*d=WEST;
			goto outCGPOG;
		}
	outCGPOG:;
}

void CanGoPoint(int x,int y,char**map,bool north,bool south,bool east,bool west,direction*d){
	if(north && (map[y-1][x]==VIRGIN_PATH || map[y-1][x]==ENERGY)){
		*d=NORTH;
		goto outCGP;	
	}

	if(east && (map[y][x+1]==VIRGIN_PATH || map[y][x+1]==ENERGY)){
		*d=EAST;
		goto outCGP;
	}

	if(south && (map[y+1][x]==VIRGIN_PATH || map[y+1][x]==ENERGY)){
		*d=SOUTH;
		goto outCGP;
	}

	if(west && (map[y][x-1]==VIRGIN_PATH || map[y][x-1]==ENERGY)){
		*d=WEST;
		goto outCGP;
	}
	outCGP:;
}