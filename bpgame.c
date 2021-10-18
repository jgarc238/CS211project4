

// file:  bpgame.c

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "bpgame.h"


/** TYPEDEFS / STRUCTs HERE ***/


struct bpgame {

   char **m;// matrix that contains all the values
   int top;// used for push and pop of values
   int score;//holds the score for the user
   int row;//stores the number of rows
   int col;//stores the number of columns

};


BPGame * bp_create(int nrows, int ncols){
   
   BPGame * bp = malloc(sizeof(struct bpgame));
   
   if(nrows > MAX_ROWS || ncols > MAX_COLS){
      fprintf(stderr, "nrows or ncols is larger than 40");
      return NULL;
   }

   char** m1;
   bp->row = nrows;
   bp->col = ncols;
   m1 = (char**) malloc (sizeof(char*) * nrows);

   for(int i = 0; i < nrows; i++){
      m1[i] = (char*) malloc (sizeof(char) * ncols);
   }

   bp->m = m1;
   free(m1);

   srand(time(0));

   for(int i = 0; i < nrows; i++){
      for(int j = 0; j < ncols; j++){
         bp->m[i][j] = "^=o+"[rand () % 4]; 
      }
   }

   bp->top = -1;
   bp->score = 0;

   return bp;
}

BPGame * bp_create_from_mtx(char mtx[][MAX_COLS], int nrows, int ncols){

   BPGame * bp = malloc(sizeof(struct bpgame));

   if(nrows > MAX_ROWS || ncols > MAX_COLS){
      fprintf(stderr, "nrows or ncols is larger than 40");
      return NULL;
   }

   char** m1;
   bp->row = nrows;
   bp->col = ncols;
   m1 = (char**) malloc (sizeof(char*) * nrows);

   for(int i = 0; i < nrows; i++){
      m1[i] = (char*) malloc (sizeof(char) * ncols);
   }

   bp->m = m1;
   free(m1);

   for(int i = 0; i < nrows; i++){
      for(int j = 0; j < ncols; j++){
         if(mtx[i][j] != '^' || mtx[i][j] != '=' || mtx[i][j] != 'o' || mtx[i][j] != '+'){
            fprintf(stderr, "One of the values in the matrix given is not a color");
            return NULL;
         } 
         else{
            bp->m[i][j] = mtx[i][j];
         }
      }
   }

   return bp;
}

void bp_destroy(BPGame * b){

   for(int i = 0; i < b->row; i++){
      free(b->m[i]);
   }

   free(b->m);
}

void bp_display(BPGame * b){
   
}



