#include<cstdio>
#include<cstdlib>
#include<string>
#include<stack>
using namespace std;
class HugeInt {
	friend ostream& operator<<(ostream& , HugeInt);
	friend istream& operator>>(istream& , HugeInt&);
	public:
	HugeInt(int num);
	HugeInt(string str);
	HugeInt();
	stack<char> plus( stack<char> s1 ,stack<char> s2 );
	stack<char> ntos(int num);
	stack<char> stos(string str);
	stack<char> substract(stack<char> s1, stack<char> s2);	
	HugeInt operator+(HugeInt &in);
	HugeInt operator-(HugeInt &in);
	stack<char> str1;
	bool sign;
};
