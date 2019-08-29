/* ENGGEN131 Project - C Project - 2018 */
/* Connect Four */

#include "connect4.h"

/*
Name: Brandon Pais
ID: 445402880
*/

/*********************************************************************************/
/*
This function will return the middle value of three values. as there are 3 different numbers there is a 
combination of 6 (3*2*1) possible arrangements to check for. If two numbers are he same then it will 
return the last equal value or first equal value.
*/
int SecondPlacePrize(int prize1, int prize2, int prize3)
{	
	int secondPlace=0;
	if ((prize1 >= prize2) && (prize1 <= prize3) || (prize1 <= prize2) && (prize1 >= prize3)) {
		secondPlace = prize1;
	}
	else if ((prize2 >= prize1) && (prize2 <= prize3) || (prize2 >= prize3) && (prize2 <= prize1)) {
		secondPlace = prize2;
	}
	else if ((prize3 >= prize1) && (prize3 <= prize2) || (prize3 >= prize2) && (prize3 <= prize1)) {
		secondPlace = prize3;
	}
	return secondPlace;
}

/*********************************************************************************/
/*
This funtion will take an array as an input and check to see if there are four consecutive numbers in it.
If there is then return the index of the starting for-in-a-row number.
*/
int FourInARow(int values[], int length)
{
	// initialise count which keeps track of how many back-to-back duplicates there are
	int count = 1;	
	// loop through all values, apart from the last one.	
    for (int i=0; i<length-1; i++) {	
        if (values[i] == values[i+1]) {
			// if the next value in the array is the same as the current then incriment count
            count++;	
        } else {
			// if the next value is not the same as the current then restart the count
            count = 1;	
        }
        if (count == 4) {
			// once count is 4 then return the index of when count was 1.
            return i-2;	
        }
    }
    return -1;
}

/*********************************************************************************/
/*
This function will convert a binary number into decimal. This is done by computing the remainder of the binary number
and multiplying this by the correct power of 2.
*/
int BinaryToDecimal(int binary)
{
	int Remainder; 
	int sum=0;
	int base_val = 1;
	while (binary) {
		// calculate the remainder of the binary no. this will extract the LSB and then use this to
		// calculate the running sum by multiplying it by the current base two value.
		Remainder = binary % 10;	
		sum += Remainder * base_val;
		
		// calculate the updated binary value and base two value
		binary /= 10;
		base_val *= 2; 
	}
	return sum;
}

/*********************************************************************************/
/*
This function will sort an array into ascending order and then select the middle (median) number.
If the length of the array is even then take the average value of the two middle values. 
*/
double MedianAbility(double abilities[], int length)
{	
	// create an variable to temporarily store some values
	double temp=0;	
	// nested for loop to rearrange the array into assending order.
	for (int i=0; i<length; i++) {
		for (int j = i+1; j<length; j++) {
			if (abilities[j] <= abilities[i]) {
				// swap values around if following value is less than the current
				temp = abilities[j];
				abilities[j] = abilities[i];
				abilities[i] = temp;
			}
		}	
	}
	if (length % 2) {
		// if the array length is odd then return the middle value
		return abilities[(length-1)/2];
	} else {
		// if array length is even then calculate the average of the two middle no.
		return (abilities[(length-1)/2] + abilities[((length-1)/2)+1]) / (double)2;
	}
}

/*********************************************************************************/
/*
This function will remove any unnessisary spaces in a string.
*/
void RemoveSpaces(char *name)
{
	int count = 0;
	int index = 0;
	while(name[index] != '\0') {
		if ((name[index] == name[index + 1]) && (name[index] == ' ')) {
			count++;	// count how many extra spaces there are in a row.
		} 
		// once the spaces is disrupted by another char then move the string back by the count
		else if ((name[index] != name[index + 1]) && (count > 0)) {
			for (int j= index - count; j < (int)strlen(name); j++) {
				name[j] = name[j+count];
			}
			count = 0;
			index = 0; 
		}
		index++;
	}
}

