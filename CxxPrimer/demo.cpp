#include <iostream>
#include <cstdlib>
#include "Integer.h"

using std::cout;
using std::cin;
using std::endl;



int main()
{
	/* destructor was executed 16 times. */

	Integer z(0);
	cout << (z = z + 1 + 2 + 3 + 4 + 5) << endl;

	return 0;
}
