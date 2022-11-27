/*　1、用户A选定一条适合加密的椭圆曲线Ep(a,b)(如:y2=x3+ax+b)，并取椭圆曲线上一点，作为基点G。
　　2、用户A选择一个私有密钥k，并生成公开密钥K=kG。
　　3、用户A将Ep(a,b)和点K，G传给用户B。
　　4、用户B接到信息后 ，将待传输的明文编码到Ep(a,b)上一点M，并产生一个随机整数r（r<n）。
　　5、用户B计算点C1=M+rK；C2=rG。
　　6、用户B将C1、C2传给用户A。
　　7、用户A接到信息后，计算C1-kC2，结果就是点M。因为
		  C1-kC2=M+rK-k(rG)=M+rK-r(kG)=M
　　　再对点M进行解码就可以得到明文。

  　　密码学中，描述一条Fp上的椭圆曲线，常用到六个参量：
	   T=(p,a,b,G,n,h)。
　　（p 、a 、b 用来确定一条椭圆曲线，G为基点，n为点G的阶，h 是椭圆曲线上所有点的个数m与n相除的整数部分）

　　这几个参量取值的选择，直接影响了加密的安全性。参量值一般要求满足以下几个条件：

　　1、p 当然越大越安全，但越大，计算速度会变慢，200位左右可以满足一般安全要求；
　　2、p≠n×h；
　　3、pt≠1 (mod n)，1≤t<20；
　　4、4a3+27b2≠0 (mod p)；
　　5、n 为素数；
　　6、h≤4。
*/
#include <iostream>
#include "tommath.h"
#include <regex>

#pragma comment(lib,"tommath.lib")

using namespace std;

#define KEY_LONG 512	//私钥比特长
#define P_LONG 512		//有限域P比特长
#define EN_LONG 72		//一次取明文字节数，偶数
#define SLICE_LEN 128	//文件切片大小	1 MB = 1048576 B

#define THREAD_COUNT 50

bool completed[THREAD_COUNT];

static const regex fileName_Enc_regex{ "(.*)\\.(.+?)\\.slice([^\\.]+)" };
static const regex fileName_Dec_regex{ "(.*)\\.ecc(.+?)\\.slice([^\\.]+)" };

long slice(string fileName)
{
	fstream fp(fileName, ios::binary | ios::in);
	fstream fq;

	if (!fp.is_open())
	{
		return 0;
	}

	char ch;
	long FileNum = 0;

	while (fp.peek()!=-1)
	{
		string fileEnc = fileName;
		fileEnc += ".slice";
		fileEnc += to_string(++FileNum);
		fq.open(fileEnc, ios::binary | ios::out);
		if (!fq.is_open())
		{
			return 0;
		}
		for (size_t i = 0; i < SLICE_LEN && fp.peek()!=-1; i++)
		{
			ch = fp.get();
			fq.put(ch);
		}
		fq.close();
	}
	fp.close();
	return FileNum;
}

long slice(string fileName, long sliceSizeByte)
{
	fstream fp(fileName, ios::binary | ios::in);
	fstream fq;

	if (!fp.is_open())
	{
		return 0;
	}

	char ch;
	long FileNum = 0;

	while (fp.peek() != -1)
	{
		string fileEnc = fileName;
		fileEnc += ".slice";
		fileEnc += to_string(++FileNum);
		fq.open(fileEnc, ios::binary | ios::out);
		if (!fq.is_open())
		{
			return 0;
		}
		for (size_t i = 0; i < sliceSizeByte && fp.peek() != -1; i++)
		{
			ch = fp.get();
			fq.put(ch);
		}
		fq.close();
	}
	fp.close();
	return FileNum;
}

