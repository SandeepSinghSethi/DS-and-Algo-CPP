#include<bits/stdc++.h>
using namespace std;

// int rodcut(int arr[], int len[] , int n,int s)
// {
// 	if(n == 0)
// 		return 0;

// 	if(len[n-1] <= s)
// 		return max(arr[n-1] + rodcut(arr,len,n,s-len[n-1]),rodcut(arr,len,n-1,s));
// 	else
// 		return rodcut(arr,len,n-1,s);
// }
vector<vector<int>> dp;

void print(vector<vector<int>> ptr)
{
	for(const auto& i : ptr){
		for(const auto& j : i){
			cout<< j << "\t";
		}
		cout<< endl;	
	}
	cout << endl;
}

int rodcut(int arr[],int len[] ,int n ,int s)
{
	if(n == 0)
		return 0;

	dp.resize(n+1,vector<int>(n+1,0));

	for(int i = 1;i<=n;i++)
	{
		for(int j = 1;j<=n;j++)
		{
			if(len[i-1] <= j)
			{
				dp[i][j] = max(arr[i-1] + dp[i][j-len[i-1]],dp[i-1][j]);
			}
			else
			{
				dp[i][j] = dp[i-1][j];
			}
		}
	}
	print(dp);
	return dp[n][n];
}

int main(int argc, char const *argv[])
{
	int arr[] = {1,5,8,9,10,17,17,20};
	int len[] = {1,2,3,4,5,6,7,8};
	int n = sizeof(arr)/sizeof(int);

	int res = rodcut(arr,len,n,n);
	cout << res << endl;
	return 0;
}