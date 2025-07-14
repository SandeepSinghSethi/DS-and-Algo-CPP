#include<bits/stdc++.h>
using namespace std;

class Item;

class Vertex{
public:
    int data , id;
    Vertex *pi;
    Item *itemPtr;
};

class Item{
public:
    Vertex *head,*tail;
};

class Edge{
public:
    Edge() = default;
    Edge(int s , int d , int w) : src(s),dest(w),weight(w) {};
    int src;
    int dest;
    int weight;
};

class Dijkstra{
private:
    unordered_map<int,Vertex *> nodeaddr;
    vector<vector<pair<int,int>>> adjList;
    vector<Edge> edges;
    int vertices;

public:
    Dijkstra(int V)
    {
        vertices = V;
        adjList.resize(V);
    };

    void makeset(int i);
    void addedge(int s , int d , int w);
    void printPath(Vertex *v);
    void DijkSolve(int source); // retval : list of {{source,{dest,weight}}
};

struct CompareEdge{
public:
    bool operator()(const pair<int,int>&a,const pair<int,int>&b)
    {
        return a.second < b.second;
    }
};

void Dijkstra::DijkSolve(int source){
    vector<pair<int,pair<int,int>>> retlist;

    // initialize single source
    for(const auto&node : nodeaddr)
    {
        Vertex *ptr = node.second;
        ptr->data = INT_MAX;
        ptr->pi = nullptr;
    }

    // declaring priority_queue
    priority_queue<pair<int,int>,vector<pair<int,int>>,CompareEdge> pq;

    Vertex *s = nodeaddr[source];
    s->data = 0;

    // filling up the pq;
    for(const auto&node : nodeaddr)
    {
        Vertex *v = node.second;
        pq.push({v->data,v->id});
    }

    // doing actual work
    while(!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        Vertex *u_id = nodeaddr[u];

        for(const auto&[v,w] : adjList[u])
        {
            Vertex *v_id = nodeaddr[v];
            int weight = w;

            // relaxation
            if(u_id->data != INT_MAX && v_id->data > u_id->data + weight)
            {
                v_id->data = u_id->data + weight;
                v_id->pi = u_id;

                pq.push({v_id->data,v_id->id});
            }
        }
    }

    cout << "From source as " << source << " to all other nodes of the graph !!" << endl;
    for(const auto&entry : nodeaddr)
    {
        Vertex *v = nodeaddr[entry.first];
        cout << "[V] : " << v->id << " : [W] : " << v->data << " : [P] : ";
        if(v->data == INT_MAX){
            cout << "no path";
        }
        else
        {
            printPath(v);
        }
        cout << endl;
    }
    for(const auto&node : nodeaddr)
    {
        Vertex *v = node.second;
        if(v->pi!=nullptr)
        {
            int u_id = v->pi->id;
            int v_id = v->id;
            int weight = v->data - v->pi->data;

            retlist.push_back({u_id,{v_id,weight}});
        }
    }
    
    
}

void Dijkstra::printPath(Vertex *ptr)
{
    if(ptr->pi == nullptr)
    {
        cout << ptr->id;
        return;
    }
    printPath(ptr->pi);
    cout << "-> " << ptr->id;
}

void Dijkstra::addedge(int s, int d , int w)
{
    adjList[s].emplace_back(d,w);
    edges.emplace_back(s,d,w);
}

void Dijkstra::makeset(int i)
{
    Item *newitem = new Item;
    newitem->head = new Vertex;
    newitem->tail = newitem->head;

    nodeaddr[i] = newitem->head;

    newitem->head->data = i;
    newitem->head->id = i;
    newitem->head->pi = nullptr;
    newitem->head->itemPtr = newitem;
}



int main(int argc, char const *argv[])
{
    int V = 7;
    Dijkstra g(V);

    for(int i = 0;i<V;i++)
        g.makeset(i);

    g.addedge(0,4,2);
    g.addedge(0,5,3);
    g.addedge(5,4,1);
    g.addedge(4,6,3);
    g.addedge(6,1,2);
    g.addedge(1,3,1);
    g.addedge(4,2,1);
    g.addedge(2,3,3);

    g.DijkSolve(0);

    return 0;
}