/*********************************************************************************/
/*
This function will create a board of size * size, and will place '0' in all row and cols.
the function will then place a '3' in the middle of the board to represent a boundary.
*/
void InitialiseBoard(int board[MAX_SIZE][MAX_SIZE], int size)
{	
	for (int i=0; i < size; i++) {
		for (int j=0; j < size; j++) {
			board[i][j] = 0;
		}
	}
	if (size % 2) {		// if size of the board is odd then place only one '3'
		board[(size-1)/2][(size-1)/2] = 3;
	} else {			// if the size is even then place four '3' in middle
		for (int i = (size/2)-1; i < (size/2)+1 ; i++) {
			for (int j = (size/2)-1; j < (size/2)+1; j++) {
				board[i][j] = 3;
			}
		}
	}
}

/*********************************************************************************/
/*
This function places a counter in the last possible position given the initial side of the board and the move no.
The function will move the player until there are no more wmpty spaces in that direction 
*/
void AddMoveToBoard(int board[10][10], int size, char side, int move, int player, int *lastRow, int *lastCol)
{
	// initialise the peice as being not placed(positioned) yet
	int positioned = 0;
	int i;
    
	// conditional statement that determines if there is space for a player to move into.
	// If not then change lastRow/lastCol to -1.
	if (((side=='N') && (board[0][move] != 0)) || ((side=='E') && (board[move][size-1] != 0)) || 
		((side=='S') && (board[ size-1][move] != 0)) || ((side=='W') && (board[move][0] != 0))) {
        *lastRow = -1;
		*lastCol = -1;
    } 
	else {                	
        // conditional statements based on which side is selected
		if (side == 'N') {
			i = 0;
            while(!positioned) {
				// if a pos. does not have a '0' then place a counter in the pos. immediately before that.
				// Also check if the counter is in the last allowed pos. and does not go off the board.
                if ((board[i][move] != 0) || (i == size)) {
                    board[i-1][move] = player;
					// assign lastCol/lastRow to the final pos. of counter
                    *lastCol = move;	
                    *lastRow = (i-1);
					// change variable to terminate while loop
                    positioned = 1;		
                }
				// increment the index value
                i++;	
            }
        } else if (side == 'E') {
			i = size - 1;
            while(!positioned) {
                if ((board[move][i] != 0) || (i<0)) {
                    board[move][i+1] = player;
                    *lastCol = i+1;
                    *lastRow = move; 	
                    positioned = 1;
                }
				// decrement the index value
                i--;		
            }
        } else if (side == 'S') {
			i = size - 1;
            while (!positioned) {
                if ((board[i][move] != 0) || (i<0)) {
                    board[i+1][move] = player;
                    *lastCol = move;
                    *lastRow = i+1;
                    positioned = 1;
                }
                i--;
            }
        } else if (side == 'W') {
			i = 0;
            while (!positioned) {
                if ((board[move][i] != 0) || (i == size)) {
                    board[move][i-1] = player;
                    *lastCol = i-1;
                    *lastRow = move;
                    positioned = 1;
                }
                i++;
            }
        }	
    }
}

void Display(int board[10][10], int size) {
        for (int i = 0; i < size; i++) {
            printf("   ");
            for (int j = 0; j < size; j++) {
                printf("%d ", board[i][j]);
            }
            printf("\n");
        }
}

