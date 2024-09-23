#include<bits/stdc++.h>
using namespace std;

#define WHITE 0
#define BLACK 1
#define GRAY 2

class Item;

class Vertex
{
public:
    int data,d,f,color;
    Item *itemPtr;
    Vertex *pi;
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
    unordered_map<int,vector<int>> adjListTranspose;

    void dfs_transpose_visit(Vertex *u,vector<int> &component)
    {
        component.push_back(u->data);
        u->color = GRAY;

        for(int node : adjListTranspose[u->data])
        {
            Vertex *v = nodeaddr[node];
            if(v->color == WHITE)
            {
                dfs_transpose_visit(v,component);
            }
        }

        u->color = BLACK;
    }

    void dfs_visit(Vertex *u,int &time)
    {
        time++;
        u->d = time;
        u->color = GRAY;

        for(int key : adjList[u->data])
        {
            Vertex *v = nodeaddr[key];
            if(v->color == WHITE){
                v->pi = u;
                dfs_visit(v,time);
            }
        }

        u->color = BLACK;
        time++;
        u->f = time;
    }

public:
    void makeset(int i);
    void dfs();
    void addedge(int a, int b);
    void doTranspose();
    vector<int> topo_sort();
    vector<vector<int>> SCC();
};

void Graph::makeset(int i)
{
    Item *newitem = new Item;
    newitem->hd = new Vertex;
    newitem->tl = newitem->hd;
    newitem->hd->data = i;

    nodeaddr[i] = newitem->hd;

    newitem->hd->d = 0;
    newitem->hd->f = 0;
    newitem->hd->color = WHITE;
    newitem->hd->pi = NULL;
    newitem->hd->itemPtr = newitem;
}

void Graph::dfs()
{
    for(const auto&entry : nodeaddr)
    {
        Vertex *u = entry.second;
        u->color = WHITE;
        u->pi = NULL;
    }

    int time =0;

    for(const auto&entry : nodeaddr)
    {
        Vertex *v = entry.second;
        if(v->color == WHITE)
            dfs_visit(v,time);
    }
}

void Graph::addedge(int a , int b)
{
    adjList[a].push_back(b);
}

void Graph::doTranspose()
{
    for(const auto&entry : adjList)
    {
        for(int key : entry.second)
        {
            adjListTranspose[key].push_back(entry.first);
        }
    }
}

void print(vector<int> &a)
{
    for(int val : a)
    {
        cout << val << " " ;
    }
    cout << endl;
}

vector<int> Graph::topo_sort()
{
    vector<pair<int,Vertex*>> nodes;
    vector<int> retlist;

    for(const auto&entry : nodeaddr)
    {
        nodes.push_back({entry.first,entry.second});
    }

    sort(nodes.begin(),nodes.end(),[](const pair<int,Vertex*>&a,const pair<int,Vertex*>b)
    {
        return a.second->f > b.second->f;
    }) ;

    for(const auto&key : nodes)
    {
        retlist.push_back(key.first);
    }

    return retlist;
}

vector<vector<int>> Graph::SCC()
{
    dfs();

    doTranspose();

    vector<int> topo_list = topo_sort();

    for(const auto&entry : nodeaddr)
    {
        Vertex *u = entry.second;
        u->color = WHITE;
    }

    // print(topo_list);

    vector<vector<int>> scclist;

    for(int fvert : topo_list)
    {
        Vertex *v = nodeaddr[fvert];
        if(v->color == WHITE)
        {
            vector<int> component;
            dfs_transpose_visit(v,component);
            scclist.push_back(component);
        }
    }



    return scclist;
}

int main(int argc, char const *argv[])
{
    Graph g;
    for(int i = 1 ; i<6;i++)
        g.makeset(i);

    // g.addedge(1, 2);
    // g.addedge(2, 3);
    // g.addedge(3, 4);
    // g.addedge(4, 1);
    // g.addedge(2, 4);
    // g.addedge(3, 6);
    // g.addedge(4, 5);
    // g.addedge(5, 6);
    // g.addedge(6, 7);
    // g.addedge(7, 5);
    g.addedge(1, 3);
    g.addedge(3, 2);
    g.addedge(2, 1);
    g.addedge(1, 4);
    g.addedge(4, 5);

    vector<vector<int>> scclist;
    scclist = g.SCC();

    for(const auto&entry : scclist)
    {
        cout << "{ ";
        for(int v : entry)
        {
            cout << v << " ";
        }
        cout << "}" << endl;
    }
    return 0;
}
