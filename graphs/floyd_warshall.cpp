#include<bits/stdc++.h>
using namespace std;

namespace graph{
namespace floyd_warshall{

class Floyd_Warshall
{
private:
    vector<vector<int>> adjMatrix;
    vector<vector<int>> W;
    vector<vector<int>> L_final;
    int vertices = 0;
public:
    Floyd_Warshall(int N) : vertices(N){
        adjMatrix.resize(vertices,vector<int>(vertices,INT_MAX));

        for(int i = 0;i<vertices;i++)
            adjMatrix[i][i] = 0;
    };

    void printMatrix();
    void solve();
    void FWSolve(vector<vector<int>> W,int n);
    void addedge(int s, int d , int w);
};

void Floyd_Warshall::FWSolve(vector<vector<int>> W,int n)
{
    // pattern for loop is K->I->J or KIJ instead of IKJ or IJK...
    vector<vector<int>> dist = W;
    for(int k = 0;k<vertices;k++)
    {
        for(int i = 0;i<vertices;i++)
        {
            for(int j = 0;j<vertices;j++)
            {
                if(dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)
                    if(dist[i][j] > dist[i][k] + dist[k][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    L_final = dist;
}

void Floyd_Warshall::addedge(int s , int d ,int w)
{
    s--;
    d--;
    adjMatrix[s][d] = w;
}

void Floyd_Warshall::solve()
{
    W = adjMatrix;
    FWSolve(W,vertices);
    printMatrix();
}

void Floyd_Warshall::printMatrix()
{
    for(int i = 0;i<vertices;i++)
    {
        for(int j = 0;j<vertices;j++)
        {
            if(L_final[i][j] == INT_MAX)
                cout << "INF" << "\t" ;
            else
                cout << L_final[i][j] << "\t";
        }
        cout << endl;
    }
}

} // floyd_warshall
} // graph

int main(int argc, char const *argv[])
{
    int V = 5;
    auto g = graph::floyd_warshall::Floyd_Warshall(V);

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
