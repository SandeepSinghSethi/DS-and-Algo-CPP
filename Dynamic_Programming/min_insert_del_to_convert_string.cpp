#include<bits/stdc++.h>
using namespace std;

void print(vector<vector<int>> ptr)
{
	for(const auto& i : ptr)
	{
		for(const auto& j :i)
		{
			cout << j << "\t";
		}
		cout << endl;
	}
}
vector<vector<int>> dp;

int min_ins_del(string s1,string s2,int n , int m )
{
	if(n == 0|| m == 0)
		return 0;

	dp.resize(n+1,vector<int>(m+1,0));
	for(int i= 1;i<=n;i++)
	{
		for(int j = 1;j<=m;j++)
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
	string str = "";
	int i = n,j = m;

	while(i>0 && j>0)
	{
		if(s1[i-1] == s2[j-1]){
			str = s1[i-1] + str;
			i--;j--;
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
	string s1 = "heap";
	string s2 = "pea";
	int n = s1.size(),m = s2.size();

	int res = min_ins_del(s1,s2,n,m);
	cout << res << endl;

	// min deletion will be the length of first string - lcs  , and minimum insertion will be the length of second string - lcs;

	int ins = 0 , del = 0;
	ins = m-res;
	del = n-res;
	cout << ins << " " << del << endl;
	return 0;
}