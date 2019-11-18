/*//////////////////////////////////////
//       YPeopleDB by SnegirSoft      //
//  Authors:                          //
//      jenyaiu90 aka sqrt(-1)        //
//                                    //
//  File: main.cpp                    //
//////////////////////////////////////*/
#include "Entry.h"
#include "logo.h"
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <direct.h>
using namespace std;
ushort entries()
{
	ifstream file("files\\dbn.ypdb");
	if (!file.is_open())
	{
		_mkdir("files\\");
		ofstream file("files\\dbn.ypdb");
		file << "0" << endl;
		file.close();
		file.open("files\\db0.ypdb");
		file.close();
		return 0;
	}
	string buff;
	file >> buff;
	file.close();
	return stoi(buff);
}
int main()
{
	//setlocale(LC_ALL, "Russian");
	system("chcp 1251");
	system("cls");
	display_logo();
	while (true)
	{
		ushort in;
		cout << "v.2.0" << endl << endl <<
			"1. Вывести список." << endl <<
			"2. Добавить запись." << endl <<
			"3. Просмотреть запись" << endl <<
			"4. Изменить запись." << endl <<
			"5. Поиск." << endl <<
			"6. Точный поиск." << endl <<
			"7. Вывести список всех записей листа." << endl <<
			"0. Выход." << endl <<
			"\t";
		cin >> in;
		switch (in)
		{
		case 0:
			return 0;
		case 1:
		{
			if (entries() == 0)
			{
				system("cls");
				cout << "Записи отсутствуют." << endl << endl;
				break;
			}
			short page = 0;
			while (page > -1)
			{
				system("cls");
				page = Entry::displayList(entries(), page);
			}
			system("cls");
			break;
		}
		case 2:
		{
			system("cls");
			Entry entry(entries() + 1);
			entry.set(entries());
			_getch();
			system("cls");
			break;
		}
		case 3:
		{
			if (entries() == 0)
			{
				system("cls");
				cout << "Записи отсутствуют." << endl << endl;
				break;
			}
			cout << "Введите 0 для поиска.\nID: ";
			cin >> in;
			system("cls");
			if (in == 0)
			{
				string buff, b;
				cout << "Запрос: ";
				cin >> b;
				getline(cin, buff);
				buff = b + buff;
				system("cls");
				Entry::search(entries(), false, true, buff);
				cout << endl << "Просмотреть ID: ";
				cin >> in;
			}
			while (in != 0)
			{
				Entry entry(in);
				if (!entry.load(entries()))
				{
					system("cls");
					cout << "Такой записи не существует." << endl << endl;
				}
				else
				{
					in = entry.display(entries());
					system("cls");
				}
			}
			break;
			_getch();
		}
		case 4:
		{
			if (entries() == 0)
			{
				system("cls");
				cout << "Записи отсутствуют." << endl << endl;
				break;
			}
			cout << "Введите 0 для поиска.\nID: ";
			cin >> in;
			system("cls");
			if (in == 0)
			{
				string buff, b;
				cout << "Запрос: ";
				cin >> b;
				getline(cin, buff);
				buff = b + buff;
				system("cls");
				Entry::search(entries(), false, true, buff);
				cout << endl << "Редактировать ID: ";
				cin >> in;
			}
			Entry entry(in);
			if (!entry.load(entries()))
			{
				system("cls");
				cout << "Такой записи не существует." << endl << endl;
			}
			else
			{
				entry.edit(entries());
				_getch();
				system("cls");
			}
			break;
		}
		case 5:
		case 6:
		{
			if (entries() == 0)
			{
				system("cls");
				cout << "Записи отсутствуют." << endl << endl;
				break;
			}
			string buff, b;
			cout << "Запрос: ";
			cin >> b;
			getline(cin, buff);
			buff = b + buff;
			system("cls");
			Entry::search(entries(), in == 6, true, buff);
			system("cls");
			break;
		}
		case 7:
		{
			if (entries() == 0)
			{
				system("cls");
				cout << "Записи отсутствуют." << endl << endl;
				break;
			}
			cout << "Лист №";
			cin >> in;
			system("cls");
			Entry::displaySheetList(entries(), in);
			system("cls");
			break;
		}
		default:
		{
			system("cls");
			cout << "Ошибка." << endl << endl;
		}
		}
	}
}