#include <functional>
#include <cmath>
#include "Integer.h"
#define axbigger 1
#define equal 0
#define bxbigger -1

static unsigned char maskH2L[8] = { 0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01 };

int Integer_compare_abs(Integer &ax, Integer &bx);
int Integer_compare_abs(Integer &ax, int bx);
int Integer_compare(Integer &ax, Integer &bx);
int Integer_compare(Integer &ax, int bx);
int Integer_compare(int ax, Integer &bx);


///Equality & Inequality///
bool Equal(Integer &ax, Integer &bx) {
	switch (Integer_compare(ax, bx))
	{
	case -1:
	case  1:return false;
	case  0:return true;
	}
	return NULL; // Does it work?
}
bool Equal(int      ax, Integer &bx) {
	switch (Integer_compare(ax, bx))
	{
	case -1:
	case  1:return false;
	case  0:return true;
	}
	return NULL; // Does it work?
}
bool Equal(Integer &ax, int      bx) {
	switch (Integer_compare(ax, bx))
	{
	case -1:
	case  1:return false;
	case  0:return true;
	}
	return NULL; // Does it work?
}
bool Unequal(Integer &ax, Integer &bx) {
	switch (Integer_compare(ax, bx))
	{
	case -1:
	case  1:return true;
	case  0:return false;
	}
	return NULL;
}
bool Unequal(int      ax, Integer &bx) {
	switch (Integer_compare(ax, bx))
	{
	case -1:
	case  1:return true;
	case  0:return false;
	}
	return NULL;
}
bool Unequal(Integer &ax, int      bx) {
	switch (Integer_compare(ax, bx))
	{
	case -1:
	case  1:return true;
	case  0:return false;
	}
	return NULL;
}
bool Less(Integer &ax, Integer &bx) {
	switch (Integer_compare(ax, bx))
	{
	case -1:return true;
	case  1:
	case  0:return false;
	}
	return NULL;
}
bool Less(int      ax, Integer &bx) {
	switch (Integer_compare(ax, bx))
	{
	case -1:return true;
	case  1:
	case  0:return false;
	}
	return NULL;
}
bool Less(Integer &ax,int       bx) {
	switch (Integer_compare(ax, bx))
	{
	case -1:return true;
	case  1:
	case  0:return false;
	}
	return NULL;
}
bool LessEqual(Integer &ax, Integer &bx) {
	switch (Integer_compare(ax, bx))
	{
	case -1:
	case  0:return true;
	case  1:return false;
	}
	return NULL;
}
bool LessEqual(int      ax, Integer &bx) {
	switch (Integer_compare(ax, bx))
	{
	case -1:
	case  0:return true;
	case  1:return false;
	}
	return NULL;
}
bool LessEqual(Integer &ax, int      bx) {
	switch (Integer_compare(ax, bx))
	{
	case -1:
	case  0:return true;
	case  1:return false;
	}
	return NULL;
}
bool Greater(Integer &ax, Integer &bx) {
	switch (Integer_compare(ax, bx))
	{
	case  1:return true;
	case -1:
	case  0:return false;
	}
	return NULL;
}
bool Greater(int      ax, Integer &bx) {
	switch (Integer_compare(ax, bx))
	{
	case  1:return true;
	case -1:
	case  0:return false;
	}
	return NULL;
}
bool Greater(Integer &ax, int     bx) {
	switch (Integer_compare(ax, bx))
	{
	case  1:return true;
	case -1:
	case  0:return false;
	}
	return NULL;
}
bool GreaterEqual(Integer &ax, Integer &bx) {
	switch (Integer_compare(ax, bx))
	{
	case  1:
	case  0:return true;
	case -1:return false;
	}
	return NULL;
}
bool GreaterEqual(int      ax, Integer &bx) {
	switch (Integer_compare(ax, bx))
	{
	case  1:
	case  0:return true;
	case -1:return false;
	}
	return NULL;
}
bool GreaterEqual(Integer &ax, int      bx) {
	switch (Integer_compare(ax, bx))
	{
	case  1:
	case  0:return true;
	case -1:return false;
	}
	return NULL;
}

bool operator==(Integer &ax, Integer &bx) {
	return Equal(ax, bx);
}
bool operator==(int      ax, Integer &bx) {
	return Equal(ax, bx);
}
bool operator==(Integer &ax, int      bx) {
	return Equal(ax, bx);
}
bool operator!=(Integer &ax, Integer &bx) {
	return Unequal(ax, bx);
}
bool operator!=(int      ax, Integer &bx) {
	return Unequal(ax, bx);
}
bool operator!=(Integer &ax, int      bx) {
	return Unequal(ax, bx);
}
bool operator< (Integer &ax, Integer &bx) {
	return Less(ax, bx);
}
bool operator< (int      ax, Integer &bx) {
	return Less(ax, bx);
}
bool operator< (Integer &ax, int      bx) {
	return Less(ax, bx);
}
bool operator<=(Integer &ax, Integer &bx) {
	return LessEqual(ax, bx);
}
bool operator<=(int      ax, Integer &bx) {
	return LessEqual(ax, bx);
}
bool operator<=(Integer &ax, int      bx) {
	return LessEqual(ax, bx);
}
bool operator> (Integer &ax, Integer &bx) {
	return Greater(ax, bx);
}
bool operator> (int      ax, Integer &bx) {
	return Greater(ax, bx);
}
bool operator> (Integer &ax, int      bx) {
	return Greater(ax, bx);
}
bool operator>=(Integer &ax, Integer &bx) {
	return GreaterEqual(ax, bx);
}
bool operator>=(int      ax, Integer &bx) {
	return GreaterEqual(ax, bx);
}
bool operator>=(Integer &ax, int      bx) {
	return GreaterEqual(ax, bx);
}

