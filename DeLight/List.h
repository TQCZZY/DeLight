#pragma once

constexpr auto MOD = 19491001;

struct Time {
	int year;
	int month;
	int date;
	void operator =(const Time x);
	bool operator ==(const Time x);
	bool operator >(const Time x);
	void operator <<(std::string src);
	void operator >>(std::string& dst);
	std::string toString();
};

struct Good_Info {
	std::string name;
	int amount = 0;
	int number = 0;
	int location = 0;
	Time time = { 0,0,0 };
	Good_Info* next = NULL;
	void operator <<(std::vector<uint8_t> src);
	void operator >>(std::vector<uint8_t> &dst);
	void operator =(const Good_Info rightOperand);
	size_t size();
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
	CString name;
	CString num;
	CString time;
	CString shelf;
	int shelfNo;// 货架编号
	int code;//编号
};

extern std::vector<Goodinfor>Com;
extern Goodinfor tmp;

extern Good_Info* head;
extern int cnt;

void Insert(Good_Info good_to_be_insert, int position = 0);
bool Delete(int number);
std::vector<int>Search(Search_Info info);
void Sort(int command);
std::string Init();
std::string Save();

void transform(bool fromList);