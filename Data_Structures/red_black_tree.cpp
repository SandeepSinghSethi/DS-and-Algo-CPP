#include "r_b_tree.h"

int main(int argc, char const *argv[])
{
	RBTree<int> tree;

	int data ;
	cout << "Enter 0 to quit insertion " << endl;
	// cin >> data ;
	// while(data != 0){
	// 	tree.insert(data);
	// 	cin >> data ;
	// }	
	int arr[] = {30,25,40,20,28,35,45,22,42,50};
	for(int i = 0;i<sizeof(arr)/sizeof(int);i++)
	{
		data = arr[i];
		tree.insert(data);
	}

	tree.print();

	cout << "Enter 0 to stop deletion " << endl;
	cout << "Enter data to delete : " ;
	cin >> data;
	while(data){
		tree.deletion(data);
		tree.print();
		cout << "Enter data to delete : " ;
		cin >> data;
	}
	return 0;
}