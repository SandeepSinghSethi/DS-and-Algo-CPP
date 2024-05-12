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

int isPalindrome(string s1,int i , int j)
{
	while(i<j)
	{
		if(s1[i] != s1[j]){
			return 0;
		}
		i++;
		j--;
	}
	return 1;
}

int solve(string s1,int i , int j)
{
	if(i>=j || isPalindrome(s1,i,j))
		return 0;

	if(dp[i][j] != -1)
		return dp[i][j];

	int minimum = INT_MAX;
	int count = 0;

	for(int k = i;k<j;k++)
	{
		// count = solve(s1,i,k) + solve(s1,k+1,j)+1;
		// a little optimization to prevent recursive calls which are done
		int left,right;

		if(dp[i][k] != -1)
			left = dp[i][k];
		else
			left = solve(s1,i,k);

		if(dp[k+1][k] != -1)
			right = dp[k+1][j];
		else
			right = solve(s1,k+1,j);

		count = 1+left+right;
		minimum = min(count,minimum);
	}

	return dp[i][j] = minimum;
}


int main(int argc, char const *argv[])
{
	string s1 = "geek";
	int n = s1.size();

	dp.resize(n+1,vector<int>(n+1,-1));
	int res = solve(s1,0,n-1);
	cout << res << endl;
	print(dp);
	return 0;
}