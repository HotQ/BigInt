#include <iostream>
#include <cstdlib>
#include "Integer.h"




int main()
{
	Integer z1("-0");                             z1.print(); std::cout << std::endl;
	Integer z2("0");                              z1.print(); std::cout << std::endl;
	Integer o1("-01");                            o1.print(); std::cout << std::endl;
	Integer o2("-0100000345456767071265432345");  o2.print(); std::cout << std::endl;
	Integer o3("07610230751327766076905725764");  o3.print(); std::cout << std::endl;
	Integer h1("0x9b0c89d90a0989f0e8");           h1.print(); std::cout << std::endl;
	Integer h2("-0X9088ff7a09e70fe8a979b089");    h2.print(); std::cout << std::endl;
	Integer d1("-65497952");                      d1.print(); std::cout << std::endl;
	Integer d2("978943897548940");                d2.print(); std::cout << std::endl;
	Integer h3("0Xfff987900800891ca98a10daeda91de8ae90debd0ae1fccb98ef902981d98908423599c8d1b264232f2d91eb8d9f");
	Integer d3("-192370987580375897138476073941471307961010978667019908019780970947602874386979027810870110191"); 
	h3.print(); std::cout << std::endl;
	d3.print(); std::cout << std::endl;

	int temp;
	std::cin >> temp;
	return 0;
}