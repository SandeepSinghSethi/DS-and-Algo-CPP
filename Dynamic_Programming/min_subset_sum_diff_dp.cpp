#include<bits/stdc++.h>
using namespace std;

std::vector<std::vector<int>> dp;
vector<int> ind;

void print(vector<vector<int>> ptr)
{
	for(const auto& i : ptr)
	{
		for(const auto& j : i)
			cout << j << "\t";
		cout << endl;
	}

}

int min_rec(int arr[],int n,int s)
{
	if(n == 0 || s == 0)
		return 0;

	if(arr[n-1] <= s)
		return max((arr[n-1]+min_rec(arr,n-1,s-arr[n-1])),min_rec(arr,n-1,s));
	else
		return min_rec(arr,n-1,s);
}

int min_dif(int arr[],int n)
{
	int sum=0;
	for(int i = 0 ; i<n;i++)
		sum += arr[i];

	int k = floor(sum/2);
	cout << sum << " " << k<<endl;
	dp.resize(n+1,vector<int>(k+1,0));

	for(int i = 1;i<=n;i++)
	{
		for(int j = 1;j<=k;j++)
		{
			if(arr[i-1] <= j)
				dp[i][j] = max(arr[i-1] + dp[i-1][j-arr[i-1]], dp[i-1][j]);
			else
				dp[i][j] = dp[i-1][j];
		}
	}
	// print(dp);
	// cout << sum << " "<< k << " " << dp[n][k] << endl;
	return abs(sum - dp[n][k]*2);
}

int sumofarr(int arr[],int n)
{
	int sum = 0;
	for(int i= 0;i<n;i++)
		sum += arr[i];
	return sum;
}

int main(int argc, char const *argv[])
{
	// int arr[] = {45, 34, 4, 12, 5, 2};
	int arr[] = {1,6,11,5,10};
	int n = sizeof(arr)/sizeof(int);

	int diff = min_dif(arr,n);
	cout << diff << endl;

	int d = min_rec(arr,n,sumofarr(arr,n)/2);
	cout << abs(sumofarr(arr,n)-d*2) << endl;

	return 0;
}