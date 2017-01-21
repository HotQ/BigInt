#include <iostream>
#include <cstdlib>
#include "Integer.h"

using std::cout;
using std::endl;



int main()
{
	Integer z1("0xffffffff"),z2("10000000000"),z3("123");

	z1.print();                      cout << endl;	
	z2.print();                      cout << endl;
	Integer_add(z1, z2, z3).print(); cout << endl;
	Integer_add(z3, z2, z3).print(); cout << endl;

	return 0;
}
