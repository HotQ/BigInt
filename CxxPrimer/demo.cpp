#include <iostream>
#include <cstdlib>
#include "Integer.h"

using std::cout;
using std::endl;



int main()
{
	Integer z1(0x7fffffffffffffff),z2(9007199254740991999),z3("123");
	
	z1 = z2;
	z2 = 1234567890987654321;

	cout << "z1:\t\t" << z1 << endl;
	cout << "z2:\t\t" << z2 << endl;
	cout << "z3:\t\t" << z3 << endl;
	
	cout << "z3 = z1+z3:\t" << Integer_add(z1, z3, z3) << endl;
	cout << "z3 = z3+z2:\t" << Integer_add(z3, z2, z3) << endl;

	return 0;
}
