#include "pch.h"
#include "EncryptionDll.hpp"

#include<fstream>
#include<string>
#include<vector>

constexpr auto MOD = 19491001;





struct Time {
	int year;
	int mounth;
	int date;
	bool operator ==(const Time x) {
		if (this->year != x.year)
			return false;
		if (this->mounth != x.mounth)
			return false;
		if (this->date != x.date)
			return false;
		return true;
	}
};

struct Good_Info {
	std::string name;
	int amount=0;
	int number=0;
	int location=0;
	Time time = { 0,0,0 };
	Good_Info* next=NULL;
};

struct Search_Info {
	std::string name;
	int amount;
	int number;
	int location;
	Time time;
	int type;
};

struct Search_Return {
	bool find;
	int number;
	std::vector<int>numbers;
};

Good_Info* head;


void Insert(Good_Info good_to_be_insert) {
	Good_Info *tmp=new Good_Info;
	tmp->next = head->next;
	head->next = tmp;
	*tmp = good_to_be_insert;
}

bool Delete(int number) {
	for (Good_Info* now = head; now->next != NULL; now = now->next)
		if (now->next->number == number) {
			Good_Info* tmp = now->next;
			now->next = tmp->next;
			delete tmp;
			return true;
		}
	return false;
}

Search_Return Search(Search_Info info) {
	Search_Return ans;
	switch (info.type) {
	  case 1: {//按名字查找第一个相同的
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
				  ans.number = now->number;
				  return ans;
			  }
		  }
		  ans.find = false;
		  return ans;//未找到
	  }
	  case 2: {//按数量查找所有相同的
		  ans.find = false;
		  for (Good_Info* now = head->next; now != NULL; now = now->next) {
			  if (now->amount == info.amount)
				  ans.find = true;
				  ans.numbers.push_back(now->number);
			  }
		  return ans;
	  }
	  case 3: {//按货架编号查找所有相同的
		  ans.find = false;
		  for (Good_Info* now = head->next; now != NULL; now = now->next)
			  if (now->location == info.location) {
				  ans.find = true;
				  ans.numbers.push_back(now->number);
			  }
		  return ans;
	  }
	  case 4: {//按时间查找所有相同的
		  ans.find = false;
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

void sort(int command) {

}

void init() {
	std::fstream file = std::fstream("货物数据.data", std::ios::in);
	std::vector<uint8_t>key(2 * 1024 * 1024);//定义一个2Mb内存块?
	file.seekg(-(2 * 1024 * 1024), std::ios::end);
	file.read((char*)key.data(), 2 * 1024 * 1024);
	qmcPreDec(key.data(), 2 * 1024 * 1024, "normal");






}

void save() {
	std::fstream file = std::fstream("货物数据.data", std::ios::out);
	std::vector<uint8_t>key(2*1024*1024);//定义一个2Mb内存块?
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
	int cnt=0;
	Good_Info* tmp = head->next;
	for (Good_Info* now = tmp; now != NULL; now = tmp) {
		tmp = tmp->next;
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
