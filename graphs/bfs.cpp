#include<bits/stdc++.h>
using namespace std;

class Item;

#define WHITE 0
#define BLACK 1
#define GRAY 2

class Vertex{
public:
    int data;
    int rank;
    int distance;
    Vertex* pi;
    int color; // gray,white,black
    Vertex *next;
    Item *itemPtr;
};

class Item{
public:
    Vertex *hd,*tl;
};

class Graph{
private:
    unordered_map<int,Vertex *> nodeaddr;
    unordered_map<int,vector<int>> adjList;

public:
    void makeset(int data);
    Item* find(int data);
    void Union(int a , int b);
    void addedge(int a, int b);
    void print();
    void LinkItem(Item *i1,Item *i2);
    void bfs(int a);
};

void Graph::makeset(int data)
{
    Item *newitem = new Item;
    newitem->hd = new Vertex;
    newitem->hd->data = data;
    newitem->tl = newitem->hd;

    nodeaddr[data] = newitem->hd;

    newitem->hd->itemPtr = newitem;
    newitem->hd->rank = 0;
    newitem->hd->next = NULL;
    newitem->hd->distance = 0;
    newitem->hd->pi = NULL;
    newitem->hd->color = WHITE;
}

void Graph::LinkItem(Item *i1,Item *i2)
{
    Vertex *cur = i2->hd;
    while(cur != 0){
        cur->itemPtr = i1;
        cur = cur->next;
    }
    i1->tl->next = i2->hd;
    i1->tl = i2->tl;

    delete i2;
}

Item* Graph::find(int key)
{
    Vertex *node = nodeaddr[key];
    return node->itemPtr;
}

void Graph::Union(int a , int b)
{

    Item *i1 = find(a);
    Item *i2 = find(b);

    Vertex *xrep = i1->hd;
    Vertex *yrep = i2->hd;

    int xrank = xrep->rank;
    int yrank = yrep->rank;

    if(xrep == yrep)
        return;

    if(xrank > yrank)
    {
        LinkItem(i1,i2);
    }
    else if(xrank < yrank)
    {
        LinkItem(i2,i1);
    }
    else
    {
        LinkItem(i1,i2);
        i1->hd->rank++;
    }
}

void Graph::print()
{
    unordered_map<int ,vector<int>> pmmap;

    for(const auto&key : nodeaddr)
    {
        Item *ptr = find(key.first);
        pmmap[ptr->hd->data].push_back(key.first);
    }

    for(const auto&key : pmmap)
    {
        cout << "{ " ;
        for(const auto&entry : key.second)
        {
            cout << entry << " , ";
        }
        cout << "}" <<  endl;
    }
}

void Graph::addedge(int a , int b)
{
    adjList[a].push_back(b);
    adjList[b].push_back(a);
}

void Graph::bfs(int s)
{

    Item *a = find(s);
    for(const auto&entry : nodeaddr)
    {
        Vertex *v = entry.second;
        v->color = WHITE;
        v->distance = INT_MAX;
        v->pi = NULL;
    }    

    Vertex *source = a->hd;
    source->color = GRAY;
    source->distance = 0;
    source->pi = NULL;
    queue<Vertex *> q;
    q.push(source);

    while(!q.empty())
    {
        Vertex *u = q.front();
        q.pop();

        for(int node : adjList[u->data])
        {
            Vertex *v = nodeaddr[node];
            if(v->color == WHITE)
            {
                v->color = GRAY;
                v->distance = u->distance+1;
                v->pi = u;
                q.push(v);
            }
        }
        u->color = BLACK;
    }

    // for(const auto&entry : adjList)
    // {
    //     cout << entry.first << " : {";
    //     for(const auto&key : entry.second)
    //     {
    //         cout << key << " , ";
    //     }
    //     cout << "} " << endl;
    // }
    for(const auto&entry : nodeaddr)
    {
        Vertex *v = entry.second;
        cout << "Vertex : " << v->data << " : distance from source = " << v->distance  << " with rank " << v->rank << endl;
    }
}

int main(int argc, char const *argv[])
{
    /* code */
    Graph g;

    for(int i = 0;i<7;i++)
    {
        g.makeset(i);
    }

    g.addedge(0,1);
    g.addedge(0,2);
    g.addedge(0,3);
    g.addedge(2,4);
    g.addedge(4,6);
    g.addedge(3,6);
    g.addedge(1,5);
    // g.Union(g.find(1),g.find(9));
    // g.Union(g.find(3),g.find(7));

    // g.print();

    g.bfs(1);
    return 0;
}
