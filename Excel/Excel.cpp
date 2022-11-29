// Excel.cpp : 定义 DLL 的导出函数。
//

#include "pch.h"
#include "afx.h"
#include "afxwin.h"
#include "comutil.h"
#include "afxdisp.h"
#include "callexcel.h"
#include "Excel.h"
#include <vector>
#include <string>

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
		if (this->year != x.year ||
			this->month != x.month ||
			this->date != x.date)
			return false;
		return true;
	}
};

std::vector<std::string> internalGoods;
std::vector<int> internalCount;
std::vector<Time> internalDate;
std::vector<int> internalShelf;

EXCEL_API void global2Excel(CString PathName)
{
	_Application app;
	Workbooks books;
	_Workbook book;
	Worksheets sheets;
	_Worksheet sheet;
	Range range;
	LPDISPATCH lpDisp;
	COleVariant vResult;
	COleVariant covTrue((short)TRUE), covFalse((short)FALSE), covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if (!app.CreateDispatch(L"Excel.Application", NULL))
	{
		AfxMessageBox(L"Error Creating Excel Service.");
		return;
	}
	app.SetVisible(TRUE);
	books.AttachDispatch(app.GetWorkbooks(), true);
	lpDisp = books.Open(PathName, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional);
	ASSERT(lpDisp);
	book.AttachDispatch(lpDisp);
	sheets.AttachDispatch(book.GetWorksheets(), true);
	//sheet.AttachDispatch(sheets.GetItem(_variant_t(1)));
	//range.AttachDispatch(sheet.GetCells(), true);
	//range.AttachDispatch(sheet.GetRange(_variant_t("A4"), _variant_t("D6")), true);
	//range.SetColumnWidth(_variant_t((long)20));
	//range.AttachDispatch(sheet.GetRange(_variant_t("A4"), _variant_t("D6")), true);
	//range.SetRowHeight(_variant_t((long)25));
	//range.AttachDispatch(sheet.GetRange(_variant_t("A4"), _variant_t("D4")), true);
	//range.Merge(_variant_t((long)0));
	//range.SetItem(_variant_t((LONG)1), _variant_t((LONG)1), _variant_t("测试成绩三率统计(全体)"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)1), _variant_t("项目"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)2), _variant_t("优秀"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)3), _variant_t("及格"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)4), _variant_t("低分"));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)1), _variant_t("比率(%)"));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)2), _variant_t((double)(pinfos->exellentpct)));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)3), _variant_t((double)(pinfos->passpct)));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)4), _variant_t((double)(pinfos->badpct)));
	//range.AttachDispatch(sheet.GetRange(_variant_t("A1"), _variant_t("E3")), true);
	//range.SetColumnWidth(_variant_t((long)20));
	//range.AttachDispatch(sheet.GetRange(_variant_t("A1"), _variant_t("E3")), true);
	//range.SetRowHeight(_variant_t((long)25));
	//range.AttachDispatch(sheet.GetRange(_variant_t("A1"), _variant_t("E1")), true);
	//range.Merge(_variant_t((long)0));
	//range.SetItem(_variant_t((LONG)1), _variant_t((LONG)1), _variant_t("测试成绩概况(全体)"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)1), _variant_t("项目"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)2), _variant_t("样本数"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)3), _variant_t("平均量"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)4), _variant_t("极差"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)5), _variant_t("标准差"));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)1), _variant_t("数值"));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)2), _variant_t((long)(pinfos->size)));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)3), _variant_t((double)(pinfos->averagescr)));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)4), _variant_t((double)(pinfos->firstobjectscr - pinfos->lastobjectscr)));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)5), _variant_t((double)(pinfos->rmsscr)));
	//sheet.SetName(L"全体情况");
	//sheet.DetachDispatch();
	sheet.AttachDispatch(sheets.Add(covOptional, covOptional, _variant_t(1), covOptional));
	sheet.SetName(L"仓库概况");
	range.AttachDispatch(sheet.GetCells(), true);
	range.AttachDispatch(sheet.GetRange(_variant_t("A1"), _variant_t("I1")), true);
	range.Merge(_variant_t((long)0));
	range.SetItem(_variant_t((LONG)1), _variant_t((LONG)1), _variant_t("货物清单(全部货物)"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)1), _variant_t("货物"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)2), _variant_t("数量"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)3), _variant_t("入库日期"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)4), _variant_t("所在货架"));
	for (long i = 0; i < internalGoods.size(); i++)
	{
		range.SetItem(_variant_t((LONG)3 + i), _variant_t((LONG)1), _variant_t(internalGoods[i].c_str()));
		range.SetItem(_variant_t((LONG)3 + i), _variant_t((LONG)2), _variant_t(std::to_string(internalCount[i]).c_str()));
		range.SetItem(_variant_t((LONG)3 + i), _variant_t((LONG)3), _variant_t((std::to_string(internalDate[i].year) + "/" + std::to_string(internalDate[i].month) + "/" + std::to_string(internalDate[i].date)).c_str()));
		range.SetItem(_variant_t((LONG)3 + i), _variant_t((LONG)4), _variant_t(std::to_string(internalShelf[i]).c_str()));
	}
	//range.AttachDispatch(sheet.GetCells(), true);
	range.SetHorizontalAlignment(_variant_t((long)-4108));
	range.SetVerticalAlignment(_variant_t((long)-4108));
	double left = 450, top = 10, width = 450, height = 260;
	_Chart chart;
	ChartObjects chartobjects;
	ChartObject chartobject;
	lpDisp = sheet.ChartObjects(covOptional);
	ASSERT(lpDisp);
	chartobjects.AttachDispatch(lpDisp);
	chartobject = chartobjects.Add(left, top, width, height);
	chart.AttachDispatch(chartobject.GetChart());
	chart.SetChartType(72);
	lpDisp = sheet.GetRange(range.GetItem(_variant_t(2), _variant_t(7)), range.GetItem(_variant_t(3 + cl - 1), _variant_t(9)));
	ASSERT(lpDisp);
	VARIANT var;
	var.vt = VT_DISPATCH;
	var.pdispVal = lpDisp;
	chart.ChartWizard(var,
		COleVariant((short)51),
		covOptional,
		COleVariant((short)1),
		covOptional,
		COleVariant((short)0),
		COleVariant((short)TRUE),
		COleVariant(L"三率统计(全部群体)"),
		covOptional,
		COleVariant(L"比率(%)"),
		covOptional);
	book.Save();
	sheet.SetName(L"全部群体");
	if (item == IDYES)
	{
		app.SetDisplayAlerts(false);
		app.Quit();
	}
	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	app.ReleaseDispatch();
	return;
}

