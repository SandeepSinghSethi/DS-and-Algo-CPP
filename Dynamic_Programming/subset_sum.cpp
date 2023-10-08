#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> m;
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

int maxsum(int arr[],int n , int s)
{
	if(n == 0 || s == 0)
		return 0;

	if(arr[n-1] <= s)
		return max((arr[n-1] + maxsum(arr,n-1,s-arr[n-1])), maxsum(arr,n-1,s));
	else
		return maxsum(arr,n-1,s);
}

int maxsummem(int arr[],int n , int s)
{
	if(n == 0 || s== 0)
		return 0;

	if(m[n][s] != -1)
		return m[n][s];

	if(arr[n-1] <= s)
		m[n][s] = max((arr[n-1] + maxsummem(arr,n-1,s-arr[n-1])), maxsummem(arr,n-1,s));
	else
		m[n][s] = maxsummem(arr,n-1,s);
}

int maxsumdp(int arr[],int n , int s)
{
	for(int i = 1;i<=n;i++)
	{
		for(int j = 1;j<=s;j++)
		{
			if(arr[i-1] <= j)
				dp[i][j] = max(arr[i-1]+ dp[i-1][j-arr[i-1]], dp[i-1][j]);
			else
				dp[i][j] = dp[i-1][j];
		}
	}
	return dp[n][s];
}

int main(int argc, char const *argv[])
{
	int arr[] = {2,3,7,8,10};//,3,43,2,29,17,24,30,10,4,21};
	int n = sizeof(arr)/sizeof(int);
	int s = 6;
	m.resize(n+1,vector<int>(s+1,-1));
	dp.resize(n+1,vector<int>(s+1,0));


	int sum = maxsum(arr,n,s);
	cout << ((sum != s) ? "Doesn't exists" : to_string(sum)) << endl;

	sum = maxsummem(arr,n,s);
	cout << ((sum != s) ? "Doesn't exists" : to_string(sum)) << endl;
	// print(m);

	sum = maxsumdp(arr,n,s);
	cout << ((sum != s) ? "Doesn't exists" : to_string(sum)) << endl;
	// print(dp);

	return 0;
}