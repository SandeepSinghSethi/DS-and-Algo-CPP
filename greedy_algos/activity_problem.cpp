#include<bits/stdc++.h>
using namespace std;

struct Time{
	int start,finish;
};	

void print(vector<Time> ptr)
{
	int n = 1;
	for(const auto& i : ptr)
	{
		cout << n << ". "<< i.start << " : " << i.finish << endl;
		n++;
	}
	cout << endl;
}

// vector<Time> result;
void solve(vector<Time> ptr)//,int k,int n)
{
	// Time o;
	int i =0;

	cout << "(" << ptr[0].start << " : " << ptr[0].finish << ")";
	for(int j = 1;j<ptr.size();j++)
	{
		if(ptr[j].start >= ptr[i].finish)
		{
			cout << "(" << ptr[j].start << " : " << ptr[j].finish << ")" ;
			i = j;
		}
	}
	// if(k==0)
	// 	result.push_back(ptr[k]);
	// int m = k+1;
	// while(m<=n && ptr[m].start < ptr[k].finish)
	// 	m++;

	// if(m<=n)
	// {
	// 	result.push_back(ptr[m]);
	// 	solve(ptr,m,n);
	// }
	
}

// this code doesn't provide the optimal solution for the problem , that's why using greedy is a must here
bool cmp(Time &a, Time &b ){
	return (a.finish < b.finish);
}

// int solve(vector<Time>& ptr)
// {
// 	int n = ptr.size();
// 	sort(ptr.begin(),ptr.end(),cmp);
// 	print(ptr);
// 	vector<int> dp(n+1,0);

// 	for(int i = 1;i<=n;i++)
// 	{
// 		for(int j = 0;j<i;j++)
// 		{
// 			if(ptr[i-1].start >= ptr[j].finish)
// 				dp[i] = max(dp[i],dp[j]+1);
// 		}
// 	}

// 	for(const auto& i : dp)
// 		cout << i << " " ;
// 	cout << endl;

// 	int maxact = *max_element(dp.begin(),dp.end());
// 	cout << maxact << endl;

// 	vector<Time> act;
// 	int j= 0;
// 	for(int i = 1;i<=n;i++)
// 	{
// 		if(dp[j] < dp[i]){
// 			act.push_back(ptr[i-1]);
// 			j = i;
// 		}
// 	}

// 	print(act);
// }

int main(int argc, char const *argv[])
{
	vector<Time> activity= {{1,4},{3,5},{0,6},{5,7},{3,9},{5,9},{6,10},{7,11},{8,12},{2,14},{12,16}};
	sort(activity.begin(),activity.end(),cmp);
	print(activity);
	solve(activity);//,0,activity.size()-1);
	// print(result);
	return 0;
}