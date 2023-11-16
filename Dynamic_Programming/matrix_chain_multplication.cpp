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

int solve(vector<int> arr,int i , int j)
{
	if(i >= j)
		return 0;

	int minimum = INT_MAX;
	int count = 0;

	if(dp[i][j] != -1)
		return dp[i][j];

	for(int k = i;k<j;k++)
	{
		dp[i][j] = solve(arr,i,k) + solve(arr,k+1,j) + (arr[i-1] * arr[k] * arr[j]);

		minimum = min(dp[i][j],minimum);
	}

	return minimum;
}

int main(int argc, char const *argv[])
{
	vector<int> arr = {1,2,3,4,5};
	int n = arr.size();

	dp.resize(n+1,vector<int>(n+1,-1));
	int res = solve(arr,1,n-1);
	cout << res << endl;
	print(dp);

	return 0;
}