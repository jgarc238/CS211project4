

// file:  bpgame.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "bpgame.h"
#include "simpleio.h"
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
}


extern BPGame * bp_create(int nrows, int ncols){

   char** m;
   m = (char**) malloc (sizeof(char*) * ncols);
   for(int i = 0; i < ncols; i++){
      m[i] = (char*) malloc (sizeof(char) * nrows);
   }
}


/*** IMPLEMENTATION OF bp_XXXX FUNCTIONS HERE  ****/

