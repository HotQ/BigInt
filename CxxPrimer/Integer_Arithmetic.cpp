#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Integer.h"


Integer &Integer_add(Integer &ax, Integer &bx, Integer &lhs);
Integer &Integer_add(Integer &ax, int bx, Integer &lhs);
Integer &Integer_sub(Integer &ax, Integer &bx, Integer &lhs);
Integer &Integer_sub(Integer &ax, int bx, Integer &lhs);
Integer &Integer_sub(int ax, Integer &bx, Integer &lhs);

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
		if (this->byte + d < sizeof(int))
			d = sizeof(int) - this->byte;
		if (this->init == 0) {
			this->init = 1;
			this->zero = 1;
			this->sign = 0;
			this->byte = d;
			this->data = (unsigned char *)malloc(d * sizeof(unsigned char));
			memset(this->data, 0, sizeof(unsigned char));
#ifdef SHOWLOG
			std::clog << this << "\t\t\t  malloc " << d << " byte" << std::endl;
#endif // SHOWLOG
		}
		else {
			int bytes = (this->byte);
			this->byte += d;
			this->data = (unsigned char *)realloc(this->data, this->byte);

			for (int i = bytes; i < (int)(this->byte); i++)
				(this->data)[i] = 0;
#ifdef SHOWLOG
			std::clog << this << "\t\t\t realloc +" << d << " byte" << std::endl;
#endif // SHOWLOG
		}
	}
	return *this;
}
Integer Plus(Integer &ax, Integer &bx) {
	if (ax.zero == 1 || bx.zero == 1) {
		if (ax.zero == 1)
			return bx;
		else
			return ax;
	}
	else {
		Integer result;

		if (ax.sign == bx.sign) {
			Integer_add(ax, bx, result);
			result.sign = ax.sign;
		}
		else
			switch (Integer_compare_abs(ax, bx)) {
			case -1:
				Integer_sub(bx, ax, result);
				result.sign = bx.sign;
				break;
			case  1:
				Integer_sub(ax, bx, result);
				result.sign = ax.sign;
				break;
			case 0:
				result = 0;
				break;
			}
		return result;
	}
}
Integer Plus(Integer &ax, int bx) {
	if (ax.zero == 1 || bx == 0) {
		if (ax.zero == 1)
			return bx;
		else
			return ax;
	}
	else {
		Integer result;
		int bx_sign = (bx > 0 ? 0 : 1);
		if (bx < 0)
			bx = -bx;
		if (ax.sign == bx_sign) {
			Integer_add(ax, bx, result);
			result.sign = ax.sign;
		}
		else
			switch (Integer_compare_abs(ax, bx)) {
			case -1:
				Integer_sub(bx, ax, result);
				result.sign = bx_sign;
				break;
			case  1:
				Integer_sub(ax, bx, result);
				result.sign = ax.sign;
				break;
			case 0:
				return 0;
				break;
			}
		return result;
	}
}
Integer Plus(int bx, Integer &ax) {
	if (ax.zero == 1 || bx == 0) {
		if (ax.zero == 1)
			return bx;
		else
			return ax;
	}
	else {
		Integer result;
		int bx_sign = (bx > 0 ? 0 : 1);
		if (ax.sign == bx_sign) {
			Integer_add(ax, bx, result);
			result.sign = ax.sign;
		}
		else
			switch (Integer_compare_abs(ax, bx)) {
			case -1:
				Integer_sub(bx, ax, result);
				result.sign = bx_sign;
				break;
			case  1:
				Integer_sub(ax, bx, result);
				result.sign = ax.sign;
				break;
			case 0:
				return 0;
				break;
			}
		return result;
	}
}
Integer Plus(int ax, int bx) {
	Integer tax = ax, tbx = bx;
	return Plus(tax, tbx);
}
Integer operator+(Integer &ax, Integer &bx) {
	return Plus(ax, bx);
}
Integer operator+(Integer &ax, int bx) {
	return Plus(ax, bx);
}
Integer operator+(int ax, Integer &bx) {
	return Plus(ax, bx);
}

///a bad lazy implement
Integer Subtract(Integer &ax, Integer &bx) {
	bx.sign = 1 - bx.sign;
	Integer result;
	if (ax.zero == 1 || bx.zero == 1) {
		if (ax.zero == 1)
			result = bx;
		else
			result = ax;
	}
	else {
		if (ax.sign == bx.sign) {
			Integer_add(ax, bx, result);
			result.sign = ax.sign;
		}
		else
			switch (Integer_compare_abs(ax, bx)) {
			case -1:
				Integer_sub(bx, ax, result);
				result.sign = bx.sign;
				break;
			case  1:
				Integer_sub(ax, bx, result);
				result.sign = ax.sign;
				break;
			case 0:
				result = 0;
				break;
			}
	}
	bx.sign = 1 - bx.sign;

	return result;
}
Integer Subtract(Integer &ax, int bx) {
	return Plus(ax, -bx);
}
Integer Subtract(int bx, Integer &ax) {
	if (ax.zero == 1 || bx == 0) {
		if (ax.zero == 1)
			return -bx;
		else {
			Integer result = ax;
			result.sign = 1 - result.sign;
			return ax;
		}
	}
	else {
		Integer result;
		ax.sign = 1 - ax.sign;
		int bx_sign = (bx > 0 ? 0 : 1);
		if (ax.sign == bx_sign) {
			Integer_add(ax, bx, result);
			result.sign = ax.sign;
		}
		else
			switch (Integer_compare_abs(ax, bx)) {
			case -1:
				Integer_sub(bx, ax, result);
				result.sign = bx_sign;
				break;
			case  1:
				Integer_sub(ax, bx, result);
				result.sign = ax.sign;
				break;
			case 0:
				return 0;
				break;
			}
		ax.sign = 1 - ax.sign;
		return result;
	}
}
Integer Subtract(int ax, int bx) {
	return ax - bx;
}
Integer operator-(Integer &ax, Integer &bx) {
	return Subtract(ax, bx);
}
Integer operator-(Integer &ax, int bx) {
	return Subtract(ax, bx);
}
Integer operator-(int ax, Integer &bx) {
	return Subtract(ax, bx);
}


