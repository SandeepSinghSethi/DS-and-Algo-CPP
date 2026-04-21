#include<bits/stdc++.h>
using namespace std;
#define INF numeric_limits<int>::max()
namespace graph
{
namespace johnson_algo
{
class Item;
class Vertex
{
public:
    int data , id;
    Item *itemptr;
    Vertex *pi;
};
class Item
{
public:
    Vertex *head,*tail;
};
class Edges
{
public:
    int src,dest,weight;
};
class Johnson_Algo
{
private:
    unordered_map<int,Vertex *> nodeaddr;
    vector<Edges> edges;
    vector<Edges> alt_edges;
    int vertices = 0;
    vector<vector<int>> finalMatrix;
public:
    Johnson_Algo(int V) : vertices(V) {
        finalMatrix.resize(V+1,vector<int>(V+1,INF));
    };
    pair<bool,vector<int>> Bellman_Ford(int source);
    vector<int> Dijkstra(int s);
    void solve();
    void makeset(int i);
    void printPath(Vertex *s);
    void addedge(int s , int d , int w);
};
void Johnson_Algo::makeset(int data)
{
    Item *newitem = new Item;
    newitem->head = new Vertex;
    newitem->tail = newitem->head;
    nodeaddr[data] = newitem->head;
    newitem->head->data = data;
    newitem->head->id = data;
    newitem->head->itemptr = newitem;
    newitem->head->pi = nullptr;
}
void Johnson_Algo::addedge(int s, int d , int w)
{
    edges.push_back({s,d,w});
}
pair<bool,vector<int>> Johnson_Algo::Bellman_Ford(int source)
{
    vector<Edges> bf_edges = edges;
    // bf_edges[source] = 0;
    for(int i = 1;i<=vertices;i++)
    {
        bf_edges.push_back({source,i,0}); // adding s to entire graph with edge weight = 0;
    }

    // init single source
    for(const auto&entry : nodeaddr)
    {
        entry.second->pi = nullptr;
        entry.second->data = INF;
    }
    Vertex *s = nodeaddr[source];
    s->data = 0;

    // vector<int> dist(vertices+1,INF);
    // dist[0] = 0;

    for(int i = 0;i<vertices;i++)
    {
        for(const auto&edge : bf_edges)
        {
            Vertex *u = nodeaddr[edge.src];
            Vertex *v = nodeaddr[edge.dest];
            int weight = edge.weight;
            if(u->data != INF && v->data > u->data + weight)
            {
                v->data = u->data + weight;
                v->pi = u;
            }

            // if(dist[edge.src] != INF && dist[edge.dest] > dist[edge.src] + edge.weight)
            //     dist[edge.dest] = dist[edge.src] + edge.weight;
        }
    }
    for(const auto&edge : bf_edges)
    {
        Vertex *u = nodeaddr[edge.src];
        Vertex *v = nodeaddr[edge.dest];
        int weight = edge.weight;
        if(u->data < INF && v->data > u->data + weight)
        {
            return {false,{}};
        }
        // if(dist[edge.src] != INF && dist[edge.dest] > dist[edge.src] + edge.weight)
        //     return {false,{}};

    }

    vector<int> h(vertices+1);
    for(int i = 1;i<=vertices;i++)
    {
        h[i] = nodeaddr[i]->data;
    }
    return {true,h};
}

struct CompareEdge{
public:
    bool operator()(const pair<int,int>&a,const pair<int,int>&b)
    {
        return a.second < b.second;
    }
};

vector<int> Johnson_Algo::Dijkstra(int source)
{
    // init single source
    for(const auto&entry: nodeaddr)
    {
        Vertex *p = entry.second;
        p->data = INF;
        p->pi = nullptr;
    }
    //alt_edges are used so pq comparision will use Edges....
    priority_queue<pair<int,int>,vector<pair<int,int>>,CompareEdge> pq;

    Vertex *s = nodeaddr[source];
    s->data = 0;
    
    for(const auto&entry : nodeaddr)
    {
        Vertex *p = entry.second;
        pq.push({p->data,p->id});
    }

    // cout << "1" << endl;
    while(!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        Vertex *u_id = nodeaddr[u];
        // cout <<  u.src << " : " << u.dest << endl;
        for(const auto&edge : alt_edges){
            if(edge.src == u_id->id)
            {
                Vertex *v_id = nodeaddr[edge.dest];
                int w = edge.weight;

                if(u_id->data != INF && v_id->data > u_id->data + w)
                {
                    v_id->data = u_id->data + w;
                    v_id->pi = u_id;

                    pq.push({v_id->data,v_id->id});
                }
            }  
        }
    }

    vector<int> D(vertices+1,INF);
    cout << "From source as " << source << " to all other nodes of the graph !!" << endl;
    for(const auto&entry : nodeaddr)
    {
        Vertex *v = nodeaddr[entry.first];
        cout << "[V] : " << v->id << " : [W] : " << v->data << " : [P] : ";
        D[v->id] = v->data;
        if(v->data == INF){
            cout << "no path";
        }
        else
        {
            printPath(v);
        }
        cout << endl;
    }
    return D;
}

void Johnson_Algo:: printPath(Vertex *v)
{
    if(v->pi == nullptr)
    {
        cout << v->id;
        return;
    }
    printPath(v->pi);
    cout << " -> " << v->id;
}

void Johnson_Algo::solve()
{
    for(int i = 0;i<=vertices;i++)
    {
        makeset(i);
    }
    auto [bool_val,bf_h] = Bellman_Ford(0);
    if(!bool_val)
    {
        cout << "[-] Negative edge cycles found !!" << endl;
        return;
    }

    // for(int i = 1 ; i<=vertices;i++){
    //     cout << "0 -> " << i << " : ";
    //     cout << bf_h[i] << endl;;
    // }
    // alt_edges.resize(vertices);
    // cout << "\nPrevious: \n";
    // for(const auto&edge : edges)
    // {
    //         cout << edge.src << " -> " << edge.dest << " : " << edge.weight << endl;
    // }
    // now reweighting
    for(const auto&edge : edges)
    {
        int s = edge.src;
        int d = edge.dest;
        int w = edge.weight;

        alt_edges.push_back({s,d,w + bf_h[s] - bf_h[d]});
    }
    // for(const auto&entry: bf_h)
    //     cout << entry << " ";
    // cout << endl;
    // cout <<"\nAfter : \n";
    // for(const auto&edge : alt_edges)
    // {
    //         cout << edge.src << " -> " << edge.dest << " : " << edge.weight << endl;
    // }
        //After this the alt_edges will all have weights > 0 , following the lemma : w`(u,v) = w(u,v) + bf_h(u) - bf_h(v) >= 0
    // output after reweighting for the current edges:
    // 1 -> 2 : 4
    // 1 -> 3 : 13
    // 1 -> 5 : 0
    // 2 -> 4 : 0
    // 2 -> 5 : 10
    // 3 -> 2 : 0
    // 4 -> 1 : 2
    // 4 -> 3 : 0
    // 5 -> 4 : 2
    //
    // & bf_h = [0 0 -1 -5 0 -4] // size of six ,first value if of no use....
    // now running dijkstra on each vertex. with alt_edges i.e. w`(u,v)......
    nodeaddr.erase(0); // we need source==0 in bellman ford only .....
    for(int u = 1;u<=vertices;u++){
        //finds shortest path vertex u to all other vertex
        vector<int> D = Dijkstra(u);
        // for(const auto&e: D)
        //     cout << e << " ";
        cout << endl;
        for(int v = 1;v<=vertices;v++)
        {
            finalMatrix[u][v] = D[v] + bf_h[v] - bf_h[u];// reweighting back again to original
        }
    }

    for(int i = 1;i<=vertices;i++)
    {
        for(int j = 1;j<=vertices;j++)
        {
            cout << finalMatrix[i][j] << "\t";
        }
        cout << endl;
    }

    // vector<Edges> alt_edges = {};
    // for(const auto&edge : edges)
    // {
    //     int s = edge.src;
    //     int d = edge.dest;
    //     int w = edge.weight;

    //     alt_edges.push_back({s,d,w + bf_h[d] - bf_h[s]});
    // }
    // for(const auto&entry : bf_h)
    //     cout << entry << " , ";
    // cout << endl;
    // for(const auto&edge : alt_edges)
    // {
    //         cout << edge.src << " -> " << edge.dest << " : " << edge.weight << endl;
    // }
}

} // namespace bellman_ford  
} // namespace graph
int main(int argc, char const *argv[])
{
    int V = 5;
    auto g = graph::johnson_algo::Johnson_Algo(V);
    //edges must start from 1 or greater ,not < 1
    g.addedge(1,2,3);
    g.addedge(1,3,8);
    g.addedge(1,5,-4);
    g.addedge(2,4,1);
    g.addedge(2,5,7);
    g.addedge(3,2,4);
    g.addedge(4,1,2);
    g.addedge(4,3,-5);
    g.addedge(5,4,6);
    
    // it works something like : running bellman ford on the graph to detect negative edge cycles , if exists then exit , else returns a shortest path to all other vertex on the graph from a virtual source '0 and relaxed |V-1| times...
    //
    // then reweighting is done to make all edges >=0 , by edges`(u,v) = edges(u,v) + bf_h(u) - bf_h(v) >=0
    //
    // then dijkstra is ran on each vertex and got the shortest path weight from each u to all vertices and return a vector for it, then again reweighting the graph so that shortest path can be viewed for the original edges in the graph.
    g.solve();
    return 0;
}
