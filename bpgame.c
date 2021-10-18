

// file:  bpgame.c

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "bpgame.h"

//#include MAX_ROWS 40
//#include MAX_COLS 40


/** #include statements... **/



/** TYPEDEFS / STRUCTs HERE ***/


struct bpgame {


   // YOU DECIDE WHAT TO PUT IN HERE TO CAPTURE THE STATE OF
   //   A "RUN" OF THE GAME.....

   char **m;// matrix that contains all the values
   int size;// size of the matrix
   int top;// used for push and pop of values
   int score;//holds the score for the user
};


BPGame * bp_create(int nrows, int ncols){
   
   BPGame * bp = malloc(sizeof(struct bpgame));
   
   char** m1;
   m1 = (char**) malloc (sizeof(char*) * ncols);
   for(int i = 0; i < ncols; i++){
      m1[i] = (char*) malloc (sizeof(char) * nrows);
   }

   bp->m = m1;
   bp->top = -1;
   bp->score = 0;

}


/*** IMPLEMENTATION OF bp_XXXX FUNCTIONS HERE  ****/

