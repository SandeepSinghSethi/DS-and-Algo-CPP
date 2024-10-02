#include<bits/stdc++.h>
using namespace std;

class Item;

class Vertex{
public:
    int data,id;
    Vertex *pi;
    Item *itemPtr;
};

class Item
{
public:
    Vertex *hd,*tl;
};

class Edge{
public:
    int src,dest,weight;
};

class BellFord{
private:
    unordered_map<int,Vertex *> nodeaddr;
    vector<Edge> edges;
    int vertices;

public:
    BellFord(int V)
    {
        vertices = V;
    };

    void makeset(int i);
    Item *find(int i);
    pair<bool,vector<pair<int,pair<int,int>>>> BellmanFord(int source);
    void addedge(int s,int d , int w);
};

void BellFord::makeset(int i)
{
    Item *newitem = new Item;
    newitem->hd = new Vertex;
    newitem->tl = newitem->hd;

    nodeaddr[i] = newitem->hd;

    newitem->hd->data = i;
    newitem->hd->id = i;
    newitem->hd->pi = NULL;
    newitem->hd->itemPtr = newitem;
}

Item* BellFord::find(int s)
{
    Vertex *ptr = nodeaddr[s];
    return ptr->itemPtr;
}

void BellFord::addedge(int s, int d , int w)
{
    edges.push_back({s,d,w});
}

pair<bool,vector<pair<int,pair<int,int>>>> BellFord::BellmanFord(int source)
{
    vector<pair<int ,pair<int,int>>> visitedOrder;

    for(const auto&node : nodeaddr)
    {
        node.second->pi = NULL;
        node.second->data = INT_MAX;
    }

    Vertex *s = nodeaddr[source];
    s->data = 0;

    for(int i = 0;i<vertices-1;i++)
    {
        for(const auto&edge : edges)
        {
            Vertex *u = nodeaddr[edge.src];
            Vertex *v = nodeaddr[edge.dest];
            int weight = edge.weight;

            if(u->data != INT_MAX && v->data > u->data + weight)
            {
                v->data = u->data + weight;
                v->pi = u;
            }
        }
    }

    for(const auto&edge : edges)
    {
        Vertex *u = nodeaddr[edge.src];
        Vertex *v = nodeaddr[edge.dest];
        int weight = edge.weight;

        if(u->data != INT_MAX && v->data > u->data + weight)
            return {false,{}};
    }

    for(const auto&node : nodeaddr)
    {
        Vertex* v = node.second;
        if(v->pi != NULL)
        {
            int u_id = v->pi->id;
            int v_id = v->id;
            int weight = v->data - v->pi->data ;

            visitedOrder.push_back({u_id,{v_id,weight}});
        }
    }

    return {true,visitedOrder};
}

int main(int argc, char const *argv[])
{
    int V = 7;
    BellFord g(V);

    for(int i = 0;i<V ;i++)
        g.makeset(i);

    g.addedge(0,4,2);
    g.addedge(0,5,3);
    g.addedge(5,4,1);
    g.addedge(4,6,3);
    g.addedge(6,1,2);
    g.addedge(1,3,1);
    g.addedge(4,2,1);
    g.addedge(2,3,3);
    // g.addedge(0,1,6);
    // g.addedge(0,4,7);
    // g.addedge(1,2,5);
    // g.addedge(2,1,-2);
    // g.addedge(1,4,8);
    // g.addedge(1,3,-4);
    // g.addedge(4,3,9);
    // g.addedge(4,2,-3);
    // g.addedge(3,2,7);
    // g.addedge(3,0,2);


    auto [success,vOrder] = g.BellmanFord(0);

    if(!success){
        cout << "Negative Cycles detected" << endl;
    }
    else
    {
        int total_weight = 0;
        for(const pair<int, pair<int,int>> &entry : vOrder)
        {
           cout << entry.first << " --- " << entry.second.first << " : " << entry.second.second << endl;
           total_weight += entry.second.second;
        }
        cout << "TOTAL WEIGHT : " << total_weight << endl;
    }

    return 0;
}
