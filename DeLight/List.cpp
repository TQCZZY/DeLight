#include "pch.h"
#include <fstream>
#include <string>
#include <vector>
#include "List.h"
#include "EncryptionDll.hpp"

std::vector<Goodinfor>Com;
Goodinfor tmp;

Search_Info Sou2;

Good_Info* head = new Good_Info;
int cnt;

void transform(bool fromList) {
	if (fromList)
	{
		Com.clear();
		for (Good_Info* now = head->next; now != NULL; now = now->next) {
			tmp.name = now->name.c_str();
			tmp.time = (std::to_string(now->time.year) + "-" + std::to_string(now->time.month) + "-" + std::to_string(now->time.date)).c_str();
			tmp.num = std::to_string(now->amount).c_str();
			tmp.shelf = std::to_string(now->location).c_str();
			tmp.shelfNo = now->location;
			tmp.code = now->number;
			Com.push_back(tmp);
		}
	} else {
		Delete(-1);
		USES_CONVERSION;
		for (int i = 0; i < Com.size(); ++i) {
			Good_Info new_good;
			USES_CONVERSION;
			new_good.name = W2A(Com[i].name);

			std::string rawDate = W2A(Com[i].time);
			Time t = { 0,0,0 };
			int p = 0;
			while (rawDate[p] != '-') {
				t.year *= 10;
				t.year += rawDate[p++] - '0';
			}
			p++;
			while (rawDate[p] != '-') {
				t.month *= 10;
				t.month += rawDate[p++] - '0';
			}
			p++;
			while (rawDate[p] != '\0') {
				t.date *= 10;
				t.date += rawDate[p++] - '0';
			}
			new_good.time.year = t.year;
			new_good.time.month = t.month;
			new_good.time.date = t.date;

			new_good.amount = _ttoi(Com[i].num);
			new_good.location = Com[i].shelfNo;
			Insert(new_good);
		}
	}
}

void Time::operator =(const Time x) {
	this->year = x.year;
	this->month = x.month;
	this->date = x.date;
	return;
}
bool Time::operator ==(const Time x) {
	return this->year == x.year && this->month == x.month && this->date == x.date;
}
bool Time::operator >(const Time x) {
	if (this->year < x.year)
		return false;
	if (this->month < x.month)
		return false;
	if (this->date < x.date)
		return false;
	return true;
}

void Good_Info::operator<<(std::vector<uint8_t> src)
{
	size_t least = (3 + 3) * sizeof(int);
	if (src.size() < least)
	{
		return;
	}
	size_t srcIdx = 0;
	for (size_t i = 0; i < src.size() - least; ++i, ++srcIdx)
	{
		name.push_back((char)src[srcIdx]);
	}
	uint8_t* intPtr;
	intPtr = (uint8_t*)&amount;
	for (size_t i = 0; i < sizeof(int); ++i, ++srcIdx)
	{
		*(intPtr + i) = src[srcIdx];
	}
	intPtr = (uint8_t*)&number;
	for (size_t i = 0; i < sizeof(int); ++i, ++srcIdx)
	{
		*(intPtr + i) = src[srcIdx];
	}
	intPtr = (uint8_t*)&location;
	for (size_t i = 0; i < sizeof(int); ++i, ++srcIdx)
	{
		*(intPtr + i) = src[srcIdx];
	}
	intPtr = (uint8_t*)&(time.year);
	for (size_t i = 0; i < sizeof(int); ++i, ++srcIdx)
	{
		*(intPtr + i) = src[srcIdx];
	}
	intPtr = (uint8_t*)&(time.month);
	for (size_t i = 0; i < sizeof(int); ++i, ++srcIdx)
	{
		*(intPtr + i) = src[srcIdx];
	}
	intPtr = (uint8_t*)&(time.date);
	for (size_t i = 0; i < sizeof(int); ++i, ++srcIdx)
	{
		*(intPtr + i) = src[srcIdx];
	}
}

void Good_Info::operator>>(std::vector<uint8_t>& dst)
{
	for (size_t i = 0; i < name.size(); ++i)
	{
		dst.push_back(name[i]);
	}
	uint8_t* intPtr;
	intPtr = (uint8_t*)&amount;
	for (size_t i = 0; i < sizeof(int); ++i)
	{
		dst.push_back(*(intPtr + i));
	}
	intPtr = (uint8_t*)&number;
	for (size_t i = 0; i < sizeof(int); ++i)
	{
		dst.push_back(*(intPtr + i));
	}
	intPtr = (uint8_t*)&location;
	for (size_t i = 0; i < sizeof(int); ++i)
	{
		dst.push_back(*(intPtr + i));
	}
	intPtr = (uint8_t*)&(time.year);
	for (size_t i = 0; i < sizeof(int); ++i)
	{
		dst.push_back(*(intPtr + i));
	}
	intPtr = (uint8_t*)&(time.month);
	for (size_t i = 0; i < sizeof(int); ++i)
	{
		dst.push_back(*(intPtr + i));
	}
	intPtr = (uint8_t*)&(time.date);
	for (size_t i = 0; i < sizeof(int); ++i)
	{
		dst.push_back(*(intPtr + i));
	}
}

