#include <iostream>
#include <cstdlib>
#include "Integer.h"

using std::cout;
using std::cin;
using std::endl;



int main()
{


	Integer z("0xffffff03");
	cout << endl;

	for (int i = 0; i < 30; i++)
		cout << z << "   " << i << "\t" << z - i << "\t" << i - z << endl;

	return 0;
}
