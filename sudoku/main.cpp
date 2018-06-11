#include<cstdio>
#include<cstdlib>
#include"sudoku.h"
#include<cstring>
#include<ctime>

using namespace std;

int main(void)
{
	sudoku obj;
	char e = 'e';
	obj.get_start(e);
	obj.print();
	printf("\n");
	obj.answer();
	printf("\n");
	obj.print();	

	return 0;
}

