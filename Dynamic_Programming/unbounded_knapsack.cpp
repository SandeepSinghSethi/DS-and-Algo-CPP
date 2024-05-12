#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> dp;

void print(vector<vector<int>> ptr)
{
	for(const auto& i : ptr)
	{
		for(const auto& j : i )
		{
			cout << j << "\t";
		}
		cout << endl;
	}
}

int unb_knapsack(int arr[],int wt[],int n ,int W)
{
	if(n == 0 || W == 0)
	{
		return 0;
	}

	if(wt[n-1] <= W)
		return max(arr[n-1] + unb_knapsack(arr,wt,n,W-wt[n-1]),unb_knapsack(arr,wt,n-1,W));
	else
		return unb_knapsack(arr,wt,n-1,W);
}

int unb_knapsackdp(int item[], int wt[] , int n , int W){
	if(n == 0 || W == 0)
		return 0;

	dp.resize(n+1,vector<int>(W+1,0));

	for(int i = 1;i<=n;i++)
	{
		for(int j = 1;j<=W;j++)
		{
			if(wt[i-1] <= j)
			{
				dp[i][j] = max(item[i-1] + dp[i][j-wt[i-1]],dp[i-1][j]);
			}
			else
			{
				dp[i][j] = dp[i-1][j];	
			}
		}
	}
	print(dp);
	return dp[n][W];
}

int main(int argc, char const *argv[])
{
	int val[] = {1,40,50,70};
	int wt[] = {1,3,4,5};
	int W = 8;
	int n = sizeof(val)/sizeof(int);

	int res = unb_knapsack(val,wt,n,W);
	cout << res << endl;
	res = unb_knapsackdp(val,wt,n,W);
	cout << res <<endl;
	return 0;
}