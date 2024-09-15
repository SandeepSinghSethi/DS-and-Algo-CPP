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
    // int distance;
    int d; // starting timestamp
    int f; // ending timestamp
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
    unordered_map<int,Vertex *> nodeaddr;
    unordered_map<int,vector<int>> adjList;

    void dfs_visit(Vertex *u,int &time)
    {
        time++;

        u->d = time;
        u->color = GRAY;

        for(int node : adjList[u->data])
        {
            Vertex *v = nodeaddr[node];
            if(v->color == WHITE)
            {
                v->pi = u;
                dfs_visit(v,time);
            }
        }
        time++;
        u->f = time;
        u->color = BLACK;
        cout << "Vertex : " << u->data << " ; d = " << u->d << " and f = " << u->f  << endl;
    }

public:
    void dfs();
    void addedge(int a , int b);
    void makeset(int i);
    Item *find(int n);
};

void Graph::makeset(int data)
{
    Item *newitem = new Item;
    newitem->hd = new Vertex;
    newitem->tl = newitem->hd;
    newitem->hd->data = data;

    nodeaddr[data] = newitem->hd;

    newitem->hd->itemPtr = newitem;
    newitem->hd->color = WHITE;
    newitem->hd->pi =NULL;
    newitem->hd->d = 0;
    newitem->hd->f = 0;
    // newitem->hd->distance = 0;
}

void Graph::addedge(int a , int b)
{
    adjList[a].push_back(b);
    adjList[b].push_back(a);
}

Item* Graph::find(int n)
{
    Vertex *x = nodeaddr[n];
    return x->itemPtr;
}

void Graph::dfs()
{
    // Item *a = find(n);
    for(const auto&node : nodeaddr)
    {
        Vertex *ptr = node.second;
        ptr->color = WHITE;
        ptr->pi = NULL;
    }
    int time = 0;

    for(const auto&node : nodeaddr)
    {
        Vertex *ptr = node.second;
        if(ptr->color == WHITE)
        {
            dfs_visit(ptr,time);
        }
    }    

    // for(const auto&entry : nodeaddr)
    // {
    //     Vertex *ptr = entry.second;

    //     cout << "Vertex : " << ptr->data << " ; d = " << ptr->d << " and f = " << ptr->f  << endl;
    // }
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
    // g.addedge(3, 5);
    // g.addedge(4, 5);

    g.dfs();

    return 0;
}
