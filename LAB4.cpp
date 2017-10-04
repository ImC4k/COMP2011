#include <iostream>
using namespace std;

//Task 1 Write a function print_maze to print the maze.
int print_maze(const char maze[], const int HEIGHT, const int WIDTH){
  for(int i = 0; i<HEIGHT*WIDTH; i++){
    cout<<maze[i];
    if(i%WIDTH==(WIDTH-1)){
      cout<<endl;
    }
  }
  return 0;
}

//Task 2 Write a function is_valid_move to check if the move is valid or not.
bool is_valid_move(const char maze[], const int HEIGHT, const int WIDTH, const int x, const int y, const char move){
  switch (move) { // TODO: HANDLE BOUNDARY CASE TOO!!!!!
    case 'w':
      if(y != 0 && (maze[x+(WIDTH)*(y-1)]==' ' || maze[x+(WIDTH)*(y-1)]=='E')){
        return true;
      }
      return false;
    case 'a':
      if(x != 0 && (maze[x-1+WIDTH*y]==' ' || maze[x-1+(WIDTH)*y]=='E')){
        return true;
      }
        return false;
    case 's':
      if(y != HEIGHT && (maze[x+WIDTH*(y+1)]==' ' || maze[x+(WIDTH)*(y+1)]=='E')){
        return true;
      }
      return false;
    case 'd':
      if(x != WIDTH && (maze[x+1+(WIDTH)*y]==' ' || maze[x+1+(WIDTH)*y]=='E')){
        return true;
      }
      return false;
  }
  return false;
}
//Task 3 Write a function update_maze to update the position of the player in the maze.
int update_maze(char maze[], const int HEIGHT, const int WIDTH, int x, int y){
  if(maze[x+WIDTH*(y+1)]=='P'){ // remove previous P position
    maze[x+WIDTH*(y+1)] = ' ';
  }
  else if(maze[x+WIDTH*(y-1)]=='P'){
    maze[x+WIDTH*(y-1)] = ' ';
  }
  else if(maze[x+1+WIDTH*y]=='P'){
    maze[x+1+WIDTH*y] = ' ';
  }
  else if(maze[x-1+WIDTH*y]=='P'){
    maze[x-1+WIDTH*y]= ' ';
  }
  maze[x+y*WIDTH] = 'P';
  return 0;
}

int main() {
	const int HEIGHT = 9;
	const int WIDTH = 18;
	char maze[] =
          {'#', '#', '#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
				   '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#',
				   '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', '#', '#',
				   '#', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', '#', ' ', '#', ' ', '#',
				   ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				   ' ', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', '#', ' ', ' ',
				   '#', '#', '#', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', '#', ' ', '#',
				   '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#',
				   '#', '#', ' ', '#', '#', '#', '#', '#', ' ', ' ', '#', 'E', '#', '#', '#', '#', '#', '#',
	};

	int x = 1, y = 1;
	char move;
	update_maze(maze, HEIGHT, WIDTH, x, y);
	bool is_valid;
	do {
		print_maze(maze, HEIGHT, WIDTH);
		cout << "Your current position is at: (" << x << ", " << y << ")"
				<< endl;
		do {
			cout << "Please enter your move: (up:w, down:s, left:a, right:d)  ";
			cin >> move;
			is_valid = is_valid_move(maze, HEIGHT, WIDTH, x, y, move);
			if (is_valid) {
				switch (move) {
				case 'w':
					y--;
					break;
				case 's':
					y++;
					break;
				case 'a':
					x--;
					break;
				case 'd':
					x++;
					break;
				default:
					break;
				}
				update_maze(maze, HEIGHT, WIDTH, x, y);
			} else {
				cout << "The move is invalid!" << endl;
			}
		} while (!is_valid);
	} while (!(x == 11 && y == 8));

	cout << "Amazing! You have completed the maze!" << endl;

	return 0;

}
