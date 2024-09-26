#include<bits/stdc++.h>
using namespace std;

class Item;

class Vertex
{
public:
    int data,id;
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

class PrimGraph{
private:
    unordered_map<int,Vertex *> nodeaddr;
    vector<vector<pair<int,int>>> adjList;

public:
    PrimGraph(int V){
        adjList.resize(V);
    }
    void makeset(int i);
    void addedge(int s,int d,int w);
    void Prims(int s);
};

void PrimGraph::makeset(int data)
{
    Item *newitem = new Item;
    newitem->hd = new Vertex;
    newitem->tl = newitem->hd;

    nodeaddr[data]= newitem->hd;

    newitem->hd->data = data;
    newitem->hd->id = data;
    newitem->hd->next = NULL;
    newitem->hd->pi = NULL;
    newitem->hd->itemPtr = newitem;
}

void PrimGraph::addedge(int s, int d , int w)
{
    adjList[s].emplace_back(d,w);
    adjList[d].emplace_back(s,w);
}

void PrimGraph::Prims(int s)
{
    priority_queue<pair<int,int>,vector<pair<int,int>>, greater<pair<int,int>>> pq;

    for(const auto&entry : nodeaddr)
    {
        Vertex *ptr = entry.second;
        ptr->data = INT_MAX;
        ptr->pi = NULL;
    }

    Vertex *source = nodeaddr[s];
    source->data = 0;
    // inserting root node
    pq.push({0,source->id});
    
    unordered_set<int> mst;
    vector<Edge> mstEdge;

    int totweight = 0;
    
    while(!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if(mst.find(u) != mst.end()) // if node exists in mst 
            continue;

        mst.insert(u);

        totweight += nodeaddr[u]->data;

        if(nodeaddr[u]->pi != NULL)
        {
            mstEdge.push_back({nodeaddr[u]->pi->id,u,nodeaddr[u]->data});
        }

        for(auto &[v,w] : adjList[u])
        {
            Vertex *vt = nodeaddr[v];
            if(mst.find(v) == mst.end() && w < vt->data) // check if node doesnt exists in mst
            {
                vt->data = w;
                vt->pi = nodeaddr[u];
                pq.push({vt->data,vt->id});
            }
        }

    }

    for(const auto&entry: mstEdge)
    {
        cout << "[src]: " << entry.src << " --- " << "[dst]: " << entry.dest << " ; weight : "<< entry.weight << endl;
    }

    cout << totweight << endl;
}

int main(int argc, char const *argv[])
{
    int V = 9;
    PrimGraph g(V);

    for(int i = 0;i<V;i++)
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

    g.Prims(0);    
    return 0;
}
