#include <iostream>
#include <conio.h>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;

bool gameover;
const int width = 25;
const int height = 25;
pair<int, int> fruit;
int score;
vector<pair<int, int>> snake;
enum eDirection { LEFT, RIGHT, UP, DOWN };
bool started = false;
eDirection dir;

void Setup()
{
	gameover = false;
	started = false;

	dir = UP;

	snake.insert(snake.begin(), make_pair(width / 2, height / 2));
	fruit = make_pair(rand() % width, rand() % height);

	score = 0;
}

void Draw()
{
	system("cls");

	for (int i = 0; i < width + 2; i++)
		cout << "#";

	cout << endl;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			if (x == 0)
				cout << "#";

			if (x == snake[0].first && y == snake[0].second)
				cout << "O";

			else if (x == fruit.first && y == fruit.second)
				cout << "@";

			else
			{
				bool print = false;

				for (int k = 1; k < snake.size(); k++)
				{
					if (snake[k].first == x && snake[k].second == y) {
						cout << "o"; print = true;
					}
				}

				if (!print) cout << " ";

			}

			if (x == width - 1)
				cout << "#";
		}

		cout << endl;

	}

	for (int i = 0; i < width + 2; i++)
		cout << "#";

	cout << endl;

	cout << "Score:" << score << endl;
}

void Input()
{
	if (_kbhit())
	{
		if (!started)
			started = true;

		switch (_getch())
		{
		case 'w':dir = UP;      break;
		case 's':dir = DOWN;    break;
		case 'a':dir = LEFT;    break;
		case 'd':dir = RIGHT;   break;

		case 'x':
		case 'q':
			gameover = true;
			break;
		}
	}
}

void Step()
{
	if (!started)
		return;

	pair<int, int> prev = snake[0];
	pair<int, int> temp;
	for (int i = 1; i < snake.size(); i++)
	{
		temp = snake[i];
		snake[i] = prev;
		prev = temp;
	}

	switch (dir)
	{
	case LEFT:snake[0].first--;
		break;

	case RIGHT:snake[0].first++;
		break;

	case UP:snake[0].second--;
		break;

	case DOWN:snake[0].second++;
		break;
	}

	//teleport
	//if (snake.first >= width) 
	//  snake.first = 0; 
	//else if (snake.first < 0) 
	//  snake.first = width - 1;
	//if (snake.second >= height) 
	//  snake.second = 0; 
	//else if (snake.second < 0) 
	//  snake.second = height - 1;

	//die out of bounds
	//if (snake[0].first >= width || snake[0].first < 0
	//  || snake[0].second >= height || snake[0].second < 0)
	//  gameover = true;

	for (int i = 1; i < snake.size(); i++)
	{
		if (snake[i] == snake[0]) {
			cout << "Hit Yourself!! :(" << "\n";
			gameover = true;
		}
	}

	if (snake[0] == fruit)
	{
		score += 10;
		fruit = make_pair(rand() % width, rand() % height);
		snake.emplace_back(make_pair(0, 0));
	}
}

int main()
{
	Setup();

	while (!gameover)
	{
		Draw();
		Input();
		Step();

		this_thread::sleep_for(chrono::milliseconds(100));
	}

	cout << "Game Over !" << "\n";
	cout << "Score : " << score << "\n";

	return 0;
}
