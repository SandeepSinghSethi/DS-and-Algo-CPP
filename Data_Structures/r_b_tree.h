#ifndef r_b_tree_h
#define r_b_tree_h
#pragma once

#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Node
{
public:
	
	T data;
	Node<T>* left;
	Node<T>* right;
	Node<T>* parent;
	bool color; // red = 1 , black = 0 , double black = 2

	Node(T data ,Node<T>* parent=nullptr,bool color=1,Node<T>* left=nullptr,Node<T>* right=nullptr) : data(data),left(left),right(right),parent(parent),color(color) {};
};

template <typename T>
class RBTree
{
private:
	Node<T>* root;	
	Node<T>* Tnil;

	void leftrotate(Node<T>* x)
	{
		Node<T>* y = x->right;
		x->right = y->left;

		if(x->right != Tnil)
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
		// return y;
	}


	void rightrotate(Node<T>* y)
	{
		Node<T>* x = y->left;
		y->left = x->right;

		if(x->right != Tnil)
			x->right->parent = y;

		x->parent = y->parent;

		if(y->parent == Tnil)
			root = x;
		else if(y->parent->left == y)
			y->parent->left = x;
		else
			y->parent->right = x;

		x->right = y;
		y->parent = x;

		// return x;
	}

	Node<T>* insertRec(Node<T>* cur , T data , Node<T>* parent)
	{
		if(cur == Tnil)
			return new Node<T>(data,Tnil,1,Tnil,Tnil);

		if(data < cur->data)
			cur->left = insertRec(cur->left,data,cur);
		else if(data > cur->data)
			cur->right = insertRec(cur->right,data,cur);

		return cur;
	}

	void destroy(Node<T>* root)
	{
		if(root != Tnil)
		{
			destroy(root->left);
			destroy(root->right);
			delete root;
		}
	}

public:
	RBTree() {
		Tnil = new Node<T>(-1,nullptr,0);
		root = Tnil;
	}

	void insert(T data)
	{
		// root = insertRec(root,data,nullptr);

		Node<T>* x = root;
		Node<T>* y = Tnil;
		Node<T>* z;

		while(x != Tnil)
		{
			y = x;
			if(data < x->data){
				x = x->left;
			}
			else if(data == x->data){
				cout << "Node with data " << data << ": exists ..\n";
				return;
			}			
			else{
				x = x->right;
			}
		}

		z = new Node<T>(data,y,1,Tnil,Tnil);

		if(y == Tnil)
			root = z;
		else if(data < y->data)
			y->left = z;
		else
			y->right = z;


		// if it is root;
		if(z->parent == Tnil)
			z->color = 0;

		// if no grandfather
		// if(z->parent->parent == nullptr)
		// 	return;

		RedBlackFixup(z);
	}

	int getcolor(Node<T>* ptr)
	{
		if(ptr == nullptr)
			return 0;

		if(ptr->color == 1)
			return 1;
		return 0;
	}

	void setcolor(Node<T>* ptr,int color)
	{
		if(ptr == nullptr)
			return;
		ptr->color = color;
	}

