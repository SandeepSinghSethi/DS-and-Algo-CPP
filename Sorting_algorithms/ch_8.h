#ifndef ch_8_h
#define ch_8_h

#include<bits/stdc++.h>

using std::vector;

template <typename T>
class CT: private vector<T>{
	public:
		using vector<T>::operator[];
		using vector<T>::size;
		using vector<T>::vector;
		using vector<T>::clear;

		int arrsize;
		int left,right;
		void init();
		void cleanup();
};

template <typename T>
void CT<T>::init()
{
	arrsize = this->size();
	left = 0;
	right = arrsize-1;
}

template <typename T>
void CT<T>::cleanup()
{
	this->clear();
}

namespace CLRS{

namespace CH8{

	template <typename T>
	void printarray(CT<T>& arr)
	{
		for(int i = 0;i<arr.arrsize;i++)
		{
			std::cout << arr[i] << " ";
		}
		std::cout << "\n";
	}

	template <typename T>
	void max_heapify(CT<T>& arr,int i)
	{
		int largest = i;
		int left = (2*i)+1;
		int right = (2*i)+2;

		if(left<arr.arrsize && arr[left] > arr[largest])
			largest = left;
		if(right<arr.arrsize && arr[right] > arr[largest])
			largest = right;

		if(largest!=i)
		{
			std::swap(arr[i],arr[largest]);
			max_heapify(arr,largest);
		}
	}

	template <typename T>
	T build_max_heap(CT<T>& arr)
	{
		CT<int> test = arr;

		for(int i=(test.arrsize/2);i>=0;i--)
		{
			max_heapify(test,i);
		}
		T data = test[0];
		// test.cleanup();
		return data;		
	}

	template <typename T>
	T getmax(CT<T>& arr)
	{
		return build_max_heap(arr); 
	}

	template <typename T>
	void ct_sort(CT<T>& arr,CT<T>& B,CT<T>& C,T max)
	{
		for(int i= 0;i<=max;i++)
			B[i] = 0;

		
		// setting array to all zero till size max
		for(int j = 0;j<arr.arrsize;j++) 
			B[arr[j]]++;

		// setting the array in a way which help to maintain the stability/order of the values in the array in the resultant array
		for(int k = 1;k<=max;k++)	
			B[k] += B[k-1];

		// setting the new array with values of the original array with the use of array B into C
		for(int l = arr.arrsize-1;l>=0;l--)
		{
			C[B[arr[l]] -1 ] = arr[l];
			B[arr[l]]--;
		}

		// copying results into the original array
		for(int m = 0;m<arr.arrsize;m++)
		{
			arr[m] = C[m];
		}
	}

	template <typename T>
	void counting_sort(CT<T>& arr)
	{
		T max =getmax(arr);
		CT<T> B(max+1,0);
		CT<T> C(arr.arrsize);
		
		ct_sort(arr,B,C,max);
	}

}	// namespace CH8
}	// namespace CLRS

#endif