/*********************************************************************************/
/*
This function checks to see if the current player has four counters in any direction. If 
there are four-in-a-row then return the winning player. The function will also check if 
there are any more valid moves that can be made. If no more valid moves then return the
 last player to place a counter. If player has not won then return 0.
*/
int CheckGameOver(int board[MAX_SIZE][MAX_SIZE], int size, int player, int row, int col)
{
	// create an array of count values for each of the 8 directions 
	//that a 4-in-a-row could be formed.
	int count[8] = {0};
	int index[8] = {1,1,1,1,1,1,1,1};	
	
	// for loop checks to see if there are any playable spaces left by looking at the perimeter of the board
	for (int i=0; i<size; i++) {
		count[0] = ((board[0][i] == 0) || (board[size-1][i] == 0) ||
					(board[i][0] == 0) || (board[i][size-1] == 0)) ? (count[0] + 1) : count[0]; 
	}
	// if count of how many '0' there are in the outer perimeter is zero then player has won
	if (count[0] == 0) 	
		return player;	
	
	count[0] = 0;	//reset count[0]	
	// count consecutive values below pos.
	while ((board[row+index[0]][col] == player) && (row+index[0] < size)) { 	
		count[0]++;
		index[0]++;
	}
	// count consecutive values above pos.
	while ((board[row-index[1]][col] == player) && (row-index[1] >= 0)) {	
		count[1]++;
		index[1]++;
	}
	// count consecutive values left of pos.
	while ((board[row][col+index[2]] == player) && (col+count[2] < size)) {	
		count[2]++;
		index[2]++;
	}
	// count consecutive values right of pos.
	while ((board[row][col-index[3]] == player) && (col-index[3] >= 0)) {	
		count[3]++;
		index[3]++;
	}
	// count consecutive values to right of +ve diagonal
	while ((board[row-index[4]][col+index[4]] == player) && (row-index[4] >= 0) && (col+index[4] < size)) {	
		count[4]++;
		index[4]++;
	}
	// count consecutive values to left of +ve diagonal
	while ((board[row+index[5]][col-index[5]] == player) && (row+index[5] < size) && (col-index[5] >= 0)) {	
		count[5]++;
		index[5]++;
	}	
	// count consecutive values to right of -ve diagonal
	while ((board[row+index[6]][col+index[6]] == player) && (row+index[6] < size) && (col+index[6] < size)) {	
		count[6]++;
		index[6]++;
	}	
	// count consecutive values to left of -ve diagonal
	while ((board[row-index[7]][col-index[7]] == player) && (row-index[7] >= 0) && (col-index[7] >= 0)) {	
		count[7]++;
		index[7]++;
	}
	
	//check to see if the total linear (up and down, left and right, etc.) count is greter than 4
	if ((count[0] + count[1] >= 3) || (count[2] + count[3] >= 3) ||	
		(count[4] + count[5] >= 3) || (count[6] + count[7] >= 3)) {
			return player;
		}	
	return 0;
}

/*********************************************************************************/
/*
This function takes a 2D integer array and converts it to a 1D character string to be displayed to the user
in a more asthetic manner. This function also adds extra rows and columns to display the moves that can be made.
*/
void GetDisplayBoardString(int board[MAX_SIZE][MAX_SIZE], int size, char *boardString)
{	
	//initialise linear index
	int pos = 0;	 
	// nested for loop going through all (size+5)*(size+4) array positions. (extra col. for new line characters)
	for (int i=0; i < size+4; i++) {
		for (int j=0; j < size+5; j++) {	
			// place all characters in correct positions using conditional statements
			if (((i < 2) && (j < 2)) || ((i < 2) && (j >= size+2) && (j < size+4)) || 
				((i >= size+2) && (j < 2)) || ((i >= size+2) && (j >= size+2) && (j < size+4))) {
				boardString[pos] = '-';				
			} 
			else if ((i == 0) && (j >= 2) && (j < size+2)) {
				boardString[pos] = 'N'; 
			} 
			else if ((i == size+3) && (j >= 2) && (j < size+2)) {
				boardString[pos] = 'S';
			} 
			else if ((j == 0) && (i >= 2) && (i < size+2)) {
				boardString[pos] = 'W';
			} 
			else if ((j == size+3) && (i >= 2) && (i < size+2)) {
				boardString[pos] = 'E';
			}
			//convert int to char (typesetting)
			else if (((i == 1) && (j >= 2) && (j < size+2)) || ((i == size+2) && (j >= 2) && (j < size+2))) {
				boardString[pos] = (char)(j-2) + '0';	
				
			}
			else if (((j == 1) && (i >= 2) && (i < size+2)) || ((j == size+2) && (i >= 2) && (i < size+2))) {
				boardString[pos] = (char)(i-2) + '0';
			}
			else if (j == size+4) {
				boardString[pos] = '\n'; 
			}
			// get values from board array
			else  {		
				if (board[i-2][j-2] == 0) {
					boardString[pos] = '.';
				}
				else if (board[i-2][j-2] == 1) {
					boardString[pos] = 'X';
				}
				else if (board[i-2][j-2] == 2) {
					boardString[pos] = 'O';
				}
				else if (board[i-2][j-2] == 3) {
					boardString[pos] = '#';
				}
			}
			// increment linear index for boardString by one
			pos++;	
		}
	}
	// end string with terminator
	boardString[pos] = '\0';	
}

