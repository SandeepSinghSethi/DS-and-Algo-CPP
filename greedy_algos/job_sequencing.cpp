#include<bits/stdc++.h>
using namespace std;

struct job{
	char num;
	int deadline;
	int profit;
};

void print(vector<job> ptr)
{
	int n;
	for(const auto &i :ptr)
	{
		cout << n << ". " << i.num << " : " << i.deadline << " : " << i.profit << '\n';
		n++;
	}
	cout << endl;
}

bool cmp(job &a,job &b)
{
	return (a.profit > b.profit);
}

int solve(vector<job> ptr)
{
	int maxdeadline = 0 ;
	for(const auto &i : ptr)
	{
		if(i.deadline > maxdeadline)
			maxdeadline = i.deadline;
	}

	int slot[maxdeadline];
	char name[maxdeadline];

	for(int i = 0;i<maxdeadline;i++)
		slot[i] = -1;

	for(int i = 0;i<maxdeadline;i++)
		name[i] = '\0';

	for(int i = 0;i<ptr.size();i++)
	{
		int d = ptr[i].deadline-1;
		if(slot[d] == -1){
			slot[d] = ptr[i].profit;
			name[d] = ptr[i].num;
		}
		else{
			while(d >= 0 && slot[d] != -1)
			{
				d--;
			}
			if(slot[d] == -1){
				slot[d] = ptr[i].profit;
				name[d] = ptr[i].num;
			}
		}

	}
	for(const auto &i: slot){
		if(i != -1)
			cout << i << '\t';
	}
	cout << endl;
	for(const auto &i: name){
		if(i != '\0')
			cout << i << '\t';
	}
	cout << endl;
}


int main(int argc, char const *argv[])
{
	/* code */
	vector<job> ptr = {
		{'a',4,20},
		{'b',1,10},
		{'c',1,40},
		{'d',2,30}
	};
	int n = ptr.size();
	sort(ptr.begin(),ptr.end(),cmp);
	print(ptr);
	solve(ptr);
	return 0;
}