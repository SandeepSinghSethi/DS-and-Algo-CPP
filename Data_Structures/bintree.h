#ifndef bintree_h
#define bintree_h
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

	Node(T data,Node<T>* parent=nullptr) : data(data),left(nullptr),right(nullptr),parent(parent) {};
};

template <typename T>
struct TypeChecker
{
	static const bool isString = false;
};

template <>
struct TypeChecker<std::string>
{
	static const bool isString = true;
};



template <typename T>
class bintree
{
private:
	Node<T>* root;
	
	Node<T>* insertBT(Node<T>* current,T data,Node<T>* parent)
	{
		if(current == nullptr)
		{
			return new Node<T>(data,parent);
		}

		if(data < current->data)
		{
			current->left = insertBT(current->left,data,current);
		}
		else if(data > current->data)
		{
			current->right = insertBT(current->right, data , current);
		}

		return current;
	}
	
	void destroytree(Node<T>* root)
	{
		if(root){
			destroytree(root->left);
			destroytree(root->right);
			delete root;
		}
	}


public:
	bintree() : root(nullptr) {};

	void insert(T data)
	{
		// root = insertBT(root,data,nullptr);

		Node<T>* x = root;
		Node<T>* y = nullptr;
		Node<T>* z;

		while(x)
		{
			y = x;
			if(data < x->data)
			{
				x= x->left;
			}
			else
			{
				x = x->right;
			}
		}

		z = new Node<T>(data,y);

		if (y == nullptr){
			root = new Node<T>(data,nullptr);
		}
		else if(data < y->data)
		{
			y->left = z;
		}
		else
		{
			y->right = z;
		}

	}


	void inordertraversal(Node<T>* root)
	{
		if(root){
			inordertraversal(root->left);
			std::cout << root->data << " ";
			inordertraversal(root->right);
		}
	}

	void preordertraversal(Node<T>* root)
	{
		if(root)
		{
			std::cout << root->data << " " ;
			preordertraversal(root->left);
			preordertraversal(root->right);
		}
	}

	void postordertraversal(Node<T>* root)
	{
		if(root)
		{
			postordertraversal(root->left);
			postordertraversal(root->right);
			std::cout << root->data << " ";
		}
	}

	void print()
	{
		cout << "INORDER-> " ;
		inordertraversal(root);
		cout << endl;
		cout << "PREORDER-> ";
		preordertraversal(root);
		cout << endl;
		cout << "POSTORDER-> "; 
		postordertraversal(root);
		cout << endl;
		std::cout << std::endl;
	}

	~bintree(){
		destroytree(root);
	}

	T getmax()
	{
		Node<T>* temp = root;
		while(temp->right)
			temp = temp->right;
		// delete temp;
		T data = temp->data;
		return data;
	}

	T getmin()
	{
		Node<T>* temp = root;
		while(temp->left != nullptr)
		{
			temp = temp->left;
		}	
		T data = temp->data;
		// delete temp;
		return data;	
	}


	Node<T>* srch(Node<T>* current , T key)
	{
		if((current == nullptr) || (key == current->data))
			return current;

		if(key < current->data)
		{
			return srch(current->left,key);
		}
		else
		{
			return srch(current->right,key);
		}
	}

	
	T search(T key)
	{
	    Node<T>* temp = root;
	
	  	temp = srch(temp,key);
	 	
	 	if(temp != nullptr){
	 		return temp->data;
	 	}
	 	else{
	 		// cout << "Key : " << key << " not found " << endl;
		 	temp = new Node<T>(-1,nullptr);
	 	}

	 	return temp->data;


	
	}

	T stringsearch(T key)
	{
		// iterative search
		Node<T>* temp = root;

		while (temp != nullptr && key != temp->data )
			{
			if (key < temp->data)
				temp = temp->left;
			else
				temp = temp->right;
		}
		if(!temp)
			temp = new Node<T>("NiL",nullptr);

		return temp->data;
	}


	// T getSuccessor(T key)
	// {
	// 	Node<T>* tmp = root;
	// 	Node<T>* suc = nullptr;

	// 	while(tmp)
	// 	{
	// 		if(key < tmp->data)
	// 		{
	// 			suc = tmp;
	// 			tmp = tmp->left;
	// 		}
	// 		else
	// 		{
	// 			tmp = tmp->right;
	// 		}
	// 	}
	// 	return suc->data;
	// }


	Node<T>* findMinNode(Node<T>* ptr)
	{
		while(ptr->left)
			ptr = ptr->left;

		return ptr;
	}

	Node<T>* findMaxNode(Node<T>* ptr)
	{
		while(ptr->right)
			ptr = ptr->right;

		return ptr;
	}

