/*
 * Author: Taha Masood
 * Name: Chess_Game.C
 * This program allows users to play a game of chess.
 */ 

#include <python.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

/*
 * This C program is currently functional with standard input and standard output.
 * This is to make it easier to compile and debug the C code for the game.
 * To compile the complete GUI, comment out the function print_board and the locations for input.
 * Insert the python code by either defining a new file or using static PyObject * {}.
 * Redirect standard output to the Python GUI.
 */ 

/*
 * The following function intializes a new structure called 'chess'.
 * The structure is created to decrease the intialization of multiple two-dimensional arrays.
 * The structure itself is used to keep track of chess pieces on an eight-by-eight chess board.
 */ 

struct chess
{
    int board[8][8];
};

/*
 * The following function is to determine the end of the game.
 * The function returns in integer corresponding to the overall layout of the board.
 * The value 3 indicates both kings are still within the game.
 * The value 2 indicates that the black king is out of the game.
 * The value 1 indicates that the white king is out of the game.
 * The value 0 indicates that both kings are out of the game.
 */ 

int game_value(struct chess current)
{
    int counter = 0;
    
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (current.board[i][j] == 5) 	counter ++;
            if (current.board[i][j] == 12) 	counter += 2;
        }
    }
    
    return counter;
}

/*
 * The following function determines if a piece is black.
 * The function returns true if the piece is black and false if the piece is white.
 */ 

bool is_black(struct chess current, int position)
{
    int value = current.board[position/10][position%10];
    
    if (value == 0) return false;
    else if ((value == 1) || (value == 2) || (value == 3) || (value == 4) || (value == 5) || (value == 6)) return true;
    else return false;
}

/*
 * The following function determines if a piece is white.
 * The function returns true if the piece is white and false if the piece is black.
 */ 

bool is_white(struct chess current, int position)
{
    int value = current.board[position/10][position%10];

    if (is_black(current, position)) return false;
    else if (value == 0) return false;
    else return true;
}

/*
 * The following function determines if a piece exists at the indicated position.
 * The function returns true if a piece exists at the indicated position and returns false otherwise.
 */ 

bool is_piece(struct chess current, int position)
{
    if ((current.board[position/10][position%10]) != 0) return true;
    else return false;
}

/*
 * The following function determines if a move is valid for a bishop.
 * The function determines if the end location is possible for a bishop.
 * The function ensures no pieces are blocking the bishop's path and/or the final position does not hold a piece of the same colour.
 * The function returns true the move is achievable and false otherwise.
 */ 

bool valid_bishop(struct chess current, int start, int end)
{
    int movement = end - start;
    int value = 0;
    
    if ((movement%11) == 0)
    {
        value = movement/11;
        
        if (value > 0)
        {
            for(int i = 1; i < value; i++)
            {
                if ((current.board[(start/10)+i][(start%10)+i]) != 0) return false;
            }
        }
        
        if (value < 0)
        {
            for(int j = -1; j > value; j--)
            {
                if((current.board[(start/10)+j][(start%10)+j]) != 0) return false;
            }
        }
        
        if((is_white(current, start)) && (is_black(current, end))) return true;
        
        else if((is_black(current, start)) && (is_white(current, end))) return true;
        
        else if((current.board[end/10][end%10]) == 0) return true;
        
        else return false;
        
    }
    
    else if ((movement%9) == 0)
    {
        value = movement/9;
        
        if (value > 0)
        {
            for(int i = 1; i < value; i++)
            {
                if ((current.board[(start/10)+i][(start%10)-i]) != 0) return false;
            }
        }
        
        if (value < 0)
        {
            for(int j = -1; j > value; j--)
            {
                if((current.board[(start/10)+j][(start%10)-j]) != 0) return false;
            }
        }
        
        if((is_white(current, start)) && (is_black(current, end))) return true;
        
        else if((is_black(current, start)) && (is_white(current, end))) return true;
        
        else if((current.board[end/10][end%10]) == 0) return true;
        
        else return false;
        
    }
    
    else return false;
}

/*
 * The following function determines if a move is valid for a king.
 * The function determines if the end location is possible for a king.
 * The function ensures no pieces are blocking the king's path and/or the final position does not hold a piece of the same colour.
 * The function returns true the move is achievable and false otherwise.
 */ 

