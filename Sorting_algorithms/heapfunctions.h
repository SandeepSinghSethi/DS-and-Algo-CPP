#ifndef heapfunctions_h
#define heapfunctions_h

#include "Heap.h"
#include <iostream>
using std::swap;

namespace CLRS
{
namespace CH6
{

	template <typename T>
	void printarray(Heap<T>& arr)
	{
		for(int i= 0;i<arr.heapsize;i++)
		{
			std::cout << arr[i] << " ";
		}
		std::cout << "\n";
	}

	int parent(int i)
	{
		return ((i-1)/2);
	}

	int left(int i)
	{
		return (2*i+1);
	}

	int right(int i)
	{
		return (2*i+2);
	}

	template <typename T>
	void max_heapify(Heap<T>& arr,int i)
	{
		int largest = i;
		int l = left(i);
		int r = right(i);

		if(l<arr.heapsize && arr[l] > arr[largest])
		{
			largest = l;
		}
		if(r<arr.heapsize && arr[r] > arr[largest])
		{
			largest = r;
		}
		if(largest != i)
		{
			swap(arr[i],arr[largest]);
			max_heapify(arr,largest);
		}
	}

	template <typename T>
	void build_max_heap(Heap<T>& arr)
	{
		for(int i = (arr.heapsize/2)-1;i>=0;i--)
		{
			max_heapify(arr,i);
		}
	}

	template <typename T>
	void min_heapify(Heap<T>& arr,int i)
	{
		int smallest = i;
		int l = left(i);
		int r = right(i);

		if(l < arr.heapsize && arr[l] < arr[smallest])
		{
			smallest = l;
		}

		if(r < arr.heapsize && arr[r] < arr[smallest])
		{
			smallest = r;
		}

		if(smallest != i)
		{
			std::swap(arr[i],arr[smallest]);
			min_heapify(arr,smallest);
		}
	}

	template <typename T>
	void build_min_heap(Heap<T>& arr)
	{
		for(int i = (arr.heapsize/2)-1;i>=0;i--)
		{
			min_heapify(arr,i);
		}
	}

	template <typename T>
	int heapMaximum(Heap<T>& arr)
	{
		build_max_heap(arr);
		return arr[0];
	}

	template <typename T>
	T heapExtractMax(Heap<T>& arr)
	{
		if(arr.heapsize < 1)
		{
			throw("Heap underflowed !!");
		}
		build_max_heap(arr);
		T max = arr[0];
		arr[0] = arr[arr.heapsize-1];
		arr.heapsize--;
		max_heapify(arr,0);
		return max;
	}

	template <typename T>
	void heapIncreaseKey(Heap<T>& arr,int i, T k)
	{
		if(k < arr[i])
		{
			throw("The key is smaller than the current key");
		}
		if(i >= arr.heapsize)
		{
			throw("Index doesn't exist in the heap\n");
		}
		build_max_heap(arr);
		arr[i] = k;
		while(i>0 && arr[parent(i)] < arr[i])
		{
			std::swap(arr[parent(i)],arr[i]);
			i = parent(i);
		}

	}

	template <typename T>
	void maxHeapInsert(Heap<T>& arr,T k)
	{
		arr.heapsize++;
		arr[arr.heapsize-1] = INT_MIN; // sothat arr can maintain the heapIncreasekey property
		heapIncreaseKey(arr,arr.heapsize-1,k);	
	}	

	template <typename T>
	void heapsort(Heap<T>& arr)
	{
		int backup_val = arr.heapsize;
		if(arr.heapsize <1)
		{
			throw("Heap underflow !!");
		}

		build_max_heap(arr);

		for(int i = arr.heapsize-1;i>=0;i--)
		{
			swap(arr[0],arr[i]);
			arr.heapsize--;
			max_heapify(arr,0);
		}

		arr.heapsize = backup_val;
	}

	template <typename T>
	void heapsort_des(Heap<T>& arr)
	{
		int backup_val = arr.heapsize;

		if(arr.heapsize < 1)
		{
			throw("Heap underflowed!!");
		}
		build_min_heap(arr);

		for(int i =arr.heapsize-1;i>=0;i--)
		{
			swap(arr[0],arr[i]);
			arr.heapsize--;
			min_heapify(arr,0);
		}

		arr.heapsize = backup_val;
	}


	// ch6q3 -> all above functions for minheap
	template <typename T>
	int heapMinimum(Heap<T>& arr)
	{
		build_min_heap(arr);
		return arr[0];
	}	

	template <typename T>
	T heapExtractMin(Heap<T>& arr)
	{
		if(arr.heapsize < 1)
		{
			throw("Heap underflowed!!");
		}
		build_min_heap(arr);
		T min = arr[0];
		arr[0] = arr[arr.heapsize-1];
		arr.heapsize--;
		min_heapify(arr,0);
		return min;
	}

	template <typename T>
	void heapDecreaseKey(Heap<T>& arr,int i , int k)
	{
		if(i >= arr.heapsize)
		{
			throw("index doesn't exists !!");
		}
		if(k > arr[i])
		{
			throw("Key is already larger can't decrease ..");
		}
		build_min_heap(arr);
		arr[i] = k;
		while(i>0 && arr[parent(i)] > arr[i])
		{
			std::swap(arr[parent(i)],arr[i]);
			i = parent(i);
		}
	}

	template <typename T>
	void minHeapInsert(Heap<T>&arr , int k)
	{
		arr.heapsize++;
		arr[arr.heapsize-1] = INT_MAX;
		heapDecreaseKey(arr,arr.heapsize-1,k);
	}


}	// namespace CH6

}	// namespace CLRS

#endif