// Preet Panchal
// 100707094
// CSCI1060U - LAB07
// CRN: 43916 
// November 08, 2020

//Create a Connect 4 Game
#include <iostream>
#include <string>

using namespace std;

//Global constants for the game pieces
const char EMP = '-';
const char P1 = 'X';
const char P2 = 'O';

//global variables/constants for the game board
const int COLS = 7;
const int ROWS = 6;
char board[COLS][ROWS]; //2D array of 7x6 connect 4 board

//Initialize the board to be empty
void initializeBoard();

//Display the board
void displayBoard();

//Get column for current move
int getColumn(bool isPlayer1);

//Add one piece to the Board
bool addPiece(int c, bool isPlayer1);

//Check Diagonals from Top left to Bottom Right 
int diagonalLtoR(char currTile, int cxLR, int ryLR); 

//Check Diagonals from Bottom Left to Top Right
int diagonalRtoL(char currTile, int cxRL, int ryRL); 

//Check if a given player has won
bool isWinner(bool isPlayer1, int lastCol);

int main() {
  //Initialize game
  //TO DO: Add code to randomize first player
  int totalMoves = 0; //number of moves by both players
  const int MAX_MOVES = COLS * ROWS; //total cells on the board
  bool playerOne = true; //boolean to keep track of current player
  bool gameWon = false; //boolean to keep track if game won
  int column = -1;

  initializeBoard();
  displayBoard();

  //Game play loop
  //loop until game is won or the board is full
  while ((!gameWon) && (totalMoves < MAX_MOVES)) {
    bool validMove = false;

    while (!validMove) {
      column = getColumn(playerOne);
      validMove = addPiece(column, playerOne);
      if (!validMove) {
        cout << "Invalid move. Try again." << endl;
      }
    }

    totalMoves++;
    displayBoard();

    //Check if game is won
    gameWon = isWinner(playerOne, column);
    if (gameWon) {
      cout << "CONGRATULATIONS Player " << (playerOne ? "1" : "2")
            << ". You've won Connect 4!!!!" << endl;
    } else if (totalMoves == MAX_MOVES) {
      cout << "Game over! No moves remaining." << endl;
    } else {
      playerOne = !playerOne; //switch player
    }
  }



  return 0;
}

void initializeBoard() {
  //Loops through each column
  for (int c = 0; c < COLS; c++) {
    //Loop through each row in a given column
    for (int r = 0; r < ROWS; r++){
      board[c][r] = EMP; //initialize all cells to empty
    }
  }
}

void displayBoard() {
  cout << endl << "Connect 4 Board:" << endl;
  //Display the board one row at a time
  for (int r = 0; r < ROWS; r++) {
    //For each row display all of the columns
    for (int c = 0; c < COLS; c++) {
      cout << board[c][r] << " ";
    }
    cout << endl; //After each row output a newline character
  }
  //Now display the column numbers below the board
  for (int c = 0; c < COLS; c++) {
    cout << c << " ";
  }
  cout << endl << endl;
}

int getColumn(bool isPlayer1) {
  int col = 0;

  /*cout << "Player ";
  if (isPlayer1) {
    cout << "1";
  } else {
    cout << "2";
  }
  cout << " - Select a column [0," << (COLS-1) <<  "] to play: ";*/
  //The below is a short form of above output
  cout << "Player " << (isPlayer1 ? "1" : "2")
        << " - Select a column [0," << (COLS-1) <<  "] to play: ";
  cin >> col;
  return col;
}

bool addPiece(int c, bool isPlayer1) {
  if ((c < 0) || (c >= COLS)) { //check if column is valid for board
    return false;
  }
  //check if column c has space
  if (board[c][0] == EMP) {
    //add a piece to the lowest unoccupied row in column c
    for (int r = (ROWS-1); r >= 0; r--) {
      if (board[c][r] == EMP) {
        //add piece
        if (isPlayer1) {
          board[c][r] = P1;
        } else {
          board[c][r] = P2;
        }
        return true;
      }
    }
  }
  //if column is full return false
  return false;
}

