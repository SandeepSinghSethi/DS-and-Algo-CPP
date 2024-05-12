#include "llist.h"

int main(int argc, char const *argv[])
{
	LinkedL<int> list ;
	list.operate() ;	

	cout <<endl;

	DBList<int> dblist;
	dblist.operate();
	return 0;
}