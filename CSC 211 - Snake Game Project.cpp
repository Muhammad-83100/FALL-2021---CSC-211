/* CSC 211 - FALL 2021
* Muhammad Ali
* CUNY ID#: 23590404
*/

#include <iostream>
#include <conio.h> //console input-output library
#include <windows.h>
#include <time.h>

using namespace std;

bool game_over;

//dimensions of the game map
const int width = 20;
const int height = 20;

//variables for the coordinates of the snake head and the fruit (and the player's score)
int x, y, fruit_x, fruit_y, score;

//snake tail-relatead variables
int tail_x[100], tail_y[100]; 
int tail_length; //length of said tail

enum Direction { Stop = 0, Left, Right, Up, Down };
Direction direc;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

//all necessary functions
void user_control_choice(char&);
void setup(); 
void draw(); 
void input();
void inverted_input();
void logic(); 

int main()
{
	char control_choice;
	
	user_control_choice(control_choice); //calling function to determine whether user wants inverted controls or not
	setup(); //calling the setup function
	
	while (!game_over) //calling the remaining functions until it is game over
	{
		draw();
		if (control_choice == 'Y' || control_choice == 'y') //if user said yes to inverted controls we call the inverted input function
		{
			inverted_input();
		}
		else //otherwise we call the regular input function
		{
			input();
		}
		logic();
		
		//slowing down the snake and making it so it travels up/down at the same speed as it does left/right
		if (direc == Left || direc == Right)
		{
			Sleep(5);
		}
		if (direc == Up || direc == Down)
		{
			Sleep(15);
		}
	}
	
	system("pause");
	return 0;
}

void user_control_choice(char& control_choice) //prompts user to establish whether they want inverted controls for their game or not
{
	cout << "Would you like to use inverted controls? (Y-y for YES and N-n for NO): ";
	cin >> control_choice;

	if (control_choice == 'Y' || control_choice == 'y')
	{
		cout << "\nDISCLAIMER: The controls for this game are now INVETRTED! (w - Down, s - Up, a - Right, d - Left)" << endl;
		cout << "GOOD LUCK!" << endl << endl;
	}
	else if (control_choice == 'N' || control_choice == 'n')
	{
		cout << "\nThe controls for this game are NORMAL! (w - Up, s - Down, a - Left, d - Right)" << endl;
		cout << "GOOD LUCK!" << endl << endl;
	}
	else
	{
		do
		{
			cout << "\nThat was the wrong input. Please try again. (Y-y for YES & N-n for NO):  ";
			cin >> control_choice;

			if (control_choice == 'Y' || control_choice == 'y')
			{
				cout << "\nDISCLAIMER: The controls for this game are now INVETRTED! (w - Down, s - Up, a - Right, d - Left)" << endl;
				cout << "GOOD LUCK!" << endl << endl;
			}
			else if (control_choice == 'N' || control_choice == 'n')
			{
				cout << "\nThe controls for this game are NORMAL! (w - Up, s - Down, a - Left, d - Right)" << endl;
				cout << "GOOD LUCK!" << endl << endl;
			}
		} 
		while (!(control_choice == 'Y' || control_choice == 'y' || control_choice == 'N' || control_choice == 'n'));
	}

	system("pause");
}

void setup() //establishes necessary game elements prior to the start of the game
{
	game_over = false;
	direc = Stop;

	//centering the snake head on the map
	x = width / 2;
	y = height / 2;

	//placing the fruit at a random position on the map
	srand(time(NULL)); //using time to make fruit position even more random
	fruit_x = rand() % width;
	fruit_y = rand() % height;

	score = 0;
}

