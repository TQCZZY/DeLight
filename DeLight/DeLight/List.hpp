//#ifndef LIST_HPP
//#define LIST_HPP
#pragma once
#include<fstream>
#include<string>
#include<vector>
//#include "EncryptionDll.hpp"

constexpr auto MOD = 19491001;

struct Time {
	int year;
	int month;
	int date;
	void operator =(const Time x);
	bool operator ==(const Time x);
	bool operator >(const Time x);
};

struct Good_Info {
	std::string name;
	int amount = 0;
	int number = 0;
	int location = 0;
	Time time = { 0,0,0 };
	Good_Info* next = NULL;
};

struct Search_Info {
	std::string name;
	int amount;
	int number;
	int location;
	Time time;
	int type;//1名称2数量3货架4时间
};

struct Goodinfor {
	CString itemName;
	CString snum;
	CString time;
	CString thing;
	int huo;// 货架编号
	int bian;//编号
};

extern std::vector<Goodinfor>Com;
extern Goodinfor tmp;

extern Search_Info Sou2;

extern Good_Info* head;
extern int cnt;

void Insert(Good_Info good_to_be_insert);
bool Delete(int number);
std::vector<int>Search(Search_Info info);
void Sort(int command);
void Init();
void Save();

void transform();