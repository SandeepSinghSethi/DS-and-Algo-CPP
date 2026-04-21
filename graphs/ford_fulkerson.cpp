#include<bits/stdc++.h>
using namespace std;

#define WHITE 0
#define BLACK 1
#define GRAY 2

namespace graph
{
namespace FordFulkerson
{
    
class Vertex{
public:
    int data;
    int id;
    int f,d,color;
};

class Ford_Fulkerson{
private:
    unordered_map<int,Vertex *> nodeaddr;
    vector<vector<int>> adjList;
    vector<vector<int>> capacity;
    int vertices = 0;
public:
    Ford_Fulkerson(int V) : vertices(V) {
        adjList.resize(vertices);
        capacity.resize(vertices,vector<int>(vertices,0));
    };

    void solve(int s,int t);
    void addedge(int s,int d ,int w);
    void printMatrix(vector<vector<int>> m);
    bool dfs(int s, int t,vector<int>&parent, vector<bool>&visited,vector<int>&vertexes);
};

void Ford_Fulkerson::printMatrix(vector<vector<int>> m)
{
    for(int i =0;i<vertices;i++)
    {
        for(int j = 0;j<vertices;j++)
        {
            cout << m[i][j] << "\t";
        }
        cout << endl;
    }
}

void Ford_Fulkerson::addedge(int s, int d , int w)
{
    adjList[s].push_back(d);
    adjList[d].push_back(s);
    capacity[s][d] = w;
}

bool Ford_Fulkerson::dfs(int s, int t, vector<int>&parent, vector<bool>&visited,vector<int>&vertexes)
{
    visited[s] = true;
    // vertexes.push_back(s);
    if(s == t) return true;

    for(auto&v : adjList[s])
    {
        if(!visited[v] && capacity[s][v] > 0)
        {
            parent[v] = s;
            if(dfs(v,t,parent,visited,vertexes))
                return true;
        }
    }
    return false;
}

void Ford_Fulkerson::solve(int s, int t)
{

    // for solving this we have to find augmented path either via bfs or dfs , then on each path , we have to find min_flow which will used for our balancing in the capacity vector and/or residual graph.
    vector<int> parent(vertices);
    int max_flow = 0;
    printMatrix(capacity);
    for(const auto&entry : adjList)
    {
        for(const auto&j : entry){
            cout << j << '\t';
        }
        cout << endl;
    }
    cout << endl << endl;
    while(true)
    {
        vector<bool> visited(vertices,false);
        fill(parent.begin(),parent.end(),-1);
        vector<int> vertexes;
        if(!dfs(s,t,parent,visited,vertexes))
        {
            break;
        }
        int v = t;
        vector<int> path;
        while(v != -1){
            path.push_back(v);
            v = parent[v];
        }
        reverse(path.begin(), path.end());

        for(int x : path) cout << x << " -> ";
        cout << endl;
        // at this point we have an augmented path from dfs() above , it will break if no existing augmented path exists

        for(const auto&i : visited)
        {
            cout << i << " : ";
        }
        cout << endl;

        for(const auto&i : parent)
        {
            cout << i << " : ";
        }
        cout << endl << endl;
        int flow = INT_MAX;
        v = t;
        while(v != s)
        {
            int u = parent[v];
            flow = min(flow,capacity[u][v]);
            v = u;
        }
        v = t ;
        while(v!=s)
        {
            int u = parent[v];
            capacity[u][v] -= flow;
            capacity[v][u] += flow;
            v = u;
        }
        cout << flow << endl;
        printMatrix(capacity);

        cout << "-----------------------------------------------------------------"<<endl << endl;
        max_flow += flow;
    }
    cout << "MaxFlow from : " << s << " -> " << t << ": " << max_flow << endl;
}

}
}

int main(int argc, char const *argv[])
{
    int V = 6;
    auto g = graph::FordFulkerson::Ford_Fulkerson(V);


    g.addedge(0,1,16);
    g.addedge(0,2,13);
    g.addedge(1,3,12);
    g.addedge(2,1,4);
    g.addedge(3,2,9);
    g.addedge(2,4,14);
    g.addedge(4,3,7);
    g.addedge(3,5,20);
    g.addedge(4,5,4);

    // g.addedge(1,4,8);
    // g.addedge(1,2,2);
    // g.addedge(2,4,4);
    // g.addedge(4,3,6);
    // g.addedge(3,5,10);
    // g.addedge(4,5,10);  

    int s = 0;
    int t = 5;
    g.solve(s,t);
    return 0;
}
