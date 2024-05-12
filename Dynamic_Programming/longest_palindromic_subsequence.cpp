#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> dp;

void print(vector<vector<int>> ptr)
{
	for(const auto& i:ptr)
	{
		for(const auto& j : i)
		{
			cout << j << "\t";
		}
		cout << endl;
	}
}

int lps(string s1)
{
	string s2 = s1;
	reverse(s2.begin(),s2.end());
	int n = s1.size(),m = n;
	dp.resize(n+1,vector<int>(m+1,0));
	cout << s1 << " "<< s2 << endl;
	for(int i = 1;i<=n;i++)
	{
		for(int j = 1 ;j<=m;j++)
		{
			if(s1[i-1] == s2[j-1])
			{
				dp[i][j] = 1+dp[i-1][j-1];
			}
			else
			{
				dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
			}
		}
	}
	print(dp);

	int i = n,j = m;
	string str = "";
	while(i>0 && j>0)
	{
		if(s1[i-1] == s2[j-1])
		{
			str = s1[i-1] + str;
			i--;j--;
		}
		else
		{
			if(dp[i][j-1]>dp[i-1][j])
				j--;
			else
				i--;
		}
	}
	cout << str << endl;
	return dp[n][m];
}

int main(int argc, char const *argv[])
{
	string s = "aebcbda";
	int n = s.size();

	int res = lps(s);
	cout << res << endl;

	return 0;
}