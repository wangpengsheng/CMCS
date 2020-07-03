#pragma once
#include <string>
#include <vector>

std::string  __declspec(dllexport) GbkToUtf8(const char* src_str);

std::string __declspec(dllexport) Utf8ToGbk(const char* src_str);

void __declspec(dllexport) BCC(char* str, char& cHigh, char& cLow);

int __declspec(dllexport)  HexToDec(const char* buff);

void __declspec(dllexport) CRC16(char *buff, unsigned short len, char &low, char &high);

