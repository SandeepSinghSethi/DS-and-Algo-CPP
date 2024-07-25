#ifndef orderstat_h
#define orderstat_h

#pragma once
#include <iostream>

using namespace std;

template <typename T>
class Node{
public:
    T data;
    Node<T>* parent;
    Node<T>* left;
    Node<T>* right;
    bool color;
    int size;

    Node(T data,Node<T>* parent=nullptr,bool color=1,Node<T>* left=nullptr,Node<T>* right=nullptr,int size=0) : data(data),left(left),right(right),parent(parent),color(color),size(size) {};
};


template <typename T>
class RBTree
{
private:
    Node<T>* root;
    Node<T>* Tnil;
    
    int getcolor(Node<T>* ptr)
    {
        if(ptr == nullptr)
            return 0;
        return (ptr->color == 1 ? 1:0);
    }

    void setcolor(Node<T>* ptr,bool color)
    {
        if(ptr == nullptr)
            return;
        ptr->color = color;
    }

    void leftrotate(Node<T>* x)
    {
        Node<T>* y = x->right;
        x->right = y->left;

        if(x->right == Tnil)
            x->right->parent = x;

        y->parent = x->parent;
        if(x->parent == Tnil)
            root = y;
        else if(x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;

        y->size = x->size;
        if(x->right != Tnil && x->left != Tnil)
        {
            x->size = x->left->size + x->right->size + 1;
        }
        else if(x->right != Tnil)
        {
            x->size = x->right->size + 1;
        }
        else if(x->left != Tnil)
        {
            x->size = x->left->size + 1;
        }
        else
        {
            x->size = 1;
        }

    }

    void rightrotate(Node<T>* y)
    {
        Node<T>* x = y->left;
        y->left = x->right;

        if(x->right == Tnil)
            x->right->parent = y;

        x->parent = y->parent;
        if(y->parent == root)
            root = x;
        else if(y->parent->left == y)
            y->parent->left = x;
        else
            y->parent->right = x;

        x->right = y;
        y->parent = x;

        x->size = y->size;

        if(y->right != Tnil && y->left != Tnil)
        {
            y->size = y->left->size + y->right->size + 1;
        }
        else if(y->right != Tnil)
        {
            y->size = y->right->size + 1;
        }
        else if(y->left != Tnil)
        {
            y->size = y->left->size + 1;
        }
        else
        {
            y->size = 1;
        }

    }

    void inorderTraversal(Node<T>* ptr)
    {
        if(ptr != Tnil)
        {
            inorderTraversal(ptr->left);
            std::cout << ptr->data << "-> " ;
            std::cout << ((ptr->color) ? "RED" : "BLACK" ) << " & Size : " << ptr->size << "\n";
            inorderTraversal(ptr->right);
        }
    }

    void RBfixup(Node<T>* ptr)
    {
        int red = 1;
        int black = 0;

        while(ptr != root && getcolor(ptr->parent) == red && getcolor(ptr) == red )
        {
            if(ptr->parent == ptr->parent->parent->right)
            {
                Node<T>* uncle = ptr->parent->parent->left;
                if(getcolor(uncle) == red)
                {
                    setcolor(uncle,black);
                    setcolor(ptr->parent,black);
                    if(ptr->parent->parent == root)
                        break;
                    else
                        setcolor(ptr->parent->parent,((getcolor(ptr->parent->parent) == black ) ? red : black));
                    ptr = ptr->parent->parent;
                }
                else
                {
                    if(ptr == ptr->parent->left)
                    {
                        ptr = ptr->parent;
                        rightrotate(ptr);
                    }
                    setcolor(ptr->parent,black);
                    setcolor(ptr->parent->parent,red);
                    leftrotate(ptr->parent->parent);
                }
            }
            else
            {
                Node<T>* uncle = ptr->parent->parent->right;
                if(getcolor(uncle) == red)
                {
                    setcolor(uncle,black);
                    setcolor(ptr->parent,black);
                    if(ptr->parent->parent == root)
                        break;
                    else
                        setcolor(ptr->parent->parent,((getcolor(ptr->parent->parent) == red) ? black:red));
                    ptr = ptr->parent->parent;
                }
                else
                {
                    if(ptr == ptr->parent->right)
                    {
                        ptr = ptr->parent;
                        leftrotate(ptr);
                    }
                    setcolor(ptr->parent,black);
                    setcolor(ptr->parent->parent,red);
                    rightrotate(ptr->parent->parent);
                }
            }
        } 
        // safety function
        if(getcolor(root) != black)
        {
            setcolor(root,black);
        }
    }

    Node<T>* fetchNode(T key)
    {
        Node<T>* ptr = root;
        while(ptr != Tnil)
        {
            if(key == ptr->data)
                return ptr;
            else if(key < ptr->data)
                ptr = ptr->left;
            else
                ptr = ptr->right;
        }

        return Tnil;
    }

    void transplant(Node<T>*u,Node<T>* v)
    {
        if(u->parent == Tnil) // if u == root;
            root = v;


        
        if(u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        v->parent = u->parent;
    }

    Node<T>* findMinNode(Node<T>* ptr)
    {
        while(ptr->left != Tnil)
        {
            ptr = ptr->left;
        }
        return ptr;
    }

    Node<T>* OSSelect(Node<T>*x , int i)
    {
        int r = 0;
        if(x->left != Tnil || x->left != nullptr)
            r = x->left->size + 1;
        else
            r = 0;

        // while (r != i)
        // {
        //     if(i < r)
        //     {
        //         x = x->left;
        //     }
        //     else
        //     {
        //         x = x->right;
        //         i = i-r;
        //     }
        //     r = x->left->size + 1;
        // }
        // return x;
        if(i == r)
        {
            return x;
        }
        else if(i < r)
        {
            return OSSelect(x->left,i);
        }
        else
        {
            return OSSelect(x->right,i-r);
        }
    }


public:
    RBTree() {
        Tnil = new Node<T>(-1,nullptr,0);
        root = Tnil;
        root->size = 1;
    }

    void insert(T data)
    {
        Node<T>* x = root;
        Node<T>* y = Tnil;
        Node<T>* z;

        while(x != Tnil)
        {
            y =x ;
            
            if(data < x->data)
            {
                x = x->left;        
            }
            else if(data > x->data)
            {
                x = x->right;
            }
            else
            {
                std::cout << "Node with data : " << data << " exists already in the tree ." << std::endl;
                return;
            }
            y->size++;
        }
        z = new Node(data,y,1,Tnil,Tnil);
        
        if(y == Tnil)
        {
            root = z;
        }
        else if(data < y->data)
        {
            y->left = z;
        }
        else
        {
            y->right = z;
        }

        if(z->parent == Tnil)
            z->color = 0 ; //black if the node is the root node;

        z->size = 1;
        RBfixup(z);
    }

    void print()
    {
        std::cout << "Printing Inorder Traversal of the RB Tree \n";
        std::cout << "ROOT : " << root->data << std::endl;
        inorderTraversal(root);
        std::cout << "\n";
    }

    Node<T>* OrderStat(int i)
    {
        if(i > root->size || i < 0)
        {
            std::cout << "There exists no node who is this small or big \n";
            return nullptr;
        }
        return OSSelect(root,i);
    }

    int getRank(Node<T>* x)
    {
        int r = x->left->size + 1;

        Node<T>* y = x;
        Node<T>* ptr = root;

        while(y != ptr)
        {
            if(y == y->parent->right)
            {
                r += y->parent->left->size + 1;
            }
            y = y->parent;
        }
        return r;
    }
    // void deletion(T key)
    // {
    //     Node<T>* tmp = fetchNode(key);
    //     if(tmp == Tnil)
    //     {
    //         std::cout << "No node found with the given key , can't delete ...\n";
    //         return;
    //     }

    //     Node<T>* x ;
    //     Node<T>* y;

    //     y = tmp;
    //     int y_color = y->color;

    //     if(tmp->left == Tnil)
    //     {
    //         x = tmp->right;
    //         transplant(tmp,tmp->right);
    //     }
    //     else if(tmp->right == Tnil)
    //     {
    //         x = tmp->left;
    //         transplant(tmp,tmp->left);
    //     }
    //     else
    //     {
    //         y = findMinNode(tmp->right);
    //         y_color = y->color;
    //         x = y->right;
    //     }

    //     delete tmp;

    //     if(y_color == 0)
    //     {
    //         DelRBFixup(x);
    //     }
    // }


};

#endif