/*//////////////////////////////////////
//       YPeopleDB by SnegirSoft      //
//  Authors:                          //
//      jenyaiu90 aka sqrt(-1)        //
//                                    //
//  File: Entry.cpp                   //
//////////////////////////////////////*/
#include <string>
#include <iostream>
#include <direct.h>
#include <Windows.h>
#include "Entry.h"
#define SCTA SetConsoleTextAttribute
using namespace std;
enum Color
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
void setColor(const Color bg_color, const Color text_color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SCTA(hConsole, (WORD)((bg_color << 4) | text_color));
}
void resetColor()
{
	setColor(Black, White);
}
void line(const string text, const int num=-999999)
{
	setColor(Blue, LightBlue);
	for (ushort i = 0; i < 80; i++)
	{
		cout << "=";
	}
	resetColor();
	cout << "\t\t\t";
	setColor(Blue, LightGreen);
	cout << text;
	if (num != -999999)
	{
		cout << num;
	}
	cout << endl << endl;
	resetColor();
}
Entry::Entry(const ushort &Id)
{
	id = Id;
	children = NULL;
	sheets = NULL;
}
Entry::~Entry()
{
	/*ushortList *spointer = children;
	for (ushortList *pointer = children->next; pointer != NULL; spointer = pointer, pointer = pointer->next)
	{
		delete spointer;
	}
	delete spointer;*/
	delete children;
	/*spointer = sheets;
	for (ushortList *pointer = sheets->next; pointer != NULL; spointer = pointer, pointer = pointer->next)
	{
		delete spointer;
	}
	delete spointer;*/
	delete sheets;
}
void Entry::set(const short &entries)
{
	line("���������");
	setName(entries);
	setGender();
	setBirth();
	setDeath();
	setParents(entries);
	setSheets();
	if (father)
	{
		Entry tmp(father);
		tmp.load(entries);
		generation = tmp.generation + 1;
	}
	else
	{
		if (mather)
		{
			Entry tmp(mather);
			tmp.load(entries);
			generation = tmp.generation + 1;
		}
		else
		setGeneration();
	}
	save();
	int count;
	ifstream ifile("files\\dbn.ypdb");
	ifile >> count;
	ifile.close();
	ofstream ofile("files\\dbn.ypdb");
	ofile << ++count;
	cout << "���������� ���������.";
}
void Entry::setName(const short &entries)
{
	bool success;
	do
	{
		success = true;
		cout << "���: ";
		string tmp;
		cin >> tmp;
		getline(cin, name);
		name = tmp + name;
		if (name.length() > 53)
		{
			setColor(Red, LightRed);
			cout << "��� �� ������ ���� ������� 53 ��������." << endl;
			resetColor();
			success = false;
		}
		if (search(entries, true, false, name, false))
		{
			setColor(Yellow, LightRed);
			cout << "��������������: ����� ��� ��� ��������:" << endl << endl;
			resetColor();
			search(entries, true, true, name, false);
			bool in;
			cout << endl << "����������� ���? ";
			cin >> in;
			if (success && !in)
			{
				success = false;
			}
		}
	} while (!success);
}
void Entry::setGender()
{
	bool success;
	do
	{
		success = true;
		char buff;
		cout << "���: ";
		cin >> buff;
		switch (buff)
		{
		case '�':
		case '�':
		case 'F':
		case 'f':
		{
			gender = false;
			break;
		}
		case '�':
		case '�':
		case 'M':
		case 'm':
		{
			gender = true;
			break;
		}
		default:
		{
			setColor(Red, LightRed);
			cout << "������� M ��� F.\n";
			resetColor();
			success = false;
		}
		}
	} while (!success);
}
void Entry::setBirth()
{
	bool success;
	string buff;
	do
	{
		success = true;
		cout << "��� ��������: ";
		cin >> buff;
		if (buff == "?")
		{
			birthStatus = Un;
			break;
		}
		if (buff.length() > 5 || buff.length() < 3)
		{
			success = false;
			continue;
		}
		switch (buff[0])
		{
		case '�':
		{
			birthStatus = Around;
			buff[0] = '0';
			break;
		}
		case '>':
		{
			birthStatus = After;
			buff[0] = '0';
			break;
		}
		case '<':
		{
			birthStatus = Before;
			buff[0] = '0';
			break;
		}
		default:
		{
			birthStatus = Norm;
		}
		}
		for (short i = 0; i < buff.length(); i++)
		{
			if (buff[i] != '0' && buff[i] != '1' &&
				buff[i] != '2' && buff[i] != '3' &&
				buff[i] != '4' && buff[i] != '5' &&
				buff[i] != '6' && buff[i] != '7' &&
				buff[i] != '8' && buff[i] != '9')
			{
				success = false;
				break;
			}
		}
	} while (!success);
	if (birthStatus != Un)
	{
		birth = stoi(buff);
	}
}
void Entry::setDeath()
{
	bool success;
	string buff;
	do
	{
		success = true;
		cout << "��� ������: ";
		cin >> buff;
		if (buff == "?")
		{
			deathStatus = Un;
			break;
		}
		if (buff.length() > 5 || buff.length() < 3)
		{
			success = false;
			continue;
		}
		switch (buff[0])
		{
		case '�':
		{
			deathStatus = Around;
			buff[0] = '0';
			break;
		}
		case '>':
		{
			deathStatus = After;
			buff[0] = '0';
			break;
		}
		case '<':
		{
			deathStatus = Before;
			buff[0] = '0';
			break;
		}
		default:
		{
			deathStatus = Norm;
		}
		}
		for (short i = 0; i < buff.length(); i++)
		{
			if (buff[i] != '0' && buff[i] != '1' &&
				buff[i] != '2' && buff[i] != '3' &&
				buff[i] != '4' && buff[i] != '5' &&
				buff[i] != '6' && buff[i] != '7' &&
				buff[i] != '8' && buff[i] != '9')
			{
				success = false;
				break;
			}
		}
		if (success)
		{
			if (stoi(buff) < birth)
			{
				success = false;
				setColor(Red, LightRed);
				cout << "��� ������ �� ����� ���� ������ ���� ��������!" << endl;
				resetColor();
			}
		}
	} while (!success);
	if (deathStatus != Un)
	{
		death = stoi(buff);
	}
}
void Entry::setParents(const short &entries)
{
	bool success;
	cout << endl << "���� �������� ����������, ������� 0." << endl <<
		"����� ������� ������ ���� �����, ������� -1." << endl <<
		"����� ������ ����� �����, ������� -2." << endl << endl;
	int in;
	bool is_mather = false;
	for (short i = 0; i < 2; i++, is_mather = true)
	{
		do
		{
			success = true;
			setColor(is_mather ? LightMagenta : LightBlue, Black);
			cout << (is_mather ? "ID ������: " : "ID ����: ");
			cin >> in;
			resetColor();
			switch (in)
			{
			case 0:
			{
				(is_mather ? mather = 0 : father) = 0;
				break;
			}
			case -1:
			{
				success = false;
				cout << endl;
				displayList(entries);
				cout << endl;
				break;
			}
			case -2:
			{
				cout << "������: ";
				string buff;
				getline(cin, buff);
				getline(cin, buff);
				cout << endl;
				search(entries, false, true, buff);
				cout << endl;
				success = false;
				break;
			}
			default:
			{
				setColor(Red, LightRed);
				if (in < 0)
				{
					cout << "ID �� ����� ���� �������������." << endl;
					success = false;
					break;
				}
				Entry entry(in);
				if (in > entries)
				{
					cout << "�������� � ����� ID �� ����������." << endl;
					success = false;
					break;
				}
				entry.load(entries);
				if (entry.getGender() == is_mather)
				{
					cout << (is_mather ? "���� ������ ���� �������� ����." : "���� ������ ���� �������� ����.") << endl;
					success = false;
					break;
				}
				resetColor();
				is_mather ? (mather = in) : (father = in);
				entry.addChild(id);
				entry.save();
				cout << "���: " << entry.name << endl << endl;
			}
			}
		} while (!success);
	}
}
void Entry::setSheets()
{
	cout << "���� �";
	delete sheets;
	sheets = new ushortList;
	cin >> sheets->id;
	sheets->next = NULL;
	while (true)
	{
		static ushortList *pointer = sheets;
		ushort in;
		cout << "��� ������ ������� 0. ���� �";
		cin >> in;
		if (in == 0)
		{
			break;
		}
		pointer->next = new ushortList;
		pointer = pointer->next;
		pointer->next = NULL;
		pointer->id = in;
	}
}
void Entry::setGeneration()
{
	cout << "��������� �";
	short tmp;
	cin >> generation;
	//sg(tmp);
}
void Entry::displayYear(const bool &is_death)
{
	setColor(is_death ? LightGray : LightGreen, Black);
	switch (is_death ? deathStatus : birthStatus)
	{
	case Norm:
	{
		break;
	}
	case Un:
	{
		cout << "?" << endl;
		break;
	}
	case Around:
	{
		cout << "��. ";
		break;
	}
	case Before:
	{
		cout << "�� ";
		break;
	}
	case After:
	{
		cout << "����� ";
		break;
	}
	}
	if ((is_death ? deathStatus : birthStatus) != Un)
	{
		cout << (is_death ? death : birth) << endl;
	}
	resetColor();
}
void Entry::displayParents(const short &entries)
{
	displayListHeader();
	if (father == 0)
	{
		setColor(Yellow, Blue);
		cout << "?   ";
		setColor(Red, LightGreen);
		cout << "���� ����������. . . . . . . . . . . . . . .";
		setColor(LightBlue, White);
		cout << "�";
		setColor(Green, LightGreen);
		cout << "     ";
		setColor(DarkGray, LightGray);
		cout << "     ";
		setColor(Blue, Yellow);
		cout << "   ";
		setColor(Magenta, Yellow);
		cout << "   ";
		setColor(LightGray, Blue);
		cout << "   " << endl;
		resetColor();
	}
	else
	{
		Entry entry(father);
		entry.load(entries);
		entry.displayInList();
	}
	if (mather == 0)
	{
		setColor(Yellow, Blue);
		cout << "?   ";
		setColor(Red, LightGreen);
		cout << "���� ����������. . . . . . . . . . . . . . .";
		setColor(LightMagenta, White);
		cout << "�";
		setColor(Green, LightGreen);
		cout << "     ";
		setColor(DarkGray, LightGray);
		cout << "     ";
		setColor(Blue, Yellow);
		cout << "   ";
		setColor(Magenta, Yellow);
		cout << "   ";
		setColor(LightGray, Blue);
		cout << "   " << endl;
		resetColor();
	}
	else
	{
		Entry entry(mather);
		entry.load(entries);
		entry.displayInList();
	}
}
void Entry::displaySheets()
{
	for (ushortList *pointer = sheets; pointer != NULL; pointer = pointer->next)
	{
		cout << " " << pointer->id;
	}
}
bool Entry::getGender()
{
	return gender;
}
ushort Entry::display(const short &entries)
{
	line("��������");
	setColor(Yellow, Blue);
	cout << "ID: " << id << endl;
	setColor(Red, LightGreen);
	cout << "���: " << name << endl;
	setColor(gender ? LightBlue : LightMagenta, White);
	cout << "���: " << (gender ? "�������" : "�������") << endl;
	resetColor();
	cout << "��� ��������: ";
	displayYear(false);
	cout << "��� ������:   ";
	displayYear(true);
	cout << endl << "��������:" << endl;
	displayParents(entries);
	cout << endl << endl << "����:" << endl;
	displayListHeader();
	for (ushortList *pointer = children; pointer != NULL; pointer = pointer->next)
	{
		if (pointer->id == 0)
		{
			break;
		}
		Entry entry(pointer->id);
		entry.load(entries);
		entry.displayInList();
	}
	cout << endl << endl << "�������:" << endl;
	displayListHeader();
	ushortList *was = new ushortList;
	was->id = 0;
	was->next = NULL;
	for (ushortList *pointer = children; pointer != NULL; pointer = pointer->next)
	{
		if (pointer->id == 0)
		{
			break;
		}
		Entry entry(pointer->id);
		entry.load(entries);
		ushort buff = entry.getParent(!gender);
		if (buff != 0)
		{
			bool check = false;
			for (ushortList *pwas = was; pwas != NULL; pwas = pwas->next)
			{
				if (buff == pwas->id)
				{
					check = true;
					break;
				}
			}
			if (!check)
			{
				entry.load(entries, buff);
				entry.displayInList();
				ushortList *tmp = new ushortList;
				tmp->id = buff;
				tmp->next = was;
				was = tmp;
			}
		}
	}
	cout << endl << endl << "�����:";
	displaySheets();
	cout << endl << endl << "��������� " << generation << ".";
	cout << endl << endl << "��� ������ ������� 0." << endl << "������� � ID: ";
	ushort ret;
	cin >> ret;
	return ret;
	return 0;
}
short Entry::displayList(const short &entries, const short page)
{
	line("������ �������. �������� ", page + 1);
	displayListHeader();
	Entry entry(1);
	short i;
	for (i = page * 150 + 1; i <= entries && i <= (page + 1) * 150; i++)
	{
		entry.load(entries, i);
		entry.displayInList();
	}
	cout << endl << "0 � ����� " << endl << (page ? "-2 � ���������� ��������" : "\0") << endl << (i <= entries ? "-1 � ��������� ��������" : "\0") << endl << "������� � ID: ";
	short ID;
	cin >> ID;
	while (ID > 0)
	{
		Entry entry(ID);
		entry.load(entries);
		ID = entry.display(entries);
	}
	switch (ID)
	{
	case 0:
		return -1;
	case -1:
		return page + 1;
	case -2:
		return page - 1;
	}
	return 0;
}
void Entry::displaySheetList(const short &entries, const ushort &sheet)
{
	line("������ ������� � ����� �" + sheet);
	displayListHeader();
	Entry entry(1);
	for (short i = 1; i <= entries; i++)
	{
		entry.load(entries, i);
		bool match = false;
		for (ushortList *pointer = entry.getSheets(); pointer != NULL; pointer = pointer->next)
		{
			if (sheet == pointer->id)
			{
				match = true;
				break;
			}
		}
		if (match)
		{
			entry.displayInList();
		}
	}
	cout << endl << "������� 0 ��� ������" << endl << "������� � ID: ";
	ushort ID;
	cin >> ID;
	while (ID != 0)
	{
		Entry entry(ID);
		entry.load(entries);
		ID = entry.display(entries);
	}
}
void Entry::displayInList()
{
	setColor(Yellow, Blue);
	cout << id;
	ushort i = 0;
	if (id < 1000) i++;
	if (id < 100) i++;
	if (id < 10) i++;
	for (; i > 0; i--)
	{
		cout << " ";
	}
	setColor(Red, LightGreen);
	cout << name;
	if (name.length() % 2)
	{
		cout << ".";
	}
	for (i = 0; i < (44 - name.length()) / 2; i++)
	{
		cout << " .";
	}
	setColor(gender ? LightBlue : LightMagenta, White);
	cout << (gender ? "�" : "�");
	for (i = 0; i < 2; i++)
	{
		setColor(i ? DarkGray : Green, i ? LightGray : LightGreen);
		switch (i ? deathStatus : birthStatus)
		{
		case Norm:
		{
			cout << " " << (i ? death : birth);
			if ((i ? death : birth) < 1000) cout << " ";
			break;
		}
		case Un:
		{
			cout << " ?   ";
			break;
		}
		case Around:
		{
			cout << "~" << (i ? death : birth);
			if ((i ? death : birth) < 1000) cout << " ";
			break;
		}
		case Before:
		{
			cout << "<" << (i ? death : birth);
			if ((i ? death : birth) < 1000) cout << " ";
			break;
		}
		case After:
		{
			cout << ">" << birth;
			if ((i ? death : birth) < 1000) cout << " ";
			break;
		}
		}
	}
	for (i = 0; i < 2; i++)
	{
		setColor(i ? Magenta : Blue, Yellow);
		if ((i ? mather : father) == 0)
		{
			cout << "?  ";
			continue;
		}
		cout << (i ? mather : father);
		ushort j = 0;
		if ((i ? mather : father) < 100) j++;
		if ((i ? mather : father) < 10) j++;
		for (; j > 0; j--)
		{
			cout << " ";
		}
	}
	setColor(LightGray, Blue);
	cout << generation;
	int c = 0;
	if (abs(generation) < 100) c++;
	if (abs(generation) < 10) c++;
	if (generation < 0) c--;
	for (int j = 0; j < c; j++)
	{
		cout << " ";
	}
	cout << endl;
	resetColor();
}
/*void Entry::sg(short Generation)
{
	generation = Generation;
	save();
	for (ushortList *pointer = children; pointer != NULL; pointer = pointer->next)
	{
		ifstream file("files\\" + to_string(pointer->id) + "\\generation.dat");
		if (!file.is_open())
		{
			Entry child(pointer->id);
			child.load(pointer->id, false);
			child.sg(Generation + 1);
		}
		file.close();
	}
}*/
void Entry::save()
{
	writeFile(id, "name", name);
	writeFile(id, "gender", gender ? "1" : "0");
	writeFile(id, "birthStatus", to_string(birthStatus));
	writeFile(id, "deathStatus", to_string(deathStatus));
	writeFile(id, "father", to_string(father));
	writeFile(id, "mather", to_string(mather));
	writeFile(id, "generation", to_string(generation));
	if (birthStatus != Un)
	{
		writeFile(id, "birth", to_string(birth));
	}
	if (deathStatus != Un)
	{
		writeFile(id, "death", to_string(death));
	}
	if (children == NULL)
	{
		writeFile(id, "children", "0");
	}
	else
	{
		ushortList *p;
		string buff = to_string(children->id);
		for (p = children->next; p != NULL; p = p->next)
		{
			buff += "," + to_string(p->id);
		}
		writeFile(id, "children", buff);
	}

	if (sheets == NULL)
	{
		writeFile(id, "sheets", "0");
	}
	else
	{
		ushortList *p;
		string buff = to_string(sheets->id);
		for (p = sheets->next; p != NULL; p = p->next)
		{
			buff += "," + to_string(p->id);
		}
		writeFile(id, "sheets", buff);
	}
}
bool Entry::load(const short &entries)
{
	return load(entries, id);
}
bool Entry::load(const short &entries, const ushort &Id)
{
	if (entries < id || id <= 0)
	{
		return false;
	}
	id = Id;
	name = readFile(Id, "name");
	gender = readFile(Id, "gender") != "0";
	ushort buff = stoi(readFile(Id, "birthStatus"));
	switch (buff)
	{
	case 0:
	{
		birthStatus = Norm;
		break;
	}
	case 1:
	{
		birthStatus = Un;
		break;
	}
	case 2:
	{
		birthStatus = Around;
		break;
	}
	case 3:
	{
		birthStatus = Before;
		break;
	}
	case 4:
	{
		birthStatus = After;
		break;
	}
	}
	buff = stoi(readFile(Id, "deathStatus"));
	switch (buff)
	{
	case 0:
	{
		deathStatus = Norm;
		break;
	}
	case 1:
	{
		deathStatus = Un;
		break;
	}
	case 2:
	{
		deathStatus = Around;
		break;
	}
	case 3:
	{
		deathStatus = Before;
		break;
	}
	case 4:
	{
		deathStatus = After;
		break;
	}
	}
	if (birthStatus != Un)
	{
		birth = stoi(readFile(Id, "birth"));
	}
	if (deathStatus != Un)
	{
		death = stoi(readFile(Id, "death"));
	}
	father = stoi(readFile(Id, "father"));
	mather = stoi(readFile(Id, "mather"));
	delete children;
	string sbuff = readFile(Id, "children");
	children = new ushortList;
	ushortList *p = children;
	children->id = 0;
	for (int i = 0; i < sbuff.length(); i++)
	{
		static short n = 0;
		if (sbuff[i] == ',')
		{
			p->next = new ushortList;
			p = p->next;
			n = 0;
			p->id = 0;
		}
		else
		{
			p->id *= 10;
			string stmp;
			stmp.resize(1);
			stmp[0] = sbuff[i];
			p->id += stoi(stmp);
		}
	}
	p->next = NULL;
	delete sheets;
	sbuff = readFile(Id, "children");
	sheets = new ushortList;
	p = sheets;
	sheets->id = 0;
	for (int i = 0; i < sbuff.length(); i++)
	{
		static short n = 0;
		if (sbuff[i] == ',')
		{
			p->next = new ushortList;
			p = p->next;
			n = 0;
			p->id = 0;
		}
		else
		{
			p->id *= 10;
			string stmp;
			stmp.resize(1);
			stmp[0] = sbuff[i];
			p->id += stoi(stmp);
		}
	}
	p->next = NULL;
	generation = stoi(readFile(Id, "generation"));
	return true;
}
void Entry::addChild(const ushort &Id)
{
	if (children == NULL)
	{
		children = new ushortList;
		children->id = Id;
		children->next = NULL;
	}
	else
	{
		ushortList *pointer = new ushortList;
		pointer->id = Id;
		pointer->next = children;
		children = pointer;
	}
}
void Entry::displayListHeader()
{
	setColor(Yellow, Blue);
	cout << "�   ";
	setColor(Red, LightGreen);
	cout << "���                                         ";
	setColor(LightBlue, White);
	cout << " ";
	setColor(Green, LightGreen);
	cout << "���. ";
	setColor(DarkGray, LightGray);
	cout << "���� ";
	setColor(Blue, Yellow);
	cout << "���";
	setColor(Magenta, Yellow);
	cout << "���";
	setColor(LightGray, Blue);
	cout << "���" << endl;
	setColor(Red, LightRed);
	for (short i = 0; i < 68; i++)
	{
		cout << "�";
	}
	cout << endl;
	resetColor();
}
bool Entry::search(const short &entries, const bool &exact, const bool &display, const string str, bool make_line)
{
	if (display)
	{
		if (make_line)
		{
			line("�����");
		}
		cout << "���������� ������ �� ������� �" << str << "�:" << endl;
		if (exact)
		{
			cout << "(������ ������ ����������)" << endl;
		}
		displayListHeader();
	}
	string buff;
	bool ret = false;
	Entry entry(1);
	for (short i = 1; i <= entries; i++)
	{
		entry.load(entries, i);
		bool match = false;
		buff = entry.getName();
		match = exact ? (buff == str) : (buff.find(str) != buff.npos);
		if (match)
		{
			ret = true;
		}
		if (match && display)
		{
			entry.displayInList();
		}
	}
	if (display && !ret)
	{
		setColor(Red, LightRed);
		cout << "������� �� ������� ������� �� �������." << endl;
		resetColor();
	}
	if (display)
	{
		cout << endl << "������� 0 ��� ������." << endl << "������� � ID: ";
		ushort ID;
		cin >> ID;
		while (ID != 0)
		{
			Entry entry(ID);
			entry.load(entries);
			ID = entry.display(entries);
		}
	}
	return ret;
}
ushort Entry::getParent(const bool &is_father)
{
	return (is_father ? father : mather);
}
ushortList* Entry::getSheets()
{
	return sheets;
}
string Entry::getName()
{
	return name;
}
void Entry::edit(const short &entries)
{
	line("��������������");
	bool in;
	cout << "������� 1, ����� ��������; 0, ����� �� ��������." << endl << endl;
	cout << "���: " << name << endl << "\t";
	cin >> in;
	if (in)
	{
		setName(entries);
	}
	cout << "������� 1, ����� ��������; 0, ����� �� ��������." << endl << endl <<
		"���: " << (gender ? "�������" : "�������") << endl << "\t";
	cin >> in;
	if (in)
	{
		setGender();
	}
	cout << "������� 1, ����� ��������; 0, ����� �� ��������." << endl << endl <<
		"��� ��������: ";
	displayYear(false);
	cout << endl << "\t";
	cin >> in;
	if (in)
	{
		setBirth();
	}
	cout << "������� 1, ����� ��������; 0, ����� �� ��������." << endl << endl <<
		"��� ������: ";
	displayYear(true);
	cout << endl << "\t";
	cin >> in;
	if (in)
	{
		setDeath();
	}
	cout << "������� 1, ����� ��������; 0, ����� �� ��������." << endl << endl <<
		"��������:" << endl;
	displayParents(entries);
	cout << endl << "\t";
	cin >> in;
	if (in)
	{
		setParents(entries);
	}
	cout << "������� 1, ����� ��������; 0, ����� �� ��������." << endl << endl <<
		"�����: ";
	displaySheets();
	cout << endl << "\t";
	cin >> in;
	if (in)
	{
		setSheets();
	}
	cout << "������� 1, ����� ��������; 0, ����� �� ��������." << endl << endl <<
		"���������: " << generation << endl << "\t";
	cin >> in;
	if (in)
	{
		setGeneration();
	}
	save();
	cout << "������ ���������.";
}