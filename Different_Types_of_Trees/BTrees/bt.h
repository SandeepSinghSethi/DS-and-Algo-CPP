#ifndef bt_h
#define bt_h

#include<bits/stdc++.h>
using namespace std;

class BTNode {
    int *keys;
    BTNode **C;
    int n ;
    bool leaf;
    int  t;

public:
    BTNode(int _t,bool _leaf);
    
    void traversal();

    void insertNonFull(int k);

    void splitChild(int i , BTNode* y);

    BTNode* splitRoot(BTNode* x);

    BTNode *search(int k);

    void remove(int k);

    int findkey(int k);

    void removeFromLeaf(int k);

    void removeFromNonLeaf(int k);

    int getPred(int i);

    int getSucc(int i);

    // void merge(BTNode *C1,BTNode *C2);
    void merge(int i);

    void fill(int i);

    void brwFromPrev(int i);

    void brwFromNext(int i);

    friend class BTree;
};

class BTree{
    BTNode* root;
    int t;

public:
    BTree(int _t) {
        root = NULL;
        t = _t;
    }

    void insert(int k);

    void traverse()
    {
        if(root != NULL)
        {
            root->traversal();
        }
    }

    BTNode* search(int k)
    {
        return (root == NULL) ? NULL : root->search(k);
    }

    void remove(int k);
};

BTNode::BTNode(int _t , bool _leaf)
{
    t = _t;
    leaf = _leaf;

    keys = new int[2*t-1];
    C = new BTNode*[2*t];
    n = 0;
}

void BTNode::traversal(){
    int i = 0;
    for(i = 0;i<n;i++)
    {
        if(leaf == false){
            cout << endl;
            C[i]->traversal();
        }
        cout << keys[i] << " " ;
    }
    if(leaf == false)
        C[i]->traversal();

}

BTNode* BTNode::search(int k )
{
    int i =0;
    while( i < n && k > keys[i])
        i++;

    if(keys[i] == k)
        return this;

    if(leaf == true)
        return NULL;

    return C[i]->search(k);

}

void BTNode::insertNonFull(int k)
{
    int i = n-1;
    if(leaf == true)
    {
        while(i >= 0 && keys[i] > k){
            keys[i+1] = keys[i];
            i--;
        }
        keys[i+1] = k;
        n++;
    }
    else
    {
        while(i >= 0 && keys[i] > k)
            i--;

        if(C[i+1]->n == 2*t-1)
        {
            splitChild(i+1,C[i+1]);
            if(keys[i+1] < k)
                i++;
        }
        C[i+1]->insertNonFull(k);
    }
}

void BTNode::splitChild(int i , BTNode* y)
{
    BTNode *z = new BTNode(y->t,y->leaf);
    z->n = t-1;
    for(int j = 0;j<t-1;j++)
    {
        z->keys[j] = y->keys[j+t];
    }
    
    if(y->leaf == false){
        for(int j = 0;j<t;j++)
        {
            z->C[j] = y->C[j+t];
        }
    }

    y->n = t-1;

    for(int j = n;j>=i+1;j--)
    {
        C[j+1] = C[j];
    }

    C[i+1] = z;

    for(int j = n-1;j>=i;j--)
    {   
        keys[j+1] = keys[j];
    }

    keys[i] = y->keys[t-1];

    n++;
}

BTNode* BTNode::splitRoot(BTNode* root)
{
    BTNode *x = new BTNode(t,false);
    x->C[0] = root;
    x->n = 0;
    root = x;
    x->splitChild(0,x);
    return x;
}

void BTree::insert(int k)
{

    if(root == NULL)
    {
        root = new BTNode(t,true);
        root->keys[0] = k;
        root->n = 1;
    }
    else 
    {
        if(root->n == 2*t-1)
        {
            // BTNode *x = root->splitRoot(root);            
            // x->insertNonFull(k);

            BTNode *x = new BTNode(t,false);
            x->C[0] = root;
            x->splitChild(0,root);

            int i = 0;
            if(x->keys[0]  < k)
                i++;
            x->C[i]->insertNonFull(k);

            root = x;
        }
        else
        {
            root->insertNonFull(k);
        }
    }
}

int BTNode::findkey(int k)
{
    int i= 0;
    while(i<n && k > keys[i])
        i++;

    return i;
}

void BTNode::removeFromLeaf(int i)
{
    for(int k = i+1;k<n;k++)
        keys[k-1] = keys[k];

    n--;
}

int BTNode::getPred(int i)
{
    BTNode *x = C[i];
    while(!x->leaf)
        x = x->C[x->n];

    return x->keys[x->n-1];
}

int BTNode::getSucc(int i)
{
    BTNode *x = C[i+1];
    while(!x->leaf)
        x = x->C[0];

    return x->keys[0];
}

// * my implementation of merge , it worked fine but needed to be simpler , used  gfg implementation
// void BTNode::merge(BTNode *C1,BTNode *C2)
// {
//     int n1 = C1->n;
//     int n2 = C2->n;

//     for(int i = 0;i<n2;i++)
//     {
//         C1->keys[n1+i] = C2->keys[i];
//     }

//     if(!C2->leaf)
//     {
//         for(int i = 0;i<=n2;i++){
//             C1->C[n1+i] = C2->C[i];
//         }
//     }

//     C1->n = C1->n + C2->n;
// }

