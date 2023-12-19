/*
	This program is a simple speech synthesizer that uses a dual shock controller. This program 
aims to help people with limited mobility create sentences to communicate. This program takes an 
input of a word text file filename from the command file of the user's choosing (one is also available 
in the extensions folder of C projects). On the screen, the options from the word text file are laid 
into five columns with a cursor there to show what option is currently selected, and as the user types 
a sentence using the buttons, it appears at the bottom of the screen.
	The right joystick lets the user move the cursor however they would like to choose an option. 
The square button adds the option the cursor is currently on to the sentence displayed at the bottom 
of the page, and the triangle button does the same thing but adds a space before the option when added 
to the sentence. The X button allows the user to undo their past moves as much as they want. Pressing 
on the right joystick clears the sentence at the bottom.


	To use this program input in a Linux environment:
./ds4rd.exe -d "NUMBER OF CONTROLLER" -D DS4_BT -t -b -j -bt || ./Speech_Synthesizer_DS4.c wordslist.txt

ds4rd.exe and wordslist.txt can be found in the extensions folder. The word text file contains the 
whole alphabet, all the punctuations, and commonly used words.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <ncurses/ncurses.h>
#define MAXWORDS 100
#define WORDLEN 11
#define CURSER '*'
#define EMPTY_SPACE ' '
#include <math.h>
#include <string.h>


int readWords(char* wl[MAXWORDS], char* filename);
void draw_character(int x, int y, char use);
int close_to(int tolerance, int point, int value);
int moving(int rjoy_LR, int rjoy_UD);



int main(int argc, char* argv[]) {
	int time, b_T, b_C, b_X, b_S;
	int rj_P, lj_P, options, share;
	int R2, L2, R1, L1;
	int ljoy_LR, ljoy_UD, rjoy_LR, rjoy_UD;
	
	int currx, curry; //current x and current y
	int oldT = 0;

	char sentence[80] = ""; //the outputted string
	int sen_loc = 0; //location in sentence
	int nummove = 0; //number of outputed moves made
	int move[80]; //contains the index of the options in wordlist and -1 for spaces
	int index;
	
	char* wordlist[MAXWORDS];
	int wordCount;
	int i, j, k;
	wordCount = readWords(wordlist, argv[1]);
	

initscr();
refresh();

  
	i = 0;
    for (j = 0; j < (wordCount / 5); j++){
        for (k = 0; k < 75; k+=15){
            mvprintw(j, k + 5, "%s", wordlist[i]);
            refresh();
            i++;
        }
    }
	mvprintw(15, 5, "%s", wordlist[75]);
	refresh();
	
	//the initial location of the cursor
	draw_character(4, 0, CURSER);
	currx = 4;
	curry = 0;

	do {
		scanf("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
		&time, &b_T, &b_C, &b_X, &b_S, &rj_P, &lj_P, &options, &share, 
		&R2, &L2, &R1, &L1, &ljoy_LR, &ljoy_UD, &rjoy_LR, &rjoy_UD);
		//move cursor
		if (time != 0){
			if (time - oldT > 200){
				switch (moving(rjoy_LR, rjoy_UD)) {
					case 0:
					//down
						draw_character(currx, curry, EMPTY_SPACE);
						curry++;
						draw_character(currx, curry, CURSER);
						break;
					case 1: 
					//up
						draw_character(currx, curry, EMPTY_SPACE);
						curry--;
						draw_character(currx, curry, CURSER);
						break;
					case 2:
					//left
						draw_character(currx, curry, EMPTY_SPACE);
						currx -= 15;
						draw_character(currx, curry, CURSER);
						break;
					case 3: 
					//right
						draw_character(currx, curry, EMPTY_SPACE);
						currx += 15;
						draw_character(currx, curry, CURSER);
						break;
					} oldT = time;
			}
		}
		
		//making word selection
		if(b_T){
			index = (curry * 5) + ((currx - 4) / 15); //finding of the option selected in wordlist
			move[nummove] = (-1 * index);
			nummove++;
		}
		if(b_X){
			nummove--;
		}
		if(b_S){
			index = (curry * 5) + ((currx - 4) / 15);
			move[nummove] = index;
			nummove++;
		}
		if (rj_P){
			nummove = 0;
			sentence[0] = '\0';
		}

		for (int i = 0; i < nummove; i++){
			if (move[i] < 0){
				strcat(sentence, " ");
				strcat(sentence, wordlist[(-1 * move[i])]);
			}
			else {
				strcat(sentence, wordlist[move[i]]);
			}

		}


		mvprintw(18, 3, "%-80s", sentence);
		refresh();
		sentence[0] = '\0';

		//implemented because one click of the button would register as multiple clicks
		while ((b_T != 0) || (b_C != 0) || (b_X != 0) || (b_S != 0)){
			scanf("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
			&time, &b_T, &b_C, &b_X, &b_S, &rj_P, &lj_P, &options, &share, 
			&R2, &L2, &R1, &L1, &ljoy_LR, &ljoy_UD, &rjoy_LR, &rjoy_UD);
		}

	} while (options != 1);

    for(i = 0; i < wordCount; i++){
        free(wordlist[i]);
    }
	
	endwin();
    return 0;
}


int readWords(char* wl[MAXWORDS], char* filename){
	FILE* inputfile;
	int wordCount = 0;
	char string[WORDLEN];

	inputfile = fopen(filename, "r");

	if (inputfile == NULL){
		printf("Could not open %s\n", filename);
		return -1;
	}
	
	while(!feof(inputfile) && !ferror(inputfile)){
		if (fscanf(inputfile, "%s", string)){
			wl[wordCount] = malloc(strlen(string + 1));
			strcpy(wl[wordCount], string);
			wordCount++;
		}
		else{
			return -2;
		}
	}

	fclose(inputfile);
	return wordCount;
}

//aids in printing the cursor moving
void draw_character(int x, int y, char use){
	mvaddch(y,x,use);
	refresh();
	}

int close_to(int tolerance, int point, int value){
    return tolerance > abs(point - value);
   }

//determines what side the joystick is being moved
int moving(int rjoy_LR, int rjoy_UD){
    if  (close_to(70, rjoy_UD, 128)){
        return 0;
    }
    if  (close_to(70, rjoy_UD, -128)){
        return 1;
    }
    if  (close_to(70, rjoy_LR, -128)){
        return 2;
    }
	if  (close_to(70, rjoy_LR, 128)){
        return 3;
    }
    return -1;
   }

