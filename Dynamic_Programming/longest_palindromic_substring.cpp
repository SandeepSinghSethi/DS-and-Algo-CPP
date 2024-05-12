#include<bits/stdc++.h>
#include<chrono>
using namespace std;
using namespace chrono;

void printmap(unordered_map<string,int> mp)
{
	for(const auto&m : mp)
	{
		cout << m.first << "->" << m.second << endl; 
	}
}

int isPalindrome(string s)
{
	string t = s;
	reverse(t.begin(),t.end());
	return (t == s) ? 1 : 0;
}

unordered_map<string,int> mp;

string solve(string s1)
{

	int n = s1.length();
	int b_len = 0,start,end;
	string str = "";
	for(int L= 0;L<n;L++)
	{
		for(int R = L;R<n;R++)
		{
			int l = R-L+1,ispal;
			
			string key = to_string(L) + "-" + to_string(l);
			
			if(mp.find(key) != mp.end())
			{
				ispal = mp[key];
			}
			else
			{
				string subs = s1.substr(L,l);
				ispal = isPalindrome(subs);
				mp[key] = ispal;
			}


			if( l > b_len && ispal)
			{
					b_len = l;
					// str = subs;
					start = L;
					end = l;
			}
		}
	}
	// printmap(mp);
	return s1.substr(start,end);

}

int main(int argc, char const *argv[])
{
	string s1 = "findnitianhere";
	auto start = high_resolution_clock::now();
	string res = "";

	for(int i = 0;i<10000;i++)
	{
		res = solve(s1);
	}


	auto end = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(end-start);
	cout << res << " TIME:" << duration.count() / 10000 <<  endl;
	return 0;
}