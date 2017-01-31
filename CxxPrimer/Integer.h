#ifndef INTEGER_H_INCLUDED
#define INTEGER_H_INCLUDED

#ifndef FUNCTIONAL_INCLUDED
#define FUNCTIONAL_INCLUDED
#include <functional>
#endif // !FUNCTIONAL_INCLUDED

#ifndef IOSTREAM_INCLUDED
#define IOSTREAM_INCLUDED
#include <iostream>
#endif // !IOSTREAM_INCLUDED


class Integer
{
public:
	unsigned int sign : 1;
	unsigned int zero : 1;
	unsigned int init : 1;

private:
	unsigned int byte : 29;
	unsigned char *data;

public:
	Integer();
	Integer(int int_src);
	Integer(long long int_src);
	Integer(const char *cchr_src);
	Integer(const Integer& c);
	Integer& operator=(Integer& c);
	Integer& operator=(int int_src);
	Integer& operator=(long long int_src);
	Integer& operator=(const char *cchr_src);
	~Integer();

	/* Integer_IO */
	void print();
	int bidigits();

	friend std::ostream& operator<<(std::ostream &os, Integer &c);
	friend std::istream& operator>>(std::istream &is, Integer &c);

	/* Integer_Arithmetic */
	Integer& expand();
	Integer& expand(int d);
	Integer& reset();
	Integer& add(const Integer &rhs);
	
	friend Integer &Integer_add(Integer &ax, Integer &bx, Integer &lhs);
	friend Integer &Integer_sub(Integer &ax, Integer &bx, Integer &lhs);

	/*Integer_Testing */
	friend int Integer_compare_abs(Integer &ax, Integer &bx);

};
/* Integer_Arithmetic */
Integer Plus(Integer &ax, Integer &bx);

/* Integer_Testing */
bool Equal(Integer &ax, Integer &bx);
bool Unequal(Integer &ax, Integer &bx);
bool Less(Integer &ax, Integer &bx);
bool LessEqual(Integer &ax, Integer &bx);
bool Greater(Integer &ax, Integer &bx);
bool GreaterEqual(Integer &ax, Integer &bx);
std::function<bool(Integer &)> LessThan(Integer &ax);
std::function<bool(Integer &)> LessEqualThan(Integer &ax);
std::function<bool(Integer &)> GreaterThan(Integer &ax);
std::function<bool(Integer &)> GreaterEqualThan(Integer &ax);
//TODO: 
// bool	Between(Integer &x, List min_max);
// bool	Between(Integer &x, List Lists_min_max);
// Operator Between(List Range);

int Sign(Integer &x);
bool Positive(Integer &x);
bool Negative(Integer &x);
bool NonPositive(Integer &x);
bool NonNegative(Integer &x);

#endif // !INTEGER_H_INCLUDED