long slice(string fileName, const char* separator, size_t separatorSize)
{
	if (separatorSize == 0)
	{
		return 0;
	}
	fstream fp(fileName, ios::in | ios::binary);
	fstream fq;

	if (!fp.is_open())
	{
		return 0;
	}

	char ch;
	long FileNum = 0;

	while (fp.peek() != -1)
	{
		string fileEnc = fileName;
		fileEnc += ".slice";
		fileEnc += to_string(++FileNum);
		fq.open(fileEnc, ios::out|ios::binary);
		if (!fq.is_open())
		{
			return 0;
		}
		bool flag = true;
		while (fp.peek() != -1 && flag)
		{
			ch = fp.get();
			if (separator[0] == ch)
			{
				char* temp = new char[separatorSize];
				size_t i = 0;
				for (; i < separatorSize - 1 && flag; i++)
				{
					temp[i] = fp.get();
					separator[i + 1] != temp[i] ? flag = false : flag = true;
				}
				if (!flag)
				{
					fq.put(ch);
					for (size_t j = 0; j < i; j++)
					{
						fq.put(temp[j]);
					}
				}
				flag = !flag;
			}
			else
			{
				fq.put(ch);
			}
		}
		fq.close();
	}
	fp.close();
	return FileNum;
}

void combine(string fileName, long FileNum, const char* separator, size_t separatorSize)
{
	fstream fp(fileName, ios::out | ios::binary);
	fstream fq;

	if (!fp.is_open())
	{
		return;
	}

	char ch;
	long num = 0;

	while (num < FileNum)
	{
		string fileSlc = fileName;
		fileSlc += ".slice";
		fileSlc += to_string(++num);
		fq.open(fileSlc, ios::in | ios::binary);
		if (!fq.is_open())
		{
			return;
		}
		while (fq.peek()!=-1)
		{
			ch = fq.get();
			fp.put(ch);
		}
		fq.close();
		if (num < FileNum)
		{
			for (size_t i = 0; i < separatorSize; i++)
			{
				fp.put(separator[i]);
			}
		}
	}
	fp.close();
	return;
}

int GetPrime(mp_int* m, int lon) {
	mp_prime_rand(m, 10, lon, MP_PRIME_2MSB_ON);
	return MP_OKAY;
}

void Get_G_X_Y(mp_int* x1, mp_int* y1, mp_int* b, mp_int* a)
{
	mp_int tempx;
	mp_int temp1;
	mp_int temp2;
	mp_int temp3;

	mp_init(&tempx);
	mp_init(&temp1);
	mp_init(&temp2);
	mp_init(&temp3);

	//y2=x3+ax+b,随机产生X坐标,根据X坐标计算Y坐标
	GetPrime(x1, 30);
	mp_expt_n(x1, 3, &temp1);
	mp_mul(a, x1, &temp2);
	mp_add(&temp1, &temp2, &temp3);
	mp_add(&temp3, b, &tempx);
	mp_sqrt(&tempx, y1);

	mp_clear(&tempx);
	mp_clear(&temp1);
	mp_clear(&temp2);
	mp_clear(&temp3);
}

void Get_G_Y(mp_int* x1, mp_int* y1, mp_int* b, mp_int* a)
{
	mp_int tempx;
	mp_int temp1;
	mp_int temp2;
	mp_int temp3;

	mp_init(&tempx);
	mp_init(&temp1);
	mp_init(&temp2);
	mp_init(&temp3);

	//y2=x3+ax+b,随机产生X坐标,根据X坐标计算Y坐标
	mp_expt_n(x1, 3, &temp1);
	mp_mul(a, x1, &temp2);
	mp_add(&temp1, &temp2, &temp3);
	mp_add(&temp3, b, &tempx);
	mp_sqrt(&tempx, y1);

	mp_clear(&tempx);
	mp_clear(&temp1);
	mp_clear(&temp2);
	mp_clear(&temp3);
}

void Get_B(mp_int* b, mp_int* a, mp_int* p)
{
	mp_int temp;
	mp_int compare;
	mp_int temp1;
	mp_int temp2;
	mp_int temp3;
	mp_int temp4;
	mp_int temp5;

	mp_init(&compare);
	mp_zero(&compare);
	mp_init(&temp);
	mp_init(&temp1);
	mp_init(&temp2);
	mp_init(&temp3);
	mp_init(&temp4);
	mp_init(&temp5);

	while (1)
	{

		//4a3+27b2≠0 (mod p)
		GetPrime(b, 40);
		mp_expt_n(a, 3, &temp1);
		mp_sqr(b, &temp2);
		mp_mul_d(&temp1, 4, &temp3);
		mp_mul_d(&temp2, 27, &temp4);
		mp_add(&temp3, &temp4, &temp5);
		mp_mod(&temp5, p, &temp);

		if (mp_cmp(&temp, &compare) != 0)
		{
			break;
		}
	}

	mp_clear(&temp);
	mp_clear(&temp1);
	mp_clear(&temp2);
	mp_clear(&temp3);
	mp_clear(&temp4);
	mp_clear(&temp5);
}

