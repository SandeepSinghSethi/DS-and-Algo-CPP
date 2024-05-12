#include<bits/stdc++.h>
using namespace std;

void print_map(unordered_map<string,int> mp)
{
	for(const auto& entry : mp)
	{
		cout << entry.first << " -> " << entry.second << '\n';
	}
}

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


unordered_map<string , int> mp;

// int solve(int e,int f)
// {
// 	if(e == 1)
// 		return f;

// 	if(f == 0 || f == 1)
// 		return f;

// 	string s = to_string(e) + "e_f" + to_string(f);
// 	if(mp.find(s) != mp.end())
// 		return mp[s];

// 	int minimum = INT_MAX;
// 	int temp;

// 	for(int k = 1;k<=f;k++) // because we will start from 1st floor to kth one
// 	{
// 		string s1 = to_string(e-1) + "e_f" + to_string(k-1);
// 		string s2 = to_string(e) + "e_f" + to_string(f-k);

// 		int t1,t2 ;
// 		t1 = (mp.find(s1) != mp.end()) ? mp[s1] : solve(e-1,k-1);
// 		t2 = (mp.find(s2) != mp.end()) ? mp[s2] : solve(e,f-k);



// 		// temp = 1+  max(solve(e-1,k-1), solve(e,f-k)) ;
// 		temp  = 1+max(t1,t2);
// 		minimum = min(temp,minimum);
// 	}
	
// 	return mp[s] = minimum;
// }

int solve(int e,int f)
{
	dp.resize(e+1,vector<int>(f+1,0));

	for(int i = 1;i<=e;i++)
	{
		dp[i][1] = 1;
		dp[i][0] = 0;
	}

	if(e == 1)
		return f;

	if(f == 0 || f== 1)
		return f;

	for(int j = 1;j<=f;j++)
	{
		dp[1][j] = j;
	}


	for(int i = 2;i<=e;i++)
	{
		for(int j = 2;j<=f;j++)
		{
			dp[i][j] = INT_MAX;

			for(int k = 1;k<=j;k++)
			{
				int temp = 1 + max(dp[i-1][k-1],dp[i][j-k]);
				dp[i][j] = min(dp[i][j],temp);
			}
		}
	}
	print(dp);
	return 1;
}

int main(int argc, char const *argv[])
{
	int egg = 3;
	int fl = 5;

	int res = solve(egg,fl);
	cout << "RES -> " << res << endl;
	print_map(mp);
	return 0;
}