EXCEL_API void singleGoods2Excel(CString PathName)
{
	_Application app;
	Workbooks books;
	_Workbook book;
	Worksheets sheets;
	_Worksheet sheet;
	Range range;
	LPDISPATCH lpDisp;
	COleVariant vResult;
	COleVariant covTrue((short)TRUE), covFalse((short)FALSE), covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if (!app.CreateDispatch(L"Excel.Application", NULL))
	{
		AfxMessageBox(L"Error Creating Excel Service.");
		return;
	}
	app.SetVisible(TRUE);
	books.AttachDispatch(app.GetWorkbooks(), true);
	lpDisp = books.Open(PathName, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional);
	ASSERT(lpDisp);
	book.AttachDispatch(lpDisp);
	sheets.AttachDispatch(book.GetWorksheets(), true);
	//sheet.AttachDispatch(sheets.GetItem(_variant_t(1)));
	//range.AttachDispatch(sheet.GetCells(), true);
	//range.AttachDispatch(sheet.GetRange(_variant_t("A4"), _variant_t("D6")), true);
	//range.SetColumnWidth(_variant_t((long)20));
	//range.AttachDispatch(sheet.GetRange(_variant_t("A4"), _variant_t("D6")), true);
	//range.SetRowHeight(_variant_t((long)25));
	//range.AttachDispatch(sheet.GetRange(_variant_t("A4"), _variant_t("D4")), true);
	//range.Merge(_variant_t((long)0));
	//range.SetItem(_variant_t((LONG)1), _variant_t((LONG)1), _variant_t("测试成绩三率统计(全体)"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)1), _variant_t("项目"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)2), _variant_t("优秀"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)3), _variant_t("及格"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)4), _variant_t("低分"));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)1), _variant_t("比率(%)"));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)2), _variant_t((double)(pinfos->exellentpct)));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)3), _variant_t((double)(pinfos->passpct)));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)4), _variant_t((double)(pinfos->badpct)));
	//range.AttachDispatch(sheet.GetRange(_variant_t("A1"), _variant_t("E3")), true);
	//range.SetColumnWidth(_variant_t((long)20));
	//range.AttachDispatch(sheet.GetRange(_variant_t("A1"), _variant_t("E3")), true);
	//range.SetRowHeight(_variant_t((long)25));
	//range.AttachDispatch(sheet.GetRange(_variant_t("A1"), _variant_t("E1")), true);
	//range.Merge(_variant_t((long)0));
	//range.SetItem(_variant_t((LONG)1), _variant_t((LONG)1), _variant_t("测试成绩概况(全体)"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)1), _variant_t("项目"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)2), _variant_t("样本数"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)3), _variant_t("平均量"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)4), _variant_t("极差"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)5), _variant_t("标准差"));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)1), _variant_t("数值"));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)2), _variant_t((long)(pinfos->size)));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)3), _variant_t((double)(pinfos->averagescr)));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)4), _variant_t((double)(pinfos->firstobjectscr - pinfos->lastobjectscr)));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)5), _variant_t((double)(pinfos->rmsscr)));
	//sheet.SetName(L"全体情况");
	//sheet.DetachDispatch();
	sheet.AttachDispatch(sheets.Add(covOptional, covOptional, _variant_t(1), covOptional));
	USES_CONVERSION;
	sheet.SetName(A2W(("单个货物 " + internalGoods[0]).c_str()));
	range.AttachDispatch(sheet.GetCells(), true);
	range.AttachDispatch(sheet.GetRange(_variant_t("A1"), _variant_t("I1")), true);
	range.Merge(_variant_t((long)0));
	range.SetItem(_variant_t((LONG)1), _variant_t((LONG)1), _variant_t("货物清单(单个货物)"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)1), _variant_t("货物"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)2), _variant_t("数量"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)3), _variant_t("入库日期"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)4), _variant_t("所在货架"));
	long cl = 0;
	for (long j = 0; j < GROUPSIZE; j++)
	{
		if (pinfos->groups[j].existst == 1)
		{
			range.SetItem(_variant_t((LONG)3 + cl), _variant_t((LONG)1), _variant_t(pinfos->groups[j].name));
			range.SetItem(_variant_t((LONG)3 + cl), _variant_t((LONG)2), _variant_t(pinfos->groups[j].type == 1 ? "必须参加" : "选择参加"));
			range.SetItem(_variant_t((LONG)3 + cl), _variant_t((LONG)3), _variant_t(pinfos->groups[j].size));
			range.SetItem(_variant_t((LONG)3 + cl), _variant_t((LONG)4), _variant_t(pinfos->groups[j].averagescr));
			cl++;
		}
	}
	//range.AttachDispatch(sheet.GetCells(), true);
	range.SetHorizontalAlignment(_variant_t((long)-4108));
	range.SetVerticalAlignment(_variant_t((long)-4108));
	double left = 450, top = 10, width = 450, height = 260;
	_Chart chart;
	ChartObjects chartobjects;
	ChartObject chartobject;
	lpDisp = sheet.ChartObjects(covOptional);
	ASSERT(lpDisp);
	chartobjects.AttachDispatch(lpDisp);
	chartobject = chartobjects.Add(left, top, width, height);
	chart.AttachDispatch(chartobject.GetChart());
	chart.SetChartType(72);
	lpDisp = sheet.GetRange(range.GetItem(_variant_t(2), _variant_t(7)), range.GetItem(_variant_t(3 + cl - 1), _variant_t(9)));
	ASSERT(lpDisp);
	VARIANT var;
	var.vt = VT_DISPATCH;
	var.pdispVal = lpDisp;
	chart.ChartWizard(var,
		COleVariant((short)51),
		covOptional,
		COleVariant((short)1),
		covOptional,
		COleVariant((short)0),
		COleVariant((short)TRUE),
		COleVariant(L"三率统计(全部群体)"),
		covOptional,
		COleVariant(L"比率(%)"),
		covOptional);
	book.Save();
	sheet.SetName(L"全部群体");
	if (item == IDYES)
	{
		app.SetDisplayAlerts(false);
		app.Quit();
	}
	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	app.ReleaseDispatch();
	return;
}

