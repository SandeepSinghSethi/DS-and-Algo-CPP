#include<bits/stdc++.h>
using namespace std;

class Item;

class Node {
public:
    int data;
    Node* next;
    Item* itemPtr;
};

class Item{
public:
    Node *hd;
    Node *tail;
};

class DisJSet {
private:
    // * using hashset to ease finding parent of a key
    unordered_map<int , Node *> nodeaddr;

public:
    void makeset(int a);
    void Union(Item *i1 , Item *i2);
    Item* find(int key);
    void print();
};

Item *DisJSet::find(int key)
{
    Node *ptr = nodeaddr[key];
    return ptr->itemPtr ;
}

void DisJSet::makeset(int a)
{
    Item *newset = new Item;
    newset->hd = new Node;
    newset->tail = newset->hd;

    nodeaddr[a] = newset->hd;

    newset->hd->data = a;
    newset->hd->itemPtr = newset;
    newset->hd->next = NULL;
}

void DisJSet::Union(Item *i1, Item *i2)
{
    Node *xrep = i1->hd;
    Node *yrep = i2->hd;

    if(xrep == yrep)
        return;

    Node* cur = i2->hd;
    while(cur != 0)
    {
        cur->itemPtr = i1;
        cur = cur->next;
    }

    i1->tail->next = i2->hd;
    i1->tail = i2->tail;

    delete i2;    
}

void DisJSet::print()
{
    unordered_map<int , vector<int>> pmmap;

    for(const auto&entry : nodeaddr)
    {
        Item *root = find(entry.first);
        // here we will get the root of entry.first (which is key of the set) and put that in as the key of the new map
        int rootkey = root->hd->data;
        pmmap[rootkey].push_back(entry.first);
        
    }

    for(const auto&key: pmmap)
    {
        cout << "{ ";
        for(int val: key.second)
        {
            cout << val << ", " ;
        }
        cout << "}\n";
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
    DisJSet obj;    
    // obj.makeset(1);

    for(int i = 1;i<10;i++)
    {
        obj.makeset(i);
    }

    // for(int i = 0;i<100000;i++)
    // {
    //     obj.Union(obj.find(getrandom(1,99999)),obj.find(getrandom(1,99999)));
    // }

    obj.Union(obj.find(4),obj.find(6));
    obj.Union(obj.find(4),obj.find(9));
    obj.Union(obj.find(3),obj.find(8));
    obj.Union(obj.find(1),obj.find(2));
    obj.Union(obj.find(9),obj.find(8));

    if(obj.find(4)->hd == obj.find(2)->hd)
        cout << "Yes" << endl;
    else
        cout << "No " << endl;

    if(obj.find(3)->hd == obj.find(4)->hd)
        cout << "Yes" << endl;
    else
        cout << "No " << endl;

    obj.print();

    return 0;
}
