/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>

#include "battleship.h"

CellContent my[FIELDSIZE][FIELDSIZE];
CellContent op[FIELDSIZE][FIELDSIZE];
CellContent guesses[FIELDSIZE][FIELDSIZE];


void load_game(){
FILE* my_fd = fopen("battleship.my", "r");
FILE* op_fd = fopen("battleship.op", "r");

for (int i = 0; i < FIELDSIZE; i++) {
  for (int j = 0; j < FIELDSIZE; j++) {
    fread(&my[i][j], sizeof(CellContent), 1, my_fd);
    fread(&op[i][j], sizeof(CellContent), 1, op_fd);
    guesses[i][j] = Unknown;
  }
}
fclose(my_fd);
fclose(op_fd);
}


CellContent get_shot(int row, int col){
  if (row < 0 || row > 9 || col < 0 || col > 9) {
    return OutOfRange;
  }
  else{
    return my[row][col];
  }
}


bool shoot(int row, int col){
  CellContent guess = get_my_guess(row, col);
  if (guess == OutOfRange || row < 0 || row > 9 || col < 0 || col > 9) {
    return false;
  }
  else if (op[row][col] == Water || op[row][col] == Boat) {
    guesses[row][col] = op[row][col];
    if (guesses[row][col] == Boat) {
      for (int i = row - 1; i < row + 2; i++) {
        for (int j = col - 1; j < col + 2; j++) {
          guess = get_my_guess(i, j);
          if (guess == Unknown) {
            guesses[i][j] = Water;
          }
        }
      }
    }
  }
return true;
}


CellContent get_my_guess(int row, int col){
  if (row < 0 || row > 9 || col < 0 || col > 9) {
    return OutOfRange;
  }
  else{
    return guesses[row][col];
  }
}
