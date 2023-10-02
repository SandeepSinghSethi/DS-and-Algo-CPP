#include<bits/stdc++.h>
using namespace std;

static vector<vector<int>> t;
static std::vector<vector<int>> v;


int knapsackrec(int item[],int weight[],int w, int n)
{
	if(w == 0 || n == 0)
		return 0;

	if(weight[n-1] <= w)
		return max(item[n-1]+knapsackrec(item,weight,w-weight[n-1],n-1) , knapsackrec(item,weight,w,n-1));
	else
		return knapsackrec(item,weight,w,n-1);

}

int knapsack(int item[],int weight[],int w,int n)
{
	if(n == 0 || w == 0)
		return 0;

	if(t[n][w] != -1)
		return t[n][w];

	if(weight[n-1] <= w)
		t[n][w] = max(item[n-1] + knapsack(item,weight,w-weight[n-1],n-1),knapsack(item,weight,w,n-1));
	else
		t[n][w] = knapsack(item,weight,w,n-1);


}

int knapsacktopdown(int item[],int weight[],int w , int n ){
	for(int i = 1;i<=n;i++)
	{
		for(int j = 1;j<=w;j++)
		{
			if(weight[i-1] <= j){
				v[i][j] = max(item[i-1] + v[i-1][j-weight[i-1]],v[i-1][j]);
			}
			else{
				v[i][j] = v[i-1][j];
			}
		}
	}

	return v[n][w];
}


void print(vector<vector<int>> t){
	for(const auto& row : t) {
		for(const auto& j : row){
			cout << j << "\t";
		}
		cout << endl;
	}
}

int main(int argc, char const *argv[])
{
	int item[] =   {1,3,4,5};//,3,43,2,29,17,24,30,10,4,21};
	int weight[] = {1,4,5,7};//,6,3,1,6,12,8,5,6,2,10};
	int n = sizeof(item)/sizeof(int);
	int w = 7;//60;

	t.resize(n+1,vector<int>(w+1,-1));
	v.resize(n+1,vector<int>(w+1,0));

	int profit = knapsack(item,weight,w,n);
	cout << profit << endl;

	profit = knapsackrec(item,weight,w,n);
	cout << profit << endl;

	profit = knapsacktopdown(item,weight,w,n);
	cout << profit << endl;

	print(v);
	return 0;
}