void draw() //prints out the map of the game
{
	//calling windows command to clear the screen
	system("cls");

	//printing top wall of the map
	for (int i = 0; i < (width + 2)/2; i++)
	{
		SetConsoleTextAttribute(h, 9); //setting top wall to color bright blue
		cout << "\\/";
	}
	
	cout << endl;

	//printing the side walls of the map
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
			{
				SetConsoleTextAttribute(h, 11); //setting the left side wall to color bright cyan
				cout << ')';
			}
			if (i == y && j == x)
			{
				SetConsoleTextAttribute(h, 10); //setting snake head to color bright green
				cout << 'S';
				SetConsoleTextAttribute(h, 11); //setting right side wall parallel to the snake head to color bright cyan
			}
			else if (i == fruit_y && j == fruit_x)
			{
				SetConsoleTextAttribute(h, 12); //setting fruit to color bright red
				cout << 'F';
				SetConsoleTextAttribute(h, 11); //setting right side wall parallel to fruit to  color bright cyan
			}
			else
			{
				bool print = false;
				for (int k = 0; k < tail_length; k++)
				{
					if (tail_x[k] == j && tail_y[k] == i)
					{ 
						SetConsoleTextAttribute(h, 10); //setting tail to color bright green
						cout << "s";
						SetConsoleTextAttribute(h, 11); //setting right side wall parallel to tail to  color bright cyan

						print = true;
					}
				}
				if (!print)
				{
					cout << ' ';
				}
			}
			if (j == width - 1)
			{
				cout << '(';
			}
		}
		cout << endl;
	}

	//printing bottom wall of the map
	for (int i = 0; i < (width + 2)/2; i++)
	{
		SetConsoleTextAttribute(h, 9); //setting bottom wall to the color bright blue
		cout << "/\\";
	}
	
	cout << endl;
	SetConsoleTextAttribute(h, 15);
	cout << "\nScore: " << score << endl << endl; //setting score to color bright white
}

void input() //assigns the input keys for the movement of the snake
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
		{
			direc = Left;
			break;
		}
		case 'd':
		{
			direc = Right;
			break;
		}
		case 'w':
		{
			direc = Up;
			break;
		}
		case 's':
		{
			direc = Down;
			break;
		}
		case 'x':
		{
			game_over = true;
			break;
		}
		}
	}
}

void inverted_input() //assigns the input keys for the movement of the snake, but inverted
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
		{
			direc = Right;
			break;
		}
		case 'd':
		{
			direc = Left;
			break;
		}
		case 'w':
		{
			direc = Down;
			break;
		}
		case 's':
		{
			direc = Up;
			break;
		}
		case 'x':
		{
			game_over = true;
			break;
		}
		}
	}

}

void logic() //establishes the rules of the game
{
	int prev_x = tail_x[0]; //previous x-coordinate of the tail
	int prev_y = tail_y[0]; //previous y-coordinate of the tail
	int prev_2x, prev_2y;
	tail_x[0] = x;
	tail_y[0] = y;

	for (int i = 1; i < tail_length; i++)
	{
		prev_2x = tail_x[i];
		prev_2y = tail_y[i];
		tail_x[i] = prev_x;
		tail_y[i] = prev_y;
		prev_x = prev_2x;
		prev_y = prev_2y;
	}

	switch (direc)
	{
	case Left:
	{
		x--;
		break;
	}
	case Right:
	{
		x++;
		break;
	}
	case Up:
	{
		y--;
		break;
	}
	case Down:
	{
		y++;
		break;
	}
	default: 
	{
		break;
	}
	}

	//terminating the game if the snake head goes out of the bonds of the map
	/*if (x > width || x < 0 || y > height || y < 0)
	{
		game_over = true;
	}*/

	//if the snake goes through the wall it appears at the parallel wall going to the opposite direction
	if (x >= width)
	{
		x = 0;
	}
	else if (x < 0)
	{
		x = width - 1;
	}

	if (y >= height)
	{
		y = 0;
	}
	else if(y < 0)
	{
		y = height - 1;
	}

	//terminates the game if the snake head touches the tail
	for (int i = 0; i < tail_length; i++)
	{
		if (tail_x[i] == x && tail_y[i] == y)
		{
			game_over = true;
		}
	}
	if (x == fruit_x && y == fruit_y)
	{
		score += 10;
		fruit_x = rand() % width;
		fruit_y = rand() % height;
		tail_length++;
	}
}