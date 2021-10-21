#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "bpgame.h"


/** TYPEDEFS / STRUCTs HERE ***/


struct bpgame {

   char **m;// matrix that contains all the values
   char **pMtx;//matix that contains the matrix just incase user does undo
   int top;// used for push and pop of values
   int score;//holds the score for the user
   int row;//stores the number of rows
   int col;//stores the number of columns

};


BPGame * bp_create(int nrows, int ncols){
   
   BPGame * bp = malloc(sizeof(struct bpgame));// creates a new struct
   
   if(nrows > MAX_ROWS || ncols > MAX_COLS){// checks if the input cols or rows are too large
      fprintf(stderr, "nrows or ncols is larger than 40");
      return NULL;
   }

   bp->row = nrows;// input rows into struct
   bp->col = ncols;//input cols into struct
   bp->m = (char**) malloc (sizeof(char*) * nrows);// allocate mem for matrix

   for(int i = 0; i < nrows; i++){
      bp->m[i] = (char*) malloc (sizeof(char) * ncols);
   }

   bp->pMtx = (char**) malloc (sizeof(char*) * nrows);// allocate mem for matrix

   for(int i = 0; i < nrows; i++){
      bp->pMtx[i] = (char*) malloc (sizeof(char) * ncols);
   }

   srand(time(0));

   for(int i = 0; i < nrows; i++){
      for(int j = 0; j < ncols; j++){
         bp->m[i][j] = "^=o+"[rand () % 4];// inputs random color into matrix
      }
   }

   bp->top = -1;// sets top to -1
   bp->score = 0;// sets score to 0

   return bp;
}

BPGame * bp_create_from_mtx(char mtx[][MAX_COLS], int nrows, int ncols){

   BPGame * bp = malloc(sizeof(struct bpgame));// creates a struct

   if(nrows > MAX_ROWS || ncols > MAX_COLS){// checks if the input cols or rows are too large
      fprintf(stderr, "nrows or ncols is larger than 40");
      return NULL;
   }

   bp->row = nrows;// input rows into struct
   bp->col = ncols;//input cols into struct
   bp->m = (char**) malloc (sizeof(char*) * nrows);// allocate mem for matrix

   for(int i = 0; i < nrows; i++){
      bp->m[i] = (char*) malloc (sizeof(char) * ncols);
   }

   bp->pMtx = (char**) malloc (sizeof(char*) * nrows);// allocate mem for matrix

   for(int i = 0; i < nrows; i++){
      bp->pMtx[i] = (char*) malloc (sizeof(char) * ncols);
   }


   for(int i = 0; i < nrows; i++){
      for(int j = 0; j < ncols; j++){

         if(mtx[i][j] == None){// checks for air
            continue;
         }

         else if(mtx[i][j] == Red){// checks for the color red
            continue;
         }
         else if(mtx[i][j] == Blue){// checks for the color blue
            continue;
         }
         else if(mtx[i][j] == Yellow){// checks for the color yellow
            continue;
         }
         else if(mtx[i][j] == Green){// checks for the color green
            continue;
         }
         else{// if neither then send error
            fprintf(stderr, "One of the values in the matrix given is not a color");
            return NULL;
         }
      }
   }
   

   for(int i = 0; i < nrows; i++){
      for(int j = 0; j < ncols; j++){
         bp->m[i][j] = mtx[i][j];// input values from mtx into the struct matrix
      }
   }

   return bp;
}

void bp_destroy(BPGame * b){

   for(int i = 0; i < b->row; i++){
      free(b->m[i]);// free the inner array
   }

   free(b->m);// free outer array
}

