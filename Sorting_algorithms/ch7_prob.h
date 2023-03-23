#ifndef ch7_prob_h
#define ch7_prob_h

#include <bits/stdc++.h>

using std::vector;

template <typename T>
class ARR : private vector<T>
{
	public :
		using vector<T>::size;
		using vector<T>::operator[];
		using vector<T>::vector;

	int arraysize;
	int left,right;
	void init();
};

template <typename T>
void ARR<T>::init()
{
	arraysize = this->size();
	left= 0;
	right = arraysize- 1;
}

#include <cmath>

namespace CLRS
{
namespace CH7_P
{
	template <typename T>
	void printarray(ARR<T>& arr)
	{
		for(int i = 0;i<arr.arraysize;i++)
		{
			std::cout << arr[i] << " ";
		}
		std::cout << "\n";
	}

	template <typename T>
	void st_sort(ARR<T>& arr,int left,int right)
	{
		if(left>=right)
			return;
		if(arr[left] > arr[right])
		{
			std::swap(arr[left],arr[right]);
		}

		if(2 < right-left+1)
		{
			int k = (right-left+1)/3;
			st_sort(arr,left,right-k);
			st_sort(arr,left+k,right);
			st_sort(arr,left,right-k);
		}
	}

	template <typename T>
	void stooge_sort(ARR<T>& arr)
	{
		st_sort(arr,arr.left,arr.right);
	}
}
}

#endif