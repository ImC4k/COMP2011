#include <iostream>
#include <stdlib.h>

using namespace std;

/*
 * print the game board
 *
 * this function is given and already complete
 * do NOT modify anything of it
 */
void printGameBoard(char s1, char s2, char s3, char s4, char s5, char s6, char s7, char s8, char s9)
{
	cout << "     |     |     " << endl;
	cout << "  " << s1 << "  |  " << s2 << "  |  " << s3 << endl;
	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;
	cout << "  " << s4 << "  |  " << s5 << "  |  " << s6 << endl;
	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;
	cout << "  " << s7 << "  |  " << s8 << "  |  " << s9 << endl;
	cout << "     |     |     " << endl << endl;
}

/*
 * print the message that asks the current player for his/her input
 *
 * you MUST call this function in your getValidInput implementation
 *
 * this function is given and already complete
 * do NOT modify anything of it
 */
void printQuestion(char currentPlayerSymbol)
{
	 cout << "Player " << currentPlayerSymbol << ", please choose an unoccupied space (0 to quit): " << endl;
}

/*
 * return 'X' (uppercase English letter X) when roundNumber is odd
 * return 'O' (uppercase English letter O) otherwise
 *
 * complete the function body code, but do NOT modify the function prototype (including the function name, parameters, and return type)
 */
char getCurrentPlayerSymbol(int roundNumber)
{
	if(roundNumber%2){
		return 'X';
	}else{
		return 'O';
	}
}

/*
 * return whether the input is valid
 * an input is valid if and only if the input is in the valid range of [0, 9]
 * and that the input refers to an unoccupied space (i.e. not 'O' and not 'X')
 *
 * be reminded to always return either true or false in all scenarios
 *
 * complete the function body code, but do NOT modify the function prototype (including the function name, parameters, and return type)
 */
bool isInputValid(int input, char s1, char s2, char s3, char s4, char s5, char s6, char s7, char s8, char s9)
{
	if(input<0 || input>9){
		return false;
	}
	switch(input){
		case 0: return true;
		case 1: if(s1=='O'||s1=='X'){return false;} else {return true;}
		case 2: if(s2=='O'||s2=='X'){return false;} else {return true;}
		case 3: if(s3=='O'||s3=='X'){return false;} else {return true;}
		case 4: if(s4=='O'||s4=='X'){return false;} else {return true;}
		case 5: if(s5=='O'||s5=='X'){return false;} else {return true;}
		case 6: if(s6=='O'||s6=='X'){return false;} else {return true;}
		case 7: if(s7=='O'||s7=='X'){return false;} else {return true;}
		case 8: if(s8=='O'||s8=='X'){return false;} else {return true;}
		case 9: if(s9=='O'||s9=='X'){return false;} else {return true;}
		default: return false;

	}
}

/*
 * use some kind of loop to retrieve a valid integer input from the player, and return it at the end of the function
 * the flow is as follows
 * 1. Print exactly the question message "Player X, please choose an unoccupied space (0 to quit): "
 *    or "Player O, please choose an unoccupied space (0 to quit): " depending on what currentPlayerSymbol is,
 *    using the given printQuestion function
 * 2. Retrieve the integer input using cin
 * 3. If the input is valid (use the isInputValid function), return the input; if the input is invalid, go back to step 1
 *
 * *** IMPORTANT REQUIREMENT ***
 * you must NOT use any cout statement directly to print the question message in this function - you MUST call the given printQuestion function to print the message
 *
 * you can assume the player is sane and always inputs an integer (e.g. no alphabet/symbol input etc.)
 *
 * complete the function body code, but do NOT modify the function prototype (including the function name, parameters, and return type)
 */
int getValidInput(char currentPlayerSymbol, char s1, char s2, char s3, char s4, char s5, char s6, char s7, char s8, char s9)
{
	int input = -1;
	do{
		//1.
		printQuestion(currentPlayerSymbol);
		//2.
		cin >> input;
	}while(!isInputValid(input, s1, s2, s3, s4, s5, s6, s7, s8, s9)); // 3.
	return input;
}

/*
 * put the currentPlayerSymbol to one of the s1, s2, ..., s9 variables according to the input which is guaranteed to be in the range of [1, 9]
 *
 * complete the function body code, but do NOT modify the function prototype (including the function name, parameters, and return type)
 */
void putSymbol(int input, char currentPlayerSymbol, char& s1, char& s2, char& s3, char& s4, char& s5, char& s6, char& s7, char& s8, char& s9)
{
	switch(input){
		case 1: s1 = currentPlayerSymbol; break;
		case 2: s2 = currentPlayerSymbol; break;
		case 3: s3 = currentPlayerSymbol; break;
		case 4: s4 = currentPlayerSymbol; break;
		case 5: s5 = currentPlayerSymbol; break;
		case 6: s6 = currentPlayerSymbol; break;
		case 7: s7 = currentPlayerSymbol; break;
		case 8: s8 = currentPlayerSymbol; break;
		case 9: s9 = currentPlayerSymbol; break;
		default: break;
	}
}