void Insert(Good_Info good_to_be_insert, int position) {
	Good_Info* tmp = new Good_Info;
	Search_Info s;
	s.name = good_to_be_insert.name;
	s.type = 1;
	//能否合并?
	std::vector<int>rev = Search(s);
	for (int i = 0; i < rev.size(); i++) {
		for (Good_Info* now = head->next; now != NULL; now = now->next) {
			if (now->number == rev[i]) {
				if (now->location == good_to_be_insert.location && now->time == good_to_be_insert.time) {
					now->amount += good_to_be_insert.amount;
					delete tmp;
					return;
				}
			}
		}
	}
	//新建
	if (position == 0) {
		tmp->next = head->next;
		head->next = tmp;
		*tmp = good_to_be_insert;
		tmp->number = ++cnt;
		return;
	}
	Good_Info* now = head;
	for (int i = 0; i < position; i++)
		now = now->next;
	tmp->next = head->next;
	now->next = tmp;
	*tmp = good_to_be_insert;
	tmp->number = ++cnt;
}

bool Delete(int number) {
	bool deleted = false;
	for (Good_Info* now = head; now->next != NULL; now = now->next)
	{
		if (now->next->number == number || number == -1) {
			Good_Info* tmp = now->next;
			now->next = tmp->next;
			delete tmp;
			deleted = true;
			break;
		}
	}
	return deleted;
}

std::vector<int> Search(Search_Info info) {
	std::vector<int> ans;
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
			if (find_hash == hash)
				ans.push_back(now->number);
		}
		return ans;//未找到
	}
	case 2: {//按数量查找所有相同的
		for (Good_Info* now = head->next; now != NULL; now = now->next)
			if (now->amount == info.amount)
				ans.push_back(now->number);
		return ans;
	}
	case 3: {//按货架编号查找所有相同的
		for (Good_Info* now = head->next; now != NULL; now = now->next)
			if (now->location == info.location)
				ans.push_back(now->number);
		return ans;
	}
	case 4: {//按时间查找所有相同的
		for (Good_Info* now = head->next; now != NULL; now = now->next)
			if (now->time == info.time)
				ans.push_back(now->number);
		return ans;
	}
	}
	return ans;
}

void Swap(Good_Info* x) {
	Good_Info* tmp1 = x->next;
	Good_Info* tmp2 = tmp1->next;
	tmp1->next = tmp2->next;
	tmp2->next = tmp1;
	x->next = tmp2;
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
					Swap(tmp);
				}
			}
		}
	}
	break;
	case 2: {//数量
		for (int i = 1; i < n; i++)
		{
			for (int j = 0; j < n - i; j++) {
				Good_Info* tmp = head;
				for (int k = 0; k < j; k++)
					tmp = tmp->next;
				if (tmp->next->amount > tmp->next->next->amount) {
					Swap(tmp);
				}
			}
		}
	}
	break;
	case 3: {//货架
		for (int i = 1; i < n; i++)
		{
			for (int j = 0; j < n - i; j++) {
				Good_Info* tmp = head;
				for (int k = 0; k < j; k++)
					tmp = tmp->next;
				if (tmp->next->location > tmp->next->next->location) {
					Swap(tmp);
				}
			}
		}
	}
	break;
	case 4: {//时间
		for (int i = 1; i < n; i++)
		{
			for (int j = 0; j < n - i; j++) {
				Good_Info* tmp = head;
				for (int k = 0; k < j; k++)
					tmp = tmp->next;
				if (tmp->next->time > tmp->next->next->time) {
					Swap(tmp);
				}
			}
		}
	}
	break;
	}
}

