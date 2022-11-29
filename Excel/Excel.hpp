// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 EXCEL_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// EXCEL_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef EXCEL_EXPORTS
#define EXCEL_API __declspec(dllexport)
#else
#define EXCEL_API __declspec(dllimport)
#endif

EXCEL_API void global2Excel(CString PathName, bool AutoQuit = false, bool ReadOnly = false, CString Password = L"", CString WriteResPassword = L"");
EXCEL_API void singleGoods2Excel(CString PathName, bool AutoQuit = false, bool ReadOnly = false, CString Password = L"", CString WriteResPassword = L"");
EXCEL_API void shelf2Excel(CString PathName, bool AutoQuit = false, bool ReadOnly = false, CString Password = L"", CString WriteResPassword = L"");
EXCEL_API void specDate2Excel(CString PathName, bool AutoQuit = false, bool ReadOnly = false, CString Password = L"", CString WriteResPassword = L"");
EXCEL_API void setInfo(std::vector<std::string> goods, std::vector<int> count, std::vector<Time> date, std::vector<int> shelf);
#pragma comment(lib,"Excel.lib")