int Two_points_add(mp_int* x1, mp_int* y1, mp_int* x2, mp_int* y2, mp_int* x3, mp_int* y3, mp_int* a, bool zero, mp_int* p)
{
	mp_int x2x1;
	mp_int y2y1;
	mp_int tempk;
	mp_int tempy;
	mp_int tempzero;
	mp_int k;
	mp_int temp1;
	mp_int temp2;
	mp_int temp3;
	mp_int temp4;
	mp_int temp5;
	mp_int temp6;
	mp_int temp7;
	mp_int temp8;
	mp_int temp9;
	mp_int temp10;


	mp_init(&x2x1);
	mp_init(&y2y1);
	mp_init(&tempk);
	mp_init(&tempy);
	mp_init(&tempzero);
	mp_init(&k);
	mp_init(&temp1);
	mp_init(&temp2);
	mp_init_set(&temp3, 2);
	mp_init(&temp4);
	mp_init(&temp5);
	mp_init(&temp6);
	mp_init(&temp7);
	mp_init(&temp8);
	mp_init(&temp9);
	mp_init(&temp10);


	if (zero)
	{
		mp_copy(x1, x3);
		mp_copy(y1, y3);
		zero = false;
		goto L;
	}
	mp_zero(&tempzero);
	mp_sub(x2, x1, &x2x1);
	if (mp_cmp(&x2x1, &tempzero) == -1)
	{

		mp_add(&x2x1, p, &temp1);
		mp_zero(&x2x1);
		mp_copy(&temp1, &x2x1);
	}
	mp_sub(y2, y1, &y2y1);
	if (mp_cmp(&y2y1, &tempzero) == -1)
	{

		mp_add(&y2y1, p, &temp2);
		mp_zero(&y2y1);
		mp_copy(&temp2, &y2y1);
	}
	if (mp_cmp(&x2x1, &tempzero) != 0)
	{

		mp_invmod(&x2x1, p, &tempk);

		mp_mulmod(&y2y1, &tempk, p, &k);
	}
	else
	{
		if (mp_cmp(&y2y1, &tempzero) == 0)
		{

			mp_mulmod(&temp3, y1, p, &tempy);
			mp_invmod(&tempy, p, &tempk);
			mp_sqr(x1, &temp4);
			mp_mul_d(&temp4, 3, &temp5);
			mp_add(&temp5, a, &temp6);
			mp_mulmod(&temp6, &tempk, p, &k);

		}
		else
		{
			zero = true;
			goto L;
		}
	}

	mp_sqr(&k, &temp7);
	mp_sub(&temp7, x1, &temp8);
	mp_submod(&temp8, x2, p, x3);

	mp_sub(x1, x3, &temp9);
	mp_mul(&temp9, &k, &temp10);
	mp_submod(&temp10, y1, p, y3);


L:

	mp_clear(&x2x1);
	mp_clear(&y2y1);
	mp_clear(&tempk);
	mp_clear(&tempy);
	mp_clear(&tempzero);
	mp_clear(&k);
	mp_clear(&temp1);
	mp_clear(&temp2);
	mp_clear(&temp3);
	mp_clear(&temp4);
	mp_clear(&temp5);
	mp_clear(&temp6);
	mp_clear(&temp7);
	mp_clear(&temp8);
	mp_clear(&temp9);
	mp_clear(&temp10);

	return 1;
}

