#ifndef radix_sort_h
#define radix_sort_h

#include <bits/stdc++.h>
#include <cmath>

using std::vector;

template <typename T>
class RDX: private vector<T>
{
	public:
		using vector<T>::operator[];
		using vector<T>::vector;
		using vector<T>::size;

	int left,right,arrsize;
	void init();
	void zero();
};

template <typename T>
void RDX<T>::init()
{
	arrsize = this->size();
	left =0;
	right = arrsize-1;
}

template <typename T>
void zero(RDX<T>& arr)
{
	for(int i = 0;i<arr.arrsize;i++)
		arr[i] = 0;
}

namespace CLRS
{
namespace CH8_2
{

	template <typename T>
	void printarray(RDX<T>& arr)
	{
		for(int i = 0;i<arr.arrsize;i++){
			std::cout << arr[i] <<" ";
		}
		std::cout << "\n";
	}

	template <typename T>
	void max_heapify(RDX<T>& arr,int i )
	{
		int largest = i;
		int left = (2*i)+1;
		int right = (2*i)+2;

		if(left < arr.arrsize && arr[left] > arr[largest])
			largest = left;
		if(right < arr.arrsize && arr[right] > arr[largest])
			largest=right;

		if(largest!=i)
		{
			std::swap(arr[i],arr[largest]);
			max_heapify(arr,largest);
		}
	}

	template <typename T>
	T build_max_heap(RDX<T>& arr)
	{
		for(int i =arr.arrsize/2;i>=0;i--)
			max_heapify(arr,i);

		T data = arr[0];
		return data;
	}

	template <typename T>
	T getmax(RDX<T>& arr)
	{
		RDX<T> test = arr;
		return build_max_heap(test);
	}

	template <typename T>
	void counting_sort(RDX<T>& arr,RDX<T>& B , RDX<T>& digits , T d)
	{
		RDX<T> C = arr;
		C.arrsize = d+1;
		zero(C);

		for(int i = 0;i<arr.arrsize;i++)
			C[digits[i]]++;

		for(int j = 1;j<=d;j++)
			C[j] += C[j-1];

		for(int i = arr.arrsize-1;i>=0;i--)
		{
			B[C[digits[i]]-1] = arr[i];
			C[digits[i]]--;
		}
	}

	template <typename T>
	int getNumPlaces(RDX<T>& arr)
	{
		RDX<T> test = arr;

		for(int i =arr.arrsize/2;i>=0;i--)
			max_heapify(test,i);

		int max= test[0];
		return ((int)log10(max))+1;
	}

	template <typename T>
	void radix_sort(RDX<T>& arr)
	{
		int m = getNumPlaces(arr);	// to set the value m upto the num places in the array , for 100k m=6 ,etc,etc, ....

		for(int i = 1;i<=m;i++)
		{
			RDX<T> B = arr;
			RDX<T> digits = arr;
			zero(B);	// zeroing out the array
			zero(digits);	// zeroing out the array

			for(int j = 0;j<arr.arrsize;j++)
			{
				digits[j] = (arr[j] / (T)pow(10 , (i-1))) % 10;
			}
			T d = getmax(digits); // to get the max value in the array digits so that , we can get d for counting sort , as counting sort operates on the array of size d <-(largest number in the array)
			counting_sort(arr,B,digits,d);	// performing counting sort on an array size n <=10 , because in a place value of a number there can only be 10 numbers (0->9)
			arr = B;

			// time complexity
			// counting sort = O(n+k) , if k=n=>O(n) 
			// radix sort = O(m(counting_sort))
			// 				O(m(n+k)) 
			// where m is the column number / place value of the largest number and n is the running time of counting sort and k is the size of C on which operations will be performed
		}
	}

}	//namespace CH8_2
}	// namespace CLRS


#endif