/*********************************************************************************/
/*
This is a helper function for the BOT to determine the final postion on a board given the Side 
and move, similar to the AddMoveToBoard function
*/
int LastPosition(int board[MAX_SIZE][MAX_SIZE], char direction, int move, int size) {
	int i = 0;
	if (direction == 'N') {
		i = 0;
		while (board[i+1][move] == 0)	// increments going DOWN the board until no more spaces available.
			i++;
	} else if (direction == 'S') {
		i = size-1;
		while (board[i-1][move] == 0)	// increments going UP the board until no more spaces available. 	
			i--;
	} else if (direction == 'E') {
		i = size-1;
		while (board[move][i-1] == 0)	// increments going LEFT across board until no more spaces available. 
			i--;
	} else if (direction == 'W') {
		i = 0;
		while (board[move][i+1] == 0)	// increments going RIGHT across board until no more spaces available. 
			i++;
	}
	return i;
}

/*********************************************************************************/
/*
This is a helper function for the BOT that checks to see if the opponent has a winning move in a position
around the current position being checked. This will prevent the opponent from winning due to the bot making a move
*/
int CheckValuesAround(int board[MAX_SIZE][MAX_SIZE], int size, int player, int row, int col)
{
	int count = 0;	
	// nested for loop goes through all 8 points around the current position 
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			// check if a winning move can be made by opponent in the next round
			// if a counter/token is placed in the current pos. 
			if (CheckGameOver(board, size, player, row+i, col+j)) {
				count++;
			}
		}
	}
	if (count == 0) {
		return 1;
	}
	return 0;
}

