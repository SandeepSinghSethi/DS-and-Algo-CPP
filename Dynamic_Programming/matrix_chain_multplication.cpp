#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> dp;

void print(vector<vector<int>> ptr)
{
	for(const auto& i : ptr)
	{
		for(const auto& j:i)
		{
			cout << j << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

// int solve(vector<int> arr,int i , int j)
// {
// 	if(i >= j)
// 		return 0;

// 	int minimum = INT_MAX;
// 	int count = 0;

// 	if(dp[i][j] != -1)
// 		return dp[i][j];

// 	for(int k = i;k<j;k++)
// 	{
// 		dp[i][j] = solve(arr,i,k) + solve(arr,k+1,j) + (arr[i-1] * arr[k] * arr[j]);

// 		minimum = min(dp[i][j],minimum);
// 	}

// 	return minimum;
// }

void printbracket(int i , int j , vector<vector<int>> bracket,char &name)
{
	if(i == j)
	{
		cout << name++;
		return;
	}

	cout << "(";

	printbracket(i,bracket[i][j],bracket,name);
	printbracket(bracket[i][j] + 1 , j,bracket,name);

	cout << ")";
}

int solve(vector<int> arr , int n)
{
	dp.resize(n+1,vector<int>(n+1,0));
	vector<vector<int>> bracket(n,vector<int>(n,0));


	for(int L = 2;L < n;L++)
	{
		for(int i = 1;i<n-L+1;i++)
		{
			int j = i+L-1;
			dp[i][j] = INT_MAX;

			for(int k = i;k<j;k++)
			{
				int q = dp[i][k] + dp[k+1][j] + (arr[i-1] * arr[k] * arr[j]);

				if(q < dp[i][j])
				{
					dp[i][j] = q;
					bracket[i][j] = k;
				}				
			}
		}
	}
	print(dp);
	print(bracket);

	char name = 'A';
	printbracket(1,n-1,bracket,name);
	cout << endl;
	return dp[1][n-1];
}

int main(int argc, char const *argv[])
{
	vector<int> arr = {1,2,3,4,5};
	int n = arr.size();

	// dp.resize(n+1,vector<int>(n+1,-1));
	// int res = solve(arr,1,n-1);
	int res = solve(arr,n);
	cout << res << endl;
	// print(dp);

	return 0;
}