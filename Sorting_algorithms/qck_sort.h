#ifndef qck_sort_h
#define qck_sort_h

#include <bits/stdc++.h>

using std::vector;

template <typename T>
class QCK: private vector<T>
{
public:
	using vector<T>::size;
	using vector<T>::operator[];
	using vector<T>::vector;

	int left ,right;
	int arraysize;
	void init();
};

template <typename T>
void QCK<T>::init()
{
	arraysize = this->size();
	left= 0;
	right = arraysize-1;
}



namespace CLRS{

namespace CH7{

	template <typename T>
	void printarray(QCK<T>& arr)
	{
		for(int i =0 ;i<arr.arraysize;i++)
		{
			std::cout << arr[i] << " ";
		}
		std::cout << "\n";
	}

	template <typename T>
	T partition(QCK<T>& arr,int l , int r)
	{
		T x = arr[r];
		int i = l-1;
		for(int j = l;j<=r-1;j++)
		{
			if(arr[j] <= x)
			{
				i++;
				std::swap(arr[j],arr[i]);
			}
		}
		std::swap(arr[i+1],arr[r]);
		return i+1;
	}

	template <typename T>
	void qck(QCK<T>& arr,int left,int right)
	{
		if(left<right)
		{
			int p = partition(arr,left,right);
			qck(arr,left,p-1);
			qck(arr,p+1,right);
		}	
	}

	template <typename T>
	void quicksort(QCK<T>& arr)
	{
		qck(arr,arr.left,arr.right);
	}

} // namespace CH7
} // namespace CLRS
#endif