#include <bits/stdc++.h>
#include "bucket_sort.h"

using namespace CLRS::CH8_3;

int main(int argc, char const *argv[])
{
	BKT<float> arr = {73,45,23,11,05,454,14,56,4};
	arr.init();

	printarray(arr);
	bucket_sort(arr);
	printarray(arr);
	return 0;
}