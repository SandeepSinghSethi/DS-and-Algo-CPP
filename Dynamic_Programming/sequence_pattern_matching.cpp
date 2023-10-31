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

int spm(string s1,int n , string s2 ,int m)
{
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
	print(dp);
	return ((dp[n][m] == min(n,m)) ? 1 : 0);
}

int main(int argc, char const *argv[])
{
	string s1 = "AXY";
	string s2 = "ADXCPY";
	int n = s1.size();
	int m = s2.size();

	int res = spm(s1,n,s2,m);
	cout << res << endl;
	return 0;
}