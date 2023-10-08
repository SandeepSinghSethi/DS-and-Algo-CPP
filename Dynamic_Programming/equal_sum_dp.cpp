#include<bits/stdc++.h>
using namespace std;

std::vector<std::vector<int>> dp;

// in equal sum partition we have to find in an array the values which are equal to the sum of remaining values in an array


void print(vector<vector<int>> ptr)
{
	for(const auto& i : ptr)
	{
		for(const auto& j : i)
			cout << j << "\t";
		cout << endl;
	}
}

int equalsum(int arr[],int n )
{	
	// getting the sum , if sum is even equal partition exist else not.
	int sum  = 0;
	for(int i = 0;i<n;i++)
	{
		sum += arr[i];
	}
	if(sum%2 != 0)
		return 0;

	int s = sum/2;
	dp.resize(n+1,vector<int>(s+1,0));

	for(int i = 1;i<=n;i++)
	{
		for(int j = 1;j<=s;j++)
		{
			if(arr[i-1] <= j)
			{
				dp[i][j] = max(arr[i-1] + dp[i-1][j-arr[i-1]],dp[i-1][j]);
			}
			else
			{
				dp[i][j] = dp[i-1][j];
			}
		}
	}
	// print(dp);
	cout << dp[n][s] << endl;
	return (dp[n][s] == s) ? 1 : 0;

}

int main(int argc, char const *argv[])
{
	int arr[] = {1,5,5,1,2};
	int n = sizeof(arr)/sizeof(int);

	if(equalsum(arr,n))
	{
		cout << "Equal sum partition exists.." << endl;
	}
	else
	{
		cout << "Equal sum partition doesn't exists" << endl;
	}
	return 0;
}