	Node<T>* fetchnode(Node<T>* ptr,T key)
	{
		if(!ptr)
			return nullptr;

		while(ptr)
		{
			if(key == ptr->data)
				return ptr;
			else if(key < ptr->data)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}

		return nullptr;
	}

	auto getSuccessor(T key)
	{
		Node<T>* tmp = root;
		tmp = fetchnode(tmp,key);

		if(!tmp){
			return -1;
		}


		if(tmp->right)
		{
			Node<T>* ptr = findMinNode(tmp->right);
			return ptr->data;
		}



		Node<T>* prnt = tmp->parent;
		while(prnt != nullptr && tmp == prnt->right)
		{
			tmp = tmp->parent;
			prnt = prnt->parent;
		}

		cout << prnt->data << " < PDATA === TMPDATA > " << tmp->data << endl;
		return prnt->data;
	}	

	void transplant(Node<T>* u,Node<T>* v)
	{
		if(u->parent == nullptr){
			root = v;	// to check whether node is the root node or not
		}
		else if(u == u->parent->left)
		{
			u->parent->left = v; // if node is the left child of the parent
		}
		else
		{
			u->parent->right = v; // else it is the right child of the parent
		}

		if(v != nullptr)
			v->parent = u->parent; // setting up the parent of v to the parent of u , if it is not null

	}

	void deletion(T key)
	{
		Node<T>* tmp = root;
		tmp = fetchnode(tmp,key); // will get the node pointer which will be deleted

		if(!tmp)
		{
			cout << "Node doesn't exists !! " << endl;
		}
		else
		{
			if(tmp->left == nullptr)
			{
				transplant(tmp,tmp->right); // if left child doesn't exists ,swap it with its right child on its place
			}
			else if(tmp->right == nullptr)
			{
				transplant(tmp,tmp->left);
			}
			else
			{ // now the node is having both left and right child , even if we delete the root node , we have to find the min node or successor of the root node to do further deletion operation successfully
				Node<T>* ptr = findMinNode(tmp->right); // finding the successor of the current node

				if(ptr != tmp->right) // if ptr/successor != tmp->right (our difficult case)
				{
					transplant(ptr ,ptr->right);
					ptr->right = tmp->right;
					ptr->right->parent = ptr;
				}
				transplant(tmp,ptr);
				ptr->left = tmp->left;
				ptr->left->parent = ptr;
				
				delete(tmp);
			}
		}
	}

	// void deletion(T key)
	// {
	// 	Node<T>* tmp = root;
	// 	tmp = fetchnode(tmp,key);

	// 	if(!tmp)
	// 	{
	// 		cout << "Key not found in the binary tree ." << endl;
	// 	}
	// 	else
	// 	{
	// 		if(!tmp->left && !tmp->right)
	// 		{
	// 			if(tmp->parent->left == tmp)
	// 				tmp->parent->left = nullptr;
	// 			else if(tmp->parent->right == tmp)
	// 				tmp->parent->right = nullptr;

	// 			delete tmp;
	// 		}
	// 		else if(tmp->left == nullptr && tmp->right != nullptr)
	// 		{
	// 			tmp->right->parent = tmp->parent;
	// 			tmp = tmp->right;
	// 		}
	// 		else if(tmp->right == nullptr && tmp->left != nullptr)
	// 		{
	// 			tmp->left->parent = tmp->parent;
	// 			tmp = tmp->left;
	// 		}
	// 		else if((tmp->right != nullptr && tmp->right->left == nullptr))
	// 		{
	// 			tmp->right->parent = tmp->parent;
	// 			tmp->right->left = tmp->left;
	// 			tmp = tmp->right;
	// 		}
	// 		else
	// 		{
	// 			T data = getSuccessor(tmp->data);
	// 			Node<T>* ptr = root;
	// 			ptr = fetchnode(ptr,data);
	// 			cout << "HJJ" << endl;
	// 			if(ptr->right == nullptr)
	// 			{
	// 				ptr->parent->left = nullptr;
	// 				ptr->left = tmp->left;
	// 				ptr->right = tmp->right;
	// 				ptr->parent = tmp->parent;
	// 				ptr->left->parent = ptr;
	// 				ptr->right->parent = ptr;
	// 			}
	// 			else
	// 			{
	// 				ptr->parent->left = ptr->right;
	// 				ptr->right->parent = ptr->parent;
	// 				ptr->parent = tmp->parent;
	// 				ptr->left = tmp->left;
	// 				ptr->left->parent = ptr;
	// 				ptr->right = tmp->right;
	// 				ptr->right->parent = ptr;
	// 				tmp = ptr;
	// 				delete ptr;
	// 			}
	// 		}
	// 	}
	// }


};

#endif

