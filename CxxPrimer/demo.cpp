#include <iostream>
#include <cstdlib>
#include "Integer.h"

using std::cout;
using std::cin;
using std::endl;



int main()
{
	Integer z1(-0x7fffffffffffffff), z3("-123");
	Integer z2;
	
	cout << Plus(z1, z3) << endl;
	z1 = z2;
	return 0;
}
