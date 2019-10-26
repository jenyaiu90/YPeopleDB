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
using namespace std;
ushort entries()
{
	ushort ret;
	ret = 1;
	while (true)
	{
		static ifstream file;
		static ifstream version_check;
		file.open("files\\" + to_string(ret) + "\\name.dat");
		if (!file.is_open())
		{
			return ret - 1;
		}
		file.close();
		ret++;
	}
}
int main()
{
	//setlocale(LC_ALL, "Russian");
	system("chcp 1251");
	system("cls");
	//display_logo();
	entries();
	while (true)
	{
		ushort in;
		cout << "v.2.0" << endl << endl <<
			"1. ������� ������." << endl <<
			"2. �������� ������." << endl <<
			"3. ����������� ������" << endl <<
			"4. �������� ������." << endl <<
			"5. �����." << endl <<
			"6. ������ �����." << endl <<
			"7. ������� ������ ���� ������� �����." << endl <<
			"0. �����." << endl <<
			"\t";
		cin >> in;
		switch (in)
		{
		case 0:
			return 0;
		case 1:
		{
			short page = 0;
			while (page > -1)
			{
				system("cls");
				page = Entry::displayList(page);
			}
			system("cls");
			break;
		}
		case 2:
		{
			system("cls");
			Entry entry(entries() + 1);
			entry.set();
			_getch();
			system("cls");
			break;
		}
		case 3:
		{
			cout << "������� 0 ��� ������.\nID: ";
			cin >> in;
			system("cls");
			if (in == 0)
			{
				string buff, b;
				cout << "������: ";
				cin >> b;
				getline(cin, buff);
				buff = b + buff;
				system("cls");
				Entry::search(false, true, buff);
				cout << endl << "����������� ID: ";
				cin >> in;
			}
			while (in != 0)
			{
				Entry entry(in);
				if (!entry.load())
				{
					system("cls");
					cout << "����� ������ �� ����������." << endl << endl;
				}
				else
				{
					in = entry.display();
					system("cls");
				}
			}
			break;
			_getch();
		}
		case 4:
		{
			cout << "������� 0 ��� ������.\nID: ";
			cin >> in;
			system("cls");
			if (in == 0)
			{
				string buff, b;
				cout << "������: ";
				cin >> b;
				getline(cin, buff);
				buff = b + buff;
				system("cls");
				Entry::search(false, true, buff);
				cout << endl << "������������� ID: ";
				cin >> in;
			}
			Entry entry(in);
			if (!entry.load())
			{
				system("cls");
				cout << "����� ������ �� ����������." << endl << endl;
			}
			else
			{
				entry.edit();
				_getch();
				system("cls");
			}
			break;
		}
		case 5:
		case 6:
		{
			string buff, b;
			cout << "������: ";
			cin >> b;
			getline(cin, buff);
			buff = b + buff;
			system("cls");
			Entry::search(in == 6, true, buff);
			system("cls");
			break;
		}
		case 7:
		{
			cout << "���� �";
			cin >> in;
			system("cls");
			Entry::displaySheetList(in);
			system("cls");
			break;
		}
		default:
		{
			system("cls");
			cout << "������." << endl << endl;
		}
		}
	}
}