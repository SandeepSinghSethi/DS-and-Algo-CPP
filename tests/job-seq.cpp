#include<bits/stdc++.h>
using namespace std;

vector<int> solve(vector<int> &deadline , vector<int> &profit)
{
    int slotsize = 0;
    for(const auto&entry : deadline){
        if(entry > slotsize)
            slotsize = entry;
    }

    int n = deadline.size();
    int slot[slotsize];
    vector<int> result;

    vector<pair<int,int>> jobs;
    for(int i = 0 ; i < n ; i++)
    {
        jobs.push_back({deadline[i],profit[i]});
    }

    sort(jobs.begin(),jobs.end(),greater<pair<int,int>>());

    for(const auto&entry: jobs)
    {
        cout << entry.first << ":" << entry.second << endl;
    }

    for(int i = 0;i<slotsize;i++)
        slot[i] = -1;
    
    for(int i = 0;i<n;i++)
    {
        int d = jobs[i].first-1;
        if(slot[d] == -1)
        {
            slot[d] = jobs[i].second;
        }
        else
        {
            while(d>=0 && slot[d] != -1)
                d--;
            if(slot[d] == -1)
            {
                slot[d] = jobs[i].second;
            }
        }
    }
    for(const auto&i : slot)
        cout << i << " " ;
    cout << endl; 
    int no = 0;
    int prf = 0;
    for(int i = 0;i<slotsize;i++)
    {
        if(slot[i] != -1){
            no++;
            prf += slot[i]; 
        }
    }
    cout << no << " " << prf << endl;
    result.push_back(no);
    result.push_back(prf);
    return result;  
}

int main(int argc, char const *argv[])
{
    vector<int> deadline = {4, 1, 1, 1};
    vector<int> profit =  {20, 10, 40, 30};

    solve(deadline, profit);
    return 0;
}
