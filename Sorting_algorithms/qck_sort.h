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
			if(arr[j] <=	 x)
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

	int random_num1(int l , int r)
	{
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937_64 generator(seed);
		std::uniform_int_distribution<int> distribution(l,r);
		return distribution(generator);
	}

	int random_num2(int l , int r)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(l,r);
		return dis(gen);
	}

	template <typename T>
	int randomized_partition(QCK<T>& arr, int  l , int r)
	{
		int i = random_num2(l,r);
		std::swap(arr[r],arr[i]);
		return partition(arr,l,r);
	}

	template <typename T>
	void rand_qck(QCK<T>& arr,int l , int r)
	{
		if(l<r)
		{
			int p = randomized_partition(arr,l,r);
			rand_qck(arr,l,p-1);
			rand_qck(arr,p+1,r);
		}
	}

	template <typename T>
	void randomized_quicksort(QCK<T>&arr)
	{
		rand_qck(arr,arr.left,arr.right);		
	}

	template <typename T>
	void quicksort(QCK<T>& arr)
	{
		qck(arr,arr.left,arr.right);
	}

	template <typename T>
	int hoare_partition(QCK<T>& arr,int left,int right)
	{
		int pivot = arr[left],i = left+1,j = right;

		do
		{
			while(arr[i] <= pivot)
			{
				i++;
			}
			while(arr[j] > pivot)
			{
				j--;
			}
			if(i<j)
			{
				std::swap(arr[i],arr[j]);
			}

		}while(i<j);

		std::swap(arr[left],arr[j]);
		return j;

	}

	template <typename T>
	void hp_qck(QCK<T>& arr,int left,int right)
	{
		if(left<right)
		{
			int p = hoare_partition(arr,left,right);
			hp_qck(arr,left,p-1);
			hp_qck(arr,p+1,right);
		}
	}

	template <typename T>
	void hoare_partition_quicksort(QCK<T>& arr)
	{
		hp_qck(arr,arr.left,arr.right);
	}

} // namespace CH7
} // namespace CLRS
#endif