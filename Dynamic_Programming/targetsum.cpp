#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> dp;

void print(vector<vector<int>> ptr)
{
	for(const auto& i : ptr){
		for(const auto& j : i)
			cout<< j << "\t";
		cout << endl;
	}
}

int target_sum(int arr[] ,int n , int t)
{	

	int sum = 0;
	for(int i = 0;i<n;i++)
		sum += arr[i];

	int s1 = (t+sum)/2; // will give the larger or equal sum subset
	int s2 = sum-s1; // will give the smaller subset 

	dp.resize(n+1,vector<int>(s2+1,0));
	dp[0][0] =1 ;
	for(int i = 1;i<=n;i++)
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
	cout << s1 << " " << s2 << " " <<  t << " " << sum << endl;	
	print(dp);
	return (s1 - dp[n][s2]);

}

int main(int argc, char const *argv[])
{
	int arr[] = {9,2,9};
	int n = sizeof(arr)/sizeof(int);

	int t = 3;
	int res = target_sum(arr,n,t);
	cout << res << endl;
	cout << ((res == 1) ? "Target Sum exists " : "Target sum doesn't exists") << endl;
	return 0;
}