#include<cstdio>
#include<cstdlib>
#include"HugeInt.h"
#include<iostream>
using namespace std;
ostream& operator<<(ostream &out, HugeInt obj)
{
	char str[100] = {'0'};
	int i;
	i = obj.str1.size()-1;
	while(!obj.str1.empty())
	{
		str[i--] = obj.str1.top();
		obj.str1.pop();
	}
	if(obj.sign == 1)
	out << "-";
	
	out << str;
	return out;
}
istream& operator>>(istream &in, HugeInt &obj)
{
	string str;
	in >> str;
	obj.str1 = obj.stos(str);
	return in;
}
int main(void)
{
	HugeInt x;
	HugeInt y(28825252);
	HugeInt z("314159265358979323846");

	cin >> x;
	HugeInt result;
	result = x+y;
	cout<< x << "+" << y << "=" << result<<endl;
	result = z-x;
	cout<< z << "-" << x << "=" << result<<endl;	
	
	return 0;
}
