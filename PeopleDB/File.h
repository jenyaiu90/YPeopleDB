/*//////////////////////////////////////
//       YPeopleDB by SnegirSoft      //
//  Authors:                          //
//      jenyaiu90 aka sqrt(-1)        //
//                                    //
//  File: File.h                      //
//////////////////////////////////////*/
#pragma once
#include <string>
#include <fstream>
#include <Windows.h>
#define ushort unsigned short
using namespace std;
struct ushortList
{
public:
	ushort id;
	ushortList *next;
};

static string readFile(const ushort id, const string field)
{
	string buff, bf;
	ifstream file("files\\db" + to_string(id / 100) + ".ypdb");
	do
	{
		getline(file, buff);
		bf = buff;
		if (file.eof())
		{
			return NULL;
		}
	} while (((bf.erase(bf.find_first_of(':'))), bf) != to_string(id));
	bf = buff;
	while ((bf.erase(0, bf.find_first_of(':') + 1), bf.erase(bf.find_first_of('=')), bf) != field)
	{
		getline(file, buff);
		bf = buff;
		if (bf.empty() || (bf.erase(bf.find_first_of(':')), bf) != to_string(id))
		{
			return NULL;
		}
		bf = buff;
	}
	buff.erase(0, buff.find_first_of('=') + 1);
	return buff;
}
static void writeFile(const ushort id, const string field, const string str)
{
	ifstream ifile("files\\db" + to_string(id / 100) + ".ypdb");
	ofstream ofile("files\\~db" + to_string(id / 100) + ".ypdb");
	string buff, bf;
	getline(ifile, buff);
	bf = buff;
	if (!bf.empty())
	{
		while ((bf.erase(bf.find_first_of('=')), bf) != (to_string(id) + ":" + field))
		{
			ofile << buff << endl;
			string tmp;
			getline(ifile, tmp);
			if (tmp == buff)
			{
				buff.clear();
			}
			buff = tmp;
			bf = buff;
			if (buff.empty())
			{
				break;
			}
		}
	}
	ofile << id << ":" << field << "=" << str << endl;
	string tmp;
	getline(ifile, tmp);
	if (buff == tmp)
	{
		tmp.clear();
	}
	buff = tmp;
	while (!buff.empty())
	{
		ofile << buff << endl;
		getline(ifile, tmp);
		if (buff == tmp)
		{
			tmp.clear();
		}
		buff = tmp;
	}
	ifile.close();
	ofile.close();
	remove(("files\\db" + to_string(id / 100) + ".ypdb").c_str());
	rename(("files\\~db" + to_string(id / 100) + ".ypdb").c_str(), ("files\\db" + to_string(id / 100) + ".ypdb").c_str());
}