#include<bits/stdc++.h>
#include "orderstat.h"


int main(int argc, char const *argv[])
{
    RBTree<int> tree;
    int arr[] = {30,25,40,20,28,35,45,22,42,50};
    for(int i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
    {
        tree.insert(arr[i]);
    } 
    tree.print();
    Node<int>* x = tree.OrderStat(3);
    if(x != nullptr)
        std::cout << x->data << " " << " & SIZE : " << x->size << "\n";

    std::cout << tree.getRank(x) << "\n";

    return 0;
}