Integer &Integer_add(Integer &ax, Integer &bx, Integer &lhs) {
	Integer *max, *min;
	unsigned int ax_byte = (unsigned int)ceil((double)(ax.bidigits()) / 8),
		bx_byte = (unsigned int)ceil((double)(bx.bidigits()) / 8),
		max_byte, min_byte;

	if (ax_byte == bx_byte) {
		max = &ax;
		min = &bx;
		max_byte = ax_byte;
		min_byte = bx_byte;

		if ((ax.data)[ax_byte - 1] + (bx.data)[bx_byte - 1] >= 0xfe)
			lhs.expand(ax_byte + 1 - lhs.byte);
		else
			lhs.expand(ax_byte - lhs.byte);
	}
	else {
		if (ax_byte > bx_byte) {
			max = &ax;
			min = &bx;
			max_byte = ax_byte;
			min_byte = bx_byte;
		}
		else {
			min = &ax;
			max = &bx;
			max_byte = bx_byte;
			min_byte = ax_byte;
		}

		if ((max->data)[max_byte - 1] >= 0xfe)
			lhs.expand(max_byte + 1 - lhs.byte);
		else
			lhs.expand(max_byte - lhs.byte);
	}

	unsigned char CF = 0;
	for (unsigned int i = 0; i < min_byte; i++) {
		int temp = (int)((max->data)[i] + (min->data)[i] + CF);

		(lhs.data)[i] = temp % 256;
		CF = temp / 256;
	}
	for (unsigned int i = min_byte; i < max_byte; i++) {
		int temp = (int)((max->data)[i] + CF);
		(lhs.data)[i] = temp % 256;
		CF = temp / 256;
	}
	if (lhs.byte > max_byte)
		(lhs.data)[max_byte] = CF;
	if (lhs.zero == 1)
		lhs.zero = 0;

	return lhs;
}
Integer &Integer_add(Integer &ax, int bx, Integer &lhs) {
	unsigned int ax_byte = (int)ceil((double)(ax.bidigits()) / 8),
		bx_byte = 4,
		bx_last_byte;

	while (bx >> 8 * (bx_byte-- - 1) == 0);
	bx_last_byte = bx >> bx_byte * 8;
	bx_byte++;


	if (ax_byte == bx_byte) {

		if ((ax.data)[ax_byte - 1] + bx_last_byte >= 0xfe)
			lhs.expand(ax_byte + 1 - lhs.byte);
		else
			lhs.expand(ax_byte - lhs.byte);
	}
	else if (ax_byte > bx_byte) {
		if ((ax.data)[ax_byte - 1] >= 0xfe)
			lhs.expand(ax_byte + 1 - lhs.byte);
		else
			lhs.expand(ax_byte - lhs.byte);
	}

	unsigned char CF = 0;
	for (unsigned int i = 0; i < bx_byte; i++) {

		int temp = (int)((ax.data)[i] + bx % 256 + CF);

		(lhs.data)[i] = temp % 256;
		CF = temp / 256;
		bx = bx / 256;
	}
	for (unsigned int i = bx_byte; i < ax_byte; i++) {
		int temp = (int)((ax.data)[i] + CF);
		(lhs.data)[i] = temp % 256;
		CF = temp / 256;
	}
	if (lhs.byte > ax_byte)
		(lhs.data)[ax_byte] = CF;
	if (lhs.zero == 1)
		lhs.zero = 0;

	return lhs;
}
/// abs(ax) is always bigger than abs(bx)
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
	if (lhs.zero)
		lhs.zero = 0;

	return lhs;
}
Integer &Integer_sub(Integer &ax, int bx, Integer &lhs) {
	unsigned char CF = 0;
	int temp;
	int ax_real_byte = (int)ceil((double)(ax.bidigits()) / 8);

	lhs.expand(ax_real_byte - lhs.byte);

	for (int i = 0; i < sizeof(int); i++) {
		temp = (ax.data)[i] - bx % 256 - CF;
		CF = (temp < 0);
		(lhs.data)[i] = (char)(256 * CF + temp);
		bx /= 256;
	}
	for (int i = sizeof(int); i < ax_real_byte; i++) {
		temp = (ax.data)[i] - CF;
		CF = (temp < 0);
		(lhs.data)[i] = (char)(256 * CF + temp);
	}
	if (lhs.zero)
		lhs.zero = 0;

	return lhs;
}
Integer &Integer_sub(int ax, Integer &bx, Integer &lhs) {
	unsigned char CF = 0;
	int temp;

	lhs.expand(sizeof(int) - lhs.byte);

	for (int i = 0; i < sizeof(int); i++) {
		temp = ax % 256 - (bx.data)[i] - CF;
		CF = (temp < 0);
		(lhs.data)[i] = (char)(256 * CF + temp);
		ax /= 256;
	}
	if (lhs.zero)
		lhs.zero = 0;

	return lhs;
}