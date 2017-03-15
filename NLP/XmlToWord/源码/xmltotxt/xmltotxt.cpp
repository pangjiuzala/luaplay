#include"stdafx.h"
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>
#include <iterator>
#include <iostream>
#include <windows.h>
#include <wchar.h>
#include "io.h"
#include <stdlib.h>
#include <vector>
#include <set>
//#define TXT_NAME "word.xml"//����ϲ����xml���
using namespace std;
//utf8תstring
std::string UTF8_To_string(const std::string & str)
{
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];
	memset(pwBuf, 0, nwLen * 2 + 2);

	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);

	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr = pBuf;

	delete[]pBuf;
	delete[]pwBuf;

	pBuf = NULL;
	pwBuf = NULL;

	return retStr;
}

//�ָ��ַ���
int StrSplit(char dst[][80], char* str, const char* spl)
{
	int n = 0;
	char *result = NULL;
	result = strtok(str, spl);
	while (result != NULL)
	{
		strcpy(dst[n++], result);
		result = strtok(NULL, spl);
	}
	return n;
}

//�ж��Ƿ���Ҫ���ָ�����
bool IncludeCh(char str[], char ch) {
	int i;
	bool has = false;
	for (i = 0; str[i]; ++i) {
		if (str[i] == ch)
			return true;
	}
	return false;
}
//stringת����char����
char* StrToChArr(string src)
{
	char *dst = new char[255];
	int i;
	for (i = 0; i < src.length(); i++)
		dst[i] = src[i];
	dst[i] = '\0';
	return dst;
}
//�����ɼ��ϵĵѿ�����
string decare(const vector<vector<string>> &sets, string add)
{
	vector<vector<string>> rs;
	int n = sets.size();
	vector<string> tmp;
	string word, result;
	for (int i = 0; i < n; ++i)
	{
		tmp.push_back(sets[i][0]);
	}
	rs.push_back(tmp);
	for (int i = n - 1; i >= 0; --i)
	{
		int nRsSize = rs.size();
		for (int k = 1; k < sets[i].size(); ++k)
		{
			for (int j = 0; j < nRsSize; ++j)
			{
				tmp = rs[j];
				tmp[i] = sets[i][k];
				rs.push_back(tmp);
			}
		}
	}
	for (vector<vector<string> >::iterator iter = rs.begin(); iter != rs.end(); iter++)
	{
		word += add;
		for (int i = 0; i < (*iter).size(); i++)
		{
			word += (*iter)[i] + " ";//��֮����ӿո�
		}
		if (iter != rs.end() - 1) {
			word += "\n";//ĩβ����Ҫ����
		}
		else {
			word += "";
		}
	}
	return word;
}
//����ѿ�����������浽�ļ�, addΪ�����
string  Descarte(string m, string add)
{
	vector<vector<string>> charSet;
	vector<string> tmp[100];
	char dst[10][80];
	int k = StrSplit(dst, StrToChArr(m), " ");//��һ�ηָ����õ� "[A|B|C]"��"D" ��"[E|F|G]""[M|N]"4������
	char dsts[10][80];
	for (int m = 0; m < k; m++)
	{
		int u = StrSplit(dsts, dst[m], "|[]");//�ڶ��ηָ����õ�ÿ�������еľ���ֵ������"[A|B|C]"�е�"A"��"B"��"C"
		for (int f = 0; f < u; f++) {
			tmp[m].push_back(dsts[f]);
		}
		charSet.push_back(tmp[m]);
	}
	return decare(charSet, add);
}


int  main() {
	string m = "[A|B|C] D [E|F|G] [M|N]";
	if (IncludeCh(StrToChArr(m), '[') && IncludeCh(StrToChArr(m), ']')) {
		cout << Descarte(m, "") << endl;
	}
	system("pause");
	return 0;

}
