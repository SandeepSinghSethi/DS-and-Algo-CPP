#include<bits/stdc++.h>
using namespace std;

class Item;

class Vertex{
public:
    int data , id;
    Vertex *pi;
    Item *itemptr;
};

class Item{
public:
    Vertex *head,*tail;
};

class SLOW_APSP{
private:
    unordered_map<int,Vertex *> nodeaddr;
    // adjacency matrix
    vector<vector<int>> adjMatrix;
    vector<vector<int>> W;
    vector<vector<int>> L_0;
    vector<vector<int>> L_final;
    int vertices = 0;
    void extended_shortest_path(vector<vector<int>> &L_r_1,vector<vector<int>> &W, vector<vector<int>> &L_r, int n);

public:
    SLOW_APSP(int N) : vertices(N) {
        adjMatrix.resize(vertices,vector<int>(vertices,INT_MAX)); // resizing adjmatrix and setting all to INT_MAX

        for(int i = 0;i<vertices;i++)
            adjMatrix[i][i] = 0; // diagonal are zero btw....
    };

    void addedge(int s ,int d , int w);
    void slowSolve(vector<vector<int>> &W,vector<vector<int>> &L_0,int n);
    void fastSolve(vector<vector<int>> &W,int n);
    void solve();
    void printMatrix();
    void printPath();
};

void SLOW_APSP::addedge(int s, int d , int w)
{
    s--;
    d--;
    adjMatrix[s][d]= w;
}

void SLOW_APSP::extended_shortest_path(vector<vector<int>> &L_r_1,vector<vector<int>> &W, vector<vector<int>> &L_r,int n)
{
    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<n;j++)
        {
            for(int k = 0;k<n;k++)
            {
               if (L_r_1[i][k] != INT_MAX && W[k][j] != INT_MAX) {
                int new_dist = L_r_1[i][k] + W[k][j];
                if (new_dist < L_r[i][j]) {
                    L_r[i][j] = new_dist;
                }
            }
            }
        }
    }
}

void SLOW_APSP::slowSolve(vector<vector<int>> &W,vector<vector<int>> &L_0,int n)
{
   vector<vector<int>> L = L_0;
   vector<vector<int>> M;
   
   for(int r = 0;r<n;r++)
   {
        M.resize(n,vector<int>(n,INT_MAX));

        extended_shortest_path(L,W,M,n);
        
        L = M;
   };
   L_final = L;
}

void SLOW_APSP::fastSolve(vector<vector<int>> &W,int n)
{
    vector<vector<int>> L = W;
    vector<vector<int>> M;

    for(int r = 0;r<n;r++)
    {
        M.resize(n,vector<int>(n,INT_MAX));

        extended_shortest_path(L,L,M,n);

        r = 2*r;

        L = M;
    }
    L_final = L;
}

void SLOW_APSP::solve()
{
    W = adjMatrix;
    L_0 = adjMatrix;
    cout << "Slow apsp: " << endl;
    slowSolve(W,L_0,vertices);
    printMatrix();

    cout << "\n\nFast apsp: " << endl;
    fastSolve(W,vertices);
    printMatrix();
    
}

void SLOW_APSP::printMatrix()
{
   for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (L_final[i][j] == INT_MAX)
                cout << "INF ";
            else
                cout << L_final[i][j] << "\t";
        }
        cout << "\n";
    }
}

int main(int argc, char const *argv[])
{
    int V = 5;

    SLOW_APSP g(V);

    g.addedge(1,2,3);
    g.addedge(1,3,8);
    g.addedge(1,5,-4);
    g.addedge(2,4,1);
    g.addedge(2,5,7);
    g.addedge(3,2,4);
    g.addedge(4,1,2);
    g.addedge(4,3,-5);
    g.addedge(5,4,6);
    
    g.solve();
    return 0;
}
