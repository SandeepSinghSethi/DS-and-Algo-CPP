#include <bits/stdc++.h>
#include "radix_sort.h"

using namespace CLRS::CH8_2;

int main(int argc, char const *argv[])
{
	RDX<int> arr = {329,441,254,845,874,321,554,343,234664,234,567,234,767,34545};
	arr.init();

	printarray(arr);
	radix_sort(arr);
	printarray(arr);

	return 0;
}