bool Ecc_points_mul(mp_int* qx, mp_int* qy, mp_int* px, mp_int* py, mp_int* d, mp_int* a, mp_int* p)
{
	mp_int X1, Y1;
	mp_int X2, Y2;
	mp_int X3, Y3;
	mp_int XX1, YY1;
	mp_int A, P;

	int i;
	bool zero = false;
	char Bt_array[800] = { 0 };
	char cm = '1';

	mp_to_radix(d, Bt_array, 800, NULL, 2);

	mp_init(&X3);
	mp_zero(&X3);
	mp_init(&Y3);
	mp_zero(&X3);
	mp_init_copy(&X1, px);
	mp_init_copy(&X2, px);
	mp_init_copy(&XX1, px);
	mp_init_copy(&Y1, py);
	mp_init_copy(&Y2, py);
	mp_init_copy(&YY1, py);

	mp_init_copy(&A, a);
	mp_init_copy(&P, p);

	for (i = 1; i <= KEY_LONG - 1; i++)
	{
		mp_copy(&X2, &X1);
		mp_copy(&Y2, &Y1);
		Two_points_add(&X1, &Y1, &X2, &Y2, &X3, &Y3, &A, zero, &P);
		mp_copy(&X3, &X2);
		mp_copy(&Y3, &Y2);
		if (Bt_array[i] == cm)
		{

			mp_copy(&XX1, &X1);
			mp_copy(&YY1, &Y1);
			Two_points_add(&X1, &Y1, &X2, &Y2, &X3, &Y3, &A, zero, &P);
			mp_copy(&X3, &X2);
			mp_copy(&Y3, &Y2);

		}

	}

	if (zero)
	{
		//cout << "It is Zero_Unit!";
		return false;//如果Q为零重新产生D
	}

	mp_copy(&X3, qx);
	mp_copy(&Y3, qy);

	mp_clear(&X1);
	mp_clear(&Y1);
	mp_clear(&X2);
	mp_clear(&Y2);
	mp_clear(&X3);
	mp_clear(&Y3);
	mp_clear(&XX1);
	mp_clear(&YY1);
	mp_clear(&A);
	mp_clear(&P);

	return true;
}

//mp_int -> file
int CipherWrite(mp_int* a, fstream& fp)
{
	int i, j;

	for (i = 0; i < a->used; i++)
	{
		for (j = 0; j < 4; j++)
		{
			fp.put(char(a->dp[i] >> mp_digit(8 * (3 - j))));
		}
	}

	fp.put(char(255));
	return MP_OKAY;
}

//char -> mp_int
int ch2mp_int(mp_int* a, char* ch, int chLength)
{
	mp_digit* temp;
	int loop = chLength / 3;
	int size = ceil((float)chLength / 3);
	int i, j, res;
	if (a->alloc < size)
	{
		res = mp_grow(a, size);
		if (res != MP_OKAY)
			return res;
	}

	a->sign = MP_ZPOS;
	mp_zero(a);
	temp = a->dp;

	//以4个字符为单元循环，把字符放入的mp_int的每个单元中
	for (j = 0; j < loop; j++)
	{
		for (i = 0; i < 3; i++)
		{
			*temp <<= (mp_digit)CHAR_BIT;
			*temp |= (mp_digit)(ch[j * 3 + i]) & 255;
		}
		*temp |= 0x3000000;
		temp++;
	}

	//剩余字符少余4个时，只需一个mp_digit单元存放
	if (chLength % 3 > 0)
	{
		for (i = 0; i < chLength % 3; i++)
		{
			*temp <<= (mp_digit)CHAR_BIT;
			*temp |= (mp_digit)(ch[loop * 3 + i]) & 255;
		}
		*temp |= ((chLength % 3) << 24);
	}
	a->used = size;
	return MP_OKAY;
}