void BTNode::merge(int i)
{
    BTNode *child = C[i];
    BTNode *sibling = C[i+1];

    //* this is used to store the current key at keys[i] to child's last key
    child->keys[t-1] = keys[i];


    //* this does copy the siblings keys to childs keys hence allowing us to remove sibling
    for(int j = 0;j<sibling->n;j++)
    {
        child->keys[j+t] = sibling->keys[j];
    }


    // if sibling have some child
    if(!child->leaf)
    {
        for(int j = 0;j<=sibling->n;j++)
        {
            child->C[j+t] = sibling->C[j];
        }
    }

    // we need to remember that we stored current keys[i] at child's last key so we need to move further keys in the current node one step before also with the childs as well

    for(int j = i+1;j<n;j++)
    {
        keys[j-1] = keys[j];
    }

    for(int j = i+2;j<=n;j++)
    {
        C[j-1] = C[j];
    }

    child->n += sibling->n;
    n--;
    delete(sibling);
    return;

}

void BTNode::removeFromNonLeaf(int i)
{
    BTNode *c0 = C[i];
    BTNode *c1 = C[i+1];

    int k = keys[i];

    if(c0->n >= t)
    {
        int pred = getPred(i);
        keys[i] = pred;
        C[i]->remove(pred);
    }
    else if(c1->n >= t)
    {
        int succ = getSucc(i);
        keys[i] = succ;
        C[i+1]->remove(succ);
    }
    else
    {
        merge(i);
        C[i]->remove(k);
    }

    // * it was my try
    // if(c1->n >= t)
    // {
    //     keys[i] = c1->keys[0];
    //     for(int k =1 ;k<c1->n;k++)
    //         c1->keys[k-1] = c1->keys[k];
    //     c1->n = c1->n - 1;
    // }
    // else if(c0->n >= t)
    // {
    //     keys[i] = c0->keys[c0->n-1];
    //     c0->n = c0->n - 1;
    // }
    // else
    // {
    //     // * at last both the child of node at ith position have exactly t-1 child so merge them together
    //     keys[i] = c0->keys[c0->n-1]; 
    //     c0->n = c0->n -1;
    //     merge(c0,c1);

    //     for(int k = i+1;k<=n;k++)
    //     {
    //         C[k-1] = C[k];
    //     }
    //     delete C[n];
    // }

    
}

void BTNode::fill(int i)
{
    // if previous child has more than t-1 keys then
    if(i!=0 && C[i-1]->n>=t){
        brwFromPrev(i);
    }
    // if next child has more than t-1 keys then
    else if (i!= n && C[i+1]->n>=t){
        brwFromNext(i);
    }
    // if both child has less than t-1 keys then we merge them
    else{
        if(i!=n)
            merge(i);
        else
            merge(i-1);
    }
}

void BTNode::brwFromPrev(int i)
{
    BTNode *child = C[i];
    BTNode *sibling = C[i-1];

    for(int j = child->n-1;j>=0;j--)
        child->keys[j+1] = child->keys[j];

    if(!child->leaf)
    {
        for(int j = child->n;j>=0;j--)
            child->C[j+1] =  child->C[j];
    }

    child->keys[0] = keys[i-1];

    if(!child->leaf)
        child->C[0] = sibling->C[sibling->n];

    keys[i-1] = sibling->keys[sibling->n-1];

    child->n += 1;
    sibling->n -= 1;
}

void BTNode::brwFromNext(int i)
{
    BTNode *child = C[i];
    BTNode *sibling = C[i+1];

    child->keys[child->n] = keys[i];

    if(!child->leaf)
        child->C[child->n+1] = sibling->C[0];

    keys[i] = sibling->keys[0];

    for(int j = 1;j<sibling->n;j++)
    {
        sibling->keys[j-1] = sibling->keys[i];
    }

    if(!sibling->leaf)
    {
        for(int j = 1;j<=sibling->n;j++)
            sibling->C[j-1] = sibling->C[j];
    }

    child->n += 1;
    sibling->n -= 1;

}

void BTNode::remove(int k)
{
    int i = findkey(k);

    if(i<n && keys[i] == k)
    {
        if(leaf)
        {
            removeFromLeaf(i);
        }
        else
        {
            removeFromNonLeaf(i);
        }
    }
    else
    {

        //* at this point we are at the last index to search , whether it is a leaf of not , if it is a leaf then its a dead end , if not a leaf then check for its child and remove from the last remaining child
        if(leaf){
            cout << "key  " << k << " is not present" << endl;
            return;
        }

        bool flag = ((i==n) ? true:false);

        //? if the last child has less than t keys then we stabilize the child keys with its siblings making child and sibling have t keys;
        if(C[i]->n < t)
            fill(i);

        //* if after fill the last child has been merged with the previous child / sibling then remove it from the last child which is i-1 in the case after the fill operation
        if(flag && i>n)
            C[i-1]->remove(k);
        else //* if not then simply remove from the last child
            C[i]->remove(k);

    }
}

void BTree::remove(int k)
{
    if(!root)
    {
        cout << "Tree is already empty" << endl;
        return;
    }

    root->remove(k);

    if(root->n == 0)
    {
        BTNode *tmp = root;
        if(root->leaf)
            root = NULL;
        else
            root = root->C[0];
        
        delete tmp;
    }
    return;

}


#endif