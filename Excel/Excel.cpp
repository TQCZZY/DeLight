// Excel.cpp : 定义 DLL 的导出函数。
//

#include "pch.h"
#include "afx.h"
#include "afxwin.h"
#include "comutil.h"
#include "afxdisp.h"
#include "callexcel.h"
#include <vector>
#include <string>

#define EXCEL_EXPORTS
#include "Excel.hpp"

std::vector<std::string> internalGoods;
std::vector<std::string> internalCount;
std::vector<std::string> internalDate;
std::vector<std::string> internalShelf;

EXCEL_API void global2Excel(CString PathName, bool AutoQuit, bool ReadOnly, CString Password, CString WriteResPassword)
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
	app.SetVisible(!AutoQuit);
	books.AttachDispatch(app.GetWorkbooks(), true);
	lpDisp = books.Open(PathName, covOptional, _variant_t(ReadOnly),
		covOptional, Password == L"" ? covOptional : _variant_t(Password),
		WriteResPassword == L"" ? covOptional : _variant_t(WriteResPassword),
		covOptional, covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional);
	ASSERT(lpDisp);
	book.AttachDispatch(lpDisp);
	sheets.AttachDispatch(book.GetWorksheets(), true);
	sheet.AttachDispatch(sheets.Add(covOptional, covOptional, _variant_t(1), covOptional));
	sheet.SetName(L"仓库概况");
	range.AttachDispatch(sheet.GetCells(), true);
	range.AttachDispatch(sheet.GetRange(_variant_t("A1"), _variant_t("D1")), true);
	range.Merge(_variant_t((long)0));
	range.SetItem(_variant_t((LONG)1), _variant_t((LONG)1), _variant_t("货物清单(全部货物)"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)1), _variant_t("货物"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)2), _variant_t("数量"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)3), _variant_t("入库日期"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)4), _variant_t("所在货架"));
	for (long i = 0; i < internalCount.size(); i++)
	{
		range.SetItem(_variant_t((LONG)3 + i), _variant_t((LONG)1), _variant_t((internalGoods[i]+" - "+ internalShelf[i]).c_str()));
		range.SetItem(_variant_t((LONG)3 + i), _variant_t((LONG)2), _variant_t(internalCount[i].c_str()));
		range.SetItem(_variant_t((LONG)3 + i), _variant_t((LONG)3), _variant_t(internalDate[i].c_str()));
		range.SetItem(_variant_t((LONG)3 + i), _variant_t((LONG)4), _variant_t(internalShelf[i].c_str()));
	}
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
	lpDisp = sheet.GetRange(range.GetItem(_variant_t(3), _variant_t(1)), range.GetItem(_variant_t(2 + internalCount.size()), _variant_t(2)));
	ASSERT(lpDisp);
	VARIANT var;
	var.vt = VT_DISPATCH;
	var.pdispVal = lpDisp;
	chart.ChartWizard(var,
		COleVariant((short)51),
		covOptional,
		COleVariant((short)2),
		covOptional,
		COleVariant((short)0),
		COleVariant((short)TRUE),
		COleVariant(L"货物数量统计(全部货物)"),
		COleVariant(L"货物"),
		COleVariant(L"数量"),
		covOptional);
	book.Save();
	if (AutoQuit)
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

