#include <bits/stdc++.h>
using namespace std;

class Item;

class Node{
public:
    int data;
    int rank;
    Node *next;
    Item *itemPtr;
};

class Item{
public:
    Node *hd,*tl;
};

class DisjSet{
private:
    unordered_map<int,Node*> nodeaddr;
public:
    void makeset(int data);
    Item* findset(int data);
    void Union(Item *a , Item *b);
    void LinkItem(Item *a, Item *b);
    void print();
};

void DisjSet::makeset(int x)
{
    Item *newptr = new Item;
    newptr->hd = new Node;
    newptr->tl = newptr->hd;

    nodeaddr[x] = newptr->hd;

    newptr->hd->data = x;
    newptr->hd->itemPtr = newptr;
    newptr->hd->rank = 0;
    newptr->hd->next = NULL;
}

Item* DisjSet::findset(int key)
{
    Node *ptr = nodeaddr[key];
    return ptr->itemPtr;
}

void DisjSet::LinkItem(Item *a,Item *b)
{
    Node *ptr = b->hd;
    while(ptr != 0)
    {
        ptr->itemPtr = a;
        ptr = ptr->next;
    }

    a->tl->next = b->hd;
    a->tl = b->tl;

    delete b;
}

void DisjSet::Union(Item *a , Item *b)
{
    Node *xrep = a->hd;
    Node *yrep = b->hd;

    if(xrep == yrep)
        return;

    int xrank = xrep->rank;
    int yrank = yrep->rank;

    if(xrank > yrank)
    {
        LinkItem(a,b);
    }
    else if(yrank > xrank)
    {
        LinkItem(b,a);
    }
    else
    {
        LinkItem(a,b);
        a->hd->rank++;
    }
    
}

void DisjSet::print()
{
    unordered_map<int ,vector<int>> pmmap;

    for(const auto&key : nodeaddr)
    {
        Item *ptr = findset(key.first);
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

int getrandom(int min, int max)
{
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distr(min,max);

    return distr(gen);
}

int main(int argc, char const *argv[])
{
    DisjSet obj;

//* this implementation of disjoint set forests allows us to use rank and pathcompression to get better results while using linked lists , although path compression can be simply acheived by using hashmaps , so used here .

    for(int i =0;i<100000;i++)
        obj.makeset(i);

    for(int i = 0;i<100000;i++)
    {
        obj.Union(obj.findset(getrandom(1,99999)),obj.findset(getrandom(1,99999)));
    }


    // ? this implementation is way much faster than the conventional linked list implementation which doesn't uses path compression or union by rank;

    // ! results for 100000 keys in the universal set:
    // *    disjoint_set_forests: 
                            // real	5.20s
                            // user	5.10s
                            // sys	0.05s
                            // cpu	99%
    
    // *    linked_list_disjoint_set: 
                            // real	52.48s
                            // user	52.14s
                            // sys	0.08s
                            // cpu	99%


    // obj.Union(obj.findset(4),obj.findset(6));
    // obj.Union(obj.findset(4),obj.findset(9));
    // obj.Union(obj.findset(3),obj.findset(8));
    // obj.Union(obj.findset(1),obj.findset(2));
    // obj.Union(obj.findset(9),obj.findset(8));

    obj.print();
    
    return 0;
}
