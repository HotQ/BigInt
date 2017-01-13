#include <iostream>
#include "Integer.h"



int main()
{

	Integer integer(-0x1234567F);
	int temp;
	integer.print();
	std::cin >> temp;
	return 0;
}