void Ecc_encipher(string fileName, mp_int* qX, mp_int* qY, mp_int* pX, mp_int* pY, mp_int* a, mp_int* p)
{
	mp_int mX, mY;
	mp_int c1X, c1Y;
	mp_int c2X, c2Y;
	mp_int r;
	mp_int tempX, tempY;
	bool zero = false;
	char cipherX[280] = { 0 };
	char cipherY[280] = { 0 };
	fstream fp(fileName, ios::binary | ios::in);

	mp_init(&mX);
	mp_init(&mY);
	mp_init(&c1X);
	mp_init(&c1Y);
	mp_init(&c2X);
	mp_init(&c2Y);
	mp_init(&r);
	mp_init(&tempX);
	mp_init(&tempY);

	//打开要加密文件
	if (!fp.is_open())
	{
		return;
	}

	unsigned int fileLength = 0;//文件字符长度
	int frequency = 0;
	int residue = 0;

	fp.seekg(0, std::ios::end);
	fileLength = (size_t)fp.tellg();
	fp.close();

	frequency = fileLength / EN_LONG;
	residue = fileLength % EN_LONG;

	const short enLengthTemp = EN_LONG / 2;

	_strlwr((char*)fileName.c_str());
	string fileEnc = regex_replace(fileName, fileName_Enc_regex, "$1.ecc$2.slice$3");

	//打开保存密文文件
	fstream fq(fileEnc, ios::binary | ios::out);
	if (!fq.is_open())
	{
		return;
	}

	fp.open(fileName, ios::binary | ios::in);
	for (size_t i = 0; i < frequency; i++)
	{
		GetPrime(&r, 100);

		for (size_t j = 0; j < enLengthTemp; j++)
		{
			cipherX[j] = fp.get();
		}

		for (size_t j = 0; j < enLengthTemp; j++)
		{
			cipherY[j] = fp.get();
		}

		ch2mp_int(&mX, cipherX, enLengthTemp);//文件存入 		
		ch2mp_int(&mY, cipherY, enLengthTemp);//文件存入

		Ecc_points_mul(&c2X, &c2Y, pX, pY, &r, a, p);//加密
		Ecc_points_mul(&tempX, &tempY, qX, qY, &r, a, p);
		Two_points_add(&mX, &mY, &tempX, &tempY, &c1X, &c1Y, a, zero, p);

		//保存密文      
		CipherWrite(&c1X, fq);
		CipherWrite(&c1Y, fq);
		CipherWrite(&c2X, fq);
		CipherWrite(&c2Y, fq);
	}
	//剩余字符处理
	if (residue > 0)
	{
		GetPrime(&r, 100);

		if (residue <= enLengthTemp)
		{
			for (size_t j = 0; j < residue; j++)
			{
				cipherX[j] = fp.get();
			}

			ch2mp_int(&mX, cipherX, residue);//文件存入 
			mp_zero(&mY);
		}
		else
		{
			for (size_t j = 0; j < enLengthTemp; j++)
			{
				cipherX[j] = fp.get();
			}

			for (size_t j = 0; j < residue - enLengthTemp; j++)
			{
				cipherY[j] = fp.get();
			}

			ch2mp_int(&mX, cipherX, enLengthTemp);//文件存入 
			ch2mp_int(&mY, cipherY, residue - enLengthTemp);//文件存入 
		}

		Ecc_points_mul(&c2X, &c2Y, pX, pY, &r, a, p);//加密
		Ecc_points_mul(&tempX, &tempY, qX, qY, &r, a, p);
		Two_points_add(&mX, &mY, &tempX, &tempY, &c1X, &c1Y, a, zero, p);

		//保存密文      
		CipherWrite(&c1X, fq);
		CipherWrite(&c1Y, fq);
		CipherWrite(&c2X, fq);
		CipherWrite(&c2Y, fq);
	}

	fq.close();
	fp.close();
	mp_clear(&mX);
	mp_clear(&mY);
	mp_clear(&c1X);
	mp_clear(&c1Y);
	mp_clear(&c2X);
	mp_clear(&c2Y);
	mp_clear(&r);
	mp_clear(&tempX);
	mp_clear(&tempY);
	completed[stoi(regex_replace(fileName, fileName_Enc_regex, "$3")) - 1] = true;
	//fileEnc += ".ok";
	//fstream ff(fileEnc, ios::out);
	//ff.close();
}

//file -> mp_int
int CipherRead(mp_int* a, fstream& fp)
{
	mp_digit* temp;
	int i, j, res;
	char ch[700] = { 0 };
	int chLength = 0;

	while (1)
	{
		ch[chLength] = fp.get();
		if (chLength % 4 == 0)
		{
			if (ch[chLength] == char(255)) goto L1;
		}
		chLength++;
	}
L1:

	if (a->alloc < chLength / 4)
	{
		res = mp_grow(a, chLength / 4);
		if (res != MP_OKAY)
			return res;
	}

	a->sign = MP_ZPOS;
	mp_zero(a);
	temp = a->dp;
	a->used = chLength / 4;

	for (i = 0; i < a->used; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (j != 0)
			{
				*temp <<= (mp_digit)CHAR_BIT;
			}
			*temp |= (mp_digit)(ch[i * 4 + j]) & 255;
		}
		temp++;
	}
	return MP_OKAY;
}

