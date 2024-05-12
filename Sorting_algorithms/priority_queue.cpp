#include <bits/stdc++.h>
#include "heapfunctions.h"

using namespace CLRS::CH6;
using namespace std;

int main(int argc, char const *argv[])
{
	cout << "Initializing a heap A " << "\n";
	Heap<int> arr = {2,53,1,443,12,44,133,12,534};
	arr.setHeapsize();
	printarray(arr);

	cout << "Finding the max in the above heap..\n" ;
	cout << "The max is : " << heapMaximum(arr) << "\n";


	cout << "\nNow extracting the maximum value in the heap (removing) : " << heapExtractMax(arr) << "\n";
	cout << "Heap after extraction(removal) : " ;
	printarray(arr);

	
	cout << "\nNow using heapIncreaseKey function to increase the value of 5th(6) index to 50 : \n";
	heapIncreaseKey(arr,5,50);
	cout << "After increment : ";
	printarray(arr);


	cout << "\nNow inserting 353 in the heap : \n";
	maxHeapInsert(arr,353);
	cout << "After Insertion : ";
	printarray(arr);

	cout << "\nNow sorting the heap in ascending order : \n";
	heapsort(arr);
	printarray(arr);

	cout << "\nNow sorting it in descending order : \n";
	heapsort_des(arr);
	printarray(arr);


	cout << "\nAgain making the sorted heap as a max-heap : \n";
	build_max_heap(arr);
	printarray(arr); 
	

	Heap<int> ch6q1 = {15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1};
	ch6q1.setHeapsize();
	printarray(ch6q1);
	cout << "Executing heapExtractMax on the above heap as per the question 1 of the book : " << heapExtractMax(ch6q1) <<"\n";
	cout << "After extraction : ";
	printarray(ch6q1);
	cout<<"\n";

	Heap<int> ch6q2 = {15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1};
	ch6q2.setHeapsize();
	printarray(ch6q2);
	cout << "Perform maxHeapInsert(arr,10) function on the above heap : \n";
	maxHeapInsert(ch6q2,10);
	printarray(ch6q2);


	Heap<int> ch6q3 = {15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1};
	ch6q3.setHeapsize();
	printarray(ch6q3);
	cout << "Using the minheap functions now the above array : ";
	cout << "Minimum : " << heapMinimum(ch6q3) << "\n";
	cout << "ExtractMin : " << heapExtractMin(ch6q3) << "\n";
	printarray(ch6q3);
	cout << "Decrease Key 5th index to 1 : ";
	heapDecreaseKey(ch6q3,5,1);
	printarray(ch6q3);
	cout<< "Insert 10 in the heap : ";
	minHeapInsert(ch6q3,10);
	printarray(ch6q3);


	// checking if the usage of build_min/build_max functions are essential for any non-maxheap array for our heap functions , and this resulted in the usage of build functions in the descrease/increase functions , as we don't maintain heap property of the heap in those functions but adding a build max/min function in the early stage result in the min/max heap ultimately.....
	
	cout << "\n\n";
	Heap<int> test = {234 ,23412,23,63456,12,0,35,56,66};
	test.setHeapsize();
	printarray(test);
	heapDecreaseKey(test,3,10);
	printarray(test);


	return 0;
}