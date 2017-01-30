#include <iostream>
#include <cstdlib>
#include "Integer.h"

using std::cout;
using std::endl;



int main()
{
	Integer z1(0x7fffffffffffffff),z2(9007199254740991999),z3("123");

	cout << "z1:\t\t"; z1.print(); cout << endl;
	cout << "z2:\t\t"; z2.print(); cout << endl;
	cout << "z3:\t\t"; z3.print(); cout << endl;
	
	cout << "z3 = z1+z3:\t"; Integer_add(z1, z3, z3).print();cout << endl;
	cout << "z3 = z3+z2:\t"; Integer_add(z3, z2, z3).print(); cout << endl;

	return 0;
}