EXCEL_API void singleGoods2Excel(CString PathName, bool AutoQuit, bool ReadOnly, CString Password, CString WriteResPassword)
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
	app.SetVisible(!AutoQuit);
	books.AttachDispatch(app.GetWorkbooks(), true);
	lpDisp = books.Open(PathName, covOptional, _variant_t(ReadOnly),
		covOptional, Password == L"" ? covOptional : _variant_t(Password),
		WriteResPassword == L"" ? covOptional : _variant_t(WriteResPassword),
		covOptional, covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional);
	ASSERT(lpDisp);
	book.AttachDispatch(lpDisp);
	sheets.AttachDispatch(book.GetWorksheets(), true);
	sheet.AttachDispatch(sheets.Add(covOptional, covOptional, _variant_t(1), covOptional));
	USES_CONVERSION;
	sheet.SetName(A2W(("单个货物 " + internalGoods[0]).c_str()));
	range.AttachDispatch(sheet.GetCells(), true);
	range.AttachDispatch(sheet.GetRange(range.GetItem(_variant_t(3), _variant_t(1)), range.GetItem(_variant_t(2 + internalCount.size()), _variant_t(1))), true);
	range.Merge(_variant_t((long)0));
	range.AttachDispatch(sheet.GetRange(_variant_t("A1"), _variant_t("D1")), true);
	range.Merge(_variant_t((long)0));
	range.SetItem(_variant_t((LONG)1), _variant_t((LONG)1), _variant_t("货物清单(单个货物)"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)1), _variant_t("货物"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)2), _variant_t("所在货架"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)3), _variant_t("数量"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)4), _variant_t("入库日期"));
	range.SetItem(_variant_t((LONG)3), _variant_t((LONG)1), _variant_t(internalGoods[0].c_str()));
	for (long i = 0; i < internalCount.size(); i++)
	{
		range.SetItem(_variant_t((LONG)3 + i), _variant_t((LONG)2), _variant_t(internalShelf[i].c_str()));
		range.SetItem(_variant_t((LONG)3 + i), _variant_t((LONG)3), _variant_t(internalCount[i].c_str()));
		range.SetItem(_variant_t((LONG)3 + i), _variant_t((LONG)4), _variant_t(internalDate[i].c_str()));
	}
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
	lpDisp = sheet.GetRange(range.GetItem(_variant_t(3), _variant_t(2)), range.GetItem(_variant_t(2 + internalCount.size()), _variant_t(3)));
	ASSERT(lpDisp);
	VARIANT var;
	var.vt = VT_DISPATCH;
	var.pdispVal = lpDisp;
	chart.ChartWizard(var,
		COleVariant((short)51),
		covOptional,
		COleVariant((short)2),
		covOptional,
		COleVariant((short)0),
		COleVariant((short)TRUE),
		COleVariant(L"货物数量统计(单个货物)"),
		COleVariant(L"货架"),
		COleVariant(L"数量"),
		covOptional);
	book.Save();
	if (AutoQuit)
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

EXCEL_API void shelf2Excel(CString PathName, bool AutoQuit, bool ReadOnly, CString Password, CString WriteResPassword)
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
	app.SetVisible(!AutoQuit);
	books.AttachDispatch(app.GetWorkbooks(), true);
	lpDisp = books.Open(PathName, covOptional, _variant_t(ReadOnly),
		covOptional, Password == L"" ? covOptional : _variant_t(Password),
		WriteResPassword == L"" ? covOptional : _variant_t(WriteResPassword),
		covOptional, covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional);
	ASSERT(lpDisp);
	book.AttachDispatch(lpDisp);
	sheets.AttachDispatch(book.GetWorksheets(), true);
	sheet.AttachDispatch(sheets.Add(covOptional, covOptional, _variant_t(1), covOptional));
	USES_CONVERSION;
	sheet.SetName(A2W(("货架概况 " + internalShelf[0]).c_str()));
	range.AttachDispatch(sheet.GetCells(), true);
	range.AttachDispatch(sheet.GetRange(range.GetItem(_variant_t(3), _variant_t(1)), range.GetItem(_variant_t(2 + internalCount.size()), _variant_t(1))), true);
	range.Merge(_variant_t((long)0));
	range.AttachDispatch(sheet.GetRange(_variant_t("A1"), _variant_t("D1")), true);
	range.Merge(_variant_t((long)0));
	range.SetItem(_variant_t((LONG)1), _variant_t((LONG)1), _variant_t("货物清单(单个货架)"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)1), _variant_t("货架"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)2), _variant_t("货物"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)3), _variant_t("数量"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)4), _variant_t("入库日期"));
	range.SetItem(_variant_t((LONG)3), _variant_t((LONG)1), _variant_t(internalShelf[0].c_str()));
	for (long i = 0; i < internalCount.size(); i++)
	{
		range.SetItem(_variant_t((LONG)3 + i), _variant_t((LONG)2), _variant_t(internalGoods[i].c_str()));
		range.SetItem(_variant_t((LONG)3 + i), _variant_t((LONG)3), _variant_t(internalCount[i].c_str()));
		range.SetItem(_variant_t((LONG)3 + i), _variant_t((LONG)4), _variant_t(internalDate[i].c_str()));
	}
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
	lpDisp = sheet.GetRange(range.GetItem(_variant_t(3), _variant_t(2)), range.GetItem(_variant_t(2 + internalCount.size()), _variant_t(3)));
	ASSERT(lpDisp);
	VARIANT var;
	var.vt = VT_DISPATCH;
	var.pdispVal = lpDisp;
	chart.ChartWizard(var,
		COleVariant((short)51),
		covOptional,
		COleVariant((short)2),
		covOptional,
		COleVariant((short)0),
		COleVariant((short)TRUE),
		COleVariant(L"货物数量统计(单个货架)"),
		COleVariant(L"货物"),
		COleVariant(L"数量"),
		covOptional);
	book.Save();
	if (AutoQuit)
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

