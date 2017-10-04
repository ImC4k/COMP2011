#include <iostream>
#include <ctime>

using namespace std;

// TODO: guessing game functions
//generate a secret number for the guessingGame, guessing process
int genSecretNum(int range){
  int secretNum;
  srand(time(NULL));
  secretNum = rand()%range+1;
  return secretNum;

}

//create time pause
void pause(int dur){
  int temp = time(NULL) + dur;
  while(temp > time(NULL));
}


int guessingGame(){
  //variable declaration area
  int totalRound = 0;

  START_GAME:
  int numPlayer = -1;
  int range;
  int guess;
  int totalTurn = 1;
  int playerTurn;
  int highValue;
  int lowValue;

  // input number of players
  cout<<"\n\n\n\n\n\n\n"<<endl;
  cout<<"How many players?"<<endl;
  {
    cin>>numPlayer;
    while(cin.fail()||numPlayer == 0){
      cout<<"Invalid input, please re-enter."<<endl;
      cin.clear();
      cin.ignore(256,'\n');
      cin>>numPlayer;
    }
  }
  cout<<"Input the range (100-1000):"<<endl;
  cin>>range;
  while(cin.fail()|| (range < 100 || range > 1000)){
    cout<<"Invalid input, the number should be 100-1000: "<<endl;
    cin.clear();
    cin.ignore(256,'\n');
    cin>>range;
  }
  const int SECRET_NUM = genSecretNum(range);
  lowValue = 1;
  highValue = range;

  //NOTE:DUBUGGING AREA
  //secretNum = 40;
  cout<<"\n\nDEBUG ONLY: GENERATED SECRET NUMBER = "<<SECRET_NUM<<"\n\n"<<endl;


  //TODO: INSTRUCTIONS for users
  if(totalRound-1){
    cout<<"\n\n************************"<<endl;
    if(numPlayer==1)
      cout<<"Hello player, welcome to the guessing game!\n"<<endl;
    else
      cout<<"Hello players, welcome to the guessing game!\n"<<endl;
    cout<<"The game is simple:\nWhoever be the first player to guess\nthe secret number correctly, he/she wins!\n"<<endl;
    cout<<"GOOD LUCK!"<<endl;
    cout<<"************************"<<endl;
    pause(3);
    cout<<"\n\n\n\n\n\n\n\n\n"<<endl;
  }
  else cout<<"\n\n\n\n\n\n\n\n\n"<<endl;


  // The guessing process, infinite loop until someone guesses the secret number (secretNum) successfully
  do{
  playerTurn = (totalTurn-1)%numPlayer+1;
    cout<<"The guessing range is now from "<<lowValue<<" to "<<highValue<<"."<<endl<<endl;
    cout<<"Player "<<playerTurn<<", it's your turn to guess.\n"<<endl;

    // Allow re-enter guess because previous guess was invalid
    INPUT_GUESS:
    cin>>guess;
    while(cin.fail()){
      cout<<"Invalid input, please try again."<<endl;
      cin.clear();
      cin.ignore(256,'\n');
      cin>>guess;
      }

    // Handle invalid answers, allow re-enter
    if (((guess == lowValue) && (lowValue != 1)) || ((guess == highValue) && (highValue != range))){
      cout<<"Someone has already guessed it and it's incorrect.\n"<<endl;
      cout<<"Please re-enter your guess.\n"<<endl;
      goto INPUT_GUESS;
    }
    else if(guess < lowValue || guess > highValue){
      cout<<"Your guess is invalid, it should be from "<<lowValue<<" to "<<highValue<<"."<<endl;
      cout<<"Please re-enter your guess.\n"<<endl;
      goto INPUT_GUESS;
    }

    // Check if player's guess is correct or not
    if(guess == SECRET_NUM){
      break;
    }
    else if(guess < SECRET_NUM){
      cout<<"Sorry, the secret number is larger than "<<guess<<"\n\n"<<endl;
      lowValue = guess;
      pause(1);
      cout<<"\n\n\n\n\n\n\n\n\n"<<endl;
    }
    else if(guess > SECRET_NUM){
      cout<<"Sorry, the secret number is smaller than "<<guess<<"\n\n"<<endl;
      highValue = guess;
      pause(1);
      cout<<"\n\n\n\n\n\n\n\n\n"<<endl;
    }

    totalTurn++;
  }
  while(guess != SECRET_NUM);

  //victory message
  if(totalTurn==1){
    cout<<"\n\n\n\n\n\n\n\n\n"<<endl;
    cout<<"************************\n"<<endl;
    cout<<"Superb! You aced it!"<<endl;
  }
  else{
    cout<<"\n\n\n\n\n\n\n\n\n"<<endl;
    cout<<"************************\n"<<endl;
    cout<<"Congratulations player "<<playerTurn<<", you won the game!\n"<<endl;
    cout<<"(A total of "<< totalTurn<<" guesses were used to guess the number correctly.)\n\n"<<endl;
  }
  cout<<"************************\n\n"<<endl;

  cout<<"Replay game? Enter \'y\' or \'n\':"<<endl;
  char rerun_game;
  cin>>rerun_game;

  while(cin.fail() || (rerun_game != 'y' && rerun_game != 'n')){
  cout<<"Invalid input, please enter again."<<endl;
  cin.clear();
  cin.ignore(256,'\n');
  cin>>rerun_game;
  }
  if(rerun_game =='y'){
    totalRound++;
    goto START_GAME;
  }
  else if(rerun_game == 'n'){
    cout<<"THANKS FOR PLAYING!"<<endl;
  }

  return 0;
}


