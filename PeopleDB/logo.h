/*//////////////////////////////////////
//       YPeopleDB by SnegirSoft      //
//  Authors:                          //
//      jenyaiu90 aka sqrt(-1)        //
//                                    //
//  File: logo.h                      //
//////////////////////////////////////*/
#include <iostream>
#include <Windows.h>
#define SCTA SetConsoleTextAttribute
using namespace std;
//Перечисление возможных цветов на консоли
enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};
//Отображение логотипа при запуске программы
void display_logo()
{
	setlocale(LC_ALL, "Russian");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//First line
	SCTA(hConsole, (WORD)((Black << 4) | LightBlue));
	cout << endl << endl << endl << "\t\t     /";
	SCTA(hConsole, (WORD)((Black << 4) | LightRed));
	cout << "----\\" << endl;
	Sleep(500);

	//Second line
	SCTA(hConsole, (WORD)((Black << 4) | LightBlue));
	cout << "\t\t     \\";
	SCTA(hConsole, (WORD)((Black << 4) | LightRed));
	cout << "\\";
	SCTA(hConsole, (WORD)((Black << 4) | LightGreen));
	cout << "---/" << endl;
	Sleep(500);

	//Third line
	SCTA(hConsole, (WORD)((Black << 4) | LightBlue));
	cout << "\t\t      \\";
	SCTA(hConsole, (WORD)((Black << 4) | LightRed));
	cout << "\\";
	SCTA(hConsole, (WORD)((Black << 4) | LightBlue));
	cout << "/";
	SCTA(hConsole, (WORD)((Black << 4) | LightGreen));
	cout << "/" << endl;
	Sleep(500);

	//Forth line
	SCTA(hConsole, (WORD)((Black << 4) | LightBlue));
	cout << "\t\t       /";
	SCTA(hConsole, (WORD)((Black << 4) | LightGreen));
	cout << "/" << endl;
	Sleep(500);

	//Fifth line
	SCTA(hConsole, (WORD)((Black << 4) | LightBlue));
	cout << "\t\t      /";
	SCTA(hConsole, (WORD)((Black << 4) | LightGreen));
	cout << "/";
	SCTA(hConsole, (WORD)((Black << 4) | LightBlue));
	cout << "\\";
	SCTA(hConsole, (WORD)((Black << 4) | LightRed));
	cout << "\\" << endl;
	Sleep(500);

	//Sixth line
	SCTA(hConsole, (WORD)((Black << 4) | LightBlue));
	cout << "\t\t/";
	SCTA(hConsole, (WORD)((Black << 4) | LightRed));
	cout << "--------";
	SCTA(hConsole, (WORD)((Black << 4) | LightBlue));
	cout << "\\";
	SCTA(hConsole, (WORD)((Black << 4) | LightRed));
	cout << "\\----\\" << endl;
	Sleep(500);

	//Seventh line
	SCTA(hConsole, (WORD)((Black << 4) | LightBlue));
	cout << "\t\t\\";
	SCTA(hConsole, (WORD)((Black << 4) | LightRed));
	cout << "\\";
	SCTA(hConsole, (WORD)((Black << 4) | LightGreen));
	cout << "--------";
	SCTA(hConsole, (WORD)((Black << 4) | LightBlue));
	cout << "\\";
	SCTA(hConsole, (WORD)((Black << 4) | LightRed));
	cout << "\\";
	SCTA(hConsole, (WORD)((Black << 4) | LightGreen));
	cout << "---/" << endl;
	Sleep(500);

	//Eighth line
	SCTA(hConsole, (WORD)((Black << 4) | LightBlue));
	cout << "\t\t \\";
	SCTA(hConsole, (WORD)((Black << 4) | LightRed));
	cout << "\\";
	SCTA(hConsole, (WORD)((Black << 4) | LightBlue));
	cout << "/";
	SCTA(hConsole, (WORD)((Black << 4) | LightGreen));
	cout << "/";
	SCTA(hConsole, (WORD)((Black << 4) | LightBlue));
	cout << "      \\";
	SCTA(hConsole, (WORD)((Black << 4) | LightRed));
	cout << "\\";
	SCTA(hConsole, (WORD)((Black << 4) | LightBlue));
	cout << "/";
	SCTA(hConsole, (WORD)((Black << 4) | LightGreen));
	cout << "/" << endl;
	Sleep(500);

	//Ninth line
	SCTA(hConsole, (WORD)((Black << 4) | LightBlue));
	cout << "\t\t  \\";
	SCTA(hConsole, (WORD)((Black << 4) | LightGreen));
	cout << "-";
	SCTA(hConsole, (WORD)((Black << 4) | LightBlue));
	cout << "        \\";
	SCTA(hConsole, (WORD)((Black << 4) | LightGreen));
	cout << "-" << endl << endl << "\t\t";
	Sleep(1000);

	SCTA(hConsole, (WORD)((Red << 4) | LightGreen));
	cout << "YPeopleDB by SnegirSoft.";
	SCTA(hConsole, (WORD)((Black << 4) | White));
	Sleep(5000);
	system("cls");
}