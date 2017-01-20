#include <iostream>
#include <cstdlib>
#include "Integer.h"

using std::cout;
using std::endl;



int main()
{
	Integer z11("9");
	Integer z12("-9");
	Integer z21("-10");
	Integer z3("999999");
	
	z11.print(); cout << endl;
	z12.print(); cout << endl;
	(z12.reset()).print(); cout << endl;
	z21.print(); cout << endl;
	z3.print();  cout << endl;
	
	return 0;
}
