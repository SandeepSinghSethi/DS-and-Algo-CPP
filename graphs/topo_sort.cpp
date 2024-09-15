#include<bits/stdc++.h>
using namespace std;

#define WHITE 0
#define BLACK 1
#define GRAY 2

class Item;

class Vertex
{
public:
    int data;
    int d,f;
    Item *itemPtr;
    Vertex *pi;
    int color;
};

class Item
{
public:  
    Vertex *hd,*tl;
};

class Graph
{
private:
    unordered_map<int,Vertex*> nodeaddr;
    unordered_map<int,vector<int>> adjList;

    void dfs_visit(Vertex *u,int &time)
    {
        time++;
        u->d = time;
        u->color = GRAY;

        for(int key : adjList[u->data])
        {
            Vertex *v = nodeaddr[key];
            if(v->color == WHITE)
            {
                v->pi = u;
                dfs_visit(v,time);
            }
        }

        time++;
        u->f = time;
        u->color = BLACK;
    }

public:
    void makeset(int n);
    void dfs();
    Item *find(int n);
    void addedge(int a,int b);
    vector<int> topological_sort();
};

void Graph::makeset(int data)
{
    Item *newitem = new Item;
    newitem->hd = new Vertex;
    newitem->tl = newitem->hd;
    newitem->hd->data = data;

    nodeaddr[data] = newitem->hd;

    newitem->hd->pi = NULL;
    newitem->hd->itemPtr = newitem;
    newitem->hd->color = WHITE;
    newitem->hd->d = 0;
    newitem->hd->f = 0;
}

Item * Graph::find(int n)
{
    Vertex *u = nodeaddr[n];
    return u->itemPtr;
}

void Graph::addedge(int a , int b)
{
    adjList[a].push_back(b);
}

void Graph::dfs()
{
    for(const auto&entry : nodeaddr)
    {
        Vertex *t = entry.second;
        t->color = WHITE;
        t->pi = NULL;
    }

    int time = 0;

    for(const auto&node : nodeaddr)
    {
        Vertex *u = node.second;
        if(u->color == WHITE)
            dfs_visit(u,time);
    }
}

vector<int> Graph::topological_sort()
{
    // * topological sort is just the printing of graphs' finishing time in descending order set by dfs

    vector<pair<int, Vertex*>> nodes;
    vector<int> retlist;

    for (const auto &entry : nodeaddr)
    {
        nodes.push_back({entry.first, entry.second});
    }

    sort(nodes.begin(), nodes.end(), [](const pair<int, Vertex*> &a, const pair<int, Vertex*> &b) {
        return a.second->f > b.second->f;  
    });

    for(const auto&key : nodes)
    {
        retlist.push_back(key.first);
        // cout << key.first << " ";
    }
    // cout << endl;
    return retlist;
}

int main(int argc, char const *argv[])
{
    Graph g;
    for(int i = 0 ; i<6;i++)
        g.makeset(i);

    g.addedge(1, 2);
    g.addedge(2, 0);
    g.addedge(0, 3);
    g.addedge(4, 5);
    // g.addedge(0 ,1);
    // g.addedge(1, 2);
    // g.addedge(3, 1);
    // g.addedge(3, 2);

    g.dfs();

    vector<int> topo_list;
    topo_list = g.topological_sort();

    cout << "TOPO SORT : ";
    for(int key : topo_list)
        cout << key <<  " ";
    cout << endl;
    return 0;
}
