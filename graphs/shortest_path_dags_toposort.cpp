#include<bits/stdc++.h>
using namespace std;

#define WHITE 0
#define BLACK 1
#define GRAY 2

class Item;

class Vertex {
public:
    int data,color,id;
    int d,f;
    Vertex *next,*pi;
    Item *itemPtr;
};

class Edge{
public:
    int src,dest,weight;
};

class Item{
public:
    Vertex *hd,*tl;
};

class SPDag{
private:
    unordered_map<int,Vertex *> nodeaddr;
    unordered_map<int,vector<int>> adjList;
    vector<Edge> edges;

    void dfs_visit(Vertex *u,int &time)
    {
        time++;
        u->color = GRAY;
        u->d = time;

        for(int key : adjList[u->data])
        {
            Vertex *v = nodeaddr[key];
            if(v->color == WHITE){
                v->pi = u;
                dfs_visit(v,time);
            }
        }

        time++;
        u->f  = time;
        u->color = BLACK;
    }
public:
    void makeset(int i);
    void dfs();
    void addedge(int s , int d , int w);
    vector<int> topo_sort();
    void spdag(int src);
    void printPath(Vertex *v);
};

void SPDag::makeset(int data)
{
    Item *newitem = new Item;
    newitem->hd = new Vertex;
    newitem->tl = newitem->hd;

    nodeaddr[data] = newitem->hd;

    newitem->hd->data = data;
    newitem->hd->id = data;
    newitem->hd->d = 0;
    newitem->hd->f = 0;
    newitem->hd->color = WHITE;
    newitem->hd->pi = NULL;
    newitem->hd->itemPtr = newitem;
}

void SPDag::dfs()
{
    for(const auto&entry : nodeaddr)
    {
        entry.second->color = WHITE;
        entry.second->pi = NULL;
    }

    int time = 0;

    for(const auto&entry : nodeaddr)
    {
        Vertex *v = entry.second;
        if(v->color == WHITE)
            dfs_visit(v,time);
    }   
}

void SPDag::addedge(int s, int d , int w)
{
    adjList[s].push_back(d);
    edges.push_back({s,d,w});
}

vector<int> SPDag::topo_sort()
{
    vector<pair<int,Vertex *>> nodes;
    vector<int> retlist;

    for(const auto&entry : nodeaddr)
    {
        nodes.push_back({entry.first,entry.second});
    }

    sort(nodes.begin(),nodes.end(),[](const pair<int,Vertex*>&a,pair<int,Vertex*>&b)
    {
        return a.second->f > b.second->f;
    });

    for(const auto&entry : nodes)
        retlist.push_back(entry.first);

    return retlist;
}

void SPDag::spdag(int src)
{
    dfs();
    vector<int> topolist = topo_sort();
    unordered_map<int,int> dist;

    for(const auto&entry : nodeaddr)
        dist[entry.first] = INT_MAX;
    

    int source = src;
    dist[source] = 0;

    for(int u : topolist)
    {
        if(dist[u] != INT_MAX)
        {
            for(int v : adjList[u])
            {
                for(const Edge&edge : edges)
                {
                    if(edge.src == u && edge.dest == v)
                    {
                        if(dist[v] > dist[u] + edge.weight)
                        {
                            dist[v] = dist[u] + edge.weight;
                            nodeaddr[v]->pi = nodeaddr[u];
                        }
                    }
                }
            }
        }
    }

    for(const auto&entry: dist)
    {
        cout << "[V] : " << entry.first << " : [W] : " << entry.second << endl;
    }
    cout <<endl;

    for(const auto&entry : dist)
    {
        Vertex *v = nodeaddr[entry.first];
        cout << "[V] : " << entry.first << " : [W] : " << entry.second  << " : [P] : ";
        if(entry.second == INT_MAX){
            cout << "no path" ;
        }
        else
        {
            printPath(v);
        }
        cout << endl;

    }

}

void SPDag::printPath(Vertex *u)
{
    if(u->pi == NULL)
    {
        cout << u->data ;
        return;
    }
    printPath(u->pi);
    cout << "-> " << u->id ;
}

int main(int argc, char const *argv[])
{
    SPDag g;    
    int V = 7;

    for(int i =0; i<V;i++)
        g.makeset(i);

    g.addedge(0,4,2);
    g.addedge(0,5,3);
    g.addedge(5,4,1);
    g.addedge(4,6,3);
    g.addedge(6,1,2);
    g.addedge(1,3,1);
    g.addedge(4,2,1);
    g.addedge(2,3,3);

    g.spdag(0);
    return 0;
}
