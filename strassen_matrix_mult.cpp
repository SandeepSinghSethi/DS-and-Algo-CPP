#include<bits/stdc++.h>
using namespace std;

int ** create_matrix(int row)
{
	int **temp = new int*[row];
	for(int i = 0;i<row;i++)
	{
		temp[i] = new int[row];
	}
	return temp;
}

void **settozero(int **A,int r, int c)
{
	for(int i = 0;i<r;i++)
	{
		for(int j = 0;j<c;j++)
		{
			A[i][j] = 0;
		}
	}
}

void printmatrix(int **A,int r , int c)
{
	for(int i = 0;i<r;i++)
	{
		for(int j =0;j<c;j++)
		{
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int **add(int **A,int ** B,int n)
{
	int **temp = create_matrix(n);
	for(int i = 0;i<n;i++)
	{
		for(int j = 0;j<n;j++)
		{
			temp[i][j] = A[i][j] + B[i][j];
		}
	}
	return temp;
}

int **sub(int **A,int ** B,int n)
{
	int **temp = create_matrix(n);
	for(int i = 0;i<n;i++)
	{
		for(int j = 0;j<n;j++)
		{
			temp[i][j] = A[i][j] - B[i][j];
		}
	}
	return temp;
}

int ** strassen_multiply(int ** A,int ** B,int n)
{
	if(n == 1)
	{
		int ** C = create_matrix(1);
		C[0][0] = A[0][0] * B[0][0];
		return C;
	}
	else
	{
		// if n > 1 then creating submatrices of size k (n/2)

		int ** C = create_matrix(n);
		int k = n/2;

		// creating 8 submatrices of size k each
		int ** A11 = create_matrix(k);
		int ** A12 = create_matrix(k);
		int ** A21 = create_matrix(k);
		int ** A22 = create_matrix(k);
		int ** B11 = create_matrix(k);
		int ** B12 = create_matrix(k);
		int ** B21 = create_matrix(k);
		int ** B22 = create_matrix(k);

		for(int i = 0;i<k;i++)
		{
			for(int j= 0;j<k;j++)
			{
				A11[i][j] = A[i][j];
				A12[i][j] = A[i][k+j];
				A21[i][j] = A[k+i][j];
				A22[i][j] = A[k+i][k+j];
				B11[i][j] = B[i][j];
				B12[i][j] = B[i][k+j];
				B21[i][j] = B[k+i][j];
				B22[i][j] = B[k+i][k+j];
			}
		}


		// formula
		// MATRIX
		//		A11      A12 			B11 	B12
		//	[A11 A12] [A13 A14]		[B11 B12] [B13 B14]
		//	[A21 A22] [A23 A24]		[B21 B22] [B23 B24]
		//
		//		A21 	 A22			B21 	B22
		// 	[A31 A32] [A33 A34]		[B31 B32] [B33 B34]
		//	[A41 A42] [A43 A44]		[B41 B42] [B43 B44]
		//
		// - P1 = A11.(B12-B22)			C1 = P5+P4-P2+P6
		// - P2 = (A11+A12).B22 		C2 = P1+P2
		// - P3 = (A21+A22).B11 		C3 = P3+P4
		// - P4 = A22.(B21-B11) 		C4 = P5+P1-P3-P7
		// - P5 = (A11+A22).(B11+B22)
		// - P6 = (A12-A22).(B21+B22)
		// - P7 = (A11-A21).(B11+B12)

		int ** P1 = strassen_multiply(A11,sub(B12,B22,k),k);
		
		int ** P2 = strassen_multiply(add(A11,A12,k),B22,k);
		
		int ** P3 = strassen_multiply(add(A21,A22,k),B11,k);
		
		int ** P4 = strassen_multiply(A22,sub(B21,B11,k),k);
		
		int ** P5 = strassen_multiply(add(A11,A22,k),add(B11,B22,k),k);
		
		int ** P6 =	strassen_multiply(sub(A12,A22,k),add(B21,B22,k),k);
		
		int ** P7 = strassen_multiply(sub(A11,A21,k),add(B11,B12,k),k);
		

		// merge all data to the C matrix

		int **C11 = sub(add(add(P5,P6,k),P4,k),P2,k);
		int **C12 = add(P1,P2,k);
		int **C21 = add(P3,P4,k);
		int **C22 = sub(sub(add(P5,P1,k),P3,k),P7,k);

		for(int i=0;i<k;i++)
		{
			for(int j = 0;j<k;j++)
			{
				C[i][j] = C11[i][j];
				C[i][j+k] = C12[i][j];
				C[i+k][j] = C21[i][j];
				C[i+k][j+k] = C22[i][j];
			}
		}
		return C;
	}	
}

void input(int ** A,int n)
{
	cout << "Enter the data in the matrix " << endl;
	for(int i = 0;i<n;i++)
	{
		cout << "Enter data "<<n<< " times : " << endl;
		for(int j = 0;j<n;j++)
		{	
			cout << "\t\t=> ";
			cin >> A[i][j];
		}
	}
	cout << endl;
}

void input_auto(int ** A,int n)
{
	cout << endl;
	srand(time(0));
	for(int i = 0;i<n;i++)
	{
		for(int j = 0;j<n;j++)
		{	
			A[i][j] = (rand() % 10 ) + 1;
		}
	}
	cout << endl;
}


int main(int argc, char const *argv[])
{
	std::ios::sync_with_stdio(false);
	int r1,c1 = 0,r2 =1,c2;

	cout << "\t** If you see the loop again and again , it's because entered matrix dimensions can't be multiplied.. **" << endl << endl;

	while(c1 != r2)
	{
		cout << "Enter the row and cols of matrixA and matrixB.." << endl;
		cout << "Enter the row of matrixA: ";
		cin >> r1;
		cout << "Enter the col of matrixA: ";
		cin >> c1;

		cout << "Enter the row of matrixB: ";
		cin >> r2;
		cout << "Enter the col of matrixB: ";
		cin >> c2;
	}

	int **A;
	int **B;
	int **C;

	int temp = 0,i=0,j=0,k=0;
	
	// if the dimension of matrix is not equal to any 2^n then strassen algo will fail , so we pad k blocks in the matrix such that the size/dimension of created matrix is of 2^n;

	float ispower2 = log2(r2);

	cout << ispower2 << " " << ceil(ispower2) << " " << floor(ispower2) << endl;

	if(ceil(ispower2) != floor(ispower2))
	{

		// difference between the value of r2 and next higher value of 2^n
		k = pow(2,ceil(ispower2)) - r2;
		r2 = pow(2,ceil(ispower2));

		A = create_matrix(r2);
		B = create_matrix(r2);
		settozero(A,r2,r2);
		settozero(B,r2,r2);

		// set r2 to original value to prevent any hassle
		r2 -= k;

	}	
	else
	{
		A = create_matrix(r1);
		B = create_matrix(r2);
	}

	int c = 0;

	cout << "Enter 0 (if custom value) or 1 (if random value) to be inserted in the created matrix:  ";
	cin >>c;

	if(c>0)
	{
		input_auto(A,r1);
		// printmatrix(A,r1,r1);
		input_auto(B,r1);
		// printmatrix(B,r2,r2);
	}
	else
	{
		input(A,r1);
		printmatrix(A,r1,r1);
		input(B,r2);
		printmatrix(B,r2,r2);
	}


	if(ceil(ispower2) != floor(ispower2))
	{

		C = strassen_multiply(A,B,r2+k);

	}
	else
	{
		C = strassen_multiply(A,B,r1);	
	}
	printmatrix(C,r1,r1);		

	return 0;
}

		