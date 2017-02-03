#include <iostream>
#include <cstdlib>
#include "Integer.h"

using std::cout;
using std::cin;
using std::endl;



int main()
{


	int b = 0x01020304;
	Integer z(123), z1(1), z2(2), z3(3);
	cout << "---------------\n\n";
	cout << endl << z + z1 + z2 + z3 << endl;
	cout << "---------------\n\n";
	cout << endl << z - z1 - z2 - z3 << endl;
	cout << "---------------\n\n";

	return 0;
}
