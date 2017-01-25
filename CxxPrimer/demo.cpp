#include <iostream>
#include <cstdlib>
#include "Integer.h"

using std::cout;
using std::endl;



int main()
{
	Integer z1("0xffffffff"),z2("4294967306"),z3("123");

	cout << LessThan(z1)(z1) << "  " << LessThan(z1)(z2) << "  " << LessThan(z1)(z3) << endl;
	cout << LessEqualThan(z1)(z1) << "  " << LessEqualThan(z1)(z2) << "  " << LessEqualThan(z1)(z3) << endl;

	return 0;
}