#define FDBG
std::string Init() {
	std::fstream file = std::fstream("货物数据.data", std::ios::in);
	std::vector<uint8_t>key(2 * 1024 * 1024);//定义一个2Mb内存块
	file.seekg(-(2 * 1024 * 1024), std::ios::end);
	file.read((char*)key.data(), 2 * 1024 * 1024);
	int qmcrev = qmcPreDec(key.data(), 2 * 1024 * 1024, "normal");
	if (qmcrev == -1) {
		std::string error;
		qmcGetErr((char*)error.c_str());
		return error;
		//把这个字符串给WJB再退出
	}
	key.resize(qmcrev);
	int count = 0;
	int length = 0;
	char c = '\0';
	int n = 0;
	while (c != '\n') {
		file.read(&c, sizeof(c));
#ifndef FDBG
		length = qmcDecBlock((uint8_t*)c, sizeof(c), count);
#else
		length = sizeof(c);
#endif
		count += sizeof(c);
		if (length == 0) {
			std::string error;
			qmcGetErr((char*)error.c_str());
			return error;
			//把这个字符串给WJB再退出
		}
		n *= 10;
		n += c;
	}
	cnt = n;
	//c = '\0';
	//n = 0;
	//while (c != '\n') {
	//	file.read(&c, 1);
	//	n *= 10;
	//	n += c;
	//}
	Good_Info* now=head;
	Good_Info* tmp;
	for (int i = 0; i < cnt; i++) {
		std::vector<uint8_t> binBlock;
		tmp = new Good_Info;
		int size = 0;
		c = '\0';
		while (c != '\n') {
			file.read(&c, sizeof(c));
#ifndef FDBG
			length = qmcDecBlock((uint8_t*)c, sizeof(c), count);
#else
			length = sizeof(c);
#endif
			count += sizeof(c);
			if (length == 0) {
				std::string error;
				qmcGetErr((char*)error.c_str());
				return error;
				//把这个字符串给WJB再退出
			}
			if (c == '\n')
			{
				size *= 10;
				size += c;
			}
		}
		binBlock.resize(size);
		file.read((char*)binBlock.data(), size);
#ifndef FDBG
		length = qmcDecBlock(binBlock.data(), size, count);
#else
		length = size;
#endif
		count += size;
		if (length == 0) {
			std::string error;
			qmcGetErr((char*)error.c_str());
			return error;
			//把这个字符串给WJB再退出
		}
		now->next = tmp;
	}
	file.close();
	now->next = NULL;
	return "";
}

std::string Save() {
	std::fstream file = std::fstream("货物数据.data", std::ios::out);
	std::vector<uint8_t>key(2 * 1024 * 1024);//定义一个2Mb内存块
	int qmcrev = qmcPreEnc(key.data(), key.size(), "RC4");
	if (qmcrev == -1) {
		std::string error;
		qmcGetErr((char*)error.c_str());
		return error;
		//把这个字符串给WJB再退出
	}
	key.resize(qmcrev);
	transform(true);
	//qmcEncBlock((uint8_t*)Com.data(), sizeof(Com), 0);
	int count = 0;
	int length = 0;
	int n = cnt;//计数
	std::vector<char>s;
	while (n != 0) {
		s.push_back(n % 10);
		n /= 10;
	}
	s.push_back('\n');
#ifndef FDBG
	length = qmcEncBlock((uint8_t*)s.data(), sizeof(s), count);
#else
	length = sizeof(s);
#endif
	count += sizeof(s);
	if (length == 0) {
		std::string error;
		qmcGetErr((char*)error.c_str());
		return error;
		//把这个字符串给WJB再退出
	}
	file.write((const char*)s.data(), sizeof(s));
	//n = 0;
	//s.clear();
	//for (Good_Info* now = head->next; now != NULL; now = now->next)
	//	n++;
	//while (n != 0) {
	//	s.push_back(n % 10);
	//	n /= 10;
	//}
	//s.push_back('\n');
	//file.write((const char*)s.data(), sizeof(s));
	for (Good_Info* now = head->next; now != NULL; now = now->next) {
		std::vector<uint8_t> binBlock;
		*now >> binBlock;
		int size = binBlock.size();
		char c;
		while (size != 0) {
			c = size % 10;
			size /= 10;
#ifndef FDBG
			length = qmcEncBlock((uint8_t*)c, sizeof(c), count);
#else
			length = sizeof(c);
#endif
			count += sizeof(c);
			if (length == 0) {
				std::string error;
				qmcGetErr((char*)error.c_str());
				return error;
				//把这个字符串给WJB再退出
			}
			file.write(&c, 1);
		}
		c = '\n';
#ifndef FDBG
		length = qmcEncBlock((uint8_t*)c, sizeof(c), count);
#else
		length = sizeof(c);
#endif
		count += sizeof(c);
		if (length == 0) {
			std::string error;
			qmcGetErr((char*)error.c_str());
			return error;
			//把这个字符串给WJB再退出
		}
		file.write(&c, sizeof(c));
#ifndef FDBG
		length = qmcEncBlock(binBlock.data(), binBlock.size(), count);
#else
		length = binBlock.size();
#endif
		count += binBlock.size();
		if (length == 0) {
			std::string error;
			qmcGetErr((char*)error.c_str());
			return error;
			//把这个字符串给WJB再退出
		}
		file.write((const char*)binBlock.data(), binBlock.size());
	}
	file.write((const char*)key.data(), key.size());
	file.close();
	return "";
}