// TODO: tic tac toe
/*
 * print the game board
 *
 * this function is given and already complete
 * do NOT modify anything of it
 */
void printGameBoard_TTT(char s1, char s2, char s3, char s4, char s5, char s6, char s7, char s8, char s9){
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
void printQuestion(char currentPlayerSymbol){
	 cout << "Player " << currentPlayerSymbol << ", please choose an unoccupied space (0 to quit): " << endl;
}

/*
 * return 'X' (uppercase English letter X) when roundNumber is odd
 * return 'O' (uppercase English letter O) otherwise
 *
 * complete the function body code, but do NOT modify the function prototype (including the function name, parameters, and return type)
 */
char getCurrentPlayerSymbol(int roundNumber){
	// TODO
	return (roundNumber%2)? 'X':'O';
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
bool isInputValid(int input, char s1, char s2, char s3, char s4, char s5, char s6, char s7, char s8, char s9){
	// TODO
	switch(input){
		case 0: return true;
		case 1: if(s1!='O' && s1!='X') return true; else return false;
		case 2: if(s2!='O' && s2!='X') return true; else return false;
		case 3: if(s3!='O' && s3!='X') return true; else return false;
		case 4: if(s4!='O' && s4!='X') return true; else return false;
		case 5: if(s5!='O' && s5!='X') return true; else return false;
		case 6: if(s6!='O' && s6!='X') return true; else return false;
		case 7: if(s7!='O' && s7!='X') return true; else return false;
		case 8: if(s8!='O' && s8!='X') return true; else return false;
		case 9: if(s9!='O' && s9!='X') return true; else return false;
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
 * you can assume the player is same and always inputs an integer (e.g. no alphabet/symbol input etc.)
 *
 * complete the function body code, but do NOT modify the function prototype (including the function name, parameters, and return type)
 */
int getValidInput(char currentPlayerSymbol, char s1, char s2, char s3, char s4, char s5, char s6, char s7, char s8, char s9){
	// TODO
	int input;
	do{
		printQuestion(currentPlayerSymbol);
		cin>>input;
	}while(!isInputValid(input, s1, s2, s3, s4, s5, s6, s7, s8, s9));
	return input;
}

/*
 * put the currentPlayerSymbol to one of the s1, s2, ..., s9 variables according to the input which is guaranteed to be in the range of [1, 9]
 *
 * complete the function body code, but do NOT modify the function prototype (including the function name, parameters, and return type)
 */
void putSymbol(int input, char currentPlayerSymbol, char& s1, char& s2, char& s3, char& s4, char& s5, char& s6, char& s7, char& s8, char& s9){
	// TODO
	switch (input) {
		case 1: s1 = currentPlayerSymbol; break;
		case 2: s2 = currentPlayerSymbol; break;
		case 3: s3 = currentPlayerSymbol; break;
		case 4: s4 = currentPlayerSymbol; break;
		case 5: s5 = currentPlayerSymbol; break;
		case 6: s6 = currentPlayerSymbol; break;
		case 7: s7 = currentPlayerSymbol; break;
		case 8: s8 = currentPlayerSymbol; break;
		case 9: s9 = currentPlayerSymbol; break;
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
int getGameState(char s1, char s2, char s3, char s4, char s5, char s6, char s7, char s8, char s9){
	// TODO
	// X player cases
	if((s1=='X' && s4=='X' && s7=='X') || (s2=='X' && s5=='X' && s8=='X') || (s3=='X' && s6=='X' && s9=='X')){// Vertical
		return 1;
	}
	else if((s1=='X' && s2=='X' && s3=='X') || (s4=='X' && s5=='X' && s6=='X') || (s7=='X' && s8=='X' && s9=='X')){// Horizontal
		return 1;
	}
	else if ((s1=='X' && s5=='X' && s9=='X') || (s3=='X' && s5=='X' && s7=='X')) {// Diagonal
		return 1;
	}

	// O player cases
	if((s1=='O' && s4=='O' && s7=='O') || (s2=='O' && s5=='O' && s8=='O') || (s3=='O' && s6=='O' && s9=='O')){// Vertical
		return 1;
	}
	else if((s1=='O' && s2=='O' && s3=='O') || (s4=='O' && s5=='O' && s6=='O') || (s7=='O' && s8=='O' && s9=='O')){// Horizontal
		return 1;
	}
	else if ((s1=='O' && s5=='O' && s9=='O') || (s3=='O' && s5=='O' && s7=='O')) {// Diagonal
		return 1;
	}

	if((s1 == 'X' || s1 == 'O') && (s2 == 'X' || s2 == 'O') && (s3 == 'X' || s3 == 'O') && (s4 == 'X' || s4 == 'O') && (s5 == 'X' || s5 == 'O') &&
	 (s6 == 'X' || s6 == 'O') && (s7 == 'X' || s7 == 'O') && (s8 == 'X' || s8 == 'O') && (s9 == 'X' || s9 == 'O')){// Draw situation
		 return -1;
	 }

	 return 0;// Still playing

}

/*
 * return whether the game is over
 * the game is over when the game is a draw game, or either of the players has won
 *
 * complete the function body code, but do NOT modify the function prototype (including the function name, parameters, and return type)
 */
bool isGameOver(char s1, char s2, char s3, char s4, char s5, char s6, char s7, char s8, char s9){
	// TODO: call getGameState
	return (getGameState(s1, s2, s3, s4, s5, s6, s7, s8, s9) !=0);

}

/*
 * this is the main function
 *
 * this function is given and already complete
 * do NOT modify anything of it
 */
int ticTacToe(){
  START_GAME:
	char s1 = '1', s2 = '2', s3 = '3', s4 = '4', s5 = '5', s6 = '6', s7 = '7', s8 = '8', s9 = '9'; //variables that represent the 9 spaces in the game board
	int roundNumber = 1; //the round number, starts with 1
	int gameState = 0; //game state, refer to the getGameState function for a description

	while(!isGameOver(s1, s2, s3, s4, s5, s6, s7, s8, s9)) //keep going until the game is over
	{
		char currentPlayerSymbol = getCurrentPlayerSymbol(roundNumber); //player symbol is either 'X' or 'O', refer to the getCurrentPlayerSymbol function for a description

		//print the round number and game board
		cout << "Round " << roundNumber << ":" << endl << endl;
		printGameBoard_TTT(s1, s2, s3, s4, s5, s6, s7, s8, s9);

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
	printGameBoard_TTT(s1, s2, s3, s4, s5, s6, s7, s8, s9);
	if(gameState == -1) cout << "Draw game! Whoops!" << endl;
	else cout << "Congratulations, player " << (gameState==1?'X':'O') << "! You won! Wow!" << endl;

  cout<<"Replay game? Enter \'y\' or \'n\':"<<endl;
  char rerun_game;
  cin>>rerun_game;

  while(cin.fail()||(rerun_game != 'y' && rerun_game != 'n')){
  cout<<"Invalid input, please enter again."<<endl;
  cin.clear();
  cin.ignore(256,'\n');
  cin>>rerun_game;
  }
  if(rerun_game =='y'){
    goto START_GAME;
  }
  else if(rerun_game == 'n'){
    cout<<"THANKS FOR PLAYING!"<<endl;
  }

	return 0;
}

int printGameBoard_REVERSI(char board_slots[],const int HEIGHT, const int WIDTH){
  for(int i = 0; i<HEIGHT*WIDTH; i++){
    cout<<board_slots[i];
    if(i%WIDTH ==7){
      cout<<endl;
    }
  }
  return 0;
}

int reversi(){
  START_GAME:
  // char s1 = 1, s2 = 2, s3 = 3, s4 = 4, s5 = 5, s6 = 6, s7 = 7, s8 = 8,
  //       s9 = 9, s10 = 10, s11 = 11, s12 = 12, s13 = 13, s14 = 14, s15 = 15, s16 = 16,
  //       s17 = 17, s18 = 18, s19 = 19, s20 = 20, s21 = 21, s22 = 22, s23 = 23, s24 = 24,
  //       s25 = 25, s26 = 26, s27 = 27, s28 = 28, s29 = 29, s30 = 30, s31 = 31, s32 = 32,
  //       s33 = 33, s34 = 34, s35 = 35, s36 = 36, s37 = 37, s38 = 38, s39 = 39, s40 = 40,
  //       s41 = 41, s42 = 42, s43 = 43, s44 = 44, s45 = 45, s46 = 46, s47 = 47, s48 = 48,
  //       s49 = 49, s50 = 50, s51 = 51, s52 = 52, s53 = 53, s54 = 54, s55 = 55, s56 = 56,
  //       s57 = 57, s58 = 58, s59 = 59, s60 = 60, s61 = 61, s62 = 62, s63 = 63, s64 = 64;
  const int HEIGHT = 8;
  const int WIDTH = 8;
  char board_slots[] = {
        '1', '2', '3', '4', '5', '6', '7', '8',
        '9', '10', '11', '12', '13', '14', '15', '16',
        '17', '18', '19', '20', '21', '22', '23', '24',
        '25', '26', '27', 'X', 'O', '30', '31', '32',
        '33', '34', '35', 'O', 'X', '38', '39', '40',
        '41', '42', '43', '44', '45', '46', '47', '48',
        49, 50, 51, 52, 53, 54, 55, 56,
        57, 58, 59, 60, 61, 62, 63, 64
  };
  printGameBoard_REVERSI(board_slots, HEIGHT, WIDTH);
  return 0;
}




int main(){
  cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n************************"<<endl;
  cout<<"WELCOME TO GAME CENTER!"<<endl;

  START_GAME_CENTER:

  cout<<"************************"<<endl;
  cout<<"Enter a number to \nselect a game!"<<endl<<endl;
  cout<<"1: THE GUESSING GAME"<<endl<<endl;
  cout<<"2: TIC TAC TOE"<<endl;
  cout<<"3: REVERSI"<<endl<<endl;
  cout<<"************************"<<endl;
  int gameSelect;
  cin>>gameSelect;
  while(cin.fail() || (gameSelect<1 || gameSelect>3)){
    cout<<"Game selection is not available, please choose again: "<<endl;
    cin.clear();
    cin.ignore(256,'\n');
    cin>>gameSelect;
  }
  switch(gameSelect){
    case 1: cout<<"GUESSING GAME is now commencing"<<endl; pause(1); cout<<"."<<endl; pause(1); cout<<"."<<endl; pause(1); cout<<"."<<endl; pause(1);
            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n"<<endl; guessingGame(); break;
    case 2: cout<<"TIC TAC TOE is now commencing"<<endl; pause(1); cout<<"."<<endl; pause(1); cout<<"."<<endl; pause(1); cout<<"."<<endl; pause(1);
            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n"<<endl; ticTacToe(); break;
    case 3: cout<<"REVERSI is now commencing"<<endl; pause(1); cout<<"."<<endl; pause(1); cout<<"."<<endl; pause(1); cout<<"."<<endl; pause(1);
            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n"<<endl; reversi(); break;
    default: cout<<"?"<<endl;
  }
  cout<<"\n\n\n\n\n\n\n\nDo you want to play another game?"<<endl;
  cout<<"Enter \'y\' to play, \'n\' to escape program."<<endl;
  char rerun_program;
  cin>> rerun_program;
  while(cin.fail() || (rerun_program != 'y' && rerun_program != 'n')){
    cout<<"Invalid input."<<endl;
    cin.clear();
    cin.ignore(256,'\n');
    cin>>rerun_program;
  }
  if(rerun_program=='y'){
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n"<<endl;
    goto START_GAME_CENTER;
  }
  else cout<<"GOODBYE!"<<endl;
  return 0;
}
