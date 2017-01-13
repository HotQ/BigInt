#include <cstdlib>
#include <math.h>
#include "Integer.h"

#define Log_10_2 0.3010299957
#define print2console

#include <iostream>


struct intString{
	int   digits;
	char *string;
};
static char maskH2L[8] = { (char)0x80,(char)0x40,(char)0x20,(char)0x10,(char)0x08,(char)0x04,(char)0x02,(char)0x01 };
//static char maskL2H[8] = { 0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80 };
static char product_256[9][4] = {
	{ '0','2','5','6' },
	{ '0','5','1','2' },
	{ '0','7','6','8' },
	{ '1','0','2','4' },
	{ '1','2','8','0' },
	{ '1','5','3','6' },
	{ '1','7','9','2' },
	{ '2','0','4','8' },
	{ '2','3','0','4' }
};
static char product_256_nooffset[10][4] = {
	{ 0,0,0,0 },
	{ 0,2,5,6 },
	{ 0,5,1,2 },
	{ 0,7,6,8 },
	{ 1,0,2,4 },
	{ 1,2,8,0 },
	{ 1,5,3,6 },
	{ 1,7,9,2 },
	{ 2,0,4,8 },
	{ 2,3,0,4 }
};

static intString* intString_init(int d);
static intString* intString_init(int d, int int_src);
static void intString_print(intString *intStr);
static void intString_destroy(intString* intStr);
static               int intString_add(intString *ax, intString *bx);
static inline intString* intString_add(intString *ax, unsigned int bx);
static inline intString* intString_add(intString *ax, unsigned char bx);
static        intString* intString_add(intString *ax, char bx);
static intString* intString_mul256(intString *ax);



static intString* intString_init(int d) {
	intString *p=(intString*)malloc(sizeof(intString));
	p->digits = d;
	p->string = (char*)malloc(d);
	for (int i = 0; i < d; i++) {
		(p->string)[i] = 0;
	}
	return p;
}
static intString* intString_init(int d, int int_src) {
	intString *result = intString_init(d);
	int int_src_digits= (int)ceil(log10((double)(int_src+1)));
	for (int i = 0; i < int_src_digits; i++) {
		(result->string)[i] = int_src % 10;
		int_src /= 10;
	}
	return result;
}
static void intString_print(intString *intStr) {
	for (int i = (intStr->digits) - 1; i >= 0; i--) {
		std::cout << (char)((intStr->string)[i]+'0');
	}
}
static void intString_destroy(intString* intStr) {
	free(intStr->string);
	free(intStr);
}
/// <returns> useless method </returns>
static               int intString_add(intString *ax, intString *bx) {
	int CF = 0, temp;
	for (int i = 0; i < ax->digits; i++) {
		temp = (ax->string)[i] + (bx->string)[i] + CF;
		CF = temp / 10;
		(ax->string)[i] = temp % 10;
	}
	return 0;
}
static inline intString* intString_add(intString *ax, unsigned int bx) {
	intString *result = intString_init(ax->digits);
	int CF = 0, temp;
	for (int i = 0; i < ax->digits; i++) {
		temp = (ax->string)[i] + bx % 10 + CF;
		CF = temp / 10;
		bx /= 10;
		(result->string)[i] = temp % 10;
	}
	return result;
}
static inline intString* intString_add(intString *ax, unsigned char bx) {
	return intString_add(ax, (unsigned int)bx);
}
static        intString* intString_add(intString *ax, char bx) {
	return intString_add(ax, (unsigned char)bx);
}
static intString* intString_mul256(intString *ax) {
	intString *result = intString_init(ax->digits);
	char CF = 0, temp = 0;

	for (int i = 0; i < ax->digits; i++) {
		CF = 0;
		temp = 0;
		char *product = product_256_nooffset[(int)(ax->string)[i]];
		for (int j = 0; j < 4; j++) {
			temp = (result->string)[i + j] + product[3-j] + CF;
			CF = temp / 10;
			(result->string)[i + j] = temp % 10;
		}
	}
	return result;
}
/// <returns> ax = ax * 256 + bx </returns>
static void intString_mul256_add(intString *ax, char bx) {

}

Integer::Integer() {
	this->init = 0;
}
Integer::Integer(int int_src) {
	int bytes = (int)sizeof(int);
	this->init = 1;
	this->data = (char*)malloc(bytes);

	if (int_src == 0)
		this->zero = 1;
	else {
		this->zero = 0;
		this->byte = bytes;

		if (int_src > 0)
			this->sign = 1; 
		else { 
			this->sign = 0;
			int_src = -int_src;
		}
	}
	for (int i = 0; i < bytes; i++) {
		data[i] = int_src % 0x100;
		int_src = int_src >> 8;
	}
}

void Integer::print() {
	char q = (char)0x84;
	int digits = 0;
	for (int i = this->byte - 1; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
			if ((this->data[i]) & maskH2L[j]) {
				digits = 8 * i + 8 - j;
				break;
			}
		}
		if (digits)
			break;
	}

	/*begin to destroy the world*/
	
	intString *temp_intString = intString_init((int)ceil(Log_10_2*(double)32), 123),
		*p1 = intString_init((int)ceil(Log_10_2*(double)digits), 3456789),
		*p2 = intString_init((int)ceil(Log_10_2*(double)digits), 9879);
	
	intString_print(intString_mul256(p2));
	/*drop the mic*/
}