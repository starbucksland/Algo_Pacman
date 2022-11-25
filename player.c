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
bool checkdiagSupGauche(char**,int,int);    //this module check if there is a ghost in the top lef diagonal
bool checkdiagSupDroite(char**,int,int);
bool checkdiagInfDroite(char**,int,int);
bool checkdiagInfGauche(char**,int,int);


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
		 ) { //Beginning of main code
  direction d; // the direction to return

  bool north=false; // indicate whether pacman can go north; no by default
  bool east=false; // indicate whether pacman can go east; no by default
  bool south=false; // indicate whether pacman can go south; no by default
  bool west=false; // indicate whether pacman can go west; no by default
  int i;   //for the checking of the cases ahead

/*-------------------------------------------------------------------------*/

if(energy){  //Beginning of IfEnergy
	//dealing with top left door to transfer pacman to top right door
	if(x==0 && y==9){
		printf("Porte sup gauche\n");
		x=18;
		y=9;
	}

//dealing with bottom left door
	if(x==0 && y==11){
		printf("Porte inf gauche\n");
		x=18;
		y=11;
	}

//Top right door
	if(x==18 && y==9){
		printf("Porte sup droite\n");
		x=0;
		y=9;
	}

//Bottom left door
	if(x==18 && y==11){
		printf("Porte inf droite\n");
		x=0;
		y=11;
	}

		if(y==0 || (y>0 && map[y-1][x]!=WALL && map[y-1][x]!=DOOR)){  //We check if pacman can go north (no wall or anything else)      
				north=false;                                    
			} else north=true;
	
		if(x==xsize-1 || (x<xsize-1 && map[y][x+1]!=WALL && map[y][x+1]!=DOOR)){  //We check if pacman can go east (no wall or anything else)
			east=false;
			} else east=true;

		if(y==ysize-1 || (y<ysize-1 && map[y+1][x]!=WALL && map[y+1][x]!=DOOR)){  //We check if pacman can go south (no wall or anything else)
			south=false;
			} else south=true;

		if(x==0 || (x>0 && map[y][x-1]!=WALL && map[y][x-1]!=DOOR)){  //We check if pacman can go west (no wall or anything else)
			west=false;
			} else west=true;

/*---------------------------------------------*/
//Debug permettant de savoir quelles directions sont dispo

	printf("nord : %d\n",north);
	printf("est : %d\n",east);
	printf("sud : %d\n",south);
	printf("ouest : %d\n",west);

/*---------------------------------------------------------------------------------------------------------------------------*/

if((north && map[y-1][x]!=PATH) || (east && map[y][x+1]!=PATH) || (south && map[y+1][x]!=PATH)|| (west && map[y][x-1]!=PATH)){  //If princ
	printf("1er cas \n");

	if(north && (map[y-1][x]==VIRGIN_PATH || map[y-1][x]==ENERGY)){
		d=NORTH;
		printf("il va nord\n");
		goto outIF;	
	}

	if(east && (map[y][x+1]==VIRGIN_PATH || map[y][x+1]==ENERGY)){
		d=EAST;
		printf("il va est\n");
		goto outIF;
	}

	if(south && (map[y+1][x]==VIRGIN_PATH || map[y+1][x]==ENERGY)){
		d=SOUTH;
		printf("il va sud\n");
		goto outIF;
	}

	if(west && (map[y][x-1]==VIRGIN_PATH || map[y][x-1]==ENERGY)){
		d=WEST;
		printf("il va ouest\n");
		goto outIF;
	}

} //End if princ

else {
	printf("2eme cas\n");
	if(north || south || east || west){
		if(north && map[y-1][x]==PATH){
			d=NORTH;
			goto outIF;
		}

		if(east && map[y][x+1]==PATH){
			d=EAST;
			goto outIF;
		}

		if(south && map[y+1][x]==PATH){
			d=SOUTH;
			goto outIF;
		}

		if(west && map[y][x-1]==PATH){
			d=WEST;
			goto outIF;
		}
	} //end if after else
} //End else

	
} //End if Energy


else { //Beginning if else (No energy)
	//dealing with top left door to transfer pacman to top right door
if(x==0 && y==9){
	printf("Porte sup gauche\n");
	x=18;
	y=9;
}

//dealing with bottom left door
if(x==0 && y==11){
	printf("Porte inf gauche\n");
	x=18;
	y=11;
}

//Top right door
if(x==18 && y==9){
	printf("Porte sup droite\n");
	x=0;
	y=9;
}

//Bottom left door
if(x==18 && y==11){
	printf("Porte inf droite\n");
	x=0;
	y=11;
}

/*--------------------------------------------------------------------------*/
/*Il faut que tu revois la stratégie pour les déplacement*/

/*--------------------------------------------------------------------------*/

	if(y==0 || (y>0 && map[y-1][x]!=WALL && map[y-1][x]!=DOOR)){  //We check if pacman can go north (no wall or anything else)  
			//printf("il rentre nord \n");
			if(checkghostN(map,x,y)==true || checkdiagSupGauche(map,x,y)==true || checkdiagSupDroite(map,x,y)==true){                // we check that there are no ghost in this cases
				north=false;                                     //if there is a ghost, you can't go north
			} else north=true;
			//printf("nord : %d\n",north); 
	}


	if(x==xsize-1 || (x<xsize-1 && map[y][x+1]!=WALL && map[y][x+1]!=DOOR)){  //We check if pacman can go east (no wall or anything else)
	//printf("il rentre east \n");    
		for (i=1;i<4;i++){                                        //we check the 3 positions up east
			if(checkghostE(map,x,y)==true || checkdiagSupDroite(map,x,y)==true || checkdiagInfDroite(map,x,y)==true){                              // we check that there are no ghost in this cases
				east=false;                                      //if there is a ghost, you can't go east
			} else east=true;
			//printf("est : %d\n",east);
		}
	}

	if(y==ysize-1 || (y<ysize-1 && map[y+1][x]!=WALL && map[y+1][x]!=DOOR)){  //We check if pacman can go south (no wall or anything else)
	//printf("il rentre sud \n");
		for (i=1;i<4;i++){                                        //we check the 3 positions up south
			if(checkghostS(map,x,y)==true || checkdiagInfGauche(map,x,y)==true || checkdiagInfDroite(map,x,y)==true){                              // we check that there are no ghost in this cases
				south=false;                                      //if there is a ghost, you can't go south
			} else south=true;
			//printf("sud : %d\n",south);
		}
	}

	if(x==0 || (x>0 && map[y][x-1]!=WALL && map[y][x-1]!=DOOR)){  //We check if pacman can go west (no wall or anything else)
		//printf("il rentre ouest \n");
		for (i=1;i<4;i++){                                        //we check the 3 positions up west
			if(checkghostW(map,x,y)==true || checkdiagInfGauche(map,x,y)==true || checkdiagSupGauche(map,x,y)==true){                              // we check that there are no ghost in this cases
				west=false;                                      //if there is a ghost, you can't go west
			} else west=true;
			//printf("ouest : %d\n",west);
		}
	}

/*---------------------------------------------*/
//Debug permettant de savoir quelles directions sont dispo

	printf("nord : %d\n",north);
	printf("est : %d\n",east);
	printf("sud : %d\n",south);
	printf("ouest : %d\n",west);

/*---------------------------------------------------------------------------------------------------------------------------*/

if((north && map[y-1][x]!=PATH) || (east && map[y][x+1]!=PATH) || (south && map[y+1][x]!=PATH)|| (west && map[y][x-1]!=PATH)){  //If princ
	printf("1er cas \n");

	if(north && (map[y-1][x]==VIRGIN_PATH || map[y-1][x]==ENERGY)){
		d=NORTH;
		printf("il va nord\n");
		goto outIF;	
	}

	if(east && (map[y][x+1]==VIRGIN_PATH || map[y][x+1]==ENERGY)){
		d=EAST;
		printf("il va est\n");
		goto outIF;
	}

	if(south && (map[y+1][x]==VIRGIN_PATH || map[y+1][x]==ENERGY)){
		d=SOUTH;
		printf("il va sud\n");
		goto outIF;
	}

	if(west && (map[y][x-1]==VIRGIN_PATH || map[y][x-1]==ENERGY)){
		d=WEST;
		printf("il va ouest\n");
		goto outIF;
	}

} //End if princ

else {
	printf("2eme cas\n");
	if(north || south || east || west){
		if(north && map[y-1][x]==PATH){
			d=NORTH;
			goto outIF;
		}

		if(east && map[y][x+1]==PATH){
			d=EAST;
			goto outIF;
		}

		if(south && map[y+1][x]==PATH){
			d=SOUTH;
			goto outIF;
		}

		if(west && map[y][x-1]==PATH){
			d=WEST;
			goto outIF;
		}
	} //end if after else

} //End else

} //End else no energy

/*-------------------------------------------------------------------------*/

outIF:
  return d; // answer to the game engine
}  //End of main code


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
			printf("ya un fantome est \n");
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

bool checkdiagSupGauche(char * * map, int x,int y){
	if(map[y-1][x-1]==GHOST1 || map[y-1][x-1]==GHOST2 || map[y-1][x-1]==GHOST3 || map[y-1][x-1]==GHOST4){
		printf("Ya diag sup gauche\n");
		return true;
	} else return false;
}

bool checkdiagSupDroite(char ** map, int x,int y){
	if(map[y-1][x+1]==GHOST1 || map[y-1][x+1]==GHOST2 || map[y-1][x+1]==GHOST3 || map[y-1][x+1]==GHOST4){
		printf("Ya diag sup droite\n");
		return true;
	} else return false;
}

bool checkdiagInfDroite(char ** map, int x,int y){
	if(map[y+1][x+1]==GHOST1 || map[y+1][x+1]==GHOST2 || map[y+1][x+1]==GHOST3 || map[y+1][x+1]==GHOST4){
		printf("Ya diag inf droite\n");
		return true;
	} else return false;
}

bool checkdiagInfGauche(char ** map, int x,int y){
	if(map[y+1][x-1]==GHOST1 || map[y+1][x-1]==GHOST2 || map[y+1][x-1]==GHOST3 || map[y+1][x-1]==GHOST4){
		printf("Ya diag inf gauche\n");
		return true;
	} else return false;
}

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
