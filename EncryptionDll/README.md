# DeLight
## Encryption

Encryption & Decryption Dynamic Link Library

# How to use
```
Other operations
1: Place the EncryptionDll.lib in yout project directory
2: Add `#include "EncryptionDll.hpp"` to your source
Other operations
```

# Functions
## File Encryption (Using Elliptic Curve Cryptography)
Name | Usage | Params
------------ | ------------- | -------------
eccEnc | Encrypt, Simple | Param1 (const char* fn): Name of file to encrypt<br>Param2 (const char* pswfn): Name of file that stores the key
eccDec | Decrypt, Simple | Param1 (const char* fn): Name of file to decrypt<br>Param2 (const char* pswFn): Name of file that stores the key
eccEncEx | Encrypt, Extended(Decimal Curve Props As Params) | Param1 (const char* fn) & Param2 (const char* pswfn): see eccEnc<br>Param3 (const char* c_p): Limited Field<br>Param4 (const char* c_a): Curve Coefficient A<br>Param5 (const char* c_gx): X Coordinate Of Base Point<br>Param6 (const char* c_gy): Y Coordinate Of Base Point<br>Param7 (const char* c_qx): X Coordinate Of Public Key<br>Param8 (const char* c_qy): Y Coordinate Of Public Key
eccDecEx | Decrypt, Extended(Decimal Curve Props As Params) | Param1 (const char* fn): see eccDec<br>Param2 (const char* c_p): Limited Field<br>Param3 (const char* c_a): Curve Coefficient A<br>Param4 (const char* c_k): Private Key
## Memory Encryption (Using QQMusic EncV2 Cryptography)
Name | Usage | Params
------------ | ------------- | -------------
qmcEncBlock | Encrypt | Param1 (uint8_t * block): Buffer To Encrypt<br>Param2 (size_t blockSize): Bytes Of The Given Buffer<br>Param3 (size_t offset): Offset Of The Given Block From The Beginning Of The Whole Plain Memory
qmcDecBlock | Decrypt | Param1 (uint8_t * block): Buffer To Decrypt<br>Param2 (size_t blockSize): Bytes Of The Given Buffer<br>Param3 (size_t offset): Offset Of The Given Block From The Beginning Of The Whole Cipher Memory
qmcPreEnc | Encrypt Preparations | Param1 (uint8_t * block): Empty Buffer For Key Storage<br>Param2 (size_t blockSize): Bytes Of The Given Buffer<br>Param3 (const char* type): Encryption type("Map"/"RC4"/"QTag"/"Static"/"cache"/"ios", Case-sensitive)
qmcPreDec | Decrypt Preparations | Param1 (uint8_t * block): A Buffer Containing The Key<br>Param2 (size_t blockSize): Bytes Of The Given Buffer<br>Param3 (const char* type): Decryption type("normal"/"cache"/"ios", Case-sensitive)
qmcGetErr | Get Error | Param (char* error): Empty Buffer To Store Error Message