EXCEL_API void shelf2Excel(CString PathName)
{
	_Application app;
	Workbooks books;
	_Workbook book;
	Worksheets sheets;
	_Worksheet sheet;
	Range range;
	LPDISPATCH lpDisp;
	COleVariant vResult;
	COleVariant covTrue((short)TRUE), covFalse((short)FALSE), covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if (!app.CreateDispatch(L"Excel.Application", NULL))
	{
		AfxMessageBox(L"Error Creating Excel Service.");
		return;
	}
	app.SetVisible(TRUE);
	books.AttachDispatch(app.GetWorkbooks(), true);
	lpDisp = books.Open(PathName, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional);
	ASSERT(lpDisp);
	book.AttachDispatch(lpDisp);
	sheets.AttachDispatch(book.GetWorksheets(), true);
	//sheet.AttachDispatch(sheets.GetItem(_variant_t(1)));
	//range.AttachDispatch(sheet.GetCells(), true);
	//range.AttachDispatch(sheet.GetRange(_variant_t("A4"), _variant_t("D6")), true);
	//range.SetColumnWidth(_variant_t((long)20));
	//range.AttachDispatch(sheet.GetRange(_variant_t("A4"), _variant_t("D6")), true);
	//range.SetRowHeight(_variant_t((long)25));
	//range.AttachDispatch(sheet.GetRange(_variant_t("A4"), _variant_t("D4")), true);
	//range.Merge(_variant_t((long)0));
	//range.SetItem(_variant_t((LONG)1), _variant_t((LONG)1), _variant_t("测试成绩三率统计(全体)"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)1), _variant_t("项目"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)2), _variant_t("优秀"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)3), _variant_t("及格"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)4), _variant_t("低分"));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)1), _variant_t("比率(%)"));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)2), _variant_t((double)(pinfos->exellentpct)));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)3), _variant_t((double)(pinfos->passpct)));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)4), _variant_t((double)(pinfos->badpct)));
	//range.AttachDispatch(sheet.GetRange(_variant_t("A1"), _variant_t("E3")), true);
	//range.SetColumnWidth(_variant_t((long)20));
	//range.AttachDispatch(sheet.GetRange(_variant_t("A1"), _variant_t("E3")), true);
	//range.SetRowHeight(_variant_t((long)25));
	//range.AttachDispatch(sheet.GetRange(_variant_t("A1"), _variant_t("E1")), true);
	//range.Merge(_variant_t((long)0));
	//range.SetItem(_variant_t((LONG)1), _variant_t((LONG)1), _variant_t("测试成绩概况(全体)"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)1), _variant_t("项目"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)2), _variant_t("样本数"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)3), _variant_t("平均量"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)4), _variant_t("极差"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)5), _variant_t("标准差"));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)1), _variant_t("数值"));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)2), _variant_t((long)(pinfos->size)));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)3), _variant_t((double)(pinfos->averagescr)));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)4), _variant_t((double)(pinfos->firstobjectscr - pinfos->lastobjectscr)));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)5), _variant_t((double)(pinfos->rmsscr)));
	//sheet.SetName(L"全体情况");
	//sheet.DetachDispatch();
	sheet.AttachDispatch(sheets.Add(covOptional, covOptional, _variant_t(1), covOptional));
	sheet.SetName(L"仓库概况");
	range.AttachDispatch(sheet.GetCells(), true);
	range.AttachDispatch(sheet.GetRange(_variant_t("A1"), _variant_t("I1")), true);
	range.Merge(_variant_t((long)0));
	range.SetItem(_variant_t((LONG)1), _variant_t((LONG)1), _variant_t("货物清单(全部货物)"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)1), _variant_t("货物"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)2), _variant_t("数量"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)3), _variant_t("入库日期"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)4), _variant_t("所在货架"));
	long cl = 0;
	for (long j = 0; j < GROUPSIZE; j++)
	{
		if (pinfos->groups[j].existst == 1)
		{
			range.SetItem(_variant_t((LONG)3 + cl), _variant_t((LONG)1), _variant_t(pinfos->groups[j].name));
			range.SetItem(_variant_t((LONG)3 + cl), _variant_t((LONG)2), _variant_t(pinfos->groups[j].type == 1 ? "必须参加" : "选择参加"));
			range.SetItem(_variant_t((LONG)3 + cl), _variant_t((LONG)3), _variant_t(pinfos->groups[j].size));
			range.SetItem(_variant_t((LONG)3 + cl), _variant_t((LONG)4), _variant_t(pinfos->groups[j].averagescr));
			cl++;
		}
	}
	//range.AttachDispatch(sheet.GetCells(), true);
	range.SetHorizontalAlignment(_variant_t((long)-4108));
	range.SetVerticalAlignment(_variant_t((long)-4108));
	double left = 450, top = 10, width = 450, height = 260;
	_Chart chart;
	ChartObjects chartobjects;
	ChartObject chartobject;
	lpDisp = sheet.ChartObjects(covOptional);
	ASSERT(lpDisp);
	chartobjects.AttachDispatch(lpDisp);
	chartobject = chartobjects.Add(left, top, width, height);
	chart.AttachDispatch(chartobject.GetChart());
	chart.SetChartType(72);
	lpDisp = sheet.GetRange(range.GetItem(_variant_t(2), _variant_t(7)), range.GetItem(_variant_t(3 + cl - 1), _variant_t(9)));
	ASSERT(lpDisp);
	VARIANT var;
	var.vt = VT_DISPATCH;
	var.pdispVal = lpDisp;
	chart.ChartWizard(var,
		COleVariant((short)51),
		covOptional,
		COleVariant((short)1),
		covOptional,
		COleVariant((short)0),
		COleVariant((short)TRUE),
		COleVariant(L"三率统计(全部群体)"),
		covOptional,
		COleVariant(L"比率(%)"),
		covOptional);
	book.Save();
	sheet.SetName(L"全部群体");
	if (item == IDYES)
	{
		app.SetDisplayAlerts(false);
		app.Quit();
	}
	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	app.ReleaseDispatch();
	return;
}

