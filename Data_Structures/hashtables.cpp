#include "hashtb.h"

int main(int argc, char const *argv[])
{
	HashTB hashtable;
	hashtable.insert("sandeep",420);
	hashtable.insert("pankaj",12);
	hashtable.insert("vasu",221);
	hashtable.insert("adarsh",234);
	hashtable.insert("abhishek",23);




	hashtable.print();
	// retreiving pankaj
	int pkj = hashtable.retreive("pankaj");
	cout << pkj << endl;

	hashtable.print();
	// removing pankaj
	hashtable.remove("pankaj");

	hashtable.insert("yash",2324);
	hashtable.insert("himanshu",2134);

	hashtable.print();
	return 0;
}