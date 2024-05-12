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

int lcsub(string s1,string s2,int n , int m)
{
	if(n == 0 || m == 0)
		return 0;

	string str = "";
	int ans = 0;

	dp.resize(n+1,vector<int>(m+1,0));

	for(int i = 1;i<=n;i++)
	{
		for(int j = 1 ;j<=m;j++)
		{
			if(s1[i-1] == s2[j-1])
			{
				str += s1[i-1];
				dp[i][j] = 1+dp[i-1][j-1];
				ans = max(ans,1+dp[i-1][j-1]);
			}
			else
			{
				dp[i][j] = 0;
			}
		}
	}		
	cout << str << ans << endl;
	print(dp);
	return ans;
}

int main(int argc, char const *argv[])
{
	string S1 = "abcdgh";
	string S2 = "abedfhr";
	int n = S1.size();
	int m = S2.size();

	int res = lcsub(S1,S2,n,m);
	cout << res << endl;
	return 0;
}