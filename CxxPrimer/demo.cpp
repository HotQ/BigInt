#include <iostream>
#include "Integer.h"



int main()
{

	Integer integer(-0x1234567F);
	//integer.byte = 15;
	int temp=3;

	//for (int i = 0; i < (int)sizeof(int); i++)std::cout << (int)integer.data[i] << std::endl;
	
	integer.print();
	
	
	
	
	std::cin >> temp;
	return 0;
}