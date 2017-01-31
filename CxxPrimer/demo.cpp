#include <iostream>
#include <cstdlib>
#include "Integer.h"

using std::cout;
using std::cin;
using std::endl;



int main()
{
	Integer z1(-0x7fffffffffffffff), z3("-123");
	Integer z2( 0x7fffffffffffffff), z4(  123 );
	
	cout << "z1:\t\t" << z1 << endl;
	cout << "z2:\t\t" << z2 << endl;
	cout << "z3:\t\t" << z3 << endl;
	cout << "z4:\t\t" << z4 << endl << endl;

	cout << "z1+z3=\t\t" << Plus(z1, z3) << endl;
	cout << "z2+z4=\t\t" << Plus(z2, z4) << endl;
	cout << "z1+z2=\t\t" << Plus(z1, z2) << endl;
	cout << "z3+z4=\t\t" << Plus(z3, z4) << endl;
	cout << "z1+z4=\t\t" << Plus(z1, z4) << endl;
	cout << "z2+z3=\t\t" << Plus(z2, z3) << endl;

	return 0;
}
