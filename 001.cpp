#include <iostream>
#include <sstream>
#include <string>
using namespace std;

string oneline(char a, string str);

string add0(int a)
{
	return string(a,'0');
}

string num2str(int a)
{
	stringstream ss;
	ss << a;
	return ss.str();
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
		s2 = s2 + add0(max - s2.size());
	}else {
		max = s2.size();
		s1 = s1 + add0(max - s1.size());
	}
	for(int i = 0; i < max; i++)
	{
		temp = (s1[i] - '0') + (s2[i] - '0') + addflag;
		if(temp >= 10)
		{
			addflag = temp / 10 ;
			temp = temp % 10;
		} else {
			addflag = 0;
		}

		result =  result + num2str(temp);
	}
	if(addflag != 0)
	{
		result = result + num2str(addflag);
	}
	return result; //不需要倒序
	
}
string multiply(string s1, string s2)
{
	string result;
	for(int i = s1.size() - 1; i >= 0; i--)
	{
		string temp = add0(s1.size() - 1 - i) + oneline(s1[i], s2);
		result = addstring(temp,result);
	}
	return result;
}
string oneline(char a, string str2)
{
	string result;
	int num = 0;
	int addflag = 0;
	for(int i = str2.size() - 1; i >= 0; i--)
	{
		num = (a - '0') * (str2[i] - '0') + addflag;
		if (num >= 10)
		{
			addflag = num / 10;
			num = num % 10;
		} else {
			addflag = 0;
		}
		result = result + num2str(num);
	}
	if(addflag != 0)
	{
		result += num2str(addflag);
	}
	return result;	//需要倒序
}
//-----------------高位减0-----------
string minus0(string str)
{
	int zeros = 0;
	string result;
	for(int i = str.size() - 1; i >= 0; i--)
	{
		if(str[i] != '0')
		{
			zeros = i;
			break;
		}
	}

	for (int j = zeros; j >= 0; j--)
	{
		result = result + str[j];
	}
	return result;

}
int main()
{
	string s1 = "123456789123456789";
	string s2 = "123456789123456789";
	string result;
	result = minus0(multiply(s1,s2));
	cout << "result::" << result << endl;
}

