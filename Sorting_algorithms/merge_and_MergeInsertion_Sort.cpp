#include<bits/stdc++.h>

template <typename T>
void printarray(T *arr,int n)
{
	for(int i  =0;i<n;i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << '\n';
}

template <typename T>
void insertion_sort(T *arr,int low , int high)
{
	for(int i = low+1;i<high;i++)
	{
		int j = i-1;
		while(j>=low && arr[j] > arr[i])
		{
			std::swap(arr[j--],arr[i--]);
		}
	}
}

template <typename T>
void merge(T *arr,int l,int m, int r)
{
	int left_size = (m-l)+1;
	int right_size = r-m;

	int *left = new int[left_size];
	int *right = new int[right_size];

	for(int i = 0;i<left_size;i++){ 
		left[i] = arr[i+l];
	}

	for(int j = 0;j<right_size;j++)
	{	
		 right[j] = arr[m+1+j];
	}

	int i = 0, j = 0, k =l;

	while(i<left_size && j < right_size)
	{
		if(left[i] <= right[j])
		{
			arr[k++] = left[i++];
		}
		else
		{
			arr[k++] = right[j++];
		}
	}

	while(i<left_size)
	{
		arr[k++] = left[i++];
	}


	while(j<right_size)
	{
		arr[k++] = right[j++];
	}

	delete[] left;
	delete[] right;
}

template <typename T>
void mergesort(T *arr,int low , int high)
{
	if(low<high)
	{
		int mid = (low+high)/2;
		mergesort(arr,low,mid);
		mergesort(arr,mid+1,high);
		merge(arr,low,mid,high);
		// insertion_sort(arr,low,high);
	}
}

template <typename T>
void stress_testing(T *heap , int n)
{
	std::vector<int> arr;
	srand(time(0));
	for(int i= 0;i<n;i++)
	{
		arr.push_back(rand() + 1);
	}
	// printarray(arr.data(),arr.size());
	mergesort(arr.data(),0,arr.size()-1);
	// printarray(arr.data(),arr.size());
}

int main(int argc, char const *argv[])
{
	int arr[] = {4,254,1,34,6,3,7,7};
	int n =sizeof(arr)/sizeof(int);

	printarray(arr,n);
	mergesort(arr,0,n-1);
	printarray(arr,n);

	if(argc > 1)
	{
		std::cout << "Doing stress testing on " << argv[1] << " input size array" << "\n";
		stress_testing(arr,atoi(argv[1]));
	}
	return 0;
}