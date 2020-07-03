#include "StdAfx.h"
#include "GeneralFunc.h"

std::string GbkToUtf8(const char* src_str)
{
	int len = MultiByteToWideChar(CP_ACP, 0, src_str, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, src_str, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	std::string strTemp = str;
	if (wstr) delete[] wstr;
	if (str) delete[] str;
	return strTemp;
}

std::string Utf8ToGbk(const char* src_str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, src_str, -1, NULL, 0);
	wchar_t* wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, src_str, -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char* szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	std::string strTemp(szGBK);
	if (wszGBK) delete[] wszGBK;
	if (szGBK) delete[] szGBK;
	return strTemp;
}

void BCC(char* str, char& cHigh, char& cLow)
{
	int uch = 0;
	while (*str)
	{
		uch ^= *str++;
	}

	cHigh = ((uch & 0xF0) >> 4);
	if (cHigh > 9)
	{
		cHigh = (cHigh - 10 + 'A');
	}
	else
	{
		cHigh = cHigh + '0';
	}

	cLow = uch & 0x0F;
	if (cLow > 9)
	{
		cLow = (cLow - 10 + 'A');
	}
	else
	{
		cLow = cLow + '0';
	}
}

int HexToDec(const char* buff)
{
	int res = 0;
	const char buffHex[] = "0123456789ABCDEF";
	while (*buff)
	{
		res = res * 16 + (strchr(buffHex, *buff++) - buffHex);
	}
	return res;
}

void CRC16(char* buff, unsigned short len, char& low, char& high)
{
	unsigned short crcVal = 0xFFFF;
	unsigned char data = 0;
	unsigned short val = 0;

	for (int i = 0; i < len; i++)
	{
		data = *buff++;
		crcVal ^= data;
		for (int k = 0; k < 8; k++)
		{
			val = crcVal;
			crcVal >>= 1; //右移一位
			if (val & 0x01)
			{
				//判断末位是否为1
				crcVal ^= 0xA001;
			}
		}
	}
	high = (char)(crcVal >> 8);
	low = (char)(crcVal & 0xFF);
}