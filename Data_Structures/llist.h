#ifndef list_h
#define list_h

#include<bits/stdc++.h>
using namespace std;


template <typename T>
class Node 
{
public:
	T data;
	Node<T>* next = nullptr;
};

template <typename T>
class LinkedL
{
private:
	Node<T>* head;
	Node<T>* tail;
	int size;

public:
	LinkedL(){
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	void updtail()
	{
		Node<T>* temp = head;
		if(temp == nullptr){
			tail = nullptr;
			return;
		}
		while(temp->next !=nullptr)
		{
			temp = temp->next;
		}
		tail = temp;
	}

	void updsize()
	{
		size=0;
		Node<T>* temp = head;
		while(temp!=nullptr)
		{
			temp = temp->next;
			size++;
		}
		return;
	}

	void display()
	{
		Node<T>* temp = head;
		while(temp!= nullptr)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	void delstart()
	{
		head = head->next;
	}

	void delend()
	{	
		Node<T>* temp = head;
		while(temp->next->next !=nullptr)
		{
			temp = temp->next;
		}
		temp->next = nullptr;
	}

	void delbtw()
	{
		int pos;
		int sz= this->size;
		display();
		cout << "Enter position to insert [0-" << size-1 << "] : ";
		cin>>pos;
		
		if(pos == 0)
		{
			delstart();
			return;
		}
		else if(pos == sz)
		{
			delend();
			return;
		}
		else if(pos > sz)
		{
			cout << "Unknown size !!" << endl;
			return;
		}

		Node<T>* temp = head;
		Node<T>* var;
		for(int i= 0;i<pos-1 ;i++)
			temp = temp->next;

		var = temp->next;
		temp->next = var->next;
		delete(var);
	}

	void del()
	{
		if(size == 0)
		{
			cout << "List is empty" << endl;
			return;
		}
		int pos;
		cout << "\nWhere To Delete : 0:Start | 1:End | 2:In-Between : " ;
		cin >> pos;
		switch (pos)
		{
		case 0:
			delstart();
			break;
		case 1:
			delend();
			break;
		case 2:
			delbtw();
			break;
		default:
			cout << "Invalid Choice !!\nAborting insert operation .." << endl;
			return;	
		}
	}

	void insertbtw(T data)
	{
		int pos;
		int sz= this->size;
		display();
		cout << "Enter position to insert [0-" << size-1 << "] : ";
		cin>>pos;
		
		if(pos == 0){
			insertstart(data);
			return;
		}
		if(pos == sz){
			insertend(data);
			return;
		}
		else if(pos > sz){
			cout << "Unknown size !! " <<endl;
			return;
		}

		Node<T>* temp = head;
		Node<T>* t2 = new Node<T>();

		for(int i =0;i<pos-1;i++)
		{
			temp = temp->next;
		}

		t2->data = data;
		t2->next = temp->next;
		temp->next= t2;
	}

	void insertstart(T data)
	{
		Node<T>* temp = new Node<T>();
		temp->data = data;
		temp->next = head;
		head = temp;
	}

	void insertend(T data)
	{
		if(head == nullptr)
		{
			insertstart(data);
			return;
		}
		Node<T>* temp = new Node<T>();
		temp->data = data;
		temp->next = nullptr;

		Node<T>* ptr = head;
		while(ptr->next != nullptr)
		{
			ptr = ptr->next;
		}
		ptr->next = temp;
	}

	void insert()
	{
		int pos;
		cout << "\nWhere to enter : 0:Start | 1:End | 2:In-Between : " << " ";
		cin >> pos;
		T data;
		cout << "Enter data : " ;
		cin >> data;
		switch (pos)
		{
		case 0:
			insertstart(data);
			break;
		case 1:
			insertend(data);
			break;
		case 2:
			insertbtw(data);
			break;
		default:
			cout << "Invalid Choice !!\nAborting insert operation .." << endl;
			return;
		}
	}

	void searchBydata()
	{
		T data;
		cout << "Enter data : " ;
		cin >> data;

		Node<T>* temp = head;
		int i =0;
		while(temp!=nullptr){
			if(temp->data == data)
			{
				cout << "Found at index : " << i << " -> " << data << " \n";
				return;
			}
			temp = temp->next;
			i++;
		}
		cout << "Nothing found " << endl;
	}

	void searchBypos()
	{
		int pos;
		int sz = this->size;
		cout << "Enter the position to find the value of [0-" << sz-1 << "] : ";
		cin >> pos;
		if(pos == 0)
		{
			cout << head->data << endl;
			return;
		}
		else if(pos == sz-1)
		{
			cout << tail->data << endl;
			return;
		}
		else if(pos >= sz)
		{
			cout<< "Invalid index !!"<<endl;
			return;
		}
		Node<T>* temp = head;
		for(int i=0;i<pos;i++)
			temp = temp->next;
		
		cout << temp->data << endl;
		return;
	}

	void search()
	{
		if(size== 0)
		{
			cout << "LIST empty , can't search !! " << endl;
			return;
		}
		int pos;
		cout << "\nHow to find : 1:ByPosition | 2:ByData : ";
		cin>> pos;
		switch(pos)
		{
		case 1:
			searchBypos();
			break;
		case 2:
			searchBydata();
			break;
		default:
			cout << "Invalid option detected !! " << endl;
		}
	}

	void operate()
	{
		cout << "Welcome to the linkedlist implementation in cpp .." << "\n";
		cout << "TYPE <Singly Linked List> ||  Operations <insert,delete,display,listsize,search> " << "\n";
		int opt = 1;

		while(opt >= 1 && opt <= 5){
			cout << "1:Insert | 2:Delete | 3:Display | 4:ListSize | 5:Search | 0:Exit  : ";
			cin >> opt;
			switch (opt)
			{
			case 1:
				insert();		
				break;
			case 2:
				del();
				break;
			case 3:
				display();
				break;
			case 4:
				cout << "Size : " << size << endl;
				break;
			case 5:
				search();
				break;
			case 0:
				cout << "EXITING !! " << endl;
				return;
			default:
				cout << "Invalid Choice !! " << endl;
			}
			updsize();
			updtail();
		}
		return;
	}
};

template <typename T>
class DBNode
{
public:
	T data;
	DBNode<T>* next = nullptr;
	DBNode<T>* prev = nullptr;
};


template <typename T>
class DBList 
{
private:
	DBNode<T>* head;
	DBNode<T>* tail;
	int size;

public:
	DBList(){
		head = nullptr;
		tail = nullptr;
		size =0;
	}

	void updsize()
	{
		size=0;
		DBNode<T>* temp = head;
		while(temp!=nullptr)
		{
			temp = temp->next;
			size++;
		}
		return;
	}

	void display()
	{
		DBNode<T>* temp = head;
		while(temp!= nullptr)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	void delstart()
	{
		DBNode<T>* ptr = head;
		head = head->next;
		head->prev = nullptr;
		delete(ptr);
	}

	void delend()
	{	
		DBNode<T>* temp = head;
		DBNode<T>* p ;
		while(temp->next->next !=nullptr)
		{
			temp = temp->next;
		}
		p = temp->next;
		temp->next = nullptr;
		delete(p);
	}

	void delbtw()
	{
		int pos;
		int sz= this->size;
		display();
		cout << "Enter position to insert [0-" << size-1 << "] : ";
		cin>>pos;
		
		if(pos == 0)
		{
			delstart();
			return;
		}
		else if(pos == sz)
		{
			delend();
			return;
		}
		else if(pos > sz)
		{
			cout << "Unknown size !!" << endl;
			return;
		}

		DBNode<T>* temp = head;
		DBNode<T>* var;
		for(int i= 0;i<pos-1 ;i++)
			temp = temp->next;

		var = temp->next;
		temp->next = var->next;
		var->next->prev = temp;
		delete(var);
	}

	void del()
	{
		if(size == 0)
		{
			cout << "List is empty" << endl;
			return;
		}
		int pos;
		cout << "\nWhere To Delete : 0:Start | 1:End | 2:In-Between : " ;
		cin >> pos;
		switch (pos)
		{
		case 0:
			delstart();
			break;
		case 1:
			delend();
			break;
		case 2:
			delbtw();
			break;
		default:
			cout << "Invalid Choice !!\nAborting Delete operation .." << endl;
			return;	
		}
	}

	void insertbtw(T data)
	{
		int pos;
		int sz= this->size;
		display();
		cout << "Enter position to insert [0-" << size-1 << "] : ";
		cin>>pos;
		
		if(pos == 0){
			insertstart(data);
			return;
		}
		if(pos == sz){
			insertend(data);
			return;
		}
		else if(pos > sz){
			cout << "Unknown size !! " <<endl;
			return;
		}

		DBNode<T>* temp = head;
		DBNode<T>* p ;
		DBNode<T>* t2 = new DBNode<T>();

		for(int i =0;i<pos-1;i++)
		{
			temp = temp->next;
		}

		t2->data = data;
		t2->next = temp->next;
		temp->next->prev = t2;
		t2->prev = temp;
		temp->next= t2;
	}


	void insertend(T data)
	{
		if(size == 0)
		{
			insertstart(data);
			return;
		}
		DBNode<T>* temp = new DBNode<T>();
		temp->data = data;
		temp->next = nullptr;

		DBNode<T>* ptr = head;
		while(ptr->next != nullptr)
		{
			ptr = ptr->next;
		}
		ptr->next = temp;
		temp->prev = ptr;
	}

	void insertstart(T data)
	{
		DBNode<T>* temp = new DBNode<T>();
		temp->data = data;
		temp->next = head;
		temp->prev = nullptr;

		if(head != nullptr)
		{
			head->prev = temp;
		}
		head = temp;
	}

	void insert()
	{
		int pos;
		cout << "\nWhere to enter : 0:Start | 1:End | 2:In-Between : " << " ";
		cin >> pos;
		T data;
		cout << "Enter data : " ;
		cin >> data;
		switch (pos)
		{
		case 0:
			insertstart(data);
			break;
		case 1:
			insertend(data);
			break;
		case 2:
			insertbtw(data);
			break;
		default:
			cout << "Invalid Choice !!\nAborting insert operation .." << endl;
			return;
		}
	}

	void searchBydata()
	{
		T data;
		cout << "Enter data : " ;
		cin >> data;

		DBNode<T>* temp = head;
		DBNode<T>* t2 = tail;
		int i =0,j=size-1;

		while((temp!=nullptr || tail!=nullptr) && (temp!=t2)){
			if(temp->data == data)
			{
				cout << "Found at index : " << i << " -> " << data << " \n";
				return;
			}
			temp = temp->next;
			i++;

			if(t2->data == data)
			{
				cout << "Found at index : " << j << " -> " << data << "\n";
				return;
			}
			t2 = t2->prev;
			j--;
		}
		cout << "Nothing found " << endl;
	}

	void searchBypos()
	{
		int pos;
		int sz = this->size;
		cout << "Enter the position to find the value of [0-" << sz-1 << "] : ";
		cin >> pos;
		if(pos == 0)
		{
			cout << head->data << endl;
			return;
		}
		else if(pos == sz-1)
		{
			cout << tail->data << endl;
			return;
		}
		else if(pos >= sz)
		{
			cout<< "Invalid index !!"<<endl;
			return;
		}
		DBNode<T>* t1 = head;
		DBNode<T>* t2 = tail;

		if(pos > size/2)
		{
			for(int i = 0;i<pos-(size/2)-1;i++)
			{
				t2 = t2->prev;
			}
			cout << t2->data << endl;
		}
		else
		{
			for(int i=0;i<pos;i++)
				t1 = t1->next;	
			cout << t1->data << endl;
		}
		
		return;
	}

	void search()
	{
		if(size== 0)
		{
			cout << "LIST empty , can't search !! " << endl;
			return;
		}
		int pos;
		cout << "\nHow to find : 1:ByPosition | 2:ByData : ";
		cin>> pos;
		switch(pos)
		{
		case 1:
			searchBypos();
			break;
		case 2:
			searchBydata();
			break;
		default:
			cout << "Invalid option detected !! " << endl;
		}
	}

	void updtail()
	{
		DBNode<T>* temp = head;
		if(head == nullptr){
			tail = nullptr;
			return;
		}

		while(temp->next !=nullptr)
		{
			temp = temp->next;
		}
	
		tail = temp;
	}

	void operate()
	{
		cout << "Welcome to the DBlinkedlist implementation in cpp .." << "\n";
		cout << "TYPE <Doubly Linked List> ||  Operations <insert,delete,display,listsize,search> " << "\n";
		int opt = 1;

		while(opt >= 1 && opt <= 5){
			cout << "1:Insert | 2:Delete | 3:Display | 4:ListSize | 5:Search | 0:Exit  : ";
			cin >> opt;
			switch (opt)
			{
			case 1:
				insert();		
				break;
			case 2:
				del();
				break;
			case 3:
				display();
				break;
			case 4:
				cout << "Size : " << size << endl;
				break;
			case 5:
				search();
				break;
			case 0:
				cout << "EXITING !! " << endl;
				return;
			default:
				cout << "Invalid Choice !! " << endl;
			}
			cout << " 1 " <<endl;
			updsize();
			cout << " 2 " <<endl;
			updtail();
			cout << " 3 " <<endl;

		}
		return;
	}
};

#endif