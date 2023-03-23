#include<bits/stdc++.h>
#include "ch7_prob.h"

using namespace CLRS::CH7_P;

int main(int argc, char const *argv[])
{
	ARR<int> arr1 = {13, 19, 9, 5, 12, 8, 7, 4, 11, 2, 6, 21};
	arr1.init();

	printarray(arr1);
	stooge_sort(arr1);
	printarray(arr1);
	return 0;
}