EXCEL_API void specDate2Excel(CString PathName)
{
	_Application app;
	Workbooks books;
	_Workbook book;
	Worksheets sheets;
	_Worksheet sheet;
	Range range;
	LPDISPATCH lpDisp;
	COleVariant vResult;
	COleVariant covTrue((short)TRUE), covFalse((short)FALSE), covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if (!app.CreateDispatch(L"Excel.Application", NULL))
	{
		AfxMessageBox(L"Error Creating Excel Service.");
		return;
	}
	app.SetVisible(TRUE);
	books.AttachDispatch(app.GetWorkbooks(), true);
	lpDisp = books.Open(PathName, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional);
	ASSERT(lpDisp);
	book.AttachDispatch(lpDisp);
	sheets.AttachDispatch(book.GetWorksheets(), true);
	//sheet.AttachDispatch(sheets.GetItem(_variant_t(1)));
	//range.AttachDispatch(sheet.GetCells(), true);
	//range.AttachDispatch(sheet.GetRange(_variant_t("A4"), _variant_t("D6")), true);
	//range.SetColumnWidth(_variant_t((long)20));
	//range.AttachDispatch(sheet.GetRange(_variant_t("A4"), _variant_t("D6")), true);
	//range.SetRowHeight(_variant_t((long)25));
	//range.AttachDispatch(sheet.GetRange(_variant_t("A4"), _variant_t("D4")), true);
	//range.Merge(_variant_t((long)0));
	//range.SetItem(_variant_t((LONG)1), _variant_t((LONG)1), _variant_t("测试成绩三率统计(全体)"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)1), _variant_t("项目"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)2), _variant_t("优秀"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)3), _variant_t("及格"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)4), _variant_t("低分"));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)1), _variant_t("比率(%)"));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)2), _variant_t((double)(pinfos->exellentpct)));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)3), _variant_t((double)(pinfos->passpct)));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)4), _variant_t((double)(pinfos->badpct)));
	//range.AttachDispatch(sheet.GetRange(_variant_t("A1"), _variant_t("E3")), true);
	//range.SetColumnWidth(_variant_t((long)20));
	//range.AttachDispatch(sheet.GetRange(_variant_t("A1"), _variant_t("E3")), true);
	//range.SetRowHeight(_variant_t((long)25));
	//range.AttachDispatch(sheet.GetRange(_variant_t("A1"), _variant_t("E1")), true);
	//range.Merge(_variant_t((long)0));
	//range.SetItem(_variant_t((LONG)1), _variant_t((LONG)1), _variant_t("测试成绩概况(全体)"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)1), _variant_t("项目"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)2), _variant_t("样本数"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)3), _variant_t("平均量"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)4), _variant_t("极差"));
	//range.SetItem(_variant_t((LONG)2), _variant_t((LONG)5), _variant_t("标准差"));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)1), _variant_t("数值"));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)2), _variant_t((long)(pinfos->size)));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)3), _variant_t((double)(pinfos->averagescr)));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)4), _variant_t((double)(pinfos->firstobjectscr - pinfos->lastobjectscr)));
	//range.SetItem(_variant_t((LONG)3), _variant_t((LONG)5), _variant_t((double)(pinfos->rmsscr)));
	//sheet.SetName(L"全体情况");
	//sheet.DetachDispatch();
	sheet.AttachDispatch(sheets.Add(covOptional, covOptional, _variant_t(1), covOptional));
	sheet.SetName(L"仓库概况");
	range.AttachDispatch(sheet.GetCells(), true);
	range.AttachDispatch(sheet.GetRange(_variant_t("A1"), _variant_t("I1")), true);
	range.Merge(_variant_t((long)0));
	range.SetItem(_variant_t((LONG)1), _variant_t((LONG)1), _variant_t("货物清单(全部货物)"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)1), _variant_t("货物"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)2), _variant_t("数量"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)3), _variant_t("入库日期"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)4), _variant_t("所在货架"));
	long cl = 0;
	for (long j = 0; j < GROUPSIZE; j++)
	{
		if (pinfos->groups[j].existst == 1)
		{
			range.SetItem(_variant_t((LONG)3 + cl), _variant_t((LONG)1), _variant_t(pinfos->groups[j].name));
			range.SetItem(_variant_t((LONG)3 + cl), _variant_t((LONG)2), _variant_t(pinfos->groups[j].type == 1 ? "必须参加" : "选择参加"));
			range.SetItem(_variant_t((LONG)3 + cl), _variant_t((LONG)3), _variant_t(pinfos->groups[j].size));
			range.SetItem(_variant_t((LONG)3 + cl), _variant_t((LONG)4), _variant_t(pinfos->groups[j].averagescr));
			cl++;
		}
	}
	//range.AttachDispatch(sheet.GetCells(), true);
	range.SetHorizontalAlignment(_variant_t((long)-4108));
	range.SetVerticalAlignment(_variant_t((long)-4108));
	double left = 450, top = 10, width = 450, height = 260;
	_Chart chart;
	ChartObjects chartobjects;
	ChartObject chartobject;
	lpDisp = sheet.ChartObjects(covOptional);
	ASSERT(lpDisp);
	chartobjects.AttachDispatch(lpDisp);
	chartobject = chartobjects.Add(left, top, width, height);
	chart.AttachDispatch(chartobject.GetChart());
	chart.SetChartType(72);
	lpDisp = sheet.GetRange(range.GetItem(_variant_t(2), _variant_t(7)), range.GetItem(_variant_t(3 + cl - 1), _variant_t(9)));
	ASSERT(lpDisp);
	VARIANT var;
	var.vt = VT_DISPATCH;
	var.pdispVal = lpDisp;
	chart.ChartWizard(var,
		COleVariant((short)51),
		covOptional,
		COleVariant((short)1),
		covOptional,
		COleVariant((short)0),
		COleVariant((short)TRUE),
		COleVariant(L"三率统计(全部群体)"),
		covOptional,
		COleVariant(L"比率(%)"),
		covOptional);
	book.Save();
	sheet.SetName(L"全部群体");
	if (item == IDYES)
	{
		app.SetDisplayAlerts(false);
		app.Quit();
	}
	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	app.ReleaseDispatch();
	return;
}

EXCEL_API void setInfo(std::vector<std::string> goods, std::vector<int> count, std::vector<Time> date, std::vector<int> shelf)
{
	internalGoods = goods;
	internalCount = count;
	internalDate = date;
	internalShelf = shelf;
}
