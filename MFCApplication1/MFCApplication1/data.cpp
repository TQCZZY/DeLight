#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include<vector>
#include "List.cpp"

struct Goodinfor {
	CString itemName;
	CString snum;
	CString time;
	CString thing;
	int huo;// »õ¼Ü±àºÅ
	int bian;//±àºÅ
};

std::vector<Goodinfor>Com;
Goodinfor tmp;

void transform() {
	Com.clear();
	for (Good_Info* now = head->next; now != NULL; now = now->next) {
		tmp.itemName.Format(_T("%s"), now->name);
		tmp.time.Format(_T("%d-%d-%d"), now->time.year, now->time.month, now->time.date);
		tmp.snum.Format(_T("%d"), now->amount);
		tmp.thing.Format(_T("%d"), now->location);
		tmp.huo = now->location;
		tmp.bian = now->number;
		Com.push_back(tmp);
	}
}

Search_Info Sou2;