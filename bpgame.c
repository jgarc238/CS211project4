
/* 
Author: Jonathan Garcia, Viktoriia Moskova
UIN: jgarc238 , vmosk2
UIC
Fall 2021
*/

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
   //char **pMtx;matix that contains the matrix just incase user does undo
   int top;// used for push and pop of values
   int score;//holds the score for the user
   int row;//stores the number of rows
   int col;//stores the number of columns
   int count;//stores num of balloons popped
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

   srand(time(0));

   for(int i = 0; i < nrows; i++){
      for(int j = 0; j < ncols; j++){
         bp->m[i][j] = "^=o+"[rand () % 4];// inputs random color into matrix
      }
   }

   bp->count = 0;// sets num of ballons popped to 0
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

   bp->count = 0;// sets num of ballons popped to 0
   bp->score = 0;// sets score to 0

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

int pop(BPGame * b, int r, int c){

   int i;
   int j;
   int Ballon = 0;
   int check = 0;

   for(i = 0; i < b->row; i++){
      for(j = 0; j < b->col; j++){
         if(r == i && c == j){
            Ballon = bp_get_balloon(b, r, c);
            
            check=valid_bp_pop(b,r+1,c);
            if(check == 1){
               if(Ballon == b->m[i+1][j]){
                 // printf("need to pop up\n");
                  b->m[i][j] = '.';
                  //b->count++;
                  b->count = b->count + pop(b, r +1, c);
                  b->m[i+1][j] = '.';
                  //count++;
                  
               }
            }

            check=valid_bp_pop(b,r-1,c);
            if(check == 1){
               if(Ballon == b->m[i-1][j]){
                  //printf("need to pop down\n");
                  b->m[i][j] = '.';
                  //b->count++;
                  b->count = b->count + pop(b, r-1, c);
                  b->m[i-1][j] = '.';
                  //count++;
                  
               }
            } 

            check=valid_bp_pop(b,r,c+1);
            if(check == 1){
               if(Ballon == b->m[i][j+1]){
                  //printf("need to pop right\n");
                  b->m[i][j] = '.';
                  //b->count++;
                  b->count = b->count + pop(b, r, c+1);
                  b->m[i][j+1] = '.';
                  //count++;
                  
               }
            }   

            check=valid_bp_pop(b,r,c-1);
            if(check == 1){
               if(Ballon == b->m[i][j-1]){
                  //printf("need to pop left\n");
                  b->m[i][j] = '.';
                  //b->count++;
                  b->count = b->count + pop(b, r, c-1);
                  b->m[i][j-1] = '.';
                  //count++;
                  
               }
            }  
         }
      }
   }
   return b->count;
}

int bp_pop(BPGame * b, int r, int c){

   if(r > b->row && c > b->col){
      return 0;
   }

   int i;
   int j;
   int Ballon = 0;
   int check = 0;
   int loopBreak = 0;
   int skip = 0;
   int rpos = r;
   int cpos = c;
   int count;
   Ballon = bp_get_balloon(b, r, c);
   while(loopBreak == 0){
      for(i = 0; i < b->row; i++){
      for(j = 0; j < b->col; j++){
         if(rpos == i && cpos == j){
            
            check=valid_bp_pop(b,r+1,c);
            if(check == 1){
               if(Ballon == b->m[i+1][j]){
                 // printf("need to pop up\n");
                  b->m[i][j] = '.';
                  b->count++;
                  b->count = b->count + pop(b, r+1, c);
                  b->m[i+1][j] = '.';
                  b->count++;
                  skip = 1;
               }
            }

            check=valid_bp_pop(b,r-1,c);
            if(check == 1){
               if(Ballon == b->m[i-1][j]){
                  //printf("need to pop down\n");
                  b->m[i][j] = '.';
                  b->count++;
                  b->count = b->count + pop(b, r-1, c);
                  b->m[i-1][j] = '.';
                  b->count++;
                  skip = 1;
               }
            } 

            check=valid_bp_pop(b,r,c+1);
            if(check == 1){
               if(Ballon == b->m[i][j+1]){
                  //printf("need to pop right\n");
                  b->m[i][j] = '.';
                  b->count++;
                  b->count = b->count + pop(b, r, c+1);
                  b->m[i][j+1] = '.';
                  b->count++;
                  skip = 1;
               }
            }   

            check=valid_bp_pop(b,r,c-1);
            if(check == 1){
               if(Ballon == b->m[i][j-1]){
                  //printf("need to pop left\n");
                  b->m[i][j] = '.';
                  b->count++;
                  b->count = b->count + pop(b, r-1, c-1);
                  b->m[i][j-1] = '.';
                  b->count++;
                  skip = 1;
               }
            }  
         }
      }
      if(skip == 0){
         loopBreak = 1;
      }
      skip = 0;
   }
   }
   
   
   
   if(b->count > 0){
      b->count = b->count - 1;
      b->score = b->score + b->count * (b->count - 1);
      count = b->count;
      b->count = 0;
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

   for(i = 0; i < b->row; i++){
      for(j= 0; j < b->col; j++){
         if(r == i && c == j){
            if(b->m[i][j] == None){// checks for air
               return None;
            }
            else if(b->m[i][j] == Red){// checks for the color red
               return Red;
            }
            else if(b->m[i][j] == Blue){// checks for the color blue
               return Blue;
            }
            else if(b->m[i][j] == Yellow){// checks for the color yellow
               return Yellow;
            }
            else if(b->m[i][j] == Green){// checks for the color green
               return Green;
            }
         }
      }
         
   }

   return -1;
}

int bp_can_pop(BPGame * b){
   return -1;
}

int bp_undo(BPGame * b){


   return -1;
}

/*
int main(){

   BPGame * bp;
   bp = bp_create(8, 8);
   int num = 0;

   bp_display(bp);

   num = bp_pop(bp, 0, 0);

   printf("%d\n", num);

   bp_display(bp);

   bp_destroy(bp);
}
*/
