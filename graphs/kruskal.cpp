#include<bits/stdc++.h>
using namespace std;

class Item;

class Vertex
{
public:
    int data;
    int rank;
    Vertex *next;
    Item *itemPtr;
};

class Item
{
public:
    Vertex *hd,*tl;
};

class Edge
{
public:
    int src,dest,weight;
};

class KruskalGraph
{
private:
    unordered_map<int,Vertex *> nodeaddr;
public:
    vector<Edge> edges;    

public:
    void makeset(int i);
    void Union(int a , int b);
    Item *find(int key);
    void linkitem(Item *a,Item *b);
    void addedge(int src,int dest,int weight);
    vector<Edge> KruskalMST();
};

void KruskalGraph::makeset(int i)
{
    Item *newitem = new Item;
    newitem->hd = new Vertex;
    newitem->tl = newitem->hd;
    
    nodeaddr[i] = newitem->hd;

    newitem->hd->rank = 0;
    newitem->hd->itemPtr = newitem;
    newitem->hd->next = NULL;
    newitem->hd->data = i;
}

Item* KruskalGraph::find(int key)
{
    Vertex *ptr = nodeaddr[key];
    return ptr->itemPtr;
}

void KruskalGraph::linkitem(Item *a,Item *b)
{
    Vertex *ptr = b->hd;
    while(ptr != NULL)
    {
        ptr->itemPtr = a;
        ptr = ptr->next;
    }
    a->tl->next = b->hd;
    a->tl = b->tl;

    delete b;
}

void KruskalGraph::Union(int a , int b)
{
    Item *xitem = find(a);
    Item *yitem = find(b);

    if(xitem == yitem)
        return;

    Vertex *xrep = xitem->hd;
    Vertex *yrep = yitem->hd;

    int xrank = xrep->rank;
    int yrank = yrep->rank;

    if(xrank > yrank)
    {
        linkitem(xitem,yitem);
    }
    else if(xrank < yrank)
    {
        linkitem(yitem,xitem);
    }
    else
    {
        linkitem(xitem,yitem);
        xitem->hd->rank++;
    }

}

void KruskalGraph::addedge(int s,int d, int w)
{
    Edge e = {s,d,w};
    edges.emplace_back(e);
}

vector<Edge> KruskalGraph::KruskalMST()
{
    sort(edges.begin(),edges.end(),[](const Edge &a,const Edge &b){
        return a.weight < b.weight;
    });
    vector<Edge> mstedges; // edges which we will get 

    for(const auto&a : edges)
    {
        int src = a.src;
        int dest = a.dest;

        if(find(src) != find(dest))
        {
            Union(src,dest);
            mstedges.emplace_back(a);
        }
    }

    return mstedges;
}


int main(int argc, char const *argv[])
{
    KruskalGraph g;

    for(int i = 0;i<9;i++)
        g.makeset(i);



    g.addedge(0,1,4);
    g.addedge(0,7,8);
    g.addedge(1,7,11);
    g.addedge(1,2,8);
    g.addedge(7,8,7);
    g.addedge(2,8,2); //
    g.addedge(8,6,6);
    g.addedge(7,6,1);
    g.addedge(6,5,2);
    g.addedge(2,3,7);
    g.addedge(5,4,10);
    g.addedge(2,5,4);
    g.addedge(3,5,14);
    g.addedge(3,4,9);

    // g.Union()
    
    vector<Edge> mst = g.KruskalMST();
    int minweight = 0;
    for(const auto&a : mst)
    {
        minweight += a.weight;
        cout << "[src] : " << a.src << " -- [dst] : " << a.dest << " = " << a.weight << endl;
    }

    cout << "Min weight: " << minweight << endl; 
    return 0;
}
