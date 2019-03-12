#include <stdio.h>
#include <stdlib.h>

const int MAX_ROWS = 9;
const int MAX_COLS = 9;
const int CANNOT_CHANGE = 0;
const int CAN_CHANGE = 1;

void displayBoard(int board[MAX_ROWS][MAX_COLS], int rows, int cols) {
 	printf("\t-------------------------\n");
 	
 	for(int i = 0; i < 9; i++) {
    	printf("\t");
    	for(int j = 0; j < 9; j++) {
       		
       		if(j == 0)
    			printf("| ");

   		 	printf("%d ", board[i][j]);
       
      		if((j + 1) % 3 == 0 )
      		printf("| ");
  		 }

   	if((i + 1) % 3 == 0 )
       printf("\n\t-------------------------");

   	printf("\n");
	}
}

void displayStartBoard(int start[MAX_ROWS][MAX_COLS], int rows, int cols) {
 	printf("\t-------------------------\n");
 	
 	for(int i = 0; i < 9; i++) {
    	printf("\t");
    	for(int j = 0; j < 9; j++) {
       		
       		if(j == 0)
    			printf("| ");

   		 	printf("%d ", start[i][j]);
       
      		if((j + 1) % 3 == 0 )
      		printf("| ");
  		 }

   	if((i + 1) % 3 == 0 )
       printf("\n\t-------------------------");

   	printf("\n");
	}
}



void addInitialValues(int board[MAX_ROWS][MAX_COLS], int start[MAX_ROWS][MAX_COLS], int row, int col, int value) {
	board[row][col] = value;
	start[row][col] = CANNOT_CHANGE;
}

void addGuess(int board[MAX_ROWS][MAX_COLS], int start[MAX_ROWS][MAX_COLS], int row, int col, int value) {
	if (start[row][col] == CAN_CHANGE) {
		board[row][col] = value;
	}
	else printf("You cannot change the value here because the value here is a set value.\n");
}

void createSudokuPuzzle(int board[MAX_ROWS][MAX_COLS], int start[MAX_ROWS][MAX_COLS], int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			board[i][j] = 0;
			start[i][j] = CAN_CHANGE;
		}
	}
}

int getValueIn(int board[MAX_ROWS][MAX_COLS], int row, int col) {
	return board[row][col];
}

int isFull(int board[MAX_ROWS][MAX_COLS]) {
	for (int i = 0; i < MAX_ROWS; i++) {
		for (int j = 0; j < MAX_COLS; j++) {
			if (board[i][j] == 0) {
				return 0;
			}
		}
	}
	return 1;
}

int checkPuzzle(int board[MAX_ROWS][MAX_COLS]) {
	int rows[9][9] = {0};
	int cols[9][9] = {0}; 
	int sections[3][3][9]= {0};
	
	for(int i = 0; i < MAX_ROWS; i++) {
		for(int j = 0; j < MAX_COLS; j++) {
			if (board[i][j] != 0) {  
				int index = board[i][j] - 1;
				
				if(rows[i][index]++) 
					return 0; 
				
				if(cols[j][index]++) 
					return 0;
				
				if(sections[i/3][j/3][index]++) 
					return 0;
			}
		}
	}
	return 1;
}

void getAllowedValues(int board[MAX_ROWS][MAX_COLS], int array[10], int row, int col) {

	int rowStart = (row/3) * 3;
    int colStart = (col/3) * 3;
	
	for (int i = 1; i <= 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (board[row][j] == i) 
				array[i] = 0;
	        if (board[j][col] == i) 
	        	array[i] = 0;
	        if (board[rowStart + (j%3)][colStart + (j/3)] == i) 
	        	array[i] = 0;
		}
	}
}

void resetBoard(int board[MAX_ROWS][MAX_COLS], int start[MAX_ROWS][MAX_COLS]) {
	for (int i = 0; i < MAX_ROWS; i++) {
		for (int j = 0; j < MAX_COLS; j++) {
			if (start[i][j] == CAN_CHANGE) {
				board[i][j] = 0;
			}
		}
	}
}


int main() {
	int board[MAX_ROWS][MAX_COLS];
	int start[MAX_ROWS][MAX_COLS];

	createSudokuPuzzle(board, start, MAX_ROWS, MAX_COLS);
	
	addInitialValues(board, start, 0, 0, 1);
	addInitialValues(board, start, 0, 1, 2);
	addInitialValues(board, start, 0, 2, 3);
	addInitialValues(board, start, 0, 3, 4);
	addInitialValues(board, start, 0, 4, 9);
	addInitialValues(board, start, 0, 5, 7);
	addInitialValues(board, start, 0, 6, 8);
	addInitialValues(board, start, 0, 7, 6);
	addInitialValues(board, start, 0, 8, 5);
	addInitialValues(board, start, 1, 0, 4);
	addInitialValues(board, start, 2, 0, 6);
	addInitialValues(board, start, 3, 0, 3);
	addInitialValues(board, start, 4, 0, 2);
	addInitialValues(board, start, 5, 0, 9);
	addInitialValues(board, start, 6, 0, 8);
	addInitialValues(board, start, 7, 0, 7);
	addInitialValues(board, start, 8, 0, 5);
	addInitialValues(board, start, 1, 1, 5);
	addInitialValues(board, start, 1, 2, 9);
	addInitialValues(board, start, 2, 1, 7);
	addInitialValues(board, start, 2, 2, 8);
	addInitialValues(board, start, 3, 4, 1);
	addInitialValues(board, start, 5, 5, 5);
	addInitialValues(board, start, 8, 3, 9);

	// printf("\n\n");
	// displayStartBoard(start, MAX_ROWS, MAX_COLS);

	char option;
	int availableNumbers[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	do {
		displayBoard(board, MAX_ROWS, MAX_COLS);
		printf("Enter 'r' to reset the board, 'q' to quit, or 'g' to guess. \n");
		scanf(" %c", &option);

		if (option == 'r') {
			resetBoard(board, start);
		}
		else if (option == 'g') {
			int row;
			int col;
			int value;

			printf("Enter row number: ");
			scanf("%d", &row);
			printf("\n");
			printf("Enter column number: ");
			scanf("%d", &col);
			printf("\n");

			printf("Here are the available numbers you can put at this spot: ");
			getAllowedValues(board, availableNumbers, row, col);
			for (int i = 1; i <= 9; i++) {
				if (availableNumbers[i] == 1) {
					printf("%d ", i);
				}
			}
			printf("\n");

			printf("Enter value: \n");
			scanf("%d", &value);

			if (row < 0 || row > 8 || col < 0 || col > 8 || value < 1 || value > 9) {
				printf("Invalid input. Please try again. \n");
				continue;
			}

			else addGuess(board, start, row, col, value);
		}

		if (!checkPuzzle(board)) {
			printf("Your board so far is invalid. You may reset the board or update the value by guessing a different value at the same location. \n");
		}

		for(int i = 0; i < 10; i++) {
			availableNumbers[i] = 1;
		}

		if (isFull(board) && checkPuzzle(board)) {
			displayBoard(board, MAX_ROWS, MAX_COLS);
			printf("Congratulations, you solved the puzzle!\n");
			break;
		}

	} while(option != 'q');

	return 0;
}