/*
 * return the game state
 * game state is 1 if player 1 (X) has won the game
 * game state is 2 if player 2 (O) has won the game
 * game state is -1 if the broad is full and no one has won the game yet (i.e. draw game)
 * game state is 0 otherwise
 *
 * complete the function body code, but do NOT modify the function prototype (including the function name, parameters, and return type)
 */
int getGameState(char s1, char s2, char s3, char s4, char s5, char s6, char s7, char s8, char s9)
{
	// 1 2 3
	// 4 5 6
	// 7 8 9

	//(1,2,3) , (1,5,9) , (1,4,7)
	//(2,5,8)
	//(3,5,7) , (3,6,9)
	//(4,5,6)
	//(7,8,9)
	if(s1=='X' || s1=='O'){
		if(s1=='X' && s2=='X' && s3=='X'){
			return 1;
		}else if(s1=='X' && s5=='X' && s9=='X'){
			return 1;
		}else if(s1=='X' && s4=='X' && s7=='X'){
			return 1;
		}else if(s1=='O' && s2=='O' && s3=='O'){
			return 2;
		}else if(s1=='O' && s5=='O' && s9=='O'){
			return 2;
		}else if(s1=='O' && s4=='O' && s7=='O'){
			return 2;
		}
	}
	if(s2=='X' || s2=='O'){
		if(s2=='X' && s5=='X' && s8=='X'){
			return 1;
		}else if(s2=='O' && s5=='O' && s8=='O'){
			return 2;
		}
	}
	if(s3=='X' || s3=='O'){
		if(s3=='X' && s5=='X' && s7=='X'){
			return 1;
		}else if(s3=='O' && s5=='O' && s7=='O'){
			return 2;
		}else if(s3=='X' && s6=='X' && s9=='X'){
			return 1;
		}else if(s3=='O' && s6=='O' && s9=='O'){
			return 2;
		}
	}
	if(s4=='X' || s4=='O'){
		if(s4=='X' && s5=='X' && s6=='X'){
			return 1;
		}else if(s4=='O' && s5=='O' && s6=='O'){
			return 2;
		}
	}
	if(s7=='X' || s7=='O'){
		if(s7=='X' && s8=='X' && s9=='X'){
			return 1;
		}else if(s7=='O' && s8=='O' && s9=='O'){
			return 2;
		}
	}
	if((s1=='O'||s1=='X')&&(s2=='O'||s2=='X')&&(s3=='O'||s3=='X')&&(s4=='O'||s4=='X')&&(s5=='O'||s5=='X')
		&&(s6=='O'||s6=='X')&&(s7=='O'||s7=='X')&&(s8=='O'||s8=='X')&&(s9=='O'||s9=='X')){
			return -1;
		}
	return 0;
}

/*
 * return whether the game is over
 * the game is over when the game is a draw game, or either of the players has won
 *
 * complete the function body code, but do NOT modify the function prototype (including the function name, parameters, and return type)
 */
bool isGameOver(char s1, char s2, char s3, char s4, char s5, char s6, char s7, char s8, char s9)
{
	switch(getGameState(s1,s2,s3,s4,s5,s6,s7,s8,s9)){
		case 1:
		case 2:
		case -1:return true;
		case 0:
		default: return false;
	}
}

/*
 * this is the main function
 *
 * this function is given and already complete
 * do NOT modify anything of it
 */
int main()
{
	char s1 = '1', s2 = '2', s3 = '3', s4 = '4', s5 = '5', s6 = '6', s7 = '7', s8 = '8', s9 = '9'; //variables that represent the 9 spaces in the game board
	int roundNumber = 1; //the round number, starts with 1
	int gameState = 0; //game state, refer to the getGameState function for a description

	while(!isGameOver(s1, s2, s3, s4, s5, s6, s7, s8, s9)) //keep going until the game is over
	{
		char currentPlayerSymbol = getCurrentPlayerSymbol(roundNumber); //player symbol is either 'X' or 'O', refer to the getCurrentPlayerSymbol function for a description

		//print the round number and game board
		cout << "Round " << roundNumber << ":" << endl << endl;
		printGameBoard(s1, s2, s3, s4, s5, s6, s7, s8, s9);

		//get a valid input
		int input = getValidInput(currentPlayerSymbol, s1, s2, s3, s4, s5, s6, s7, s8, s9);

		if(input == 0) //exit the program if input is 0
		{
			cout << endl << "Bye!" << endl;
			return 0;
		}
		else //put the current player symbol to the board otherwise
			putSymbol(input, currentPlayerSymbol, s1, s2, s3, s4, s5, s6, s7, s8, s9);

		//update the game state
		gameState = getGameState(s1, s2, s3, s4, s5, s6, s7, s8, s9);

		//increase the round number
		roundNumber++;

		cout << endl << endl;
	}

	//game is done at this point, show the result
	cout << "Final state:" << endl << endl;
	printGameBoard(s1, s2, s3, s4, s5, s6, s7, s8, s9);
	if(gameState == -1) cout << "Draw game! Whoops!" << endl;
	else cout << "Congratulations, player " << (gameState==1?'X':'O') << "! You won! Wow!" << endl;
	system("pause");
	return 0;
}