bool valid_king(struct chess current, int start, int end)
{
    int movement = end - start;
    
    if ((movement == 1) || (movement == -1) || (movement == 10) || (movement == -10) || (movement == 9) || (movement == -9) || (movement == 11) || (movement == -11))
    {
        if((is_black(current, start)) && (is_white(current, end))) return true;
        else if((is_white(current, start)) && (is_black(current, end))) return true;
        else if((current.board[end/10][end%10]) == 0) return true;
        else return false;
    }
    
    else return false;
}

/*
 * The following function determines if a move is valid for a knight.
 * The function determines if the end location is possible for a knight.
 * The function ensures the final position does not hold a piece of the same colour.
 * The function returns true the move is achievable and false otherwise.
 */ 

bool valid_knight(struct chess current, int start, int end)
{
    int movement = end - start;
    
    if((movement == 21) || (movement == -21) || (movement == 19) || (movement == -19) || (movement == 12) || (movement == -12) || (movement == 8) || (movement == -8))
    {
        if((is_black(current, start)) && (is_white(current, end))) return true;
        else if((is_white(current, start)) && (is_black(current, end))) return true;
        else if((current.board[end/10][end%10]) == 0) return true;
        else return false;
    }
    
    else return false;
}

/*
 * The following function determines if a move is valid for a rook.
 * The function determines if the end location is possible for a rook.
 * The function ensures no pieces are blocking the rook's path and/or the final position does not hold a piece of the same colour.
 * The function returns true the move is achievable and false otherwise.
 */ 

bool valid_rook(struct chess current, int start, int end)
{
    int movement = (end - start);
    int value = movement/10;
    
    if (value > 0)
    {
        for(int i = 1; i < value; i++)
        {
            if((current.board[(start/10)+i][start%10]) != 0) return false;
        }
        
        if((is_black(current, start)) && ((is_white(current, end)) || ((current.board[end/10][end%10]) == 0))) return true;
        
        else if((is_white(current, start)) && ((is_black(current, end)) || ((current.board[end/10][end%10]) == 0))) return true;
        
        else return false;
    }
    
    else if (value < 0)
    {
        for(int i = -1; i > value; i--)
        {
            if((current.board[(start/10)+i][start%10]) != 0) return false;
        }
        
        if((is_black(current, start)) && ((is_white(current, end)) || ((current.board[end/10][end%10]) == 0))) return true;
        
        else if((is_white(current, start)) && ((is_black(current, end)) || ((current.board[end/10][end%10]) == 0))) return true;
        
        else return false;
    }
    
    else if (value == 0)
    {
        value == ((end%10)-(start%10));
        
        if (value > 0)
        {
            for(int i = 1; i < value; i++)
            {
                if((current.board[(start/10)+i][start%10]) != 0) return false;
            }
        }
        
        else if (value < 0)
        {
            for(int i = -1; i > value; i--)
            {
                if((current.board[(start/10)+i][start%10]) != 0) return false;
            }
        }
        
        if ((is_black(current, start)) && ((is_white(current, end)) || ((current.board[end/10][end%10]) == 0))) return true;
        
        else if ((is_white(current, start)) && ((is_black(current, end)) || ((current.board[end/10][end%10]) == 0))) return true;
        
        else return false;
    }
    
    else if (is_white(current, start))
    {
        value = movement/10;
        if (value > 0) return false;
        if (value != 0)
        {
            for(int i = 1; i < value; i++)
            {
                if((current.board[(start/10)+i][start%10]) != 0) return false;
            }
            
            if((is_white(current, end)) || ((current.board[end/10][end%10]) == 0)) return true;
            else return false;
        }
        
        if (value == 0)
        {
            value == ((end%10)-(start%10));
            
            if (value > 0)
            {
                for(int i = 1; i < value; i++)
                {
                    if((current.board[(start/10)+i][start%10]) != 0) return false;
                }
            }
            
            else if (value < 0)
            {
                for(int i = -1; i > value; i--)
                {
                    if((current.board[(start/10)+i][start%10]) != 0) return false;
                }
            }
            
            if((is_white(current, end)) || ((current.board[end/10][end%10]) == 0)) return true;
            else return false;
        }
    }
}

