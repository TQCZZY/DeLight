#include <string.h>
#include <cmath>
#include <vector>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include "qmc_key.hpp"
#include "qmc_cipher.hpp"

class QmcDecode {
private:
    std::vector<uint8_t> blockData;

    std::vector<uint8_t> rawKeyBuf;
    std::string cipherType = "";

    size_t dataOffset = 0;
    size_t keySize = 0;
    int mediaVer = 0;

    std::string checkType(std::string type) {
        if (type == "normal")
        {
            std::string buf_tag = "";
            for (int i = 4; i > 0; --i)
            {
                buf_tag += *((char*)blockData.data() + blockData.size() - i);
            }
            if (buf_tag == "QTag")
            {
                keySize = ntohl(*(uint32_t*)(blockData.data() + blockData.size() - 8));
                return "QTag";
            }
            else if (buf_tag == "STag")
            {
               return "STag";
            }
            else
            {
                keySize = (*(uint32_t*)(blockData.data() + blockData.size() - 4));
                if (keySize < 0x400)
                {
                    return "Map/RC4";
                }
                else
                {
                    keySize = 0;
                    return "Static";
                }
            }
        }
        else if (type == "cache" || type == "ios")
        {
            return type;
        }
        else
        {
            return "invalid";
        }
    }

    bool parseRawKeyQTag() {
        std::string ketStr = "";
        std::string::size_type index = 0;
        ketStr.append((char*)rawKeyBuf.data(), rawKeyBuf.size());
        index = ketStr.find(",", 0);
        if (index != std::string::npos)
        {
            rawKeyBuf.resize(index);
        }
        else
        {
            return false;
        }
        ketStr = ketStr.substr(index + 1);
        index = ketStr.find(",", 0);
        if (index != std::string::npos)
        {
            this->sId = ketStr.substr(0, index);
        }
        else
        {
            return false;
        }
        ketStr = ketStr.substr(index + 1);
        index = ketStr.find(",", 0);
        if (index == std::string::npos)
        {
            this->mediaVer = std::stoi(ketStr);
        }
        else
        {
            return false;
        }
        return true;
    }

    bool readRawKey(size_t tailSize) {
        // get raw key data length
        rawKeyBuf.resize(keySize);
        if (rawKeyBuf.size() != keySize) {
            return false;
        }
        for (size_t i = 0; i < keySize; i++)
        {
            rawKeyBuf[i] = blockData[i + blockData.size() - (tailSize + keySize)];
        }
        return true;
    }

    void DecodeStatic();

    void DecodeMapRC4();

    void DecodeCache();

    void DecodeTm();

public:
    bool SetBlock(uint8_t* block, size_t blockSize) {
        blockData.resize(blockSize);
        if (blockData.size() != blockSize) {
            return false;
        }
        memcpy(blockData.data(), block, blockSize);
        return true;
    }
    
    int PreDecode(std::string type) {
        cipherType = checkType(type);
        size_t tailSize = 0;
        if (cipherType == "QTag") {
            tailSize = 8;
        }
        else if (cipherType == "Map/RC4") {
            tailSize = 4;
        }
        if (tailSize > 0) {
            if (!readRawKey(tailSize)) {
                error = "cannot read embedded key from file";
                return -1;
            }
            if (tailSize == 8) {
                cipherType = "Map/RC4";
                if (!parseRawKeyQTag()) {
                    error = "cannot parse embedded key";
                    return -1;
                }
            }
            std::vector<uint8_t> tmp;
            if (!QmcDecryptKey(rawKeyBuf, tmp)) {
                error = "cannot decrypt embedded key";
                return -1;
            }
            rawKeyBuf = tmp;
        }
        if (cipherType == "invalid") {
            error = "file is invalid or not supported(Please downgrade your app.)";
            return -1;
        }
        return keySize + tailSize;
    }

    std::vector<uint8_t> Decode(size_t offset);

    std::string sId = "";
    std::string error = "";
};

void QmcDecode::DecodeStatic()
{
    QmcStaticCipher sc;
    sc.proc(blockData, dataOffset);
}

void QmcDecode::DecodeMapRC4() {
    if (rawKeyBuf.size() > 300)
    {
        QmcRC4Cipher c(rawKeyBuf);
        c.proc(blockData, dataOffset);
    }
    else
    {
        QmcMapCipher c(rawKeyBuf);
        c.proc(blockData, dataOffset);
    }
}

void QmcDecode::DecodeCache()
{
    for (size_t i = 0; i < blockData.size(); i++) {
        blockData[i] ^= 0xf4;
        blockData[i] = ((blockData[i] & 0b00111111) << 2) | (blockData[i] >> 6); // rol 2
    }
}

void QmcDecode::DecodeTm()
{
    uint8_t const TM_HEADER[] = { 0x00, 0x00, 0x00, 0x20, 0x66, 0x74, 0x79, 0x70 };
    for (size_t cur = dataOffset, i = 0; cur < 8 && i < blockData.size(); ++cur, ++i) {
        blockData[i] = TM_HEADER[dataOffset];
    }
}

