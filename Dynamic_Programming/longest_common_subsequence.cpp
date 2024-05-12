#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> dp;

void print(vector<vector<int>> ptr)
{
	for(const auto& i :ptr){
		for(const auto& j : i){
			cout << j << "\t";
		}
		cout << endl;
	}

	cout << endl;
}

// tabular approach
int lcs(string s1,string s2,int n , int m)
{
	cout << n << " " << m << endl;
	dp.resize(n+1,vector<int>(m+1,0));

	for(int i = 1;i<=n;i++)
	{
		for(int j = 1;j<=m;j++)
		{
			if(s1[i-1] == s2[j-1]){
				// str += s1[i-1];	
				dp[i][j] = 1+dp[i-1][j-1];
			}
			else{
				dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
			}
		}
	}

	string str = "";
	int i = n , j = m;
	while(i>0 && j>0)
	{
		if(s1[i-1] == s2[j-1])
		{
			str = s1[i-1] + str;
			i--;
			j--;
		}
		else
		{
			if(dp[i][j-1] > dp[i-1][j]){
				j--;
			}
			else{
				i--;
			}
		}
	}
	cout << str << endl;
	print(dp);
	return dp[n][m];
}

// memoization approach
// int lcs(string s1,string s2,int n ,int m,vector<vector<int>> dp)
// {
// 	if(n <= 0 || m <= 0)
// 		return 0;

// 	if(s1[n-1] == s2[n-1])
// 		dp[n][m] = 1+lcs(s1,s2,n-1,m-1,dp);

// 	if(dp[n][m] != -1)
// 		return dp[n][m];	
	
// 	dp[n][m] = max(lcs(s1,s2,n,m-1,dp),lcs(s1,s2,n-1,m,dp));

// 	return dp[n][m];
// }

// recursive approach
// int lcs(string s1,string s2,int n , int m)
// {
// 	if(n == 0 || m == 0)
// 		return 0;

// 	if(s1[n-1] == s2[n-1]){
// 		return 1+ lcs(s1,s2,n-1,m-1);
// 	}
// 	else{
// 		return max(lcs(s1,s2,n,m-1),lcs(s1,s2,n-1,m));
// 	}
// }

int main(int argc, char const *argv[])
{
	string S1 = "AGGTAB";
	string S2 = "GTXTAYB";
	int n = S1.size();
	int m = S2.size();

	int res = lcs(S1,S2,n,m);
	// for memoization --
	// dp.resize(n+1,vector<int>(m+1,-1));
	cout << res <<  endl;
	return 0;
}