//mp_int -> char
int mp_int2ch(mp_int* a, char* ch)
{
	int i, j;
	short c = 0;
	mp_digit* temp;

	temp = a->dp;

	for (j = 0; j < a->used; j++)//以1个单元为循环，把1个单元的比特串赋给6个字符
	{
		if (j != 0)
		{
			temp++;
		}
		c = 0;
		for (i = (*temp >> 24) - 1; i >= 0; --i)
		{
			ch[j * 3 + c] = char(*temp >> mp_digit(CHAR_BIT * i));
			c++;
		}
	}
	//ch[(a->used - 1) * 3 + c] = '\0';//字符串结尾
	return (a->used - 1) * 3 + c;
}

void Ecc_decipher(string fileName, mp_int* k, mp_int* a, mp_int* p)
{
	mp_int c1X, c1Y;
	mp_int c2X, c2Y;
	mp_int tempX, tempY;
	mp_int mX, mY;
	mp_int temp;

	mp_init(&temp);
	mp_init(&c1X);
	mp_init(&c1Y);
	mp_init(&c2X);
	mp_init(&c2Y);
	mp_init(&tempX);
	mp_init(&tempY);
	mp_init(&mX);
	mp_init(&mY);

	mp_int tempZero;
	mp_init(&tempZero);

	char sTemp[700] = { 0 };
	fstream fp(fileName, ios::in | ios::binary);
	bool zero = false;

	if (!fp.is_open())
	{
		return;
	}

	//打开保存解密结果文件
	_strlwr((char*)fileName.c_str());
	string fileDec = regex_replace(fileName, fileName_Dec_regex, "$1.$2.slice$3");

	fstream fq(fileDec, ios::out | ios::binary);
	if (!fq.is_open())
	{
		return;
	}

	while (fp.peek()!=-1)
	{
		CipherRead(&c1X, fp);
		CipherRead(&c1Y, fp);
		CipherRead(&c2X, fp);
		CipherRead(&c2Y, fp);

		mp_zero(&tempZero);
		if (mp_cmp(&c1X, &tempZero) == 0) break;

		Ecc_points_mul(&tempX, &tempY, &c2X, &c2Y, k, a, p);

		mp_neg(&tempY, &temp);
		Two_points_add(&c1X, &c1Y, &tempX, &temp, &mX, &mY, a, zero, p);

		int chtem;
		chtem = mp_int2ch(&mX, sTemp);//从ming中取出字符串

		//保存解密结果
		for (int kk = 0; kk < chtem; kk++)
		{
			fq.put(sTemp[kk]);
		}

		chtem = mp_int2ch(&mY, sTemp);//从ming中取出字符串

		 //保存解密结果
		for (int kk = 0; kk < chtem; kk++)
		{
			fq.put(sTemp[kk]);
		}
	}

	fp.close();
	fq.close();
	mp_clear(&c1X);
	mp_clear(&c1Y);
	mp_clear(&c2X);
	mp_clear(&c2Y);
	mp_clear(&tempX);
	mp_clear(&tempY);
	mp_clear(&mX);
	mp_clear(&mY);
	mp_clear(&temp);
	completed[stoi(regex_replace(fileName, fileName_Dec_regex, "$3")) - 1] = true;
	//fileDec += ".ok";
	//fstream ff(fileDec, ios::out);
	//ff.close();
}

