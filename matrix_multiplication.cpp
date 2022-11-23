#include <bits/stdc++.h>
using namespace std;

#define R1 3
#define C1 3
#define R2 3
#define C2 3
#define MAX 100

void print_matrix(string display,int matrix[MAX][MAX],auto row_start,auto column_start,auto row_end,auto column_end)
{
	cout << endl << display << "=> " << endl;
	for(int i = row_start;i<row_end;i++)
	{
		for(int j = column_start;j<column_end;j++)
		{
			cout << "\t" << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	return;
}

int matrixC[MAX][MAX] = {0};

void matrix_multiplication(int row1,int col1,int matrixA[][MAX] , int row2,int col2,int matrixB[][MAX],int matrixC[][MAX])
{
	static int i=0,j=0,k=0;

	if(i>=row1){
		return;
	}

	if(j<col2)
	{
		if(k < col1)
		{
			matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
			k++;

			matrix_multiplication(row1,col1,matrixA,row2,col2,matrixB,matrixC);
		}

		k=0;
		j++;
		matrix_multiplication(row1,col1,matrixA,row2,col2,matrixB,matrixC);
	}

	j = 0;
	i++;
	matrix_multiplication(row1,col1,matrixA,row2,col2,matrixB,matrixC);
}


void matrix_iterative(int row1,int col2,int matrixA[][MAX],int matrixB[][MAX],int matrixD[][MAX])
{
	for(int i = 0;i<row1;i++)
	{
		for(int j = 0;j<col2;j++)
		{
			for(int k = 0;k<col2;k++)
			{
				matrixD[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	int matrixA[][MAX] = { {5,1,12,},
							{6,7,3},
							{66,-1,-12}
						  };

	
	int matrixB[][MAX] = { {4,-2,12},
						   {6,-7,-54},
						   {2,1,0}
						  };

    if(R1 != C2)
    {
    	cout << "Not possible" << endl;
    	return -1;
    }

	print_matrix("Matrix A",matrixA,0,0,R1,C1);
	print_matrix("Matrix B",matrixB,0,0,R2,C2);

	matrix_multiplication(R1,R2,matrixA,R2,C2,matrixB,matrixC);

	print_matrix("Matrix C",matrixC,0,0,R1,C2);

	int matrixD[MAX][MAX] = {0};

	matrix_iterative(R1,C2,matrixA,matrixB,matrixD);
	print_matrix("Matrix D",matrixD,0,0,R1,C2);

	return 0;
}