void bp_display(BPGame * b){
   int i;
   int j;

    for(i = 0; i < b->row; i++){
        for(j = 0; j < b->col; j++){
            printf("%c", b->m[i][j]);//print colors
        }
        printf("\n");// create a new line
    }
}
/*
void bp_display(BPGame * b){
   int i;
   int j;
   int counter = 0;

   for(i = 0; i < b->row; i++){
      if(i == 0 || i == b->row - 1){
         printf("+");
      }
      else{
         printf("-");
      }
   }

   printf("\n");
   
   for(i = 0; i < b->row; i++){
      printf("%d", i);
      printf("|");
      
      for(j = 0; j < b->col; j++){
         printf("%c", b->m[i][j]);
      }
      printf("\n");
   }

   for(i = 0; i < b->row; i++){
      if(i == 0 || i == b->row - 1){
         printf("+");
      }
      else{
         printf("-");
      }
   }
}
*/
void bp_display_STD(BPGame *b) {
   int i;
   int j;

    for(i = 0; i < b->row; i++){
        for(j = 0; j < b->col; j++){
            printf("%c", b->m[i][j]);
        }
        printf("\n");
    }
}

int valid_bp_pop(BPGame * b, int r, int c ) {
         if(r>-1 && r<b->row ){
            if(c>-1 && c<b->col ){
               return 1;
            }  
         }
   return 0;
}



int bp_pop(BPGame * b, int r, int c){

   if(r > b->row && c > b->col){
      return 0;
   }

   int i = 0;
   int j = 0;
   int Ballon = 0;
   int count = 0;
   int check =0;

   for(i = 0; i < b->row; i++){
      for(j = 0; j < b->col; j++){
         if(r == i || c == j){
            Ballon = bp_get_balloon(b, r, c);
            
            check=valid_bp_pop(b,r+1,c);
            if(check == 1){
               if(Ballon == b->m[i+1][j]){
                  b->m[i][j] = None;
                  bp_pop(b, r + 1, c);
                  count++;
               }
            }            
            check=valid_bp_pop(b,r-1,c);
            if(check == 1){
               if(Ballon == b->m[i-1][j]){
                  b->m[i][j] = None;
                  bp_pop(b, r - 1, c);
                  count++;
               }
            }
            
            check=valid_bp_pop(b,r,c+1);
            if(check == 1){
               if(Ballon == b->m[i][j+1]){
                  b->m[i][j] = None;
                  bp_pop(b, r, c + 1);
                  count++;
               }
            }
            
            check=valid_bp_pop(b,r,c-1);
            if(check == 1){
               if(Ballon == b->m[i][j-1]){
               b->m[i][j] = None;
               bp_pop(b, r, c - 1);
               count++;
            }
            }
            
            
         }
      }
   }

   if(count > 0){
      b->score = b->score + count * (count - 1);
      return count;
   }

   return 0;
}

int bp_is_compact(BPGame * b){
   return -1;
}

void bp_float_one_step(BPGame * b){

}

int bp_score(BPGame * b){
   return b->score;
}

int bp_get_balloon(BPGame * b, int r, int c){

   int i;
   int j;

   if(r > b->row || c > b->col){
      return -1;
   }
            if(b->m[i][j] == None){// checks for error
               return -1;
            }
   return b->m[r][c];
   
}

int bp_can_pop(BPGame * b){

   int check = 0;
   int i;
   int j;

   for(i = 0; i < b->row; i++){
      for(j = 0; j < b->col; j++){
         if(b->m[i][j] != None){
            check = 1;
         }
      }
   }

   if(check == 0){
      return 0;
   }

   else{

   }

   return -1;
}

int bp_undo(BPGame * b){

   int check = 0; // used to check if the undo function is needed
   int i; 
   int j;

   for(i = 0; i < b->row; i++){
      for(j = 0; j < b->col; j++){
         if(b->m[i][j] != b->pMtx[i][j]){
            check = 1;
         }
         else{
            continue;
         }
      }
   }

   if(check == 0){

   }

   else{

   }

   return -1;
}

int main(){

   BPGame * bp;
   bp = bp_create(5, 5);
   int num = 0;

   bp_display(bp);

   num = bp_pop(bp, 0, 0);

   printf("%d\n", num);

   bp_display(bp);

   bp_destroy(bp);
}