/*********************************************************************************/
/*
This is a helper function for the BOT that checks to see if there are any players with two counters as well as a combination
of two spaces and one space on either side of the counters. This stops the possibility of the opponent forcing a 
win by having three in a row and an empty space either side. ie. prevents [--XX-] ==> [-XXX-] from occuring in any direction. 
This function will also check to see if by making this TwoRecurring move it allows the opponent to play a winning move, 
in which case the inital move will not be made.
*/
int CheckTwoRecurring(int board[MAX_SIZE][MAX_SIZE], int size, int player, int row, int col)	
{
	// count specific combination below pos.
	if ((board[row-1][col] == 0) && (board[row+1][col] == player) && (board[row+2][col] == player) && 
		(board[row+3][col] == 0) && (row-1 >= 0) && (row+3 <size) && 
		CheckValuesAround(board, size, 3-player, row, col)) {
			return 1;
	}
	// count specific combination above pos.
	if ((board[row+1][col] == 0) && (board[row-1][col] == player) && (board[row-2][col] == player) && 
		(board[row-3][col] == 0) && (row+1 <size) && (row-3 >=0) &&
		CheckValuesAround(board, size, 3-player, row, col)) {
			return 1;
	}
	// count specific combination left of pos.
	if ((board[row][col+1] == 0) && (board[row][col-1] == player) && (board[row][col-2] == player) && 
		(board[row][col-3] == 0) && (col+1 < size) && (col-3 >= 0) &&
		CheckValuesAround(board, size, 3-player, row, col)) {
			return 1;

	}
	// count specific combination right of pos.
	if ((board[row][col-1] == 0) && (board[row][col+1] == player) && (board[row][col+2] == player) && 
		(board[row][col+3] == 0) && (col-1 >= 0) && (col+3 < size) && 
		CheckValuesAround(board, size, 3-player, row, col)) {
			return 1;
	}
	// count specific combination to right of +ve diagonal
	if ((board[row+1][col-1] == 0) && (board[row-1][col+1] == player) && (board[row-2][col+2] == player) && 
		(board[row-3][col+3] == 0) && (board[row-3][col+4] != 0) && (board[row-3][col+2] != 0) && (col-1 >= 0) && 
		(col+3 < size) && (row-3 >= 0) && (row+1 < size) && CheckValuesAround(board, size, 3-player, row, col)) {
			return 1;
	}
	// count specific combination to left of +ve diagonal
	if ((board[row-1][col+1] == 0) && (board[row+1][col-1] == player) && (board[row+2][col-2] == player) && 
		(board[row+3][col-3] == 0) && (board[row+3][col-4] != 0) && (board[row+3][col-2] != 0) && (col-3 >= 0) && 
		(col+1 < size) && (row-1 >= 0) && (row+3 < size) && CheckValuesAround(board, size, 3-player, row, col)) {
			return 1;
	}
	// count specific combination to right of -ve diagonal
	if ((board[row-1][col-1] == 0) && (board[row+1][col+1] == player) && (board[row+2][col+2] == player) && 
		(board[row+3][col+3] == 0) && (board[row+3][col+4] != 0) && (board[row+3][col+2] != 0) && (col-1 >= 0) && 
		(col+3 < size) && (row-1 >= 0) && (row+3 < size) && CheckValuesAround(board, size, 3-player, row, col)) {
			return 1;
	}
	// count specific combination to left of -ve diagonal
	if ((board[row+1][col+1] == 0) && (board[row-1][col-1] == player) && (board[row-2][col-2] == player) && 
		(board[row-3][col-3] == 0) && (board[row-3][col-4] != 0) && (board[row-3][col-2] != 0) && (col-3 >= 0) && 
		(col+1 < size) && (row-3 >= 0) && (row+1 < size) && CheckValuesAround(board, size, 3-player, row, col)) {
			return 1;
	}
	return 0;
}

/*********************************************************************************/
/*
This helper function for the BOT checks if there is already at least one counter positionedso to add 
another counter next to it. This is very similar to CheckGameOver function. One of the inputs to the 
function is the minimum number of counters in a row called 'InARow'
*/
int AddOneMore(int board[MAX_SIZE][MAX_SIZE], int size, int player, int row, int col, int InARow)
{
	// create an array of count values for each of the 8 directions 
	//that a 4-in-a-row could be formed.
	int count[8] = {0};
	int index[8] = {1,1,1,1,1,1,1,1};	
	
	// count consecutive values below pos.
	while ((board[row+index[0]][col] == player) && (row+index[0] < size)) { 	
		count[0]++;
		index[0]++;
	}
	// count consecutive values above pos.
	while ((board[row-index[1]][col] == player) && (row-index[1] >= 0)) {	
		count[1]++;
		index[1]++;
	}
	// count consecutive values left of pos.
	while ((board[row][col+index[2]] == player) && (col+count[2] < size)) {	
		count[2]++;
		index[2]++;
	}
	// count consecutive values right of pos.
	while ((board[row][col-index[3]] == player) && (col-index[3] >= 0)) {	
		count[3]++;
		index[3]++;
	}
	// count consecutive values to right of +ve diagonal
	while ((board[row-index[4]][col+index[4]] == player) && (row-index[4] >= 0) && (col+index[4] < size)) {	
		count[4]++;
		index[4]++;
	}
	// count consecutive values to left of +ve diagonal
	while ((board[row+index[5]][col-index[5]] == player) && (row+index[5] < size) && (col-index[5] >= 0)) {	
		count[5]++;
		index[5]++;
	}	
	// count consecutive values to right of -ve diagonal
	while ((board[row+index[6]][col+index[6]] == player) && (row+index[6] < size) && (col+index[6] < size)) {	
		count[6]++;
		index[6]++;
	}	
	// count consecutive values to left of -ve diagonal
	while ((board[row-index[7]][col-index[7]] == player) && (row-index[7] >= 0) && (col-index[7] >= 0)) {	
		count[7]++;
		index[7]++;
	}
	
	//check to see if the total linear (up and down, left and right, etc.) count is greter than or equal to input 'InARow'
	if (((count[0] + count[1] >= InARow) && CheckValuesAround(board, size, 3-player, row, col)) ||
		((count[2] + count[3] >= InARow) && CheckValuesAround(board, size, 3-player, row, col)) ||	
		((count[4] + count[5] >= InARow) && CheckValuesAround(board, size, 3-player, row, col)) || 
		((count[6] + count[7] >= InARow) && CheckValuesAround(board, size, 3-player, row, col))) {
			return player;
		}	
	return 0;
}

