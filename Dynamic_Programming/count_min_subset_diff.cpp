#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> dp;

void print(vector<vector<int>> ptr)
{
	for(const auto& i : ptr)
	{
		for(const auto& j: i)
			cout<< j << "\t";
		cout << endl;
	}
}

int min_dif(int arr[],int n,int diff)
{
	int sum = 0;
	for(int i = 0;i<n;i++)
		sum += arr[i];

	int s1 = (diff + sum)/2;
	int s2 = sum-s1;

	dp.resize(n+1,vector<int>(s2+1,0));
	dp[0][0] = 1;
	for(int i=1;i<=n;i++)
		dp[i][0] = 1;

	for(int i = 1;i<=n;i++)
	{
		for(int j = 1;j<=s2;j++)
		{
			if(arr[i-1] <= j)
				dp[i][j] = dp[i-1][j-arr[i-1]] + dp[i-1][j];
			else
				dp[i][j] = dp[i-1][j];
		}
	}
	cout << s1 << " " << s2 << " " <<  diff << endl;	
	print(dp);
	return dp[n][s2];
}

int main(int argc, char const *argv[])
{
	int arr[] = {1, 1, 2, 3} ;
	int n = sizeof(arr)/sizeof(int);
	int diff = min_dif(arr,n,2);
	cout << diff << endl;

	return 0;
}