#include <iostream>
#include <cstdlib>
#include "Integer.h"

using std::cout;
using std::cin;
using std::endl;



int main()
{


	Integer z("0x7fffff03"), l("0x7fffff02");
	cout << endl;

	cout << (z > l) << "\t" << GreaterThan(l)(z) << endl;
	cout << (z <= 1) << "\t" << (0x7fffffff > z) << endl;

	return 0;
}
