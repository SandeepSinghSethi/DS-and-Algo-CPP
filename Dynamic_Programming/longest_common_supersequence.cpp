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
int lcs(string s1,string s2,int n , int m)
{
	cout << n << " " << m << endl;
	dp.resize(n+1,vector<int>(m+1,0));

	for(int i = 1;i<=n;i++)
	{
		for(int j = 1;j<=m;j++)
		{
			if(s1[i-1] == s2[j-1]){
				dp[i][j] = 1+dp[i-1][j-1];
			}
			else{
				dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
			}
		}
	}
	string str = "";
	string s = "";
	int i = n , j = m;
	while(i>0 && j>0)
	{
		if(s1[i-1] == s2[j-1])
		{
			str = s1[i-1] + str;
			s = s1[i-1] + s;
			i--;
			j--;
		}
		else
		{
			if(dp[i][j-1] > dp[i-1][j])
			{
				str = s2[j-1] + str;
				j--;
			}
			else
			{
				str = s1[i-1] + str;
				i--;
			}
		}
	}
	cout << s << " " << str << endl;
	while(i>0)
	{
		str = s1[i-1] + str;
		i--;
	}
	while(j>0)
	{
		str = s2[j-1] + str;
		j--;
	}
	cout << str << endl;
	print(dp);
	return dp[n][m];
}

int main(int argc, char const *argv[])
{
	string S1 = "heap";
	string S2 = "pea";
	int n = S1.size();
	int m = S2.size();

	int res = lcs(S1,S2,n,m);
	// for memoization --
	// dp.resize(n+1,vector<int>(m+1,-1));
	cout << res <<  endl;
	return 0;
}