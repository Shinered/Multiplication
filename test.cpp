#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
using namespace std;
//long int 32位
//int :16位
//get_data time: 0.09439s
//check time: 83.3131s
//number_of_inversion time: 48.7092s
//number of inversion: 2407905288
long int number_of_inversion(vector<long int> &a);
long int split_inversion(vector<long int> &left, vector<long int> &right, vector<long int> & sorted_result);
void print(vector<long int> a);
long int check(vector<long int> &a);
void get_data(vector<long int> &numbers);//读取txt文件中所有数据
int main()
{
	clock_t start, get, check1, end;
	vector<long int> numbers;
	vector<long int> result;
	long int count = 0;
	start = clock();
	get_data(numbers);
	get = clock();
	cout << "get_data time" << (double)(get - start) / CLOCKS_PER_SEC << "s" << endl;
	cout << "checking count:" << check(numbers) << endl;
	check1 = clock();
	cout << "check time: " << (double)(check1 - get) / CLOCKS_PER_SEC << "s" << endl;
	count = number_of_inversion(numbers);
	end = clock();
	cout << "inversion: " << (double)(end - check1) / CLOCKS_PER_SEC << "s" << endl;
	cout << "count:" << count << endl;
//	vector<int>:: iterator it = a.begin();
//	print(numbers);
/*	while (it != a.end())
	{
		cout << "a:" << (*it) << endl;
		it++;
	}*/
	return 0;
	
}
long int check(vector<long int> &a)
{
	long int count = 0;
	for(long int  i = 0; i < a.size(); i++)	
	{
		for(long int j = 0; j < a.size(); j++)
		{
			if(i < j && a[i] > a[j]) count ++;
		}
	}
	return count;
}
long int number_of_inversion(vector<long int> &a)
{
	long int half = a.size() / 2;
	long int n = a.size(), count = 0;
	long int left_number, right_number, split_number, total_number;
	vector<long int> left, right, result;
	vector<long int>::iterator it;
	if(n == 1) return 0;
	if(n == 2) 
	{
		if(a[0] > a[1]) {
			long int t = a[1];
			a[1] = a[0];
			a[0] = t;
			return 1;
		} else {
			return 0;
		}
	}
	it = a.begin();
	left.insert(left.end(), it, it + half);
	right.insert(right.end(), it + half, a.end());
	left_number = number_of_inversion(left);
	right_number = number_of_inversion(right);
	split_number = split_inversion(left, right, result);
	a = result;
	total_number = left_number + right_number + split_number;
	return 	total_number;
}

void print(vector<long int> a)
{
	for(long int i = 0; i < a.size(); i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

long int split_inversion(vector<long int> &left, vector<long int> &right, vector<long int> & sorted_result)
{
	long int count = 0;
	long int length = right.size() + left.size();
	long int smaller = 0;
	vector<long int>::iterator left_it = left.begin(), right_it = right.begin();
	while(1)
	{
		if((*left_it) < (*right_it)) {
			sorted_result.push_back((*left_it));
			left_it++;
			if (left_it == left.end()){
				sorted_result.insert(sorted_result.end(), right_it, right.end());
				break;
			}
			
		} else {
			sorted_result.push_back((*right_it));
			right_it++;
			if (right_it == right.end()) 
			{
				sorted_result.insert(sorted_result.end(), left_it, left.end());
				break;
			}

		}
	}
	for(long int i = 0; i < left.size(); i++)
	{
		for(long int j = 0; j < right.size(); j++)
		{
			if(left[i] > right[j]) {
				count++;
			}
		}
	}

	return count;
}

void get_data(vector<long int> &numbers)
{
	fstream f("1.txt");
	string line;
	long int temp;
	stringstream ss;
	while(getline(f,line))
	{
		long int temp;
		stringstream ss;
		ss << line;
		ss >> temp;
		numbers.push_back(temp);	
	}
}
