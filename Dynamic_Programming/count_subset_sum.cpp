#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> dp;

void print(vector<vector<int>> ptr)
{
	for(const auto& i : ptr)
	{
		for(const auto& j : i)
			cout << j << "\t";
		cout << endl;
	}
}

int subsetdp(int arr[],int n , int s)
{
	for(int i = 1;i<=n;i++)
	{
		for(int j = 1;j<=s;j++)
		{
			if(arr[i-1] <= j)
			{
				dp[i][j] = dp[i-1][j-arr[i-1]]+dp[i-1][j];	
			else
			{
				dp[i][j] = dp[i-1][j];
			}
		}
	}
	print(dp);
	return dp[n][s];
}

int main(int argc, char const *argv[])
{
	int arr[] = {2,3,5,6,7,10};
	int n = sizeof(arr)/sizeof(int);	
	int s = 10;
	dp.resize(n+1,vector<int>(s+1,0));
	dp[0][0] = 1;
	for(int i = 1;i<=s;i++)
	{
		dp[0][i] = 0;
		if(i<=n)
			dp[i][0] = 1;
	}
	int sum = subsetdp(arr,n,s);
	cout << sum << " " << endl;
	return 0;
}