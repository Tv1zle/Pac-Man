#include <iostream> 
#include <windows.h> 
#include <conio.h> 
#include <vector>


int main()
{
	HANDLE h = GetStdHandle(-11);


	const int width = 50;
	const int height = 15;
	int count = 0, prev = 0, breaker = 2, usercount = 0, maze[height][width] = {};
	std::vector <int> PosX;
	std::vector <int> PosY;


	// заполнение массива
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			maze[y][x] = rand() % 4; // 0 1 2 3

			if (maze[y][x] == 1) // стены
			{
				int r = rand() % 2; // уменьшить количество стен в 2 раза
				if (r != 0)
				{
					maze[y][x] = 0;
				}
			}
			else if (maze[y][x] == 3) // враги
			{
				int r = rand() % 20;
				if (r != 0)
				{
					maze[y][x] = 0;
				}
				if (maze[y][x] == 3)
				{
					PosY.push_back(y);
					PosX.push_back(x);
				}
			}

			if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
			{
				maze[y][x] = 1;
			}
		}
	}


	// показ элементов массива
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (maze[y][x] == 0) // коридоры
			{
				SetConsoleTextAttribute(h, 0);
				std::cout << " ";
			}
			else if (maze[y][x] == 1) // стены
			{
				SetConsoleTextAttribute(h, 2);
				std::cout << (char)178;
			}
			else if (maze[y][x] == 2) // монетки
			{
				SetConsoleTextAttribute(h, 14);
				std::cout << ".";
				count++;
			}
			else if (maze[y][x] == 3) // враги
			{

				SetConsoleTextAttribute(h, 12);
				std::cout << (char)1;
			}
		}
		std::cout << "\n";
	}


	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = false;
	cursor.dwSize = 100;
	SetConsoleCursorInfo(h, &cursor);


	COORD smile;
	smile.X = 0; // поля структуры
	smile.Y = 2;
	SetConsoleCursorPosition(h, smile);
	SetConsoleTextAttribute(h, 9);
	std::cout << (char)1;


	COORD fragmove;
	fragmove.X = 0;
	fragmove.Y = 0;


	COORD breakwalls;
	breakwalls.X = 0;
	breakwalls.Y = 0;


	int coins = 0;
	int health = 100;


	// информация по всем показателям
	COORD infobox;
	infobox.X = width + 1;
	infobox.Y = 2;
	SetConsoleCursorPosition(h, infobox);
	SetConsoleTextAttribute(h, 6);
	std::cout << "For win: collect all the coins \n ";
	infobox.Y = 3;
	SetConsoleCursorPosition(h, infobox);
	std::cout << "To break walls, press 'E' \n";


	infobox.Y = 5;
	SetConsoleCursorPosition(h, infobox);
	std::cout << "You can break: ";
	SetConsoleTextAttribute(h, 9);
	std::cout << breaker << " walls \n";


	infobox.Y = 6;
	SetConsoleCursorPosition(h, infobox);
	SetConsoleTextAttribute(h, 6);
	std::cout << "COINS: ";
	SetConsoleTextAttribute(h, 14);
	std::cout << coins << " / " << count << " \n";


	infobox.Y = 7;
	SetConsoleCursorPosition(h, infobox);
	SetConsoleTextAttribute(h, 4);
	std::cout << "HEALTH: ";
	SetConsoleTextAttribute(h, 12);
	std::cout << health << "\n";


	// получаем код нажатой клавиши
	srand(time(0));
	while (true)
	{
		int code = _getch();
		if (code == 224)
		{
			code = _getch(); // если была нажата стрелка, то получаем второй код
		}


		SetConsoleCursorPosition(h, smile);
		SetConsoleTextAttribute(h, 0);
		std::cout << " ";


		prev = code;
		if (code == 77 && maze[smile.Y][smile.X + 1] != 1)
		{
			smile.X++;
		}
		else if (code == 80 && maze[smile.Y + 1][smile.X] != 1)
		{
			smile.Y++;
		}
		else if (code == 75 && maze[smile.Y][smile.X - 1] != 1)
		{
			smile.X--;
		}
		else if (code == 72 && maze[smile.Y - 1][smile.X] != 1)
		{
			smile.Y--;
		}
		///////////////////////////////////Не работает
		else if (code == 69 && breaker != 0)
		{
			if (prev == 77 && maze[smile.Y][smile.X + 1] == 1)
			{
				maze[smile.Y][smile.X + 1] = 4;
				breakwalls.X = smile.X + 1;
				breakwalls.Y = smile.Y;
				SetConsoleCursorPosition(h, breakwalls);
				SetConsoleTextAttribute(h, 0);
				std::cout << " ";
				breaker--;
			}
			else if (prev == 80 && maze[smile.Y + 1][smile.X] == 1)
			{
				maze[smile.Y + 1][smile.X] = 4;
				breakwalls.X = smile.X;
				breakwalls.Y = smile.Y + 1;
				SetConsoleCursorPosition(h, breakwalls);
				SetConsoleTextAttribute(h, 0);
				std::cout << " ";
				breaker--;
			}
			else if (prev == 75 && maze[smile.Y][smile.X - 1] == 1)
			{
				maze[smile.Y][smile.X - 1] = 4;
				breakwalls.X = smile.X - 1;
				breakwalls.Y = smile.Y;
				SetConsoleCursorPosition(h, breakwalls);
				SetConsoleTextAttribute(h, 0);
				std::cout << " ";
				breaker--;
			}
			else if (prev == 72 && maze[smile.Y - 1][smile.X] == 1)
			{
				maze[smile.Y - 1][smile.X] = 4;
				breakwalls.X = smile.X;
				breakwalls.Y = smile.Y - 1;
				SetConsoleCursorPosition(h, breakwalls);
				SetConsoleTextAttribute(h, 0);
				std::cout << " ";
				breaker--;
			}
			SetConsoleCursorPosition(h, smile);
		}


		//////////////////////////////////////////Не доработал
		int frag = rand() % 8;
		fragmove.Y = PosY[frag];
		fragmove.X = PosX[frag];
		SetConsoleCursorPosition(h, fragmove);
		SetConsoleTextAttribute(h, 0);
		std::cout << " ";
		if (fragmove.X - 1 != 1)
		{
			fragmove.X--;
			SetConsoleCursorPosition(h, fragmove);
			SetConsoleTextAttribute(h, 12);
			std::cout << (char)1;
		}


		if (maze[smile.Y][smile.X] == 3)
		{
			health -= 20;
			infobox.X = width + 1;
			infobox.Y = 7;
			SetConsoleCursorPosition(h, infobox);
			SetConsoleTextAttribute(h, 4);
			std::cout << "HEALTH: ";
			SetConsoleTextAttribute(h, 12);
			std::cout << health << " \n";
			maze[smile.Y][smile.X] = 4;


			if (health <= 0)
			{
				int answer = MessageBoxA(0, "health is over!\n\nwant to play again?", "FAIL!", MB_YESNO);
				system("cls");
				if (answer == IDYES)
				{
					main();
				}
				else
				{
					exit(0);
				}
			}
		}
		else if (maze[smile.Y][smile.X] == 2)
		{
			coins++;
			infobox.X = width + 1;
			infobox.Y = 6;
			SetConsoleCursorPosition(h, infobox);
			SetConsoleTextAttribute(h, 6);
			std::cout << "COINS: ";
			SetConsoleTextAttribute(h, 14);
			std::cout << coins << " / " << count << " \n";
			maze[smile.Y][smile.X] = 4;


			if (coins == count)
			{
				int answer = MessageBoxA(0, "You win!\n\nwant to play again?", "COMPLETE!", MB_YESNO);
				system("cls");
				if (answer == IDYES)
				{
					main();
				}
				else
				{
					exit(0);
				}
			}
		}


		SetConsoleCursorPosition(h, smile);
		SetConsoleTextAttribute(h, 9);
		std::cout << (char)1;
	}


	Sleep(INFINITE);


}