std::function<bool(Integer &)> LessThan(Integer &ax) {
	return [&](Integer &bx)-> bool { return Less(bx, ax); };
}
std::function<bool(Integer &)> LessThan(int     ax) {
	return [&](Integer &bx)-> bool { return Less(bx, ax); };
}
std::function<bool(Integer &)> LessEqualThan(Integer &ax) {
	return [&](Integer &bx)-> bool { return LessEqual(bx, ax); };
}
std::function<bool(Integer &)> LessEqualThan(int     ax) {
	return [&](Integer &bx)-> bool { return LessEqual(bx, ax); };
}
std::function<bool(Integer &)> GreaterThan(Integer &ax) {
	return [&](Integer &bx)-> bool { return Greater(bx, ax); };
}
std::function<bool(Integer &)> GreaterThan(int      ax) {
	return [&](Integer &bx)-> bool { return Greater(bx, ax); };
}
std::function<bool(Integer &)> GreaterEqualThan(Integer &ax) {
	return [&](Integer &bx)-> bool { return GreaterEqual(bx, ax); };
}
std::function<bool(Integer &)> GreaterEqualThan(int      ax) {
	return [&](Integer &bx)-> bool { return GreaterEqual(bx, ax); };
}
std::function<bool(Integer &)> EqualTo(Integer &ax) {
	return [&](Integer &bx)-> bool { return Equal(bx, ax); };
}
std::function<bool(Integer &)> EqualTo(int      ax) {
	return [&](Integer &bx)-> bool { return Equal(bx, ax); };
}
std::function<bool(Integer &)> UnequalTo(Integer &ax) {
	return [&](Integer &bx)-> bool { return Unequal(bx, ax); };
}
std::function<bool(Integer &)> UnequalTo(int      ax) {
	return [&](Integer &bx)-> bool { return Unequal(bx, ax); };
}

int Sign(Integer &x) {
	if (x.zero == 1)
		return 0;
	else {
		if (x.sign == 0)
			return 1;
		else
			return -1;
	}
}
bool Positive(Integer &x) {
	switch (Sign(x))
	{
	case -1:
	case  0:return false;
	case  1:return true;
	}
	return NULL;
}
bool Negative(Integer &x) {
	switch (Sign(x))
	{
	case -1:return true;
	case  0:
	case  1:return false;
	}
	return NULL;
}
bool NonPositive(Integer &x) {
	switch (Sign(x))
	{
	case -1:
	case  0:return true;
	case  1:return false;
	}
	return NULL;
}
bool NonNegative(Integer &x) {
	switch (Sign(x))
	{
	case  1:
	case  0:return true;
	case -1:return false;
	}
	return NULL;
}


int Integer_compare_abs(Integer &ax, Integer &bx) {
	if (&ax == &bx) return equal;
	else {
		int ax_bidigits = ax.bidigits(),
			bx_bidigits = bx.bidigits();

		if (ax_bidigits > bx_bidigits)return axbigger;
		else if (ax_bidigits < bx_bidigits)return bxbigger;
		else {
			for (int i = (int)ceil((double)ax_bidigits / 8) - 1; i >= 0; i--) {
				if ((ax.data)[i] != (bx.data)[i]) {
					if ((ax.data)[i] >(bx.data)[i])return axbigger;
					else return bxbigger;
				}
			}
			return equal;
		}
	}
}
int Integer_compare_abs(Integer &ax, int bx) {
	int ax_real_byte = (int)ceil((double)(ax.bidigits()) / 8);
	if (ax_real_byte > 4) {
		return axbigger;
	}
	else {
		for (int i = (int)sizeof(int) - 1; i >= 0; i--) {
			unsigned char tbx = bx >> 8 * i;
			bx = bx - ((int)tbx << (8 * i));
			if ((ax.data)[i] != tbx) {
				if ((ax.data)[i] > tbx)return axbigger;
				else return bxbigger;
			}
		}
		return equal;
	}
}
int Integer_compare(Integer &ax, Integer &bx) {
	if (ax.sign == bx.sign) {
		if (ax.sign == 0)
			return Integer_compare_abs(ax, bx);
		else
			return Integer_compare_abs(ax, bx)*(-1);
	}
	else {
		if (ax.sign == 0)
			return axbigger;
		else
			return bxbigger;
	}
}
int Integer_compare(Integer &ax, int bx) {
	int bx_sign = bx >= 0 ? 0 : 1;
	if (ax.sign == bx_sign) {
		if (ax.sign == 0)
			return Integer_compare_abs(ax, bx);
		else
			return Integer_compare_abs(ax, bx)*(-1);
	}
	else {
		if (ax.sign == 0)
			return axbigger;
		else
			return bxbigger;
	}
}
int Integer_compare(int ax, Integer &bx) {
	return Integer_compare(bx, ax)*(-1);
}
