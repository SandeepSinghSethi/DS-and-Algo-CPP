#include <bits/stdc++.h>
#include "ch_8.h"

using namespace CLRS::CH8;

int main(int argc, char const *argv[])
{
	CT<int> arr = {6, 0, 2, 0, 1, 3, 4, 6, 1, 3, 2};
	arr.init();

	printarray(arr);
	counting_sort(arr);
	printarray(arr);
	return 0;
}