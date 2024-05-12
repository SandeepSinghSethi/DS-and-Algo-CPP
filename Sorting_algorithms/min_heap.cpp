#include <bits/stdc++.h>

template <typename T>
void printarray(T *arr,int n)
{
	for(int i=0;i<n;i++)
	{
		std::cout << arr[i] << ' ';
	}
	std::cout << '\n';
}

template <typename T>
void min_heapify(T *arr,int i , int n)
{
	int smallest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if(l < n && arr[l] < arr[smallest])
		smallest = l;

	if(r < n && arr[r] < arr[smallest])
		smallest = r;

	if(smallest != i){
		std::swap(arr[i],arr[smallest]);
		min_heapify(arr,smallest,n);
	}
}

template <typename T>
void build_min_heap(T *arr,int n)
{
	for(int i=(n/2)-1;i>=0;i--)
	{
		min_heapify(arr,i,n);
	}
}

template <typename T>
void heapsort_descending(T *arr,int n)
{
	build_min_heap(arr,n);
	printarray(arr,n);

	for(int i = n-1;i>=0;i--)
	{
		std::swap(arr[0],arr[i]);
		min_heapify(arr,0,i);
	}
}



int main(int argc, char const *argv[])
{

	int arr[] = {4,232,5,22,65,2,56,7,0};
	int n = sizeof(arr)/sizeof(int);

	printarray(arr,n);
	heapsort_descending(arr,n);
	printarray(arr,n);
	return 0;
}