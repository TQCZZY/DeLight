extern "C" __declspec(dllimport) void eccEncEx(const char* fn, const char* pswfn, const char* c_p, const char* c_a, const char* c_gx, const char* c_gy, const char* c_qx, const char* c_qy);
extern "C" __declspec(dllimport) void eccDecEx(const char* fn, const char* c_p, const char* c_a, const char* c_k);
extern "C" __declspec(dllimport) void eccEnc(const char* fn, const char* pswfn);
extern "C" __declspec(dllimport) void eccDec(const char* fn, const char* pswfn);
extern "C" __declspec(dllimport) int qmcPreDec(uint8_t * block, size_t blockSize, const char* type);
extern "C" __declspec(dllimport) size_t qmcDecBlock(uint8_t * block, size_t blockSize, size_t offset);
extern "C" __declspec(dllimport) int qmcPreEnc(uint8_t * block, size_t blockSize, const char* type);
extern "C" __declspec(dllimport) size_t qmcEncBlock(uint8_t * block, size_t blockSize, size_t offset);
extern "C" __declspec(dllimport) void qmcGetErr(char* error);
#pragma comment(lib,"EncryptionDll.lib")