	Node<T>* fetchnode(Node<T>* ptr,T key)
	{
		if(ptr == Tnil)
			return Tnil;

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

	void RedBlackFixup(Node<T>* ptr)
	{
		int red = 1;
		int black = 0;

		while(ptr != root && getcolor(ptr->parent) == 1 && getcolor(ptr) == red)
		{
			if(ptr->parent == ptr->parent->parent->right)
			{//right side of the tree

				Node<T>* uncle = ptr->parent->parent->left;
				if(getcolor(uncle) == 1)
				{
					setcolor(uncle,black);
					setcolor(ptr->parent,black);
					if(ptr->parent->parent == root)
						break;
					else
						setcolor(ptr->parent->parent,((getcolor(ptr->parent->parent) == red) ? black : red));
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
				if(getcolor(uncle) == 1)
				{
					setcolor(uncle,black);
					setcolor(ptr->parent,black);
					if(ptr->parent->parent == root)
						break;
					else
						setcolor(ptr->parent->parent,((getcolor(ptr->parent->parent) == red) ? black : red));
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
	}



	~RBTree()
	{
		destroy(root);
	}

	void inordertraversal(Node<T>* root)
	{
		if(root != Tnil){
			inordertraversal(root->left);
			std::cout << root->data << "->";
			cout << ((root->color) ? "RED" : "BLACK") << "\n";
			inordertraversal(root->right);
		}
	}

	void preordertraversal(Node<T>* root)
	{
		if(root != Tnil)
		{
			std::cout << root->data << "->" ;
			cout << ((root->color) ? "RED" : "BLACK") << "\n";
			preordertraversal(root->left);
			preordertraversal(root->right);
		}
	}

	void postordertraversal(Node<T>* root)
	{
		if(root != Tnil)
		{
			postordertraversal(root->left);
			postordertraversal(root->right);
			std::cout << root->data << "->";
			cout << ((root->color) ? "RED" : "BLACK") << "\n";
		}
	}

	void print()
	{
		cout << "INORDER-> \n" ;
		cout << "ROOT: " << root->data << endl;
		inordertraversal(root);
		cout << endl;
		// cout << "PREORDER-> ";
		// preordertraversal(root);
		// cout << endl;
		// cout << "POSTORDER-> "; 
		// postordertraversal(root);
		// cout << endl;
		// std::cout << std::endl;
	}

	void transplant(Node<T>* u,Node<T>* v)
	{
		if(u->parent == Tnil)
			root = v;
		if(u->parent->left == u)
			u->parent->left =v;
		else
			u->parent->right = v;

		// while using Tnil we dont have to worry about if the v is nullptr or not
		v->parent = u->parent;
	}

	Node<T>* findminNode(Node<T>* ptr)
	{
		while(ptr->left != Tnil)
			ptr = ptr->left;
		return ptr;
	}

	void deletion(T key)
	{
		Node<T>* tmp = root;
		tmp = fetchnode(tmp,key);
		Node<T>* x;
		Node<T>* y;

		if(tmp == Tnil)
		{
			cout << "No key found in the tree ." << endl;
			return;
		}

		y = tmp;
		int y_orig_color = y->color;

		if(tmp->left == Tnil)
		{
			x = tmp->right;
			transplant(tmp,tmp->right);
		}
		else if(tmp->right == Tnil)
		{
			x = tmp->left;
			transplant(tmp,tmp->left);
		}
		else
		{
			y = findminNode(tmp->right);
			y_orig_color = y->color;
			x = y->right;

			if(y->parent == tmp)
			{
				x->parent = y;
			}
			else
			{
				transplant(y,y->right);
				y->right = tmp->right;
				y->right->parent = y;
			}

			transplant(tmp,y);
			y->left = tmp->left;
			y->left->parent = y;
			y->color = tmp->color;
		}

		delete tmp;

		if(y_orig_color == 0){
			DelRBFixup(x);
		}
		
	}

	void DelRBFixup(Node<T>* x)
	{
		Node<T>* w;

		if(x != root && getcolor(x) == 0)
		{
			if(x == x->parent->left)
			{
				w = x->parent->right;
				if(getcolor(w) == 1)
				{
					setcolor(w,0);
					setcolor(x->parent,1);
					leftrotate(x->parent);
					w = x->parent->right;
				}

				if(getcolor(w->left) == 0 && getcolor(w->right) == 0)
				{
					setcolor(w,1);
					x = x->parent;					
				}
				else
				{
					if(getcolor(w->right) == 0)
					{
						setcolor(w->left,0);
						setcolor(w,1);
						rightrotate(w);
						w = x->parent->right;
					}
					setcolor(w,getcolor(x->parent));
					setcolor(x->parent,0);
					setcolor(w->right,0);
					leftrotate(x->parent);
					x = root;
				}

			}
			else
			{
				w = x->parent->left;
				if(getcolor(w) == 1)
				{
					setcolor(w,0);
					setcolor(x->parent,1);
					rightrotate(x->parent);
					w = x->parent->left;
				}

				if(getcolor(w->left) == 0 && getcolor(w->right) == 0)
				{
					setcolor(w,1);
					x = x->parent;					
				}
				else
				{
					if(getcolor(w->left) == 0)
					{
						setcolor(w->right,0);
						setcolor(w,1);
						leftrotate(w);
						w = x->parent->left;
					}
					setcolor(w,getcolor(x->parent));
					setcolor(x->parent,0);
					setcolor(w->left,0);
					rightrotate(x->parent);
					x = root;
				}
			}

		}	
		setcolor(x,0);
	}

};


#endif