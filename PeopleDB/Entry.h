/*//////////////////////////////////////
//       YPeopleDB by SnegirSoft      //
//  Authors:                          //
//      jenyaiu90 aka sqrt(-1)        //
//                                    //
//  File: Entry.h                     //
//////////////////////////////////////*/
#pragma once
#include <string>
#include "File.h"
using namespace std;
#define ushort unsigned short
#define uint unsigned int
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
	void setName(const short&);
	void setGender();
	void setBirth();
	void setDeath();
	void setParents(const short&);
	void setSheets();
public: void setGeneration();
private: void displayYear(const bool&);
	void displayParents(const short&);
	void displaySheets();
public:
	Entry(const ushort&);
	~Entry();
	void set(const short&);
	bool getGender();
	ushort display(const short&);
	static short displayList(const short&, const short page=0);
	static short displaySheetList(const short&, const ushort&, const short page=0);
	void displayInList();
	void save();
	bool load(const short&);
	bool load(const short&, const ushort&);
	void addChild(const ushort&);
	static void displayListHeader();
	static bool search(const short&, const bool&, const bool&, const string, const bool make_line=true);
	ushort getParent(const bool&);
	ushortList* getSheets();
	string getName();
	void edit(const short&);
};