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

int lrs(string s1,int n)
{
	string s2 = s1;
	int m = s2.size();

	dp.resize(n+1,vector<int>(m+1,0));

	for(int i = 1;i<=n;i++)
	{
		for(int j = 1;j<=m;j++)
		{
			if(s1[i-1] == s2[j-1] && i != j ){
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
		if(s1[i-1] == s2[j-1] && i!=j)
		{
			str = s1[i-1] + str;
			i--;
			j--;
		}
		else
		{
			if(dp[i][j-1] > dp[i-1][j])
			{
				j--;
			}
			else
			{
				i--;
			}
		}
	}

	cout << str << endl;
	print(dp);
	return dp[n][m];
}

int main(int argc, char const *argv[])
{
	string s1 = "AABEBCDD";
	int n = s1.size();

	int res = lrs(s1,n);
	cout << res << endl;
	return 0;
}