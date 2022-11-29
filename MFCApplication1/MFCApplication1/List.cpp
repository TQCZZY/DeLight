#include "pch.h"
#include<fstream>
#include<string>
#include<vector>
#include "EncryptionDll.hpp"

constexpr auto MOD = 19491001;

void Insert(Good_Info good_to_be_insert);
bool Delete(int number);
Search_Return Search(Search_Info info);
void Sort(int command);
void Init();
void Save();

struct Time {
	int year;
	int month;
	int date;
	void operator =(const Time x) {
		this->year = x.year;
		this->month = x.month;
		this->date = x.date;
		return;
	}
	bool operator ==(const Time x) {
		return this->year == x.year && this->month == x.month && this->date == x.date;
	}
	bool operator >(const Time x) {
		if (this->year < x.year)
			return false;
		if (this->month < x.month)
			return false;
		if (this->date < x.date)
			return false;
		return true;
	}
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

struct Search_Return {
	bool find;
	std::vector<int>numbers;
};

Good_Info* head;


void Insert(Good_Info good_to_be_insert) {
	Good_Info* tmp = new Good_Info;
	Search_Info s;
	s.name = good_to_be_insert.name;
	s.type = 1;
	//能否合并?
	Search_Return rev = Search(s);
	for (int i = 0; i < rev.numbers.size(); i++)
	{
		for (Good_Info* now = head->next; now != NULL; now = now->next)
		{
			if (now->number == rev.numbers[i])
			{
				if (now->location == good_to_be_insert.location && now->time == good_to_be_insert.time) {
					now->amount += good_to_be_insert.amount;
					return;
				}
			}
		}
	}
	//新建
	tmp->next = head->next;
	head->next = tmp;
	*tmp = good_to_be_insert;
}

bool Delete(int number) {
	for (Good_Info* now = head; now->next != NULL; now = now->next)
	{
		if (now->next->number == number) {
			Good_Info* tmp = now->next;
			now->next = tmp->next;
			delete tmp;
			return true;
		}
	}
	return false;
}

Search_Return Search(Search_Info info) {
	Search_Return ans;
	ans.find = false;
	switch (info.type) {
	case 1: {//按名字查找所有相同的
		int find_hash = 0;
		for (int i = 0; i < info.name.length(); i++) {
			find_hash *= 10;
			find_hash += info.name[i];
			find_hash %= MOD;
		}
		for (Good_Info* now = head->next; now != NULL; now = now->next) {
			int hash = 0;
			for (int i = 0; i < now->name.length(); i++) {
				hash *= 10;
				hash += now->name[i];
				hash %= MOD;
			}
			if (find_hash == hash) {
				ans.find = true;
				ans.numbers.push_back(now->number);
			}
		}
		return ans;//未找到
	}
	case 2: {//按数量查找所有相同的
		for (Good_Info* now = head->next; now != NULL; now = now->next) {
			if (now->amount == info.amount)
				ans.find = true;
			ans.numbers.push_back(now->number);
		}
		return ans;
	}
	case 3: {//按货架编号查找所有相同的
		for (Good_Info* now = head->next; now != NULL; now = now->next)
			if (now->location == info.location) {
				ans.find = true;
				ans.numbers.push_back(now->number);
			}
		return ans;
	}
	case 4: {//按时间查找所有相同的
		for (Good_Info* now = head->next; now != NULL; now = now->next)
			if (now->time == info.time) {
				ans.find = true;
				ans.numbers.push_back(now->number);
			}
		return ans;
	}
	}
	return ans;
}

void Sort(int command) {
	int n = 0;
	for (Good_Info* tmp = head->next; tmp != NULL; tmp = tmp->next)
		n++;
	switch (command) {
	case 1: {//名称(非字典序)
		for (int i = 1; i < n; i++)
		{
			for (int j = 0; j < n - i; j++) {
				Good_Info* tmp = head;
				for (int k = 0; k < j; k++)
					tmp = tmp->next;
				bool flag = false;
				for (int i = 0; i < min(tmp->next->name.length(), tmp->next->next->name.length()); i++)
					if (tmp->next->name[i] > tmp->next->next->name[i]) {
						flag = true;
						break;
					}
				if (flag) {
					Good_Info* swap = tmp->next->next;
					tmp->next->next = tmp->next->next->next;
					swap->next = tmp->next;
					tmp->next = swap;
				}
			}
		}
	}
	case 2: {//数量
		for (int i = 1; i < n; i++)
		{
			for (int j = 0; j < n - i; j++) {
				Good_Info* tmp = head;
				for (int k = 0; k < j; k++)
					tmp = tmp->next;
				if (tmp->next->amount > tmp->next->next->amount) {
					Good_Info* swap = tmp->next->next;
					tmp->next->next = tmp->next->next->next;
					swap->next = tmp->next;
					tmp->next = swap;
				}
			}
		}
	}
	case 3: {//货架
		for (int i = 1; i < n; i++)
		{
			for (int j = 0; j < n - i; j++) {
				Good_Info* tmp = head;
				for (int k = 0; k < j; k++)
					tmp = tmp->next;
				if (tmp->next->location > tmp->next->next->location) {
					Good_Info* swap = tmp->next->next;
					tmp->next->next = tmp->next->next->next;
					swap->next = tmp->next;
					tmp->next = swap;
				}
			}
		}
	}
	case 4: {//时间
		for (int i = 1; i < n; i++)
		{
			for (int j = 0; j < n - i; j++) {
				Good_Info* tmp = head;
				for (int k = 0; k < j; k++)
					tmp = tmp->next;
				if (tmp->next->time > tmp->next->next->time) {
					Good_Info* swap = tmp->next->next;
					tmp->next->next = tmp->next->next->next;
					swap->next = tmp->next;
					tmp->next = swap;
				}
			}
		}
	}
	}
}

void Init() {
	std::fstream file = std::fstream("货物数据.data", std::ios::in);
	std::vector<uint8_t>key(2 * 1024 * 1024);//定义一个2Mb内存块?
	file.seekg(-(2 * 1024 * 1024), std::ios::end);
	file.read((char*)key.data(), 2 * 1024 * 1024);
	int qmcrev = qmcPreDec(key.data(), 2 * 1024 * 1024, "normal");
	if (qmcrev == -1) {
		std::string error;
		qmcGetErr((char*)error.c_str());
		//把这个字符串给WJB再退出
	}
	char c = '\0';
	int n = 0;
	while (c != '\n') {
		file.read(&c, 1);
		n *= 10;
		n += c;
	}
	Good_Info* now = head;
	Good_Info* tmp;
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		tmp = new Good_Info;
		int size = 0;
		c = '\0';
		while (c != '\n') {
			file.read(&c, 1);
			size *= 10;
			size += c;
		}
		int lenth = qmcDecBlock((uint8_t*)tmp, size, cnt);
		if (lenth == 0) {
			std::string error;
			qmcGetErr((char*)error.c_str());
			//把这个字符串给WJB再退出
		}
		cnt += size;
		now->next = tmp;
	}
	file.close();
	now->next = NULL;
}

