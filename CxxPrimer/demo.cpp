#include <iostream>
#include <cstdlib>
#include "Integer.h"

using std::cout;
using std::endl;



int main()
{
	Integer z1("0xffffffff"),z2("4294967306"),z3("123");

	Integer_sub(z2, z3, z3).print(); cout << endl;
	cout << Greater(z1, z3) << endl;
	
	return 0;
}
