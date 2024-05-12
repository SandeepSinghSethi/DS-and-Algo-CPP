#include<bits/stdc++.h>
using namespace std;

int sum(vector<int> freq,int i ,int j)
{
	int sum = 0;
	for(int k =i;k<=j;k++)
	{
		sum += freq[k];
	}
	return sum;
}

int solve(vector<int> freq,int i ,int j)
{
	if(j<i)
		return 0;
	if(i == j)
		return freq[i];

	int fsum = sum(freq,i,j);
	int min = INT_MAX;

	for(int k =i;k<=j;k++)
	{
		int cost = solve(freq,i,k-1) + solve(freq,k+1,j) + fsum ;
		min = std::min(min,cost);
	}
	return min;
}

int main(int argc, char const *argv[])
{
	vector<int> keys = {10,12,20};
	vector<int> freq = {34,8,50};

	int n = keys.size();

	int res =solve(freq,0,n-1);
	cout << res << endl;
	return 0;
}