void Save() {
	std::fstream file = std::fstream("货物数据.data", std::ios::out);
	std::vector<uint8_t>key(2 * 1024 * 1024);//定义一个2Mb内存块?
	int qmcrev = qmcPreEnc(key.data(), key.size(), "RC4");
	if (qmcrev == -1) {
		std::string error;
		qmcGetErr((char*)error.c_str());
		//把这个字符串给WJB再退出
	}
	key.resize(qmcrev);
	int n = 0;//计数
	for (Good_Info* now = head->next; now != NULL; now = now->next)
		n++;
	std::vector<char>s;
	while (n != 0) {
		s.push_back(n % 10);
		n /= 10;
	}
	s.push_back('\n');
	file.write((const char*)s.data(), sizeof(s));
	int cnt = 0;
	Good_Info* tmp = head->next;
	for (Good_Info* now = tmp; now != NULL; now = tmp) {
		tmp = tmp->next;
		int size = sizeof(now);
		char c;
		while (size != 0) {
			c = size % 10;
			size /= 10;
			file.write(&c, 1);
		}
		c = '\n';
		file.write(&c, 1);
		int lenth = qmcEncBlock((uint8_t*)now, sizeof(now), cnt);
		if (lenth == 0) {
			std::string error;
			qmcGetErr((char*)error.c_str());
			//把这个字符串给WJB再退出
		}
		file.write((const char*)now, lenth);
		cnt += sizeof(now);
	}
	file.write((const char*)key.data(), key.size());
	file.close();
}