bool isWinner(bool isPlayer1, int lastCol) {
  int counter;

  //Identify which tile is used by current player
  char currTile;
  if (isPlayer1) {
    currTile = P1;
  } else {
    currTile = P2;
  }

  //Check if current player has 4 vertical tiles in a row in the current column
  counter = 0;
  for (int r = ROWS-1; r >= 0; r--) {
    if (board[lastCol][r] == currTile) {
      counter++;
      if (counter == 4) {
        return true;
      }
    } else if (board[lastCol][r] == EMP) { //an optimization to stop searching
      break;                               //if no more tiles in columns
    }
    else {
      counter = 0;
    }
  }

  //First start at top of column and find row of last piece played
  //check if last piece player has three below it first
  //then check that piece and three below are same
  int rowNum; 
  for (int i = (COLS-1); i >= 0; i--) {
    if (board[lastCol][i] == currTile) {
      rowNum = i; 
    }
  }

  //Check if current player has 4 horizontal tiles in a row
  counter = 0; 
  //loops through each column and checks if there are 4 Xs or Os 
  //and returns true to indicate win! 
  //else counter remains zero
  for (int c = 0; c < COLS; c++) {
    if (board[c][rowNum] == currTile) {
      counter++;
      if (counter == 4) {
        return true; 
      }
    }
    else {
      counter = 0; 
    }
  }

  //Check if current player has 4 diagonal tiles in a row

  // BOTTOM TOP LEFT TO BOTTOM RIGHT CASES BEGIN----------------------------------------

  //Diagonals A to F all start and end Top Left to Bottom Right
  //Each diagonal is assigned a letter and it is initialized with 
  //a column and row 
  //Then for each and every assigned diagonal, diagonalLtoR() is called
  int colA = 0; 
  int rowA = 2; 
 
  //diagonalLtoR takes in a char for the current player tile to be checked,
  //the initialized col and row for each diagonal on the Top Left to 
  //Bottom Right respectively
  if (diagonalLtoR(currTile, colA, rowA) == 1) {
    return true; 
  } //this is repeated for each diagonal (A to F)

  //checking diagonal case B 
  int colB = 0;
  int rowB = 1; 
  if (diagonalLtoR(currTile, colB, rowB) == 1) {
    return true; 
  }

  //checking diagonal case C
  int colC = 0; 
  int rowC = 0;
  if (diagonalLtoR(currTile, colC, rowC) == 1) {
    return true; 
  }

  //checking diagonal case D
  int colD = 1; 
  int rowD = 0;
  if (diagonalLtoR(currTile, colD, rowD) == 1) {
    return true; 
  }

  //checking diagonal case E
  int colE = 2; 
  int rowE = 0;
  if (diagonalLtoR(currTile, colE, rowE) == 1) {
    return true; 
  }

  //checking diagonal case F
  int colF = 3; 
  int rowF = 0;
  if (diagonalLtoR(currTile, colF, rowF) == 1) {
    return true; 
  }

  // BOTTOM LEFT TO TOP RIGHT CASES BEGIN----------------------------------------

  //Diagonals G to L all start and end Bottom Left to Top Right
  //Each diagonal is assigned a letter and it is initialized with 
  //a column and row 
  //Then for each and every assigned diagonal, diagonalRtoL() is called
  int colG = 0; 
  int rowG = 3; 

  //diagonalRtoL takes in a char for the current player tile to be checked,
  //the initialized col and row for each diagonal on the Bottom Left to 
  //Top Right respectively
  if (diagonalRtoL(currTile, colG, rowG) == 1) {
    return true; 
  } //this is repeated for each diagonal (G to L)

  //checking diagonal case H
  int colH = 0;
  int rowH = 4; 
  if (diagonalRtoL(currTile, colH, rowH) == 1) {
    return true; 
  }

  //checking diagonal case I
  int colI = 0; 
  int rowI = 5;
  if (diagonalRtoL(currTile, colI, rowI) == 1) {
    return true; 
  }

  //checking diagonal case J
  int colJ = 1; 
  int rowJ = 5;
  if (diagonalRtoL(currTile, colJ, rowJ) == 1) {
    return true; 
  }

  //checking diagonal case K
  int colK = 2; 
  int rowK = 5;
  if (diagonalRtoL(currTile, colK, rowK) == 1) {
    return true; 
  }

  //checking diagonal case L
  int colL = 3; 
  int rowL = 5;
  if (diagonalRtoL(currTile, colL, rowL) == 1) {
    return true; 
  }


  //otherwise no winner
  return false;

}

//diagonalLtoR() takes a char currTile (P1='X', P2='O'), 
//initial column cxLR as integer and initial row ryLR as integer
//and it returns an integer (1='WIN', 0='NO WIN, CONTINUE GAME')
int diagonalLtoR(char currTile, int cxLR, int ryLR) {

  int countDLR = 0; //count for Diagonals Left to Right (DLR) initialized

  //This for-loop loops through each row and column and it begins 
  //looping from the initial column and row integers that were 
  //assigned in each diagonal (A to F)
  for (int c = cxLR, r = ryLR; c <= (COLS-1) && r <= (ROWS-1); c++, r++) {
    //countDLR increments if the player tile ('X' OR 'O') is detected
    //once countDLR is 4; there are 4 Xs or Os found in the diagonal and
    //the integer function returns 1 to indicating P1 or P2 has won 
    if (board[c][r] == currTile) {
      countDLR++;   
      if (countDLR == 4) {
        return 1; 
      }
    }
  }
  return 0; 
}

//diagonalRtoL() takes a char currTile (P1='X', P2='O'), 
//initial column cxRL as integer and initial row ryRL as integer
//and it returns an integer (1='WIN', 0='NO WIN, CONTINUE GAME')
int diagonalRtoL(char currTile, int cxRL, int ryRL) {

  int countDRL = 0; //count for Diagonals Right to Left (DRL) initialized

  //This for-loop loops through each row and column and it begins 
  //looping from the initial column and row integers that were 
  //assigned in each diagonal (G to L)
  for (int c = cxRL, r = ryRL; c <= (COLS-1) && r >= 0; c++, r--) {
    //countDLR increments if the player tile ('X' OR 'O') is detected
    //once countDRL is 4; there are 4 Xs or Os found in the diagonal and
    //the integer function returns 1 to indicating P1 or P2 has won 
    if (board[c][r] == currTile) {
      countDRL++; 
      if (countDRL == 4) {
        return 1; 
      }
    }
  }
  return 0; 
}