/*
 * The following function determines if a move is valid for a queen.
 * The function determines if the end location is possible for a queen.
 * The function ensures no pieces are blocking the queen's path and/or the final position does not hold a piece of the same colour.
 * The function returns true the move is achievable and false otherwise.
 * The function evidently utilizes previously defined functions to reduce the complexity of the program.
 */ 

bool valid_queen(struct chess current, int start, int end)
{
    if (valid_rook(current, start, end)) return true;
    else if (valid_bishop(current, start, end)) return true;
    else return false;
}

/*
 * The following function determines if a move is valid for a white pawn.
 * The function determines if the end location is possible for a white pawn.
 * The function ensures no pieces are blocking the pawn's path and/or the final position does not hold a piece of the same colour.
 * The function returns true the move is achievable and false otherwise.
 */ 

bool white_valid_pawn(struct chess current, int start, int end)
{
    int movement = (end - start);
    
    if ((movement == -10) && ((current.board[end/10][end%10]) == 0)) return true;
    
    else if ((start%10 != (0 && 7)) && (movement == -9 || movement == -11) && (is_black(current, end))) return true;
    
    else if ((start%10 == 0) && (movement == -9) && (is_black(current, end))) return true;
    
    else if ((start%10 == 8) && (movement == -11) && (is_black(current, end))) return true;
    
    else if (((start/10) == 6) && (movement == -20) && ((current.board[end/10][end%10]) == 0)) return true;
    
    else return false;
}

/*
 * The following function determines if a move is valid for a black pawn.
 * The function determines if the end location is possible for a black pawn.
 * The function ensures no pieces are blocking the pawn's path and/or the final position does not hold a piece of the same colour.
 * The function returns true the move is achievable and false otherwise.
 */ 

bool black_valid_pawn(struct chess current, int start, int end)
{
    int movement = (end - start);
    
    if ((movement == 10) && ((current.board[end/10][end%10]) == 0)) return true;
    
    if (((start%10) != (0 && 7)) && ((movement == 9) || (movement == 11)) && (is_white(current, end))) return true;
    
    if ((start%10 == 0) && (movement == 11) && (is_white(current, end))) return true;
    
    if ((start%10 == 8) && (movement == 9) && (is_white(current, end))) return true;
    
    if (((start/10) == 1) && movement == 20 && ((current.board[end/10][end%10]) == 0)) return true;
    
    return false;
}

/*
 * This function determines if the move entered aligns with the correct colour turn.
 * This function restricts a player to move opposite colour pieces.
 * The function returns true if the move complies with the current turn, and false otherwise.
 */ 

bool turn(struct chess current, int position, int counter)
{
    int determine = counter%2;
    
    if((is_black(current, position)) && (determine == 1)) return true;
    else if ((is_white(current, position)) && (determine == 0)) return true;
    
    else return false;
}

/*
 * This is one of the few non-boolean functions.
 * This function physically moves a piece from position to another and returns a struct chess.
 * Pointers can be used to update the current board setting and the following 'move_piece' function.
 */ 

struct chess move_piece(struct chess current, int start, int end)
{
    int value = current.board[start/10][start%10];
    
    current.board[end/10][end%10] = 0;
    current.board[start/10][start%10] = 0;
    current.board[end/10][end%10] = value;
    
    return current;
}

/*
 * The follwoing function is only for debugging and quick compilation.
 * The fucntion prints the board out in the standard output.
 * This function should be commented out when compiling with the Python GUI.
 */ 

void print_board(struct chess current)
{
    int value = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j ++)
        {
            value = current.board[i][j];
            
            if (value == 0) printf("E        ");
            if (value == 1) printf("Rook_B   ");
            if (value == 2) printf("Knight_B ");
            if (value == 3) printf("Bishop_B ");
            if (value == 4) printf("Queen_B  ");
            if (value == 5) printf("King_B   ");
            if (value == 6) printf("Pawn_B   ");
            if (value == 7) printf("Pawn_W   ");
            if (value == 8) printf("Rook_W   ");
            if (value == 9) printf("Knight_W ");
            if (value == 10) printf("Bishop_W ");
            if (value == 11) printf("Queen_W  ");
            if (value == 12) printf("King_W   ");
        }
        printf("\n\n");
    }
    printf("\n");
}