EXCEL_API void specDate2Excel(CString PathName, bool AutoQuit, bool ReadOnly, CString Password, CString WriteResPassword)
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
	app.SetVisible(!AutoQuit);
	books.AttachDispatch(app.GetWorkbooks(), true);
	lpDisp = books.Open(PathName, covOptional, _variant_t(ReadOnly),
		covOptional, Password == L"" ? covOptional : _variant_t(Password),
		WriteResPassword == L"" ? covOptional : _variant_t(WriteResPassword),
		covOptional, covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional);
	ASSERT(lpDisp);
	book.AttachDispatch(lpDisp);
	sheets.AttachDispatch(book.GetWorksheets(), true);
	sheet.AttachDispatch(sheets.Add(covOptional, covOptional, _variant_t(1), covOptional));
	USES_CONVERSION;
	sheet.SetName(A2W(("入库清单 " + internalDate[0]).c_str()));
	range.AttachDispatch(sheet.GetCells(), true);
	range.AttachDispatch(sheet.GetRange(range.GetItem(_variant_t(3), _variant_t(1)), range.GetItem(_variant_t(2 + internalCount.size()), _variant_t(1))), true);
	range.Merge(_variant_t((long)0));
	range.AttachDispatch(sheet.GetRange(_variant_t("A1"), _variant_t("D1")), true);
	range.Merge(_variant_t((long)0));
	range.SetItem(_variant_t((LONG)1), _variant_t((LONG)1), _variant_t("货物清单(单日入库)"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)1), _variant_t("入库日期"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)2), _variant_t("货物"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)3), _variant_t("数量"));
	range.SetItem(_variant_t((LONG)2), _variant_t((LONG)4), _variant_t("所在货架"));
	range.SetItem(_variant_t((LONG)3), _variant_t((LONG)1), _variant_t(internalDate[0].c_str()));
	for (long i = 0; i < internalCount.size(); i++)
	{
		range.SetItem(_variant_t((LONG)3 + i), _variant_t((LONG)1), _variant_t((internalGoods[i] + " - " + internalShelf[i]).c_str()));
		range.SetItem(_variant_t((LONG)3 + i), _variant_t((LONG)2), _variant_t(internalCount[i].c_str()));
		range.SetItem(_variant_t((LONG)3 + i), _variant_t((LONG)3), _variant_t(internalShelf[i].c_str()));
	}
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
	lpDisp = sheet.GetRange(range.GetItem(_variant_t(3), _variant_t(2)), range.GetItem(_variant_t(2 + internalCount.size()), _variant_t(3)));
	ASSERT(lpDisp);
	VARIANT var;
	var.vt = VT_DISPATCH;
	var.pdispVal = lpDisp;
	chart.ChartWizard(var,
		COleVariant((short)51),
		covOptional,
		COleVariant((short)2),
		covOptional,
		COleVariant((short)0),
		COleVariant((short)TRUE),
		COleVariant(L"货物数量统计(单日入库)"),
		COleVariant(L"货物"),
		COleVariant(L"数量"),
		covOptional);
	book.Save();
	if (AutoQuit)
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

EXCEL_API void setInfo(std::vector<std::string> goods, std::vector<std::string> count, std::vector<std::string> date, std::vector<std::string> shelf)
{
	internalGoods = goods;
	internalCount = count;
	internalDate = date;
	internalShelf = shelf;
}
