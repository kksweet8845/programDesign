#include<cstdio>
#include<cstdlib>
#include<stack>
#include "HugeInt.h"
using namespace std;
HugeInt::HugeInt(int num)
{
	str1 = ntos(num);
	sign = 0;
}
HugeInt::HugeInt(string str)
{
	str1 = stos(str);
	sign = 0;
}
HugeInt::HugeInt()
{
	sign = 0;
}
stack<char> HugeInt::stos(string str)
{
	stack<char> result,tem_s;
	for(int i=0;i<str.length();++i)
	{
		result.push(str.at(i));
	}

	return result;
}

stack<char> HugeInt::plus(stack<char> s1,stack<char> s2)
{
	int s1_length,s2_length;
	stack<char> str_result;
	s1_length = s1.size();
	s2_length = s2.size();
	int diff;
	if(s1_length > s2_length)
	diff = s1_length - s2_length;
	else
	diff = s2_length - s1_length;

	int i,j;
	int num1=0,num2=0,num3=0,num4=0;
	char n1,n2;
	for(i=(s1_length<s2_length? s1_length:s2_length)-1;i>=0;i--)
	{
		
		num1 = (int)s1.top()-'0';
		num2 = (int)s2.top()-'0';
		s1.pop();
		s2.pop();
		num3 = num1+num2;
		if(num4!=0)
		num3 = num4+num3;

		if(num3>=10)
		{
			num4 = num3/10;
			num3 = num3 -10;
			str_result.push(num3+'0');
		}
		else
		{
			str_result.push(num3+'0');
			num4 = 0;
		}
	}
	for(j=0;j<diff;++j)
	{
		if(num4!=0)
		{
			num3 = (int)s1.top()-'0';
			num3 = num3+num4;
			s1.pop();
			if(num3>=10)
			{
				num4 = num3/10;
				num3 = num3 -10;
				str_result.push(num3+'0');
			}
			else
			{
				str_result.push(num3+'0');
				num4 = 0;
			}
		}
		else
		{
			str_result.push(s1.top());
			s1.pop();
		}
	}
	return str_result;
}
stack<char> HugeInt::substract(stack<char> s1, stack<char> s2)
{
	int s1_length,s2_length;
	s1_length = s1.size();
	s2_length = s2.size();
	int diff;
	if(s1_length > s2_length)
	diff = s1_length - s2_length;
	else
	diff = s2_length - s1_length;
	stack<char> result;
	int i;
	int num1=0,num2=0,num3=0,num4=0;
	for(i = (s1_length<s2_length? s2_length:s1_length)-1;i>=0;--i)
	{
		if(i > diff-1)
		{
				num1 = (int)s1.top()-'0';
				if(num4 == -1)
				num1 = num1-1;

				num2 = (int)s2.top()-'0';
				num3 = num1-num2;
				s1.pop();
				s2.pop();
		
				if(num3<0)
				{
					num4 = -1;
					num3 = num3+10;
					result.push(num3+'0');
				}
				else
				{
				num4 = 0;
				result.push(num3+'0');
				}
		}
		else
		{
			result.push(s1.top());
			s1.pop();
		}
		
	}
	return result;
}
stack<char> HugeInt::ntos(int num)
{
	stack<char> result,tem_s;
	int tem;
	while(num != 0)
	{
		tem_s.push(num%10+48);
		num = num/10;

	}
	while(!tem_s.empty())
	{
		result.push(tem_s.top());
		tem_s.pop();
	}

	return result;
}

HugeInt HugeInt::operator+(HugeInt& in)
{
	HugeInt result;
	stack<char> tem;
	if(this->str1.size() > in.str1.size())
	{
	 	tem = plus(this->str1,in.str1);
		while(!tem.empty())
		{
			result.str1.push(tem.top());
			tem.pop();
		}
	}
	 else
	 {

		tem = plus(in.str1,this->str1);
		while(!tem.empty())
		{
			result.str1.push(tem.top());
			tem.pop();
		}
	 }

	 return result;

}
HugeInt HugeInt::operator-(HugeInt &in)
{
	HugeInt result;
	stack<char> tem;
	if(this->str1.size() > in.str1.size())
	{
		tem = substract(this->str1,in.str1);
		while(!tem.empty())
        {            
			result.str1.push(tem.top());
			tem.pop();
		}

	}
	else if(this->str1.size() == in.str1.size())
	{
		tem = substract(this->str1,in.str1);
		while(!tem.empty())
		{
			result.str1.push(tem.top());
			tem.pop();
		}
	}
	else if(this->str1.size() < in.str1.size())
	{
		tem = substract(in.str1,this->str1);
		while(!tem.empty())
		{
			result.str1.push(tem.top());
			tem.pop();
		}
		result.sign = true;
	}

	return result;
}
