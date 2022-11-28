

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
	union Info
	{
		std::string name;
		int amount;
		int number;
		int location;
		Time time;
	};
	int type;
	Info information;
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
		  for (int i = 0; i < info.information.name.length(); i++) {
			  find_hash *= 10;
			  find_hash += info.information.name[i];
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
			  if (now->amount == info.information.amount)
				  ans.find = true;
				  ans.numbers.push_back(now->number);
			  }
		  return ans;
	  }
	  case 3: {//按货架编号查找所有相同的
		  ans.find = false;
		  for (Good_Info* now = head->next; now != NULL; now = now->next)
			  if (now->location == info.information.location) {
				  ans.find = true;
				  ans.numbers.push_back(now->number);
			  }
		  return ans;
	  }
	  case 4: {//按时间查找所有相同的
		  ans.find = false;
		  for (Good_Info* now = head->next; now != NULL; now = now->next)
			  if (now->time == info.information.time) {
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
	
}

void save() {
	int n = 0;//计数
	for (Good_Info* now = head->next; now != NULL; now = now->next)
		n++;
	for (Good_Info* now = head->next; now != NULL; now = now->next) {

	}
}