/*********************************************************************************/
/*
This helper function is given an input called 'level' which specifies the strategy to check. It only checks 
valid positions and then assigns the side and move required to make a strategic move.
*/
void PlaceValidPosition(int board[MAX_SIZE][MAX_SIZE], int level, int size, int player, char *side, int *move) 
{	
	// initialise temporoary row and column
	int tempCol, tempRow;	

	// check: if a move has already been made in the BOT function then do nothing
	if (*move != -1) {
		return;
	}
	// loop through the side length of the board
	for (int i=0; i<size; i++) {
		//indicate valid positions in North direction (left to right)
		if (board[0][i] == 0) {		
			// find the last valid position given the direction and move (i) and the strategy level
			tempRow = LastPosition(board, 'N', i, size);	
			tempCol = i;
			// check which level is required, and check if a move at that strategy level is possible.
			if (((level == 0) && CheckGameOver(board, size, player, tempRow, tempCol)) || 
				((level == 1) && CheckGameOver(board, size, 3-player, tempRow, tempCol)) || 
				((level == 2) && CheckTwoRecurring(board, size, player, tempRow, tempCol)) ||
				((level == 3) && CheckTwoRecurring(board, size, 3-player, tempRow, tempCol)) ||
				((level == 4) && AddOneMore(board, size, player, tempRow, tempCol, 2)) ||
				((level == 5) && AddOneMore(board, size, player, tempRow, tempCol, 1))) {		
				*side = 'N';	
				*move = i;
				break;
			}
		}
		//indicate valid positions in South direction (left to right)
		if (board[size-1][i] == 0) {	
			// find the last valid position given the direction and move (i) and the strategy level
			tempRow = LastPosition(board, 'S', i, size);	
			tempCol = i;
			if (((level == 0) && CheckGameOver(board, size, player, tempRow, tempCol)) || 
				((level == 1) && CheckGameOver(board, size, 3-player, tempRow, tempCol)) || 
				((level == 2) && CheckTwoRecurring(board, size, player, tempRow, tempCol)) ||
				((level == 3) && CheckTwoRecurring(board, size, 3-player, tempRow, tempCol)) ||
				((level == 4) && AddOneMore(board, size, player, tempRow, tempCol, 2)) ||
				((level == 5) && AddOneMore(board, size, player, tempRow, tempCol, 1))) {
				*side = 'S';
				*move = i;				
				break;
			}
		}
		//indicate valid positions in East direction (top to bottom)
		if (board[i][size-1] == 0) {		
			tempRow = i;
			// find the last valid position given the direction and move (i) and the strategy level
			tempCol = LastPosition(board, 'E', i, size);	
			if (((level == 0) && CheckGameOver(board, size, player, tempRow, tempCol)) || 
				((level == 1) && CheckGameOver(board, size, 3-player, tempRow, tempCol)) || 
				((level == 2) && CheckTwoRecurring(board, size, player, tempRow, tempCol)) ||
				((level == 3) && CheckTwoRecurring(board, size, 3-player, tempRow, tempCol)) ||
				((level == 4) && AddOneMore(board, size, player, tempRow, tempCol, 2)) ||
				((level == 5) && AddOneMore(board, size, player, tempRow, tempCol, 1))) {
				*side = 'E'; 
				*move = i;	
				break;
			} 
		}
		//indicate valid positions in West direction (top to bottom)
		if (board[i][0] == 0) {		
			tempRow = i;
			// find the last valid position given the direction and move (i) and the strategy level
			tempCol = LastPosition(board, 'W', i, size);	
			if (((level == 0) && CheckGameOver(board, size, player, tempRow, tempCol)) || 
				((level == 1) && CheckGameOver(board, size, 3-player, tempRow, tempCol)) || 
				((level == 2) && CheckTwoRecurring(board, size, player, tempRow, tempCol)) ||
				((level == 3) && CheckTwoRecurring(board, size, 3-player, tempRow, tempCol)) ||
				((level == 4) && AddOneMore(board, size, player, tempRow, tempCol, 2)) ||
				((level == 5) && AddOneMore(board, size, player, tempRow, tempCol, 1))) {
				*side = 'W';
				*move = i;		
				break;
			} 
		}
	}
}

