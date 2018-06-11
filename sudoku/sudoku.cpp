#include<cstdio>
#include<cstdlib>
#include"sudoku.h"
#include<cstring>
#include<ctime>
sudoku::sudoku()
{
	e = 0;
	memset(board,0,sizeof(board));
	memset(dx,0,sizeof(dx));
	memset(dy,0,sizeof(dy));
	memset(grid,0,sizeof(grid));
}
void sudoku::get_start(char level)
{
	if(level == 'e')
	{
		rand_(30);	
	}
	else if(level == 'n')
	{
		rand_(15);
	}
	else if(level == 'd')
	{
		rand_(10);
	}
}
void sudoku::answer()
{
	backtrack(0,0);	
}
void sudoku::rand_(int num)
{
	int rand_num;
	int rand_x,rand_y;
	srand(time(NULL));
	for(int i=1;i<=num;i++)
	{
		rand_num = rand()%9+1;
		rand_x = rand()%9;
		rand_y = rand()%9;
		
		if(!dx[rand_x][rand_num] && !dy[rand_y][rand_num] && !grid[rand_num][rand_x/3][rand_y/3] && board[rand_x][rand_y]==0)
		{
			dx[rand_x][rand_num]=dy[rand_y][rand_num] = grid[rand_num][rand_x/3][rand_y/3]=true;
			board[rand_x][rand_y] = rand_num;
		}
		else
		{
			--i;
		}
	}
}

void sudoku::valid()
{
	int i,j;
	bool dx[10],dy[10];
	memset(dx,0,sizeof(dx));
	memset(dy,0,sizeof(dy));
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(!dx[board[i][j]])
				dx[board[i][j]] = true;
			else
			{
				printf("Incorrect!\n");
				return;
			}
			if(!dy[board[j][i]])
				dy[board[j][i]] = true;
			else 
			
				printf("Incorrect!\n");
				return;
			}
	}
	
	int l,m;
	bool grid[10];
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
		{	
			memset(grid,0,sizeof(grid));
			for(l=i;i<3*i+2;l++)
				for(m=j;m<3*j+2;m++)
					if(!grid[board[l][m]])
					{
						grid[board[l][m]] = true;
					}
					else
					{
						printf("Incorrect!\n");	
						return;
					}
		}	
}
void sudoku::backtrack(int x,int y)
{
	if(y == 9) {x++;y=0;}
	if(e == 1) return;
	if(x == 9)
	{	
		e =1;
		print();
		return;
	}
	for(int i=1;i<=9;i++)
	{
		if(board[x][y]==0 && !dx[x][i] && !dy[y][i] && !grid[i][x/3][y/3])
		{
			board[x][y] = i;
			dx[x][i] = dy[y][i] = grid[i][x/3][y/3] = true;
			backtrack(x,y+1);
			if(e ==1)
			return;
			
			dx[x][i] = dy[y][i] = grid[i][x/3][y/3] = false;
			board[x][y] = 0;
		}
			
	}
		
	backtrack(x,y+1);
	
}
void sudoku::print()
{
	int x,y;
	for(x=0;x<9;x++)
	{	for(y=0;y<9;y++)
		{
			printf("%d ",board[x][y]);
		}
		printf("\n");
	}	
}