std::vector<uint8_t> QmcDecode::Decode(size_t offset)
{
    dataOffset = offset;
    if (cipherType == "Map/RC4")
    {
        DecodeMapRC4();
    }
    else if (cipherType == "Static")
    {
        DecodeStatic();
    }
    else if (cipherType == "cache")
    {
        DecodeCache();
    }
    else if (cipherType == "ios")
    {
        DecodeTm();
    }
    else {
        error = "File is invalid or encryption type is not supported.";
    }
    return blockData;
}

class QmcEncode {
private:
    std::vector<uint8_t> blockData;

    std::vector<uint8_t> rawKeyBuf;
    std::string cipherType = "";
    size_t dataOffset = 0;

    bool genRawKey() {
        const char WordList[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        srand(time(0));
        uint32_t number = 0;
        if (cipherType == "QTag") {
            rand() % 2 ? cipherType = "Map" : cipherType = "RC4";
        }
        if (cipherType == "Map") {
            while (number > 300 || number == 0)
            {
                number = rand();
            }
        }
        else if (cipherType == "RC4") {
            while (number <= 300 || number >= 512)
            {
                number = rand();
            }
        }
        else {
            return false;
        }
        rawKeyBuf.resize(number);
        for (int i = 0; i < rawKeyBuf.size(); i++) {
            number = rand();
            rawKeyBuf[i] = WordList[number % 62];
        }
        return true;
    }

    void EncodeStatic();

    void EncodeMapRC4();

    void EncodeCache();

    void EncodeTm();

public:
    bool SetBlock(uint8_t* block, size_t blockSize) {
        blockData.resize(blockSize);
        if (blockData.size() != blockSize) {
            return false;
        }
        memcpy(blockData.data(), block, blockSize);
        return true;
    }

    std::vector<uint8_t> PreEncode(std::string type) {
        cipherType = type;
        if (cipherType != "Static" &&
            cipherType != "Map" &&
            cipherType != "RC4" &&
            cipherType != "cache" &&
            cipherType != "ios") {
            error = "type is invalid";
            return std::vector<uint8_t>{};
        }
        size_t tailSize = 0;
        if (cipherType == "QTag") {
            tailSize = 8;
        }
        else if (cipherType == "Map" || cipherType == "RC4") {
            tailSize = 4;
        }
        if (tailSize > 0) {
            if (!genRawKey())
            {
                std::cout << "Key generating failed." << std::endl;
                return std::vector<uint8_t>{};
            }
            std::vector<uint8_t> tmp;
            if (!QmcEncryptKey(rawKeyBuf, tmp, rand() % 2))
            {
                error = "Key encryption failed.";
                return std::vector<uint8_t>{};
            }
            rawKeyBuf = tmp;
            if (tailSize == 8) {
                rawKeyBuf.push_back(',');
                rawKeyBuf.push_back('0');
                rawKeyBuf.push_back(',');
                rawKeyBuf.push_back('2');
            }
            if (tailSize == 8)
            {
                uint32_t sizeNet = htonl((uint32_t)rawKeyBuf.size());
                rawKeyBuf.push_back(*((uint8_t*)&sizeNet));
                rawKeyBuf.push_back(*(((uint8_t*)&sizeNet) + 1));
                rawKeyBuf.push_back(*(((uint8_t*)&sizeNet) + 2));
                rawKeyBuf.push_back(*(((uint8_t*)&sizeNet) + 3));
                rawKeyBuf.push_back('Q');
                rawKeyBuf.push_back('T');
                rawKeyBuf.push_back('a');
                rawKeyBuf.push_back('g');
            }
            else
            {
                uint32_t size = rawKeyBuf.size();
                rawKeyBuf.push_back(*((uint8_t*)&size));
                rawKeyBuf.push_back(*(((uint8_t*)&size) + 1));
                rawKeyBuf.push_back(*(((uint8_t*)&size) + 2));
                rawKeyBuf.push_back(*(((uint8_t*)&size) + 3));
            }
        }
        return rawKeyBuf;
    }

    std::vector<uint8_t> Encode(size_t offset);

    std::string error = "";
};

void QmcEncode::EncodeStatic()
{
    QmcStaticCipher sc;
    sc.proc(blockData, dataOffset);
}

void QmcEncode::EncodeMapRC4() {
    if (cipherType == "RC4")
    {
        QmcRC4Cipher c(rawKeyBuf);
        c.proc(blockData, dataOffset);
    }
    else
    {
        QmcMapCipher c(rawKeyBuf);
        c.proc(blockData, dataOffset);
    }
}

void QmcEncode::EncodeCache()
{
    for (size_t i = 0; i < blockData.size(); i++) {
        blockData[i] = (blockData[i] >> 2) | (blockData[i] << 6); // rol 2
        blockData[i] ^= 0xf4;
    }
}

void QmcEncode::EncodeTm()
{
    srand(time(0));
    for (size_t cur = 0; cur < 8 - dataOffset; cur++) {
        blockData[cur] = rand();
    }
}

std::vector<uint8_t> QmcEncode::Encode(size_t offset)
{
    dataOffset = offset;
    if (cipherType == "Map" || cipherType == "RC4")
    {
        EncodeMapRC4();
    }
    else if (cipherType == "Static")
    {
        EncodeStatic();
    }
    else if (cipherType == "cache")
    {
        EncodeCache();
    }
    else if (cipherType == "ios")
    {
        EncodeTm();
    }
    else {
        error = "File is invalid or encryption type is not supported.";
    }
    return blockData;
}