/*********************************************************************************/
/*
This function controls the logic for BOT1. This bot loops through 6 main strategies before 
selecting a random position.
*/
void GetMoveBot1(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	int randSide, randMove;
	// initialise variable to be used when selecting a random point
	int positioned = 0;	
	// initially make move equal to -1 indicating that a valid move has not yet been made 	
	*move = -1;		

	// loop through all six strategies, starting with the most important which is to see if there
	// is a winning move. Strategies will then be tested in order of importance.
	for (int i = 0; i < 6; i++) {
		PlaceValidPosition(board, i, size, player, side, move); 
	}

	// If there are no strategic moves then place a counter in a random valid positions
	if (*move == -1) {
		while (!positioned) {
			randSide = rand() % 4;
			randMove = rand() % size;
			if ((randSide == 0) && (board[0][randMove] == 0)) {	
				*side = 'N';
				*move = randMove;
				positioned = 1;
			}
			else if ((randSide == 1) && (board[size-1][randMove] == 0)) {
				*side = 'S';
				*move = randMove;
				positioned = 1;
			}
			else if ((randSide == 2) && (board[randMove][size-1] == 0)) {
				*side = 'E';
				*move = randMove;
				positioned = 1;
			}
			else if ((randSide == 3) && (board[randMove][0] == 0)) {
				*side = 'W';
				*move = randMove;
				positioned = 1;
			}
		}
	}
}

/*********************************************************************************/
/*
This function controls the logic for BOT2. This bot only checks to see if a winning move is 
possible and will only play valid moves. Otherwise it will play random moves. 
*/
void GetMoveBot2(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	int randSide, randMove;
	int positioned = 0;
	// initially make move equal to zero
	*move = -1;		 

	// only strategic move is to check if a winning move is possible for this BOT (level 0)
	PlaceValidPosition(board, 0, size, player, side, move);

	// If there are no strategic moves then place a counter in a random valid positions
	if (*move == -1) {
		while (!positioned) {
			randSide = rand() % 4;
			randMove = rand() % size;
			if ((randSide == 0) && (board[0][randMove] == 0)) {
				*side = 'N';
				*move = randMove;
				positioned = 1;
			}
			else if ((randSide == 1) && (board[size-1][randMove] == 0)) {
				*side = 'S';
				*move = randMove;
				positioned = 1;
			}
			else if ((randSide == 2) && (board[randMove][size-1] == 0)) {
				*side = 'E';
				*move = randMove;
				positioned = 1;
			}
			else if ((randSide == 3) && (board[randMove][0] == 0)) {
				*side = 'W';
				*move = randMove;
				positioned = 1;
			}
		}
	}
}