#include<bits/stdc++.h>

// so the heapsort algorithm works by taking the advantage that BUILD_MAX_HEAP procedure will create an array a max_heap i.e. first value of the array will be the greatest
// [5,3,17,10,84,19,6,22,9]	<- normal array (not a max_heap)
// [84,22,19,10,3,17,6,5,9]	<- build_max_heap array

// then we loop from n to 1st index (2nd place) and we just swap the 0th index value of the array with the last place or n in the array

// then we can see that the largest value is at the end , so we decrement the n to n-1 so that we can further store further larger values at the end following the largest , also we have to make sure that after swapping the values , the remaining array doesn't remains the max_heap anymore , so we have to run max_heap on the 1st index to maintain the max_heap property

// according to chatGPT for -
//		10,000 size array it will take = 1.74 ms (0.12ms of cpp sort)
//		1 million size array it will take = 27.22ms (0.94ms of cpp sort)
//		1 billion size array it will take = 58.587s (26.146s of cpp sort)
// 		1 trillion size array it will take = 2.9h	(1.2h of cpp sort)

template <typename T>
void printarray(T *arr,int n)
{
	for(int i= 0;i<n;i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

template <typename T>
void max_heapify(T *arr,int i , int n)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if(l < n && arr[l] > arr[largest])
		largest = l;

	if(r < n && arr[r] > arr[largest])
		largest = r;

	if(largest != i){
		std::swap(arr[i],arr[largest]);
		max_heapify(arr,largest,n);
	}
}

template <typename T>
void build_max_heap(T *arr,int n)
{
	for(int i=(n/2)-1;i>=0;i--)
	{
		max_heapify(arr,i,n);
	}
}

template <typename T>
void heapsort(T *arr,int n)
{
	build_max_heap(arr,n);

	for(int i = n-1;i>=0;i--)
	{
		std::swap(arr[0],arr[i]);
		max_heapify(arr,0,i);
	}
}

template <typename T>
void stress_testing(T *heap,int n)
{
	std::vector<int> arr;

	srand(time(0));
	for(int i = 0;i<n;i++)
	{
		arr.push_back(rand() + 1);
	}
	// printarray(arr.data(),arr.size());
	heapsort(arr.data(),arr.size());
	// printarray(arr.data(),arr.size());
}

int main(int argc, char const *argv[])
{
	int arr[] = {5,3,7,10,84,19,6,22,9};
	int n = sizeof(arr)/sizeof(int);

	printarray(arr,n);
	heapsort(arr,n);
	printarray(arr,n);

	if(argc > 1)
	{
		std::cout << "Doing stress testing on " << argv[1] << " inputs size array " << std::endl;		
		stress_testing(arr,atoi(argv[1]));
	}
	return 0;
}