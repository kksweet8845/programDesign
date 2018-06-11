#include<cstdio>
#include<cstdlib>
class sudoku {
	public:
		sudoku();
		void get_start(char level);
		void answer();
		void rand_(int num);
		void valid();
		void backtrack(int x,int y);
		void print();
		
		 int e;
		 int board[9][9] ;
		 bool dx[9][10] ;
	 	 bool dy[9][10] ;
		 bool grid[10][3][3] ;		
	private:
};

