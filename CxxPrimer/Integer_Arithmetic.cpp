#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Integer.h"

Integer &Integer_add(const Integer &ax, const Integer &bx, Integer &lhs);
Integer &Integer_sub(const Integer &ax, const Integer &bx, Integer &lhs);

Integer& Integer::reset() {
	if (this->data) {
		if (this->byte != 4) {
			free(this->data);
			this->byte = sizeof(int);
			this->data = (unsigned char *)malloc(sizeof(int));
		}
	}
	else {
		this->byte = sizeof(int);
		this->data = (unsigned char *)malloc(sizeof(int));
	}
	for (int i = 0; i < (int)sizeof(int); i++) {
		(this->data)[i] = (unsigned char)0;
	}
	this->zero = 1;
	this->init = 1;
	return *this;
}
Integer& Integer::expand() {
	return expand(1);
}
Integer& Integer::expand(int d) {
	if (d > 0) {
		int bytes = (this->byte);
		this->byte += d;
		this->data = (unsigned char *)realloc(this->data, this->byte);

		
		for (int i = bytes; i < (int)(this->byte); i++)
			(this->data)[i] = 0;

	}
	return *this;
}
Integer& Integer::add(const Integer &rhs) {
	return *this;
}

Integer &Integer_add(Integer &ax, Integer &bx, Integer &lhs) {
	const Integer *max, *min;
	if (ax.byte == bx.byte) {
		max = &ax;
		min = &bx;

		if ((max->data)[ax.byte - 1] + (min->data)[bx.byte - 1] >= 0xfe) {
			lhs.expand(max->byte + 1 - lhs.byte);
		}
		else {
			lhs.expand(max->byte - lhs.byte);
		}
	}
	else {
		if (ax.byte > bx.byte) {
			max = &ax;
			min = &bx;
		}
		else {
			min = &ax;
			max = &bx;
		}

		if ((max->data)[ax.byte - 1] >= 0xfe) {
			lhs.expand(max->byte + 1 - lhs.byte);
		}
		else {
			lhs.expand(max->byte - lhs.byte);
		}
	}

	unsigned char CF = 0;
	for (int i = 0; i < (int)(min->byte); i++) {
		int temp = (int)((max->data)[i] + (min->data)[i] + CF);
		(lhs.data)[i] = temp % 256;
		CF = temp / 256;
	}
	for (int i = min->byte; i < (int)(max->byte); i++) {
		int temp = (int)((max->data)[i] + CF);
		(lhs.data)[i] = temp % 256;
		CF = temp / 256;
	}
	if (lhs.byte > max->byte) {
		(lhs.data)[max->byte] = CF;
	}
	return lhs;
}
/// ax is always bigger than bx
Integer &Integer_sub(Integer &ax, Integer &bx, Integer &lhs) {
	unsigned char CF = 0;
	int temp;
	int ax_real_byte = (int)ceil((double)(ax.bidigits()) / 8),
		bx_real_byte = (int)ceil((double)(bx.bidigits()) / 8);
	
	lhs.expand(ax_real_byte - lhs.byte);

	for (int i = 0; i < bx_real_byte; i++) {
		temp = (ax.data)[i] - (bx.data)[i] - CF;
		CF = (temp < 0);
		(lhs.data)[i] = (char)(256 * CF + temp);
	}
	for (int i = bx_real_byte; i < ax_real_byte; i++) {
		temp = (ax.data)[i] - CF;
		CF = (temp < 0);
		(lhs.data)[i] = (char)(256 * CF + temp);
	}
	return lhs;
}
