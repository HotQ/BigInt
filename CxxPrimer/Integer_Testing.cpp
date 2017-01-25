#include <functional>
#include <cmath>
#include "Integer.h"
#define axbigger 1
#define equal 0
#define bxbigger -1

static unsigned char maskH2L[8] = { 0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01 };

int Integer_compare_abs(Integer &ax, Integer &bx);
int Integer_compare(Integer &ax, Integer &bx);


///Equality & Inequality///
bool Equal(Integer &ax, Integer &bx) {
	switch (Integer_compare(ax,bx))
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
bool Less(Integer &ax, Integer &bx) {
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
bool Greater(Integer &ax, Integer &bx) {
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
std::function<bool(Integer &)> LessThan(Integer &ax) {
	std::function<bool(Integer &)> Operator = std::bind(Less, std::placeholders::_1, std::ref(ax));
	return Operator;
}
std::function<bool(Integer &)> LessEqualThan(Integer &ax) {
	std::function<bool(Integer &)> Operator = std::bind(LessEqual, std::placeholders::_1, std::ref(ax));
	return Operator;
}
std::function<bool(Integer &)> GreaterThan(Integer &ax) {
	std::function<bool(Integer &)> Operator = std::bind(Greater, std::placeholders::_1, std::ref(ax));
	return Operator;
}
std::function<bool(Integer &)> GreaterEqualThan(Integer &ax) {
	std::function<bool(Integer &)> Operator = std::bind(GreaterEqual, std::placeholders::_1, std::ref(ax));
	return Operator;
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
			for (int i = (int)ceil((double)ax_bidigits / 8) - 1; i >= 0; i++) {
				if ((ax.data)[i] != (bx.data)[i]) {
					if ((ax.data)[i] > (bx.data)[i])return axbigger;
					else return bxbigger;
				}
			}
			return equal;
		}
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
