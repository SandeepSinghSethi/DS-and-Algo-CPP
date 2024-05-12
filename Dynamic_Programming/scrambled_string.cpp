#include<bits/stdc++.h>
using namespace std;

int isAnagram(string s1,string s2,int n1,int n2)
{
	if(n1 != n2)
		return 0;

	sort(s1.begin(),s1.end());
	sort(s2.begin(),s2.end());

	if(s1 != s2)
		return 0;
	return 1;
}

void print_map(unordered_map<string,int> mp)
{
	for(const auto& entry : mp)
	{
		cout << entry.first << " -> " << entry.second << '\n';
	}
}

unordered_map<string,int> mp;

int solve(string s1,string s2)
{
	string key = s1 + "_" + s2;
	if(mp.find(key) != mp.end())
		return mp[key];

	if(s1.length() != s2.length())
		return 0;

	if(s1 == s2)
		return 1;

	if(!isAnagram(s1,s2,s1.length(),s2.length()))
		return 0;

	int n  = s1.length();
	for(int i = 1 ; i<n;i++)
	{
		if(solve(s1.substr(0,i),s2.substr(n-i)) && solve(s1.substr(i),s2.substr(0,n-i)) ||
			solve(s1.substr(0,i),s2.substr(0,i)) && solve(s1.substr(i),s2.substr(i)))
		{
			mp[key] = true;
			break;
		}

	}

	// mp[key] = false;
	return mp[key];
}

int main(int argc, char const *argv[])
{
	string s1 = "abcd";
	string s2 = "bcad";

	int n1 = s1.length();
	int n2 = s2.length();

	int valid = isAnagram(s1,s2,n1,n2);

	if(!valid){
		cout << "Invalid String size or not an anagram" << "\n";
		return 1;
	}
	int res = solve(s1,s2);
	cout << res << endl;
	print_map(mp);
	return 0;
}