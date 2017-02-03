#include <iostream>
#include <cstdlib>
#include "Integer.h"

using std::cout;
using std::cin;
using std::endl;



int main()
{


	int b = 0x01020304;
	Integer z1("0x01020304");

	cout << endl
		<< Integer_compare_abs(z1, 0x01020303) << endl
		<< Integer_compare_abs(z1, 0x01020304) << endl
		<< Integer_compare_abs(z1, 0x01020305) << endl;

	return 0;
}