/*
 * The following function determines if a piece is present at the indicated position.
 * The function returns true if the piece exists, and false otherwise.
 */ 

bool piece(struct chess current, int position)
{
    if ((current.board[position/10][position%10]) == 0) return false;
    else return true;
}

/*
 * The following function determines if a location exists in an eight by eight board.
 * The function returns true if the position exists, and false otherwise.
 */ 

bool is_board(int position)
{
    int value = position % 10;
    int value_2 = position / 10;
    
    if ((value > 7) || (value < 0)) return false;
    else if((value_2 > 7) || (value_2 < 0)) return false;
    
    else return true;
}

/*
 * The following function determines if a pawn swap can occur.
 * The function returns true if the move can occur, and false otherwise.
 */ 

bool pawn_swap(struct chess current, int position)
{
    int value = current.board[position/10][position%10];
    
    if ((value == 6) && ((position/10) == 7)) return true;
    else if ((value == 7) && ((position/10) == 0)) return true;
    
    else return false;
}

/*
 * The following function executes a pawn swap.
 * The function asks the user to input the value of the piece to be swapped to.
 * The function then changes the pwan to the indicated piece.
 */ 

struct chess pawn_swap_complete(struct chess current, int position)
{
    int value, color;
    
    printf("What would you like to promote the pawn to?\n\n");
    printf("Rook   = 1\nKnight = 2\nBishop  = 3\nQueen  = 4\n");
    scanf("%d", &value);
    
    color = is_black(current, position);
    
    if(color == 0)
    {
        if (value == 1) current.board[position/10][position%10] = 8;
        if (value == 2) current.board[position/10][position%10] = 9;
        if (value == 3) current.board[position/10][position%10] = 10;
        if (value == 4) current.board[position/10][position%10] = 11;
    }
    
    else if(color == 1)
    {
        if (value == 1) current.board[position/10][position%10] = 1;
        if (value == 2) current.board[position/10][position%10] = 2;
        if (value == 3) current.board[position/10][position%10] = 3;
        if (value == 4) current.board[position/10][position%10] = 4;
    }
    
    return current;
}

/*
 * The following function determines if a move is valid.
 * The function calls other functions specified on the piece entered.
 * The function returns true if the move is valid and false otherwise.
 */ 

bool valid_move(struct chess current, int start, int end)
{
    int piece = current.board[start/10][start%10];
    
    if ((piece == 6) && (black_valid_pawn(current, start, end))) return true;
    
    else if ((piece == 7) && (white_valid_pawn(current, start, end))) return true;
    
    else if (((piece == 1) || (piece == 8)) && (valid_rook(current, start, end))) return true;
    
    else if (((piece == 2) || (piece == 9)) && (valid_knight(current, start, end))) return true;
    
    else if (((piece == 3) || (piece == 10)) && (valid_bishop(current, start, end))) return true;
    
    else if (((piece == 4) || (piece == 11)) && (valid_queen(current, start, end))) return true;
    
    else if (((piece == 5) || (piece == 12)) && (valid_king(current, start, end))) return true;
    
    else return false;
}

/*
 * The following function determines if the white king is in check.
 * The function calls other functions specified on the piece entered.
 * The function returns true if the white king is not in check and false otherwise.
 */ 

bool white_king(struct chess current)
{
    int final = 0, i = 0;
    
    for (int t = 0; t < 8; t++)
    {
        for (int k = 0; k < 8; k++)
        {
            if(current.board[t][k] == 12) final = (t*10)+k;
        }
    }
    
    int final_2 = 0;
    
    for (int t = 0; t < 8; t++)
    {
        for (int k = 0; k < 8; k++)
        {
            final_2 = ((t*10)+k);
            if(valid_move(current, final_2, final)) return false;
        }
    }
    return true;
}

/*
 * The following function determines if the black king is in check.
 * The function calls other functions specified on the piece entered.
 * The function returns true if the black king is not in check and false otherwise.
 */ 

