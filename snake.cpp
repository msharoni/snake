#include<iostream>

#include<conio.h>
#include<ctime>
#include <windows.h>


using namespace std;

#define width 20
#define height 20


void resetmap(char** map, int** places, int &size)
{
	// border
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			map[i][j] = (i == 0 || j == 0 || i == 19 || j == 19 ? 'x' : ' ');

	//snake
	for (int i = 0; i < 5; i++)
		map[10][10 + i] = (i == 0 ? 'O' : 'o');
	for (int i = 0; i < 5; i++)
	{
		places[i][0] = 10;
		places[i][1] = 10 + i;
	}

	size = 5;
}


void printmap(char** map, int** places, int size)
{
	system("cls");

	//changing snake
	for (int i = 0; i < size; i++)
	{
		if (i > 0)
			map[places[i][0]][places[i][1]] = 'o';
	}
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
			cout << map[i][j];
		cout << endl;
	}
	cout << endl;
	cout << "Score: " << size - 5 << endl;
	/*if (size > 0) {
		cout << "you are a loser you have less then 20!!!" << endl;
	}
	else if (size >= 20) {
		cout << "you are ok!!!" << endl;
	}
	else if (size > 40) {
		cout << "you\"re so bored that you got up to this!!!" << endl;
	}*/
}

void printapple(char** map)
{
	int x = 0, y = 0;


	while (map[x][y] == 'x' || map[x][y] == 'o' || map[x][y] == 'O')
	{
		x = rand() % width;
		y = rand() % height;
	}

	map[x][y] = '+';
}


void snakeplace(int** places, char direction, int size, char** map)
{

	int** copyofplaces = new int*[304];
	for (int i = 0; i < 304; i++)
	{
		copyofplaces[i] = new int[2];
		copyofplaces[i][0] = places[i][0];
		copyofplaces[i][1] = places[i][1];
	}


	for (int i = 1; i < size; i++)
	{
		places[i][0] = copyofplaces[i - 1][0];
		places[i][1] = copyofplaces[i - 1][1];
	}
	if (direction == 'a' || direction == 'd')
		if (direction == 'a')
			places[0][1] = places[0][1] - 1;
		else
			places[0][1] = places[0][1] + 1;
	else if (direction == 'w' || direction == 's')
		if (direction == 's')
			places[0][0] = places[0][0] + 1;
		else
			places[0][0] = places[0][0] - 1;
	map[copyofplaces[size - 1][0]][copyofplaces[size - 1][1]] = ' ';
	for (int i = 0; i < 304; i++)
		delete[] copyofplaces[i];
	delete[] copyofplaces;
}


void changedirection(char** map, char &direction, int** places, int size)
{
	//checking where snake is
	int cordinatex = 0, cordinatey = 0;
	char directioncopy = direction;

	for (int i = 0; i < 19; i++)
		for (int j = 0; j < 20; j++)
			if (map[i][j] == 'O')
			{
				cordinatey = i;
				cordinatex = j;
			}

	if (_kbhit())
		direction = _getch();

	if (direction != 'w' && direction != 'a' && direction != 's' && direction != 'd')
		direction = directioncopy;

	// changing the saved place of the snake

	if ((directioncopy == 'w' && direction == 's') || (directioncopy == 'a' && direction == 'd') || (directioncopy == 's' && direction == 'w') || (directioncopy == 'd' && direction == 'a'))
		direction = directioncopy;
	snakeplace(places, direction, size, map);
	//end of changing the saved place of the snake
	switch (direction)
	{
	case 'w':
		map[cordinatey - 1][cordinatex] = map[cordinatey][cordinatex];
		map[cordinatey][cordinatex] = ' ';
		break;
	case 'a':
		map[cordinatey][cordinatex - 1] = map[cordinatey][cordinatex];
		map[cordinatey][cordinatex] = ' ';
		break;
	case 's':
		map[cordinatey + 1][cordinatex] = map[cordinatey][cordinatex];
		map[cordinatey][cordinatex] = ' ';
		break;
	case 'd':
		map[cordinatey][cordinatex + 1] = map[cordinatey][cordinatex];
		map[cordinatey][cordinatex] = ' ';
		break;
	}
}

bool endgame(char** map, int size, int** places)
{
	for (int i = 0; i < 20; i++)
		if (map[0][i] != 'x' || map[i][0] != 'x' || map[i][19] != 'x' || map[19][i] != 'x')
			return true;

	for (int i = 1; i < size; i++)
	{
		if (places[i][0] == places[0][0] && places[i][1] == places[0][1])
			return true;
	}
	return false;
}

void appleeaten(char** map, int** places, int &size)
{
	bool check = true;
	for (int i = 0; i < 20 && check == true; i++)
		for (int j = 0; j < 20; j++)
			if (map[i][j] == '+')
				check = false;
	if (check)
	{
		places[size][0] = places[size - 1][0];
		places[size][1] = places[size - 1][1] - 1;
		printapple(map);
		size++;
	}
}

int main()
{
	srand((unsigned)time(nullptr));
	char** map = new char*[20];
	int** places = new int*[304];
	for (int i = 0; i < 304; i++)
		places[i] = new int[2];

	for (int i = 0; i < 20; ++i)
		map[i] = new char[20];

	int size = 5, level;
	char done = '1';
	char start = 0, direction = 'a';


	while (done != '0')
	{
		if (done == '1')
		{
			resetmap(map, places, size);
			printapple(map);
			done = '2';
			cout << "what level would you like your snake game to be for easy press 1 for medium press 2 for hard press 3" << endl;
			cin >> level;
			cout << "press space start" << endl;
			while (start != ' ')
			{
				if (_kbhit())
					start = _getch();
			}
			printmap(map, places, size);
			if (level == 1)
				level = 300;
			else if (level == 2)
				level = 200;
			else
				level = 100;
		}
		Sleep(level);
		appleeaten(map, places, size);
		changedirection(map, direction, places, size);
		printmap(map, places, size);

		//end of game or not
		if (endgame(map, size, places))
		{
			cout << "GAME OVER" << endl;
			if (size<10)
				cout << "nice try you got " << size - 5 << "!!!!" << endl;
			else
				cout << "You are so good you got " << size-5 << "!!!!" << endl;
			Sleep(2500);
			system("cls");
			cout << "Would you like to play again?" << endl;
			cout << "1 for yes. 0 for no." << endl;
			
			while(done != '0' && done !='1')
				cin >> done;

		}
	}
	cout << " OK. Your Score was " << size-5 << "!!!" << endl;
	cout << "Thanks For Playing!!!  See You Next Time" << endl;

	Sleep(3500);

	for (int i = 0; i < 20; ++i)
		delete[] map[i];
	delete[] map;
	for (int i = 0; i < 304; i++)
		delete[] places[i];
	delete[] places;

	return 0;
}


