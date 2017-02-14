#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Integer.h"

#define maybe 0
#define AxGreater 1
#define BxGreater -1

Integer &Integer_add(Integer &ax, Integer &bx, Integer &lhs);
Integer &Integer_add(Integer &ax, int bx, Integer &lhs);
Integer &Integer_sub(Integer &ax, Integer &bx, Integer &lhs);
Integer &Integer_sub(Integer &ax, int bx, Integer &lhs);
Integer &Integer_sub(int ax, Integer &bx, Integer &lhs);
static void AddToResult(Integer &result, unsigned int sum, int index);

Integer& Integer::reset() {
	if (this->data) {
		if (this->byte != 4) {
			free(this->data);
			auto temp = (unsigned char *)malloc(sizeof(int));
			if (temp) {
				this->data = temp;
				this->byte = sizeof(int);
			}
		}
	}
	else {
		auto temp = (unsigned char *)calloc(sizeof(unsigned char), sizeof(int));
		if (temp) {
			this->data = temp;
			this->byte = sizeof(int);
		}
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
			auto temp = (unsigned char *)malloc(d * sizeof(unsigned char));
			if (temp) {
				this->data = temp;
				this->byte = d;
				memset(this->data, 0, d * sizeof(unsigned char));
			}
#ifdef SHOWLOG
			std::clog << this << "\t\t\t  malloc " << d << " byte" << std::endl;
#endif // SHOWLOG
		}
		else {
			int bytes = (this->byte);
			this->byte += d;
			if (this->data) {
				auto temp = (unsigned char *)realloc(this->data, this->byte);
				if (temp) {
					this->data = temp;
					memset(this->data, 0, this->byte);
				}
			}
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

Integer Times(int      a, int b) {
	Integer temp1(a), temp2(b);
	return Times(temp1, temp2);
}
Integer Times(Integer &ax, int b) {
	Integer bx(b);
	return Times(ax, bx);
}
Integer Times(Integer &ax, Integer &bx) {
	//TODO: this is the sickest implement of Times()
	//TODO: should we test an Integer equal to zero before Times() run?

	int ax_real_byte = (int)ceil((double)(ax.bidigits()) / 8),
		bx_real_byte = (int)ceil((double)(bx.bidigits()) / 8),
		a = 0, b = 0, b2 = 0;

	if (ax_real_byte == 0 || bx_real_byte == 0)
		return 0;

	Integer result;
	result.expand(ax_real_byte + bx_real_byte);
	if (result.zero)
		result.zero = 0;

	for (a = 0; a < ax_real_byte - 1; a += 2) {
		for (b = 0; b < bx_real_byte - 1; b += 2) {
			unsigned int sum = (ax[a + 1] * 256 + ax[a])*(bx[b + 1] * 256 + bx[b]),
				CF = 0;
			AddToResult(result, sum, a + b);
		}
	}
	if (a == ax_real_byte - 1) {
		for (b2 = 0; b2 < bx_real_byte - 2; b2 += 3) {
			unsigned int sum = ax[a] * (bx[b2 + 2] * 65536 + bx[b2 + 1] * 256 + bx[b2]);
			AddToResult(result, sum, a + b2);
		}
		if (bx_real_byte - b2 != 0) {
			unsigned int sum = 0;
			switch (bx_real_byte - b2) {
			case 1:
				sum = bx[b2] * ax[a];
				break;
			case 2:
				sum = (bx[b2] + bx[b2 + 1] * 256) * ax[a];
				break;
			}
			AddToResult(result, sum, a + b2);
		}
	}
	if (b == bx_real_byte - 1) {
		for (int i = 0; i < ax_real_byte - 1; i += 2) {
			unsigned int sum = (ax[i + 1] * 256 + ax[i])*  bx[b];
			AddToResult(result, sum, b + i);
		}
	}
	result.sign = ax.sign^bx.sign;
	return result;
}
Integer operator*(Integer &ax, int b) {
	return Times(ax, b);
}
Integer operator*(int a, Integer &bx) {
	return Times(bx, a);
}
Integer operator*(Integer &ax, Integer &bx) {
	return Times(ax, bx);
}

Integer Quotient(Integer &ax, Integer &bx) {
	int ax_bit = ax.bidigits(),
		bx_bit = bx.bidigits();

	switch (Integer_compare_abs(ax, bx)) {
	case -1:
		return 0;
	case 0:
		return ((ax.sign^bx.sign) == 1 ? -1 : 1);
	}

	Integer ax_1 = ax, result;
	int temp = (int)ceil((double)(ax_bit) / 8) - (int)ceil((double)(bx_bit) / 8) + 1;
	result.expand(temp > 4 ? temp : 4);
	for (int bx_tail = ax_bit - bx_bit; bx_tail >= 0; bx_tail--) {
		int isAxGreater = maybe,
			copmare_pointer = bx_tail + bx_bit;
		unsigned char CF = 0;

		if (copmare_pointer + 1 <= ax_bit && ax_1.getbit(copmare_pointer) == 1) {
			isAxGreater = AxGreater;
			result.setbit(bx_tail, 1);

			for (int i = 0; i<bx_bit; i++) {
				char temp = ax_1.getbit(i + bx_tail) - bx.getbit(i) - CF;
				switch (temp) {
				case 1:
				case 0:
					ax_1.setbit(i + bx_tail, temp);
					CF = 0; break;
				case -1:
				case -2:
					ax_1.setbit(i + bx_tail, (-temp) % 2);
					CF = 1; break;
				}
			}
			char temp = ax_1.getbit(bx_bit + bx_tail) - CF;
			switch (temp) {
			case 1:
			case 0:
				ax_1.setbit(bx_bit + bx_tail, temp);
				CF = 0; break;
			case -1:
			case -2:
				ax_1.setbit(bx_bit + bx_tail, (-temp) % 2);
				CF = 1; break;
			}
			continue;
		}
		while ((isAxGreater == maybe) && (copmare_pointer != bx_tail)) {
			copmare_pointer--;
			if (ax_1.getbit(copmare_pointer) > bx.getbit(copmare_pointer - bx_tail)) {
				isAxGreater = AxGreater;
				break;
			}
			else if (ax_1.getbit(copmare_pointer) < bx.getbit(copmare_pointer - bx_tail)) {
				isAxGreater = BxGreater;
				break;
			}
		}
		if (isAxGreater == maybe)
			isAxGreater = AxGreater;
		if (isAxGreater == AxGreater) {
			result.setbit(bx_tail, 1);
			for (int i = 0; i<bx_bit; i++) {
				char temp = ax_1.getbit(i + bx_tail) - bx.getbit(i) - CF;
				switch (temp) {
				case 1:
				case 0:
					ax_1.setbit(i + bx_tail, temp);
					CF = 0; break;
				case -1:
				case -2:
					ax_1.setbit(i + bx_tail, (-temp) % 2);
					CF = 1; break;
				}
			}
		}
	}
	result.zero = 0;
	result.sign = ax.sign^bx.sign;
	return result;
}
Integer Quotient(Integer &ax, int b) {
	Integer bx(b);
	return Quotient(ax, bx);
}
Integer Quotient(int a, int b) {
	return a / b; // lmao
}
Integer operator/(Integer &ax, Integer &bx) {
	return Quotient(ax, bx);
}
Integer operator/(Integer &ax, int b) {
	return Quotient(ax, b);
}

Integer operator>>(Integer &ax, int b) {
	int bits = ax.bidigits();
	Integer result;
	int temp = (int)ceil((double)(bits - b) / 8);
	result.expand(temp > sizeof(int) ? temp : sizeof(int));
	for (int i = 0; i < bits - b; i++)
		result.setbit(i, ax.getbit(i + b));
	result.zero = 0;
	return result;
}
Integer operator<<(Integer &ax, int b) {
	int bits = ax.bidigits();
	Integer result;
	int temp = (int)ceil((double)(bits + b) / 8);
	result.expand(temp > sizeof(int) ? temp : sizeof(int));
	for (int i = 0; i < bits; i++)
		result.setbit(i + b, ax.getbit(i));
	result.zero = 0;
	return result;
}

Integer Power(int      a, int b) {
	Integer temp(a);
	return Power(temp, b);
}
Integer Power(Integer &ax, int b) {
	Integer result = ax;
	unsigned int mask = (1 << (sizeof(int) * 8 - 1));
	bool isBegin = false;
	while (!isBegin) {
		if ((mask&b) == mask)
			isBegin = true;
		mask >>= 1;
	}
	while (mask) {
		if ((mask&b) == mask)
			result = result * result * ax;
		else
			result = result * result;
		mask >>= 1;
	}
	if (ax.sign == 1)
		result.sign = b % 2;
	return result;
}
Integer Power(Integer &ax, Integer &bx) {
	Integer result = ax;
	unsigned int mask = (1 << (sizeof(int) * 8 - 1));
	bool isBegin = false;
	for (int i = bx.bidigits() - 2; i >= 0; i--) {
		if (bx.getbit(i))
			result = result * result * ax;
		else
			result = result * result;
	}

	if (ax.sign == 1)
		result.sign = bx.getbit(0) % 2;
	return result;
}
Integer operator^(Integer &ax, int b) {
	return Power(ax, b);
}
Integer operator^(Integer &ax, Integer &bx) {
	return Power(ax, bx);
}

Integer Surd(Integer &ax, int b) {
	Integer Divide_a_b = ax / b,
		x0 = ax >> (ax.bidigits() * (b - 1) / b),
		x1 = x0 * (b - 1) / b + Divide_a_b / (x0 ^ (b - 1));

	while (Integer_compare_abs(x1 - x0, 1) != 0 && Integer_compare_abs(x1 - x0, 0) != 0) {
		x0 = x1;
		x1 = x0 * (b - 1) / b + Divide_a_b / (x0 ^ (b - 1));
#ifdef SHOWLOG
		std::cout << x0 << "\t" << x1 << std::endl;
#endif
	}
	if (Integer_compare_abs(x1 - x0, 1) == 0) {
		switch (Integer_compare_abs(ax - x1^b, ax - x0^b))
		{
		case -1:return x1;
		case  1:return x0;
		case  0:return x0;
		}
	}
	return x0;
}
Integer Sqrt(Integer &ax1) {
	Integer ax = (ax1 << 8);

	if (Sign(ax) == 0)return 0;
	else if (Sign(ax) == 1) {
		Integer Divide_a_2 = ax / 2,
			x0 = ax >> (ax.bidigits() / 2),
			x1 = x0 / 2 + Divide_a_2 / x0;

		while ((Integer_compare_abs(x1 - x0, 1) != 0) && (Integer_compare_abs(x1 - x0, 0) != 0)) {
			x0 = x1;
			x1 = x0 / 2 + Divide_a_2 / x0;
		}

		if (Integer_compare_abs(x1 - x0, 1) == 0) {
			Integer t0 = ax - x0*x0, t1 = ax - x1*x1;
			int s0 = Sign(t0), s1 = Sign(t1);

			if (s0 == 0)
				return x0 >> 4;
			else if (s1 == 0)
				return x1 >> 4;

			if (s0 == 1 && s1 == 1) {
				switch (Integer_compare_abs(t0, t1))
				{
				case -1:return x0 >> 4;
				case  1:return x1 >> 4;
				case  0:return x0 >> 4;
				}
			}
			else if (s0 == 1 && s1 == -1) {
				return x0 >> 4;
			}
			else if (s1 == 1 && s0 == -1) {

				return x1 >> 4;
			}
			else if (s0 == -1 && s1 == -1) {
				switch (Integer_compare_abs(t0, t1))
				{
				case -1:return x0 >> 4;
				case  1:return x1 >> 4;
				case  0:return x1 >> 4;
				}
			}
			return x0 >> 4;
		}
		else {
			Integer t1 = ax - x1*x1;
			int s1 = Sign(t1);

			if (s1 == 1) {
				if ((t1 - 1 - (x1 << 1)) >= 0)
					return (x1 + 1) >> 4;
				else
					return x1 >> 4;
			}
			else if (s1 == -1) {
				return (x1 - 1) >> 4;
			}
			else
				return x0 >> 4;
		}
	}
}

Integer Mod(Integer &ax, Integer &bx) {
	switch (Integer_compare_abs(ax, bx)) {
	case -1:
		return ax;
	case 0:
		return 0;
	}

	int ax_bit = ax.bidigits(),
		bx_bit = bx.bidigits();
	Integer ax_1 = ax;

	for (int bx_tail = ax_bit - bx_bit; bx_tail >= 0; bx_tail--) {
		int isAxGreater = maybe,
			copmare_pointer = bx_tail + bx_bit;
		unsigned char CF = 0;

		if (copmare_pointer + 1 <= ax_bit && ax_1.getbit(copmare_pointer) == 1) {
			isAxGreater = AxGreater;

			for (int i = 0; i < bx_bit; i++) {
				char temp = ax_1.getbit(i + bx_tail) - bx.getbit(i) - CF;
				switch (temp) {
				case 1:
				case 0:
					ax_1.setbit(i + bx_tail, temp);
					CF = 0; break;
				case -1:
				case -2:
					ax_1.setbit(i + bx_tail, (-temp) % 2);
					CF = 1; break;
				}
			}
			char temp = ax_1.getbit(bx_bit + bx_tail) - CF;
			switch (temp) {
			case 1:
			case 0:
				ax_1.setbit(bx_bit + bx_tail, temp);
				CF = 0; break;
			case -1:
			case -2:
				ax_1.setbit(bx_bit + bx_tail, (-temp) % 2);
				CF = 1; break;
			}
			continue;
		}
		while ((isAxGreater == maybe) && (copmare_pointer != bx_tail)) {
			copmare_pointer--;
			if (ax_1.getbit(copmare_pointer) > bx.getbit(copmare_pointer - bx_tail)) {
				isAxGreater = AxGreater;
				break;
			}
			else if (ax_1.getbit(copmare_pointer) < bx.getbit(copmare_pointer - bx_tail)) {
				isAxGreater = BxGreater;
				break;
			}
		}
		if (isAxGreater == maybe)
			isAxGreater = AxGreater;
		if (isAxGreater == AxGreater) {
			for (int i = 0; i < bx_bit; i++) {
				char temp = ax_1.getbit(i + bx_tail) - bx.getbit(i) - CF;
				switch (temp) {
				case 1:
				case 0:
					ax_1.setbit(i + bx_tail, temp);
					CF = 0; break;
				case -1:
				case -2:
					ax_1.setbit(i + bx_tail, (-temp) % 2);
					CF = 1; break;
				}
			}
		}
	}
	if ((ax.sign ^ bx.sign))
		return ax_1 + bx;
	else
		return ax_1;
}
Integer Mod(Integer &ax, int b) {
	Integer bx(b);
	return Mod(ax, bx);
}
Integer operator%(Integer &ax, Integer &bx) {
	return Mod(ax, bx);
}
Integer operator%(Integer &ax, int b) {
	return Mod(ax, b);
}

Integer PowerMod(int a, int b, int c)
{
	int result = 1;
	a = a % c;
	while (b>0) {
		if (b % 2 == 1)
			result = (result * a) % c;
		b = b / 2;
		a = (a * a) % c;
	}
	return result;
}
Integer PowerMod(Integer &ax, int b, int c)
{
	int result = 1;
	int a = (ax % c).toInt();
	while (b>0) {
		if (b % 2 == 1)
			result = (result * a) % c;
		b = b / 2;
		a = (a * a) % c;
	}
	return result;
}
Integer PowerMod(Integer &ax, Integer &bx, int c)
{
	int result = 1;
	int a = (ax % c).toInt();
	for (int i = 0; bx.bidigits() > i; i++) {
		if (bx.getbit(i))
			result = (result * a) % c;
		a = (a * a) % c;
	}
	return result;
}
Integer PowerMod(Integer &ax, Integer &bx, Integer &cx) {
	Integer result = 1, a = ax % cx;
	for (int i = 0; bx.bidigits() > i; i++) {
		if (bx.getbit(i))
			result = (result * a) % cx;
		a = (a ^ 2) % cx;
	}
	return result;
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

		if (ax[ax_byte - 1] + bx[bx_byte - 1] >= 0xfe)
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
		lhs[i] = temp % 256;
		CF = temp / 256;
	}
	for (unsigned int i = min_byte; i < max_byte; i++) {
		int temp = (int)((max->data)[i] + CF);
		lhs[i] = temp % 256;
		CF = temp / 256;
	}
	if (lhs.byte > max_byte)
		lhs[max_byte] = CF;
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

		if (ax[ax_byte - 1] + bx_last_byte >= 0xfe)
			lhs.expand(ax_byte + 1 - lhs.byte);
		else
			lhs.expand(ax_byte - lhs.byte);
	}
	else if (ax_byte > bx_byte) {
		if (ax[ax_byte - 1] >= 0xfe)
			lhs.expand(ax_byte + 1 - lhs.byte);
		else
			lhs.expand(ax_byte - lhs.byte);
	}

	unsigned char CF = 0;
	for (unsigned int i = 0; i < bx_byte; i++) {

		int temp = (int)(ax[i] + bx % 256 + CF);

		lhs[i] = temp % 256;
		CF = temp / 256;
		bx = bx / 256;
	}
	for (unsigned int i = bx_byte; i < ax_byte; i++) {
		int temp = (int)(ax[i] + CF);
		lhs[i] = temp % 256;
		CF = temp / 256;
	}
	if (lhs.byte > ax_byte)
		lhs[ax_byte] = CF;
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
		temp = ax[i] - bx[i] - CF;
		CF = (temp < 0);
		lhs[i] = (char)(256 * CF + temp);
	}
	for (int i = bx_real_byte; i < ax_real_byte; i++) {
		temp = ax[i] - CF;
		CF = (temp < 0);
		lhs[i] = (char)(256 * CF + temp);
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
		temp = ax[i] - bx % 256 - CF;
		CF = (temp < 0);
		lhs[i] = (char)(256 * CF + temp);
		bx /= 256;
	}
	for (int i = sizeof(int); i < ax_real_byte; i++) {
		temp = ax[i] - CF;
		CF = (temp < 0);
		lhs[i] = (char)(256 * CF + temp);
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
		temp = ax % 256 - bx[i] - CF;
		CF = (temp < 0);
		lhs[i] = (char)(256 * CF + temp);
		ax /= 256;
	}
	if (lhs.zero)
		lhs.zero = 0;

	return lhs;
}
static void AddToResult(Integer &result, unsigned int sum, int index) {
	int i = index;
	unsigned CF = 0;
	while (sum) {
		unsigned int temp = result[i] + sum % 256 + CF;
		result[i] = temp % 256;
		CF = temp / 256;
		sum = sum / 256;
		i++;
	}
	while (CF) {
		unsigned int temp = result[i] + CF;
		result[i] = temp % 256;
		CF = temp / 256;
		i++;
	}
}