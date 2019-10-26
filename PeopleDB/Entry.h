/*//////////////////////////////////////
//       YPeopleDB by SnegirSoft      //
//  Authors:                          //
//      jenyaiu90 aka sqrt(-1)        //
//                                    //
//  File: Entry.h                     //
//////////////////////////////////////*/
#pragma once
#include <string>
using namespace std;
#define ushort unsigned short
#define uint unsigned int
struct ushortList
{
public:
	ushort id;
	ushortList *next;
};
enum DateStatus { Norm, Un, Around, Before, After };

class Entry
{
private:
	ushort id;
	string name;
	bool gender; //false — F, true — M
	int birth;
	int death;
	DateStatus birthStatus;
	DateStatus deathStatus;
	ushort father; //0 = unknown
	ushort mather; //0 = unknown
	ushortList *children;
	ushortList *sheets;
	short generation;
	void setName();
	void setGender();
	void setBirth();
	void setDeath();
	void setParents();
	void setSheets();
public: void setGeneration();
private: void displayYear(const bool&);
	void displayParents();
	void displaySheets();
	void sg(short);
public:
	Entry(const ushort&);
	~Entry();
	void set();
	bool getGender();
	ushort display(const bool displayGeneration=true);
	static short displayList(const short page=0);
	static void displaySheetList(const ushort&);
	void displayInList();
	void save();
	bool load();
	bool load(const ushort&, const bool loadGeneration=true);
	void addChild(const ushort&);
	static void displayListHeader();
	static bool search(const bool&, const bool&, const string, const bool make_line=true);
	ushort getParent(const bool&);
	ushortList* getSheets();
	void edit();
};

//void line(const string text, const int num);
