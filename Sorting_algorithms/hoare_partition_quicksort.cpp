#include<bits/stdc++.h>
#include "qck_sort.h"

using namespace CLRS::CH7;

int main(int argc, char const *argv[])
{
	QCK<int> arr = {13, 19, 9, 5, 12, 8, 7, 4, 11, 2, 6, 21};
	arr.init();

	printarray(arr);
	hoare_partition_quicksort(arr);
	printarray(arr);
	return 0;
}