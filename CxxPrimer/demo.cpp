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

	cout << Plus(-123, z4) << endl << -123 + z4 << endl;
	cout << Plus(z1, 5678902) << endl << z1 + 5678902 << endl;
	
	cout << Subtract(-123, z4) << endl << -123 - z4 << endl;
	cout << Subtract(z1, 5678902) << endl << z1 - 5678902 << endl;

	return 0;
}
