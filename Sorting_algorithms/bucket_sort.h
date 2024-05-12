#ifndef bucket_sort_h
#define bucket_sort_h

#include <bits/stdc++.h>
#include <cmath>
using namespace std;
using std::vector;

template <typename T>
class BKT: private vector<T>
{
public:
	using vector<T>::operator[];
	using vector<T>::size;
	using vector<T>::vector;

	int arrsize,left,right;
	void init();
};

template <typename T>
void BKT<T>::init()
{
	arrsize = this->size();
	left =0;
	right = arrsize-1;
}

namespace CLRS
{
namespace CH8_3
{

	template <typename T>
	void printarray(BKT<T>& arr)
	{
		for(int i =0;i<arr.arrsize;i++)
		{
			std::cout << arr[i] << " ";
		}
		std::cout << "\n";
	}

	template <typename T>
	void zero(BKT<T>& arr)
	{
		for(int i = 0;i<arr.arrsize;i++)
		{
			arr[i] = 0;
		}
	}

	template <typename T>
	void int_to_bkt(BKT<T>& arr,BKT<T>& num_pow)
	{
		for(int i= 0;i<arr.arrsize;i++)
		{
			int pv = int(log10(arr[i]))+1;
			arr[i] = arr[i]/pow(10,pv);
			num_pow[i] = pv;
		}
	}

	template <typename T>
	void bkt_to_int(BKT<T>& arr,BKT<T>& num_pow)
	{
		for(int i=0;i<arr.arrsize ;i++)
		{
			T num = arr[i];
			std::string num_str = std::to_string(num);
			size_t numpos = num_str.find(".");

			if(numpos != std::string::npos)
			{
				std::string dig_after_dec = num_str.substr(numpos+1,num_pow[i]);
				arr[i] = stoi(dig_after_dec);
			}
		}
	}



	template <typename T>
	void bkt_sort(BKT<T>& arr)
	{
		// create a pointer to an 2d array which is our bucket
		std::vector<float> *b = new std::vector<float>[arr.arrsize];

		// push back values of arr into different buckets such that bi=n*arr[i] into b[bi].push_back(arr[i])
		for(int i = 0;i<arr.arrsize;i++)
		{
			int bi = arr.arrsize * arr[i] ;
			b[bi].push_back(arr[i]);
		}

		// now sort individually each and every bucket
		for(int i= 0;i<arr.arrsize;i++)
		{
			std::sort(b[i].begin(),b[i].end()); // using std::sort or introsort algorithm
		}

		// now concat the entire b into original array
		int index = 0;
		for(int i= 0;i<arr.arrsize;i++)
			for(int j = 0;j<b[i].size();j++)
				arr[index++] = b[i][j];


		delete[] b;
	}

	template <typename T>
	void bucket_sort(BKT<T>& arr)
	{
		BKT<T> num_pow = arr;
		zero(num_pow);
		int isint = std::is_same<T,int>::value; // to check whether the given array is of type(int) or not , if yes then convert all the values of int array to float where arr[i->n] are values less than 1.

		if(!isint)
			int_to_bkt(arr,num_pow);

		bkt_sort(arr);
		
		// if(!isint)
		// 	bkt_to_int(arr,num_pow);
	}

}	// namespace CH8_3
}	// namespace CLRS

#endif