void Ecc(const char* fn, const char* pswfn, const char* c_p, const char* c_a, const char* c_gx, const char* c_gy, const char* c_qx, const char* c_qy)
{
#ifdef DEBUG
	time_t st = time(0);
#endif // DEBUG

	mp_int GX;
	mp_int GY;
	mp_int K;//私有密钥
	mp_int A;
	mp_int B;
	mp_int QX;
	mp_int QY;
	mp_int P;//Fp中的p(有限域P)


	mp_init(&GX);
	mp_init(&GY);
	mp_init(&K);
	mp_init(&A);
	mp_init(&B);
	mp_init(&QX);
	mp_init(&QY);
	mp_init(&P);

	char temp[800] = { 0 };

	fstream psw(pswfn, ios::out);

	srand((unsigned)time(0));

	//有限域 P
	if (strcmp(c_p, "") == 0)
	{
		GetPrime(&P, P_LONG);
		mp_to_radix(&P, temp, 800, NULL, 10);
		psw << "P: " << temp << endl;
#ifdef DEBUG
		cout << "有限域 P 是:" << endl;
		mp_to_radix(&P, temp, 800, NULL, 10);
		cout << temp << endl;
#endif // DEBUG
	}
	else
	{
		strcpy(temp, c_p);
		mp_read_radix(&P, temp, 10);
	}

	//曲线参数 A
	if (strcmp(c_a, "") == 0)
	{
		GetPrime(&A, 30);
		mp_to_radix(&A, temp, 800, NULL, 10);
		psw << "A: " << temp << endl;
#ifdef DEBUG
		cout << "曲线参数 A 是:" << endl;
		mp_to_radix(&A, temp, 800, NULL, 10);
		cout << temp << endl;
#endif // DEBUG
	}
	else
	{
		strcpy(temp, c_a);
		mp_read_radix(&A, temp, 10);
	}

	//曲线G点XY坐标
	if (strcmp(c_gx, "") == 0)
	{
		//曲线参数 B
		Get_B(&B, &A, &P);
		Get_G_X_Y(&GX, &GY, &B, &A);
#ifdef DEBUG
		cout << "曲线参数 B 是:" << endl;
		mp_to_radix(&B, temp, 800, NULL, 10);
		cout << temp << endl;
		cout << "曲线G点X坐标是:" << endl;
		mp_to_radix(&GX, temp, 800, NULL, 10);
		cout << temp << endl;
		cout << "曲线G点Y坐标是:" << endl;
		mp_to_radix(&GY, temp, 800, NULL, 10);
		cout << temp << endl;
#endif // DEBUG
	}
	else
	{
		strcpy(temp, c_gx);
		mp_read_radix(&GX, temp, 10);
		strcpy(temp, c_gy);
		mp_read_radix(&GY, temp, 10);
	}

	//私钥 K，公钥XY坐标
	if (strcmp(c_qx, "") == 0 || strcmp(c_qy, "") == 0)
	{
		do
		{
			GetPrime(&K, KEY_LONG);
		} while (!Ecc_points_mul(&QX, &QY, &GX, &GY, &K, &A, &P));
		mp_to_radix(&K, temp, 800, NULL, 10);
		psw << "K: " << temp << endl;
		mp_to_radix(&GX, temp, 800, NULL, 10);
		psw << "GX: " << temp << endl;
		mp_to_radix(&GY, temp, 800, NULL, 10);
		psw << "GY: " << temp << endl;
		mp_to_radix(&QX, temp, 800, NULL, 10);
		psw << "QX: " << temp << endl;
		mp_to_radix(&QY, temp, 800, NULL, 10);
		psw << "QY: " << temp << endl;
#ifdef DEBUG
		cout << "私钥 K 是:" << endl;
		cout << temp << endl;
		cout << "Q点X坐标是:" << endl;
		mp_to_radix(&QX, temp, 800, NULL, 10);
		cout << temp << endl;
		cout << "Q点Y坐标是:" << endl;
		mp_to_radix(&QY, temp, 800, NULL, 10);
		cout << temp << endl;

#endif // DEBUG
	}
	else
	{
		strcpy(temp, c_qx);
		mp_read_radix(&QX, temp, 10);
		strcpy(temp, c_qy);
		mp_read_radix(&QY, temp, 10);
	}

	psw.close();
	char tempFn[MAX_PATH] = { 0 };
	strcpy(tempFn, fn);
	//Ecc_encipher(tempFn, &QX, &QY, &GX, &GY, &A, &P);//加密
	fstream fp(tempFn, ios::binary | ios::in);
	fp.seekg(0, std::ios::end);
	size_t fileLength = (size_t)fp.tellg();
	fp.close();
	long filenum = slice(tempFn, (fileLength / THREAD_COUNT) + 1);
#ifndef DEBUG
	//DeleteFileA(tempFn);
#endif // !DEBUG
	string fileNames[THREAD_COUNT];
	std::thread** tasks = new std::thread * [filenum];
	long FileNum = 0;
	while (filenum > FileNum)
	{
		completed[FileNum] = false;
		string fileEnc = tempFn;
		fileEnc += ".slice";
		fileEnc += to_string(++FileNum);
		fileNames[FileNum - 1] = fileEnc;
		//Ecc_encipher(fileenc, &QX, &QY, &GX, &GY, &A, &P);//加密
		tasks[FileNum - 1] = new std::thread(Ecc_encipher, fileEnc, &QX, &QY, &GX, &GY, &A, &P);//加密
		tasks[FileNum - 1]->detach();
	}
	bool finish = true;
	while (finish)
	{
		FileNum = 0;
		while (filenum > FileNum)
		{
			if (!completed[FileNum])
			{
				finish = false;
			}
			++FileNum;
		}
		finish = !finish;
		Sleep(3000);
	}
	combine(regex_replace(tempFn, regex{ "(.*)\\.(.+)" }, "$1.ecc$2"), filenum, "\x06\xA8\x52\x00", 4);
	FileNum = 0;
	while (filenum > FileNum)
	{
		DeleteFileA(fileNames[FileNum].c_str());
		fileNames[FileNum] = regex_replace(fileNames[FileNum], fileName_Enc_regex, "$1.ecc$2.slice$3");
		DeleteFileA(fileNames[FileNum++].c_str());
	}

	mp_clear(&GX);
	mp_clear(&GY);
	mp_clear(&K);//私有密钥
	mp_clear(&A);
	mp_clear(&B);
	mp_clear(&QX);
	mp_clear(&QY);
	mp_clear(&P);//Fp中的p(有限域P)
#ifdef DEBUG
	cout << "Encipher used " << time(0) - st << " s." << endl;
#endif // DEBUG
}

