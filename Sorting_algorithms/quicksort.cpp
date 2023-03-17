#include <bits/stdc++.h>
#include "qck_sort.h"

using namespace CLRS::CH7;
using namespace std;

int main(int argc, char const *argv[])
{
	QCK<int> arr = {23,1,56,1,45,7,43};
	arr.init(); // set left,right,arr.size into the QCK structure

	printarray(arr);
	quicksort(arr);
	printarray(arr);
	return 0;
}