bool black_king(struct chess current)
{
    int final = 0, i = 0;
    
    for (int t = 0; t < 8; t++)
    {
        for (int k = 0; k < 8; k++)
        {
            if(current.board[t][k] == 5) final = (t*10)+k;
        }
    }
    
    int final_2 = 0;
    
    for (int t = 0; t < 8; t++)
    {
        for (int k = 0; k < 8; k++)
        {
            final_2 = ((t*10)+k);
            if(valid_move(current, final_2, final)) return false;
        }
    }
    return true;
}

/*
 * The following function determines if the black king is in check mate.
 * The function calls other functions specified on the piece entered.
 * The function returns true if the black king is not in check mate and false otherwise.
 */ 

bool black_king_check(struct chess current)
{
	int flag = 0;
	
	struct chess *board_temporary;
    struct chess temporary;
    board_temporary = &temporary;
    
		for (int j = 0; j < 64; j++)
		{
		for (int i = 0; i < 64; i++)
		{
		  *board_temporary = move_piece(current, j, i);
			if(black_king(temporary)) flag ++;
		}
	}

	if (flag == 0) return false;
	else return true;
}

/*
 * The following function determines if the white king is in check mate.
 * The function calls other functions specified on the piece entered.
 * The function returns true if the white king is not in check mate and false otherwise.
 */ 

bool white_king_check(struct chess current)
{
	int flag = 0;
	
	  struct chess *board_temporary;
    struct chess temporary;
    board_temporary = &temporary;
    
		for (int j = 0; j < 64; j++)
		{
		for (int i = 0; i < 64; i++)
		{
		  *board_temporary = move_piece(current, j, i);
			if(white_king(temporary)) flag ++;
		}
	}

	if (flag == 0) return false;
	else return true;
}

/*
 * The following is the main function, which executes the game.
 * The main function intializes a blank chess board and begins a game.
 * The game is ended when one of the two kings is in check mate.
 * Alongside printing the board each move, the main function also outputs user prompts.
 * To compile with the Python GUI, redirect the outputs to the Python file.
 */ 


int main(void)
{
    struct chess current = {1,2,3,4,5,3,2,1,6,6,6,6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,7,7,7,8,9,10,11,12,10,9,8};
    
    struct chess *board;
    struct chess *board_temporary;
    struct chess temporary;
    board_temporary = &temporary;
    board = &current;
    int start = 0, end = 0, counter = 0, colour;
    
    while (black_king_check(current) && white_king_check(current))
    {
        printf("Please enter in the starting location:\n");
        scanf("%d", &start);
        
        printf("Please enter in the ending location:\n");
        scanf("%d", &end);
        
        colour = counter % 2;
        
        *board_temporary = move_piece(current, start, end); 
        
        if(current.board[start/10][start%10] == 0) printf("\nNo piece at this position!\n\n");
        
        else
        {
            if(is_board(start))
            {
                if(is_board(end))
                {
                    if(turn(current, start, counter))
                    { 
                      if(((colour == 0) && (white_king(temporary))) || ((colour == 1) && (black_king(temporary))))
                      {
                        if (valid_move(current, start, end)) 
                        {
                            *board = move_piece(current, start, end);
                            
                            if (pawn_swap(current, end))
                            {
                                *board = pawn_swap_complete(current, end);
                            }
                            
                            printf("\n");
                            print_board(current);
                            
                            counter++;
                        }
                        
                        else printf("\nThe move entered is invalid!\n\n");
                      }
                      else printf("\nThis move does not move your King out of check!\n");
                    }
                    else printf("\nWrong Player!\n\n");
                }
                else printf("\nThe final position is not on the board!\n\n");
            }
            else printf("\nThe intial position is not on the board!\n\n");
        }
        
        if((black_king(current)) == 0) printf("\nBlack King is in check!\n\n");
        
        if((white_king(current)) == 0) printf("\nWhite King is in check!\n\n");
        
    }
    
    if (black_king_check(current) == 0 ) printf("Game Over, White Wins!\n");
    else if (white_king_check(current) == 0) printf("Game Over, Black Wins!\n");
    else printf("Time to Debug!\n");
    
    return 0;
}
