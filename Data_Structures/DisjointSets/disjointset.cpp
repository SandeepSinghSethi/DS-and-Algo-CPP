#include<bits/stdc++.h>

using namespace std;

class DisJSet {
private:
    int *rank, *parent , n;

public:
    DisJSet(int i){
        rank = new int[i];
        parent = new int[i];
        this->n = i;
        makeset();
    }

    void makeset();

    int find(int i);

    void Union(int x ,int y);

    void print();
};

void DisJSet::makeset(){
    // * will fill parent array with its own index at ith index
    for(int i = 0;i<n;i++)
        parent[i] = i;
}

int DisJSet::find(int i)
{
    if(parent[i] != i)
    {
        parent[i] = find(parent[i]);
    }

    return parent[i];
}

void DisJSet::Union(int x , int y)
{
    int xrep = find(x);
    int yrep = find(y);

    if(xrep == yrep)
        return;

    if(rank[xrep] < rank[yrep]){
        parent[yrep] = xrep;
    }
    else if(rank[xrep] > rank[yrep]){
        parent[xrep] = yrep;
    }
    else
    {
        parent[yrep] = xrep;
        rank[xrep]++;
    }

}

void DisJSet::print(){
    unordered_map<int,vector<int>> subset;

    for(int i =0 ;i<n;i++)
    {
        int root = find(i);
        subset[root].push_back(i);
    }

    for(const auto& key : subset)
    {
        cout << "{ ";
        for(int val : key.second)
        {
            cout << val << ", " ;
        }
        cout << " } " << endl;
    }
}

int main(int argc, char const *argv[])
{
    DisJSet obj(10);
    obj.Union(4,6);
    obj.Union(4,9);
    obj.Union(3,8);
    obj.Union(1,2);
    obj.Union(9,8);

    obj.print();
    if(obj.find(3) == obj.find(8))
        cout << "yes" << endl;
    else
        cout << "no" << endl;

    if(obj.find(1) == obj.find(9))
        cout << "yes" << endl;
    else
        cout << "no" << endl;
    return 0;
}
