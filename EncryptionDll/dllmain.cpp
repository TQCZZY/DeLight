// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "fstream"
#include <thread>
#include "Shlwapi.h"
#pragma comment(lib, "Shlwapi.lib")

//#define DEBUG
#include "Ecc.hpp"

#include "qmc.hpp"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

extern "C" __declspec(dllexport) void eccEncEx(const char* fn, const char* pswfn, const char* c_p, const char* c_a, const char* c_gx, const char* c_gy, const char* c_qx, const char* c_qy)
{
	Ecc(fn, pswfn, c_p, c_a, c_gx, c_gy, c_qx, c_qy);
}

extern "C" __declspec(dllexport) void eccDecEx(const char* fn, const char* c_p, const char* c_a, const char* c_k)
{
	Ecc(fn, c_p, c_a, c_k);
}

extern "C" __declspec(dllexport) void eccEnc(const char* fn, const char* pswfn)
{
	Ecc(fn, pswfn, "", "", "", "", "", "");
}

extern "C" __declspec(dllexport) void eccDec(const char* fn, const char* pswfn)
{
	string p = "";
	string a = "";
	string k = "";
	fstream fk(pswfn, ios::in);
	fk >> p >> p >> a >> a >> k >> k;
	fk.close();

	Ecc(fn, p.c_str(), a.c_str(), k.c_str());
}

std::string err = "";
std::string sid = "";
QmcDecode d;
QmcEncode e;

extern "C" __declspec(dllexport) int qmcPreDec(uint8_t * block, size_t blockSize, const char* type)
{
    if (!d.SetBlock(block, blockSize))
    {
        err = "cannot allocate memory";
        return -1;
    }
    int tailSize = d.PreDecode(type);
    if (d.error != "")
    {
        err = d.error;
        d.error = "";
        return -1;
    }
    sid = d.sId;
    return tailSize;
}

extern "C" __declspec(dllexport) size_t qmcDecBlock(uint8_t* block, size_t blockSize, size_t offset)
{
    if (!d.SetBlock(block, blockSize))
    {
        err = "cannot allocate memory";
        return 0;
    }
    std::vector<uint8_t> decData = d.Decode(offset);
    if (d.error != "")
    {
        err = d.error;
        d.error = "";
        return 0;
    }
    memcpy(block, decData.data(), decData.size());
    return decData.size();
}

extern "C" __declspec(dllexport) int qmcPreEnc(uint8_t * block, size_t blockSize, const char* type)
{
    std::vector<uint8_t> tail = e.PreEncode(type);
    if (e.error != "")
    {
        err = e.error;
        e.error = "";
        return -1;
    }
    memcpy(block, tail.data(), tail.size());
    return tail.size();
}

extern "C" __declspec(dllexport) size_t qmcEncBlock(uint8_t * block, size_t blockSize, size_t offset)
{
    if (!e.SetBlock(block, blockSize))
    {
        err = "cannot allocate memory";
        return 0;
    }
    std::vector<uint8_t> encData = e.Encode(offset);
    if (e.error != "")
    {
        err = e.error;
        e.error = "";
        return 0;
    }
    memcpy(block, encData.data(), encData.size());
    return encData.size();
}

extern "C" __declspec(dllexport) void qmcGetErr(char* error)
{
    strcpy(error, err.c_str());
    return;
}
