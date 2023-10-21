#include<bits/stdc++.h>
using namespace std;

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


// int coin_max(int arr[],int n , int sum){
// 	if(n == 0 || sum < 0)
// 		return 0;
// 	if(sum == 0)
// 		return 1;

// 	if(arr[n-1] <= sum)
// 		return coin_max(arr,n,sum-arr[n-1])+coin_max(arr,n-1,sum);
// 	else
// 		return coin_max(arr,n-1,sum);
// }

vector<vector<int>> dp;

// int coin_max(int arr[] , int n , int sum)
// {
// 	if(n == 0 || sum == 0)
// 		return 0;

// 	dp.resize(n+1,vector<int>(sum+1,0));
// 	for(int i = 0 ;i<=n;i++)
// 		dp[i][0] = 1;

// 	for(int i = 1 ; i<= n ;i++)
// 	{
// 		for(int j = 1;j<=sum;j++)
// 		{
// 			if(arr[i-1] <= j)
// 				dp[i][j] = dp[i][j-arr[i-1]] + dp[i-1][j];
// 			else
// 				dp[i][j] = dp[i-1][j];
// 		}
// 	}

// 	print(dp);
// 	return dp[n][sum];	
// }

int coin_max(int arr[],int n ,int sum)
{
	// space optimization to O(n)
	if(n == 0 || sum == 0)
		return 0;

	vector<int> dp(sum+1,0);
	dp[0] =1 ;

	for(int i = 0;i<n;i++)
	{
		for(int j = arr[i];j<=sum;j++)
		{
			dp[j] += dp[j-arr[i]];
		}
	}

	for(const auto& i: dp)
		cout << i << " ";
	cout << endl;
	return dp[sum];
}

int min_count(int arr[] ,int n , int sum)
{
	if(n == 0 || sum ==0)
		return 0;

	vector<vector<int>> dp;
	dp.resize(n+1,vector<int>(sum+1,INT_MAX-1));
	for(int i = 1;i<=n;i++)
		dp[i][0] = 0;

	for(int i = 1;i<=sum ;i++)
	{
		if(i%arr[0] == 0)
		{
			dp[1][i] = i/arr[0]	;
		}
		else
			dp[1][i]= INT_MAX-1;
	}

	for(int i = 2;i<=n;i++)
	{
		for(int j =1;j<=sum;j++)
		{
			if(arr[i-1] <= j)
				dp[i][j] = min(dp[i][j-arr[i-1]] + 1,dp[i-1][j]);
			else
				dp[i][j] = dp[i-1][j];
		}
	}	

	print(dp);
	return dp[n][sum];
}

int main(int argc, char const *argv[])
{
	int arr[] = { 15, 1};
	int n = sizeof(arr)/sizeof(int);
	int sum = 5;

	int res = coin_max(arr,n,sum);
	cout << res << endl;
	res = min_count(arr,n,4);	
	cout << res << endl;
	return 0;
}