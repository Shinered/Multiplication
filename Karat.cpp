#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <time.h>
/*-----只能计算2^n次方数字的计算
 *
 * */
using namespace std;
string karatsuba(string s1, string s2);
string addstring(string s1, string s2);
string invertstring(string str);
int Max(int x, int y);
string easymul(string s1, string s2);
int str2num(string s);
string minus0(string str);
string num2str(int i);
/*----------数字转字符串--------*/
string num2str(int i)
{
	stringstream ss;
	ss << i;
	return ss.str();
}
/*---------字符串转数字---------*/
int str2num(string s)
{
	int num;
	stringstream ss(s);
	ss >> num;
	return num;
}
int Max(int x, int y)
{
	return x > y ? x : y;
}
string easymul(string s1, string s2)
{
	int num = str2num(s1) * str2num(s2);
	return num2str(num);
}

string invertstring(string str)
{
	string result;
	for(int i = str.size() - 1; i >= 0; i--)
	{
		result = result + str[i];
	}
	return result;
}
string addstring(string s1, string s2)
{
	int max;
	string result;
	int addflag = 0;
	int temp = 0;
	if(s1.size() > s2.size())
	{
		max = s1.size();
		s2 = string(max - s2.size(), '0') + s2;
	} else {
		max = s2.size();
		s1 = string(max- s1.size(), '0') + s1;
	}
	
	for(int i = max - 1; i >= 0; i--)
	{
		temp = (s1[i] - '0') + (s2[i] - '0') + addflag;
		if(temp >= 10)
		{
			addflag = temp / 10;
			temp = temp % 10;
		} else {
			addflag = 0;
		}
		result = result + num2str(temp);
	}
	if(addflag != 0)
	{
		result = result + num2str(addflag);
	}
	return result; //需要倒序
}
string minus0(string str)
{
	int zeros = 0;
	string result;
	for(int i = 0; i < str.size(); i++)
	{
		if(str[i] != '0')
		{
			zeros = i;
			break;
		}
	}
	result = str.substr(zeros);
	return result;
}
/*---------递归乘法-----------*/
string karatsuba(string s1, string s2)
{
	int size1 = s1.size();
	int size2 = s2.size();
	int max = Max(size1, size2);
	int half;
	if(max % 2 == 0)
	{
		half = max / 2;
	} else {
		half = max / 2;
		
	}

	string a, b, c , d;
	string ac, bd, bc, ad;
	string result, temp1, temp2, temp3;
	if(max == size1) {
		s2 = string(max - size2, '0') + s2;
	} else {
		s1 = string(max - size1, '0') + s1;
	}
	if (max == 1)
	{
		return easymul(s1, s2);
	}
	a = s1.substr(0, half);
	b = s1.substr(half);
	c = s2.substr(0, half);
	d = s2.substr(half);
	ac = karatsuba(a,c);
	bd = karatsuba(b,d);
	bc = karatsuba(b,c);
	ad = karatsuba(a,d);
	temp1 = ac + string((max - half) * 2, '0');
	temp2 = invertstring(addstring(bc, ad)) + string(max - half,'0');
	temp3 = invertstring(addstring(temp1, temp2));
	result = invertstring(addstring(temp3, bd));
	return result;
}
int main()
{
	clock_t start_time, end_time;
	start_time = clock();
	string s1 = "12345678901234567890";
	string s2 = "12345678901234567890";
	cout << minus0(karatsuba(s1,s2)) << endl;
	end_time = clock();
	cout << "total time:" << (double)(end_time - start_time) << endl;

	return 0;
}