void Ecc(const char* fn, const char* c_p, const char* c_a, const char* c_k)
{
#ifdef DEBUG
	time_t st = time(0);
#endif // DEBUG

	mp_int K;//私有密钥
	mp_int A;
	mp_int P;//Fp中的p(有限域P)


	mp_init(&K);
	mp_init(&A);
	mp_init(&P);

	char temp[800] = { 0 };

	if (strcmp(c_k, "") != 0 && strcmp(c_a, "") != 0 && strcmp(c_p, "") != 0)
	{
		strcpy(temp, c_k);
		mp_read_radix(&K, temp, 10);
		strcpy(temp, c_a);
		mp_read_radix(&A, temp, 10);
		strcpy(temp, c_p);
		mp_read_radix(&P, temp, 10);
		char tempFn[MAX_PATH] = { 0 };
		strcpy(tempFn, fn);
		//Ecc_decipher(tempFn, &K, &A, &P);//解密
		long filenum = slice(tempFn, "\x06\xA8\x52\x00", 4);
		string fileNames[THREAD_COUNT];
		std::thread** tasks = new std::thread * [filenum];
		long FileNum = 0;
		while (filenum > FileNum)
		{
			completed[FileNum] = false;
			string fileDec = tempFn;
			fileDec += ".slice";
			fileDec += to_string(++FileNum);
			fileNames[FileNum - 1] = fileDec;
			//Ecc_decipher(filedecs[FileNum-1], &K, &A, &P);//解密
			tasks[FileNum - 1] = new std::thread(Ecc_decipher, fileDec, &K, &A, &P);//解密
			tasks[FileNum - 1]->detach();
		}
		bool finish = true;
		while (finish)
		{
			FileNum = 0;
			while (filenum > FileNum)
			{
				if (!completed[FileNum])
				{
					finish = false;
				}
				++FileNum;
			}
			finish = !finish;
			Sleep(3000);
		}
		combine(regex_replace(tempFn, regex{ "(.*)\\.ecc(.+)" }, "$1.$2"), filenum, "", 0);
		FileNum = 0;
		while (filenum > FileNum)
		{
			DeleteFileA(fileNames[FileNum].c_str());
			fileNames[FileNum] = regex_replace(fileNames[FileNum], fileName_Dec_regex, "$1.$2.slice$3");
			DeleteFileA(fileNames[FileNum++].c_str());
		}
	}

	mp_clear(&K);//私有密钥
	mp_clear(&A);
	mp_clear(&P);//Fp中的p(有限域P)
#ifdef DEBUG
	cout << "Decipher used " << time(0) - st << " s." << endl;
#endif // DEBUG
}
