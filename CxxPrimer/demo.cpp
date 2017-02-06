#include <iostream>
#include <cstdlib>
#include "Integer.h"

using std::cout;
using std::cin;
using std::endl;



int main()
{

	Integer z("0x707fffff03"), l("0xff70207fffff02");
	cout << "34740628695596179551592446726\n" << Times(z, l) << endl;

	return 0;
}
