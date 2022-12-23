
// PswDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "DeLight.h"
#include "PswDlg.h"
#include "afxdialogex.h"
#include <iomanip>
#include <windows.h>
#include <wincrypt.h>
#include <string>
#include <sstream>
#include <fstream>
#include "json.h"

std::string GetMD5Hash(const std::string& str)
{
    // Initialize the CryptoAPI library
    HCRYPTPROV hCryptProv = 0;
    if (!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
    {
        return "Error initializing the CryptoAPI library";
    }

    // Create a handle to a hash object
    HCRYPTHASH hHash = 0;
    if (!CryptCreateHash(hCryptProv, CALG_MD5, 0, 0, &hHash))
    {
        CryptReleaseContext(hCryptProv, 0);
        return "Error creating hash object";
    }

    // Calculate the hash of the string
    if (!CryptHashData(hHash, (BYTE*)str.c_str(), str.length(), 0))
    {
        CryptDestroyHash(hHash);
        CryptReleaseContext(hCryptProv, 0);
        return "Error calculating hash";
    }

    // Get the hash value
    DWORD dwHashLen = 16; // MD5 hash is 16 bytes long
    BYTE hash[16];
    if (!CryptGetHashParam(hHash, HP_HASHVAL, hash, &dwHashLen, 0))
    {
        CryptDestroyHash(hHash);
        CryptReleaseContext(hCryptProv, 0);
        return "Error getting hash value";
    }

    // Convert the hash value to a string
    std::stringstream ss;
    for (DWORD i = 0; i < dwHashLen; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    // Clean up
    CryptDestroyHash(hHash);
    CryptReleaseContext(hCryptProv, 0);

    return ss.str(); // length is 32 if ok
}

#define CHKPSW_OK 0
#define CHKPSW_WRONG_PSW 1
#define CHKPSW_NO_USER 2
#define CHKPSW_JSON_ERROR 3
std::pair<int, std::string> CheckPsw(std::string username, std::string password)
{
    std::ifstream file("security.json");

    // Parse the JSON document
    Json::Value root;
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;
    if (!parseFromStream(builder, file, &root, &errs))
    {
        return { CHKPSW_JSON_ERROR, "Error parsing JSON file: " + errs };
    }
    file.close();

    // Check if the username key doesn't exist
    if (root[username].isNull())
    {
        return { CHKPSW_NO_USER, "The username does not exist" };
    }
    // Access the string values
    if (password == root[username]["login_hash"].asString())
    {
        return { CHKPSW_OK, "" };
    }
    return { CHKPSW_WRONG_PSW, "Your username or password is incorrect" };
}
std::string SetPsw(std::string username, std::string password)
{
    std::ifstream file("security.json");

    // Parse the JSON document
    Json::Value root;
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;
    if (!parseFromStream(builder, file, &root, &errs))
    {
        return "Error parsing JSON file: " + errs;
    }
    file.close();

    // Access the string values
    root[username]["login_hash"] = password;

    // Open the output file
    std::ofstream output("security.json");

    // Write the modified JSON data to the file
    Json::StreamWriterBuilder writerBuilder;
    writerBuilder["indentation"] = "\t";
    std::unique_ptr<Json::StreamWriter> writer(writerBuilder.newStreamWriter());
    writer->write(root, &output);
    output.close();
    return "";
}

// PswDlg 对话框

PswDlg::PswDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PSW_DIALOG, pParent)
{
}

void PswDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(PswDlg, CDialogEx)
	ON_BN_CLICKED(IDC_PSWDLG_LGN, &PswDlg::OnBnClickedButtonLgn)
END_MESSAGE_MAP()

// PswDlg 消息处理程序

void PswDlg::OnBnClickedButtonLgn()
{
	CString sun, spwd;//sun为uname,spwd为password
	GetDlgItemText(IDC_PSWDLG_UNAME,sun);
	GetDlgItemText(IDC_PSWDLG_PWD,spwd);
    if (!PathFileExists(L"security.json"))
    {
        Json::Value root;

        // Open the output file
        std::ofstream output("security.json");

        // Write the JSON data to the file
        Json::StreamWriterBuilder writerBuilder;
        writerBuilder["indentation"] = "\t";
        std::unique_ptr<Json::StreamWriter> writer(writerBuilder.newStreamWriter());
        writer->write(root, &output);
        output.close();
    }
    USES_CONVERSION;
    auto chkRes = CheckPsw(W2A(sun), GetMD5Hash(W2A(spwd)));
    if (chkRes.first != CHKPSW_OK)
    {
        if (chkRes.first == CHKPSW_NO_USER)
        {
            std::string err = SetPsw(W2A(sun), GetMD5Hash(W2A(spwd)));
            if (err != "")
            {
                MessageBox(A2W(err.c_str()), L"注册失败", MB_ICONINFORMATION);//用户登录
            }
            else
            {
                MessageBox(L"DeLight已完成" + sun + L"的注册，请验证密码以登录", L"完成注册", MB_ICONINFORMATION);//用户登录
                SetDlgItemText(IDC_PSWDLG_PWD, L"");
            }
        }
        else
        {
            MessageBox(A2W(chkRes.second.c_str()), L"登录失败", MB_ICONERROR);//用户登录
        }
    }
    else
    {
        CDialog::OnOK();
    }
}

BOOL PswDlg::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
    {
        return TRUE;
    }
    if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
    {
        OnBnClickedButtonLgn();
        return TRUE;
    }
    return CDialogEx::PreTranslateMessage(pMsg);
}
