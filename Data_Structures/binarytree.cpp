#include "bintree.h"

using namespace std;

int main(int argc, char const *argv[])
{
	// 4 5 3 2 1
	bintree<int> tree;
	tree.insert(15);
	tree.insert(6);
	tree.insert(18);
	tree.insert(17);
	tree.insert(20);
	tree.insert(3);
	tree.insert(7);
	tree.insert(2);
	tree.insert(4);
	tree.insert(13);
	tree.insert(9);
	tree.print();

	cout << "SEARCH 2: " << tree.search(2) << endl;
	cout << "SEARCH 223: " << tree.search(223) << endl;
	cout << "MAX: " << tree.getmax() << endl;
	cout << "MIN: " << tree.getmin() << endl;
	
	cout << "SUCCESSOR (13) : " << tree.getSuccessor(13) << endl;
	cout << "SUCCESSOR (132) : " << tree.getSuccessor(132) << endl;
	cout << "SUCCESSOR (2) : " << tree.getSuccessor(2) << endl;


	cout <<endl;
	cout << "DELETE 2 " << endl;
	tree.deletion(2) ;
	tree.print();
	cout << "DELETE 322 " << endl;
	tree.deletion(322) ;
	tree.print();
	cout << "DELETE 18 " <<  endl;
	tree.deletion(18) ;
	tree.print();




	bintree<double> dt;
	dt.insert(3.14);
	dt.insert(2.718);
	dt.insert(1.618);
	dt.insert(1.42);
	dt.print();

	cout << "SEARCH 1231.618 : " << dt.search(1231.618) << endl;
	cout << "SEARCH 451.618 : " << dt.search(451.618) << endl;
	cout << "SEARCH 1.618 : " << dt.search(1.618) << endl;

	cout <<"MAX: " << dt.getmax() << endl;
	cout << "MIN: "<< dt.getmin() << endl;


	bintree<string> st;
	st.insert("apple");
	st.insert("sandeep");
	st.insert("zlib.s");
	st.insert("banana");
	st.insert("orange");
	st.print();
	cout << st.getmax() << endl;
	cout << st.getmin() << endl;

	cout << st.stringsearch("banana") << " " 	 << endl;	
	cout << st.stringsearch("not_a_banana") << " " 	 << endl;	
	cout << st.stringsearch("zlib.s") << " " 	 << endl;	


	// cout << "\nDeleting : banana" << endl;
	// st.deletion("banana");
	// st.deletion("skfsdkjs");
	// st.deletion("zlib.s");

	// st.print();

	return 0;
}