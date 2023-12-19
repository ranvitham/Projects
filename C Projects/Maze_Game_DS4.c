/*
  The goal of this game is to have the avatar escape a randomized maze that has a 
difficulty (0-100) of the player's choosing. The avatar can only move left, right, or 
down which the player indicates by moving/tilting the DS4 in the direction they desire.
The game ends when the avatar gets stuck in a "bucket" where it can't move
down any further.
  To use to this program input into a Linux environment:
  ./ds4rd.exe -t -g -b || ./Maze_Game_DS4.c "LEVEL OF DIFFCULTLY"
  ds4rd.exe can be found in the extensions folder of C projects.
*/

// Headers
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ncurses/ncurses.h>
#include <unistd.h>

// Mathematical constants
#define PI 3.14159

// Screen geometry
#define NUMCOLS 100
#define NUMROWS 72

// Character definitions taken from the ASCII table
#define AVATAR 'A'
#define WALL '*'
#define EMPTY_SPACE ' '


// 2D character array which the maze is mapped into
char MAZE[NUMROWS][NUMCOLS];

void generate_maze(int difficulty);
void draw_maze(void);
void draw_character(int x, int y, char use); 
float calc_roll(float x_mag);
int close_to(double tolerance, double point, double value);
int moving(double gx);



int main(int argc, char* argv[])
{
	int time;
	double gx, gy, gz;
	int x = NUMROWS/2; //numcols prints AVATAR off center
	int y = 0;
	int nX = x;
	int nY = y;
	int oldT = 0;
	int valid = 0;
	int end = 0;
	
	if (argc <2) { printf("You forgot the difficulty\n"); return 1;}
	int difficulty = atoi(argv[1]); // get difficulty from first command line arg
	// setup screen    
	initscr();
	refresh();
	int start = 0;
	
	// Generate and draw the maze, with initial avatar
	generate_maze(difficulty);
	draw_maze();
	draw_character(x, y, AVATAR);   

	// Event loop
	do
	{
		scanf("%d, %lf, %lf, %lf", &time, &gx, &gy, &gz);
		
		
		
		if (time != 0){
			if (time - oldT > 500){
				
				if ((MAZE[nY+1][nX] != EMPTY_SPACE) &&(MAZE[nY][nX+1] != EMPTY_SPACE) &&(MAZE[nY][nX-1] != EMPTY_SPACE)){
					end = 1;
					break;
				}
				
				//at current postion cannot drop down
				if (MAZE[nY+1][nX] != EMPTY_SPACE){
					//checking if right is empty
					for (int i = 1; i < NUMROWS; i++){
						if (MAZE[nY][nX+i] == EMPTY_SPACE){
							if (MAZE[nY+1][nX+i] == EMPTY_SPACE){
								valid++;
							}
						}
						else{
							i = NUMROWS;
						}
					}
					//checking if left is empty
					for (int i = 1; i < NUMROWS; i++){
						if (MAZE[nY][nX-i] == EMPTY_SPACE){
							if (MAZE[nY+1][nX-i] == EMPTY_SPACE){
								valid++;
							}
						}
						else{
							i = NUMROWS;
						}
					}
					
					if (valid == 0){
						end = 2;
						break;
					}
				}
			
			
				switch (moving(calc_roll(gx))) {
					case 0:
						if (MAZE[nY+1][nX] == EMPTY_SPACE){
							draw_character(nX, nY, EMPTY_SPACE);
							nY++; //drops down
							draw_character(nX, nY, AVATAR);
						}
						break;
					case 1: 
						if (MAZE[nY][nX+1] == EMPTY_SPACE){
							draw_character(nX, nY, EMPTY_SPACE);
							nX++; //moves right
							draw_character(nX, nY, AVATAR);
						}
						break;
					case 2: 
						if (MAZE[nY][nX-1] == EMPTY_SPACE){
							draw_character(nX, nY, EMPTY_SPACE);
							nX--; //moves left
							draw_character(nX, nY, AVATAR);
						}
						break;
					}
				oldT = time;
			}
		}
		
       
		

	} while(nY < NUMROWS - 1);

	endwin();
	// Print the win message
	if (end == 0){
		printf("YOU WIN!\n");
	}
	if (end == 1){
		printf("YOU LOST AND GOT STUCK!\n");
	}
	if (end == 2){
		printf("YOU LOSE!\n");
	}
	
	return 0;
}



// PRE: 0 < x < COLS, 0 < y < ROWS, 0 < use < 255
// POST: Draws character use to the screen and position x,y
//THIS CODE FUNCTIONS FOR PLACING THE AVATAR AS PROVIDED.
void draw_character(int x, int y, char use)
{
	mvaddch(y,x,use);    
	refresh();
}



// POST: Generates a random maze structure into MAZE[][]
void generate_maze(int difficulty){
	for (int i = 0; i < NUMROWS; i++){
		for (int j = 0; j < NUMCOLS; j++){
			if ((rand() % 100) < difficulty){
				MAZE[i][j] = WALL;
			}
			else{
				MAZE[i][j] = EMPTY_SPACE;
			}
		}
	}
}

// PRE: MAZE[][] has been initialized by generate_maze()
// POST: Draws the maze to the screen 
void draw_maze(void){
	for (int i = 0; i < NUMROWS; i++){
		for (int j = 0; j < NUMCOLS; j++){
			draw_character(j, i, MAZE[i][j]);
		}
	}
}

int close_to(double tolerance, double point, double value){
    return tolerance > fabs(point - value);
   }

// PRE: -1.0 < x_mag < 1.0
// POST: Returns tilt magnitude scaled to -1.0 -> 1.0
float calc_roll(float x_mag){
	return asin(x_mag);
}

int moving(double gx){
    if  (close_to(0.3, gx, 0)){
        return 0;
    }
    if  (close_to(0.3, gx, -1.0)){
        return 1;
    }
    if  (close_to(0.3, gx, 1.0)){
        return 2;
    }
    return -1;
   }
