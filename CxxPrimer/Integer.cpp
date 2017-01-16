#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include "Integer.h"

#define Log_10_2 0.3010299957
#define Log_2_10 3.3219280959

struct intString {
	int   digits;
	unsigned char *string;
};
static unsigned char maskH2L[8] = { 0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01 };
static unsigned char product_256_nooffset[10][4] = {
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
static intString* intString_init(int d, unsigned char chr_src);
static void intString_print(intString *intStr);
static void intString_destroy(intString* intStr);
static intString* intString_add(intString *ax, intString *bx);
static intString* intString_add(intString *ax, unsigned char bx);
static intString* intString_mul256(intString **ax);

static inline unsigned char chr_2_0x(char chr);
static inline int divide256(char *dividend_offset);
static inline void divident_sub_256(char *dividend_offset, int quotient);


static intString* intString_init(int d) {
	intString *p = (intString*)malloc(sizeof(intString));
	p->digits = d;
	p->string = (unsigned char*)malloc(d);
	for (int i = 0; i < d; i++) {
		(p->string)[i] = 0;
	}
	return p;
}
static intString* intString_init(int d, int int_src) {
	intString *result = intString_init(d);
	int int_src_digits = (int)ceil(log10((double)(int_src + 1)));
	for (int i = 0; i < int_src_digits; i++) {
		(result->string)[i] = int_src % 10;
		int_src /= 10;
	}
	return result;
}
static intString* intString_init(int d, unsigned char chr_src) {
	intString *result = intString_init(d);
	for (int i = 0; i < 3; i++) {
		(result->string)[i] = chr_src % 10;
		chr_src /= 10;
	}
	return result;
}
static void intString_print(intString *intStr) {
	int i = (intStr->digits) - 1;
	while ((intStr->string)[i] == 0)i--;
	for (; i >= 0; i--) {
		std::cout << (char)((intStr->string)[i] + '0');
	}
}
static void intString_destroy(intString* intStr) {
	free((unsigned char *)(intStr->string));
	free(intStr);
}
/// <returns> ax += bx </returns>
static intString* intString_add(intString *ax, intString *bx) {
	int CF = 0, temp;
	for (int i = 0; i < ax->digits; i++) {
		temp = (ax->string)[i] + (bx->string)[i] + CF;
		CF = temp / 10;
		(ax->string)[i] = temp % 10;
	}
	return ax;
}
static intString* intString_add(intString *ax, unsigned char bx) {
	int CF = 0, temp;
	for (int i = 0; i < ax->digits; i++) {
		temp = (ax->string)[i] + bx % 10 + CF;
		CF = temp / 10;
		bx /= 10;
		(ax->string)[i] = temp % 10;
	}
	return ax;
}
/// <returns> *ax += 256 </returns>
static intString* intString_mul256(intString **ax) {
	intString *result = intString_init((*ax)->digits);
	unsigned char CF = 0, temp = 0;

	for (int i = 0; i < (*ax)->digits; i++) {
		CF = 0;
		temp = 0;
		unsigned char *product = product_256_nooffset[(int)((*ax)->string)[i]];
		for (int j = 0; j < (4 < ((*ax)->digits - i) ? 4 : (*ax)->digits - i); j++) {
			temp = (result->string)[i + j] + product[3 - j] + CF;
			CF = temp / 10;
			(result->string)[i + j] = temp % 10;
		}
	}
	intString_destroy(*ax);
	(*ax) = result;
	return (*ax);
}

static inline unsigned char chr_2_0x(char chr) {
	if (chr >= 'a' && chr <= 'f') return (unsigned char)(chr - 'a' + 10);
	if (chr >= '0' && chr <= '9') return (unsigned char)(chr - '0');
	return -1;
}
static inline int divide256(char *dividend_offset) {
	switch (dividend_offset[0])
	{
	case 0:
		switch (dividend_offset[1]) {
		case 0:
		case 1:
			return 0;
		case 2:
			if (dividend_offset[2] < 5 || (dividend_offset[2] == 5 && dividend_offset[3] < 6)) 
				return 0;
		case 3:
		case 4:
			divident_sub_256(dividend_offset, 1);
			return 1;
		case 5://
			if (dividend_offset[2] < 1 || (dividend_offset[2] == 1 && dividend_offset[3] < 2)) {
				divident_sub_256(dividend_offset, 1);
				return 1;
			}
		case 6:
			divident_sub_256(dividend_offset, 2);
			return 2;
		case 7:
			if (dividend_offset[2] < 6 || (dividend_offset[2] == 6 && dividend_offset[3] < 8)) {
				divident_sub_256(dividend_offset, 2);
				return 2;
			}
		case 8:
		case 9:
			divident_sub_256(dividend_offset, 3);
			return 3;
		}
	case 1:
		switch (dividend_offset[1]) {
		case 0:
			if (dividend_offset[2] < 2 || (dividend_offset[2] == 2 && dividend_offset[3] < 4)) {
				divident_sub_256(dividend_offset, 3);
				return 3;
			}
		case 1:
			divident_sub_256(dividend_offset, 4);
			return 4;
		case 2:
			if (dividend_offset[2] < 8) {
				divident_sub_256(dividend_offset, 4);
				return 4;
			}
		case 3:
		case 4:
			divident_sub_256(dividend_offset, 5);
			return 5;
		case 5:
			if (dividend_offset[2] < 3 || (dividend_offset[2] == 3 && dividend_offset[3] < 6)) {
				divident_sub_256(dividend_offset, 5);
				return 5;
			}
		case 6:
			divident_sub_256(dividend_offset, 6);
			return 6;
		case 7:
			if (dividend_offset[2] < 9 || (dividend_offset[2] == 9 && dividend_offset[3] < 2)) {
				divident_sub_256(dividend_offset, 6);
				return 6;
			}
		case 8:
		case 9:
			divident_sub_256(dividend_offset, 7);
			return 7;
		}
	case 2:
		switch (dividend_offset[1])
		{
		case 0:
			if (dividend_offset[2] < 4 || (dividend_offset[2] == 4 && dividend_offset[3] < 8)) {
				divident_sub_256(dividend_offset, 7);
				return 7;
			}
		case 1:
		case 2:
			divident_sub_256(dividend_offset, 8);
			return 8;
		case 3:
			if (dividend_offset[2] < 0 || (dividend_offset[2] == 0 && dividend_offset[3] < 4)) {
				divident_sub_256(dividend_offset, 8);
				return 8;
			}
		case 4:
		case 5:
			divident_sub_256(dividend_offset, 9);
			return 9;
		}
	}
	return -1;
}
static inline void divident_sub_256(char *dividend_offset, int quotient) {
	int CF = 0, temp;
	for (int i = 3; i >= 0; i--) {
		temp = dividend_offset[i] - CF - (int)product_256_nooffset[quotient][i];
		if (temp >= 0) {
			dividend_offset[i] = (char)temp;
			CF = 0;
		}
		else {
			dividend_offset[i] = (char)(10 + temp);
			CF = 1;
		}
	}

}
static inline int zero_number(char *dividend) {
	int i = 0;
	while (dividend[i] == 0)i++;
	return i;
}

Integer::Integer() {
	this->init = 0;
	this->data = NULL;
}
Integer::Integer(int int_src) {
	int bytes = (int)sizeof(int);
	this->init = 1;
	this->data = (unsigned char*)malloc(bytes);

	if (int_src == 0) {
		this->zero = 1;
		this->data = NULL;
	}
	else {
		this->zero = 0;
		this->byte = bytes;

		if (int_src > 0)
			this->sign = 0;
		else {
			this->sign = 1;
			int_src = -int_src;
		}
		for (int i = 0; i < bytes; i++) {
			data[i] = int_src % 0x100;
			int_src = int_src >> 8;
		}
	}

}
Integer::Integer(const char *cchr_src)
{
	this->init = 0;
	std::string str_src(cchr_src);
	int length = (int)str_src.length(),
		lengthOffset = 0,
		i, j;

	if (str_src[0] == '-') {
		this->sign = 1;
		lengthOffset++;
	}
	if (str_src[lengthOffset] == '0' && length == 1 + lengthOffset) {
		this->zero = 1;
		this->data = NULL;
	}
	else if (str_src[lengthOffset] == '0' && !(str_src[lengthOffset + 1] == 'x' || str_src[lengthOffset + 1] == 'X')) {
		/// string to octonary

		lengthOffset++;
		length -= lengthOffset;
		std::string temp = str_src.substr(lengthOffset, length);

		int digits = (int)ceil((double)length * 3 / 8);
		digits = (4 > digits ? 4 : digits);

		this->byte = digits;
		this->data = (unsigned char *)malloc(digits);
		for (i = 0; i < digits; i++)
			(this->data)[i] = (unsigned char)0x00;

		for (i = 0; i < length; i++) {
			j = 3 * (length - 1 - i);
			unsigned char chr = temp[i] - '0';

			this->data[(j + 0) / 8] += (chr & (unsigned char)1) / 1 * (unsigned char)pow(2, (j + 0) % 8);
			this->data[(j + 1) / 8] += (chr & (unsigned char)2) / 2 * (unsigned char)pow(2, (j + 1) % 8);
			this->data[(j + 2) / 8] += (chr & (unsigned char)4) / 4 * (unsigned char)pow(2, (j + 2) % 8);
		}
	}
	else if (str_src[lengthOffset] == '0' && (str_src[lengthOffset + 1] == 'x' || str_src[lengthOffset + 1] == 'X')) {
		/// string to hexadecimal

		lengthOffset += 2;
		length -= lengthOffset;
		std::string temp = str_src.substr(lengthOffset, length);

		int digits = (int)ceil((double)length / 2);
		digits = (4 > digits ? 4 : digits);

		this->byte = digits;
		this->data = (unsigned char *)malloc(digits);
		for (i = 0; i < digits; i++)
			(this->data)[i] = (unsigned char)0x00;

		j = 0;
		for (i = length - 1; i > 0; i -= 2)
			(this->data)[j++] = chr_2_0x(temp[i - 1]) * 16 + chr_2_0x(temp[i]);
		if (i == 0)
			(this->data)[j] = chr_2_0x(temp[0]);
	}
	else {
		/// string to decimal

		length -= lengthOffset;
		char *dividend = (char *)malloc(length + 1),
			*quotient = (char *)malloc(length),
			*swap;

		strcpy(dividend + 1, cchr_src + lengthOffset);
		dividend[0] = 0;
		quotient[0] = 0;
		for (i = 1; i < length + 1; i++) {
			dividend[i] -= '0';
			quotient[i] = 0;
		}

		int digits = (int)ceil((double)length* Log_2_10 / 8);
		digits = (4 > digits ? 4 : digits);

		this->byte = digits;
		this->data = (unsigned char *)malloc(digits);
		for (i = 0; i < digits; i++)
			(this->data)[i] = (unsigned char)0x00;


		j = 0;
		while (length + 1 - zero_number(dividend) >= 3) {

			for (i = 0; i <= length - 3; i++) {
				quotient[i + 3] = divide256(dividend + i);
			}
			(this->data)[j++] = (unsigned char)(100 * dividend[length - 2] + 10 * dividend[length - 1] + dividend[length]);

			swap = dividend;
			dividend = quotient;
			quotient = swap;

			quotient[length] = 0;
			quotient[length - 1] = 0;
			quotient[length - 2] = 0;

		}
		(this->data)[j++] = (unsigned char)(100 * dividend[length - 2] + 10 * dividend[length - 1] + dividend[length]);
	}
}

void Integer::print() {
	int digits = 0;
	intString *temp_intString;

	if (this->zero)
		std::cout << '0';
	else {
		if (this->sign)std::cout << '-';
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
		if (digits <= 8)
			std::cout << (unsigned)(this->data)[0];
		else {
			temp_intString = intString_init((int)ceil(Log_10_2*(double)digits), (this->data)[this->byte - 1]);
			for (int i = this->byte - 2; i >= 0; i--) {
				intString_add(intString_mul256(&temp_intString), (this->data)[i]);
			}
			intString_print(temp_intString);
			intString_destroy(temp_intString);
		}
	}
}

Integer::~Integer() {
	if (this->data)
		free(this->data);
}