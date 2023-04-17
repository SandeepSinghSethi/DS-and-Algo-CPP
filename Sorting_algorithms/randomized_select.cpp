#include <bits/stdc++.h>
#include "randomized_select.h"

using namespace CLRS::CH9;

int main(int argc, char const *argv[])
{
	RS<int> arr = {4,5,0,1,2,234};
	arr.init();

	printarray(arr);
	int k;
	std::cout << "Enter the number : ";
	std::cin >> k;
	if(k>arr.arrsize)
	{
		std::cout << "Larger value received than expected ..\n";
		return 101; 
	}
	randomized_select(arr,k); // second arg is the ith smallest number we have to find...
	printarray(arr);
	return 0;
}