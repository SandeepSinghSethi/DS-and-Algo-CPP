#include<bits/stdc++.h>
using namespace std;

vector<vector<vector<int>>> dp;

void print(vector<vector<vector<int>>> ptr)
{
	int n = dp.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << "(" << dp[i][j][0] << "," << dp[i][j][1] << ") ";
        }
        cout << endl;
    }
}

unordered_map<string,int> mp;

void print_map(unordered_map<string,int> mp)
{
	for(const auto& entry : mp)
	{
		cout << entry.first << " -> " << entry.second << '\n';
	}
}

int solve(string s , int i,int j ,int isTrue)
{
	if(i>j)
		return false;

	if(i == j)
	{
		if(isTrue == 1)
			return s[i] == 'T';
		else
			return s[i] == 'F';
	}

	string temp = to_string(i) + "_" + to_string(j) + "_" + to_string(isTrue); // this will create a unique string for our hashmap

	if(mp.find(temp) != mp.end())
		return mp[temp];

	int q = 0;

	for(int k = i+1;k<j;k+=2)
	{
		int leftT;// = solve(s,i,k-1,1);
		int rightT;// = solve(s,k+1,j,1);
		int leftF ;//= solve(s,i,k-1,0);
		int rightF;// = solve(s,k+1,j,0);

		string lt = to_string(i) + "_" + to_string(k-1) + "_" + to_string(1); 
		string lf = to_string(i) + "_" + to_string(k-1) + "_" + to_string(0);
		string rt = to_string(k+1) + "_" + to_string(j) + "_" + to_string(1);
		string rf = to_string(k+1) + "_" + to_string(j) + "_" + to_string(0);


		if(mp.find(lt) != mp.end())
			leftT = mp[lt];
		else
			leftT = solve(s,i,k-1,1);

		if(mp.find(lf) != mp.end())
			leftF = mp[lf];
		else
			leftF = solve(s,i,k-1,0);


		if(mp.find(rt) != mp.end())
			rightT = mp[rt];
		else
			rightT = solve(s,k+1,j,1);

		if(mp.find(rf) != mp.end())
			rightF = mp[rf];
		else
			rightF = solve(s,k+1,j,0);

		if(s[k] == '&'){
				if(isTrue)
					q += leftT * rightT;
				else
					q += leftT * rightF + leftF * rightT + leftF * rightF;
		}
		
		if(s[k] == '|'){
				if(isTrue)
					q += leftT * rightT + leftT * rightF + rightT * leftF;
				else
					q += leftF * rightF;

		}
		if(s[k] == '^'){
				if(isTrue)
					q += leftT * rightF + leftF * rightT;
				else
					q += leftT * rightT + leftF * rightF;
		}

	}

	return mp[temp] = q %1003;

}	


// int solve(string s1,int n)
// {
// 	dp.resize(n+1,vector<vector<int>>(n+1,vector<int>(2,0)));

// 	for(int i = 0;i<n;++i)
// 	{
// 		dp[i][i][0] = (s1[i] == 'F') ? 1 : 0;
// 		dp[i][i][1] = (s1[i] == 'T') ? 1 : 0;
// 	}

// 	for (int length = 2; length <= n; ++length) {
//         for (int i = 0; i < n - length + 1; ++i) {
//             int j = i + length - 1;
//             for (int k = i; k < j; ++k) {
//                 if (s1[k] == '|') {
//                     dp[i][j][1] += dp[i][k-1][1] * dp[k + 1][j][1] +
//                                    dp[i][k-1][1] * dp[k + 1][j][0] +
//                                    dp[i][k-1][0] * dp[k + 1][j][1];
//                     dp[i][j][0] += dp[i][k-1][0] * dp[k + 1][j][0];
//                 } else if (s1[k] == '&') {
//                     dp[i][j][1] += dp[i][k-1][1] * dp[k + 1][j][1];
//                     dp[i][j][0] += dp[i][k-1][0] * dp[k + 1][j][0] +
//                                    dp[i][k-1][0] * dp[k + 1][j][1] +
//                                    dp[i][k-1][1] * dp[k + 1][j][0];
//                 } else if (s1[k] == '^') {
//                     dp[i][j][1] += dp[i][k-1][1] * dp[k + 1][j][0] +
//                                    dp[i][k-1][0] * dp[k + 1][j][1];
//                     dp[i][j][0] += dp[i][k-1][0] * dp[k + 1][j][0] +
//                                    dp[i][k-1][1] * dp[k + 1][j][1];
//                 }
//             }
//         }
//     }
// 	print(dp);

// 	for (int i = 0; i < n; ++i) {
//         for (int j = i; j < n; ++j) {
//             cout << "dp[" << i << "][" << j << "][0] = " << dp[i][j][0] << ", ";
//             cout << "dp[" << i << "][" << j << "][1] = " << dp[i][j][1] << endl;
//         }
//     }

// 	return dp[0][n-1][1];
// }

int main(int argc, char const *argv[])
{
	string symbols = "TTFT";
    string operators = "|&^";

	string s;
    int j = 0;
 
    for (int i = 0; i < symbols.length(); i++) 
    {
        s.push_back(symbols[i]);
        if (j < operators.length())
            s.push_back(operators[j++]);
    }

    s = "T&T|F|F^F^T^T^T&T^F^T&F|F^F^F&F&F|F|F^F^T|T&T";
    int n = s.length();

    int res = solve(s,0,n-1,1);
    print_map(mp);
    // int res = solve(s,n);
    cout << res << endl;
	return 0;
}