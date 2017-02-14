#ifndef INTEGER_H_INCLUDED
#define INTEGER_H_INCLUDED

#ifndef FUNCTIONAL_INCLUDED
#define FUNCTIONAL_INCLUDED
#include <functional>
#endif // !FUNCTIONAL_INCLUDED

#ifndef STRING_INCLUDED
#define STRING_INCLUDED
#include <string>
#endif // STRING_INCLUDED


//#define SHOWLOG

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
	/* Integer */
	Integer();
	Integer(int int_src);
	Integer(long long int_src);
	Integer(const char *cchr_src);
	Integer(const Integer& c);
	Integer(Integer&& c);
	Integer& operator=(Integer& c);
	Integer& operator=(Integer&& c);
	Integer& operator=(int int_src);
	Integer& operator=(long long int_src);
	Integer& operator=(const char *cchr_src);
	~Integer();

	unsigned char & operator[](int index) { return (this->data)[index]; }

	/* Integer_IO */
	void print();
	std::string toString();
	int toInt();

	friend std::ostream& operator<<(std::ostream &os, Integer &c);
	friend std::istream& operator>>(std::istream &is, Integer &c);

	/* Integer_Arithmetic */
	Integer& expand();
	Integer& expand(int d);
	Integer& reset();

	friend Integer operator+(Integer &ax, Integer &bx);
	friend Integer operator+(Integer &ax, int bx);
	friend Integer operator+(int ax, Integer &bx);
	friend Integer operator-(Integer &ax, Integer &bx);
	friend Integer operator-(Integer &ax, int bx);
	friend Integer operator-(int ax, Integer &bx);

	friend Integer &Integer_add(Integer &ax, Integer &bx, Integer &lhs);
	friend Integer &Integer_add(Integer &ax, int bx, Integer &lhs);
	friend Integer &Integer_sub(Integer &ax, Integer &bx, Integer &lhs);
	friend Integer &Integer_sub(Integer &ax, int bx, Integer &lhs);
	friend Integer &Integer_sub(int ax, Integer &bx, Integer &lhs);

	friend Integer Times(Integer &ax, Integer &bx);
	friend Integer Quotient(Integer &ax, Integer &bx);
	friend Integer operator>>(Integer &ax, int b);
	friend Integer Power(Integer &ax, int bx);
	friend Integer Mod(Integer &ax, Integer &bx);

	/* Integer_Bitwise */
	unsigned char getbit(unsigned int indexE, unsigned int indexI);
	unsigned char getbit(unsigned int index);
	void setbit(unsigned int index, unsigned char bit);
	int bidigits();

	/*Integer_Testing */
	friend bool operator==(Integer &ax, Integer &bx);
	friend bool operator!=(Integer &ax, Integer &bx);
	friend bool operator< (Integer &ax, Integer &bx);
	friend bool operator<=(Integer &ax, Integer &bx);
	friend bool operator> (Integer &ax, Integer &bx);
	friend bool operator>=(Integer &ax, Integer &bx);

	friend int Integer_compare_abs(Integer &ax, Integer &bx);
	friend int Integer_compare_abs(Integer &ax, int bx);

};
/* Integer_Arithmetic */
Integer Plus(Integer &ax, Integer &bx);
Integer Plus(Integer &ax, int bx);
Integer Plus(int ax, Integer &bx);
Integer Plus(int ax, int bx);
Integer operator+(Integer &ax, Integer &bx);
Integer operator+(Integer &ax, int bx);
Integer operator+(int ax, Integer &bx);

Integer Subtract(Integer &ax, Integer &bx);
Integer Subtract(Integer &ax, int bx);
Integer Subtract(int ax, Integer &bx);
Integer Subtract(int ax, int bx);
Integer operator-(Integer &ax, Integer &bx);
Integer operator-(Integer &ax, int bx);
Integer operator-(int ax, Integer &bx);

Integer Times(int      a, int b);
Integer Times(Integer &ax, int b);
Integer Times(Integer &ax, Integer &bx);
Integer operator*(Integer &ax, int b);
Integer operator*(int a, Integer &bx);
Integer operator*(Integer &ax, Integer &bx);

Integer Quotient(Integer &ax, Integer &bx);
Integer Quotient(Integer &ax, int b);
Integer Quotient(int a, int b);
Integer operator/(Integer &ax, Integer &bx);
Integer operator/(Integer &ax, int b);

Integer operator>>(Integer &ax, int b);

Integer Power(int      a, int b);
Integer Power(Integer &ax, int b);
Integer Power(Integer &ax, Integer &bx);
Integer operator^(Integer &ax, int b);
Integer operator^(Integer &ax, Integer &bx);

Integer Surd(Integer &ax, int b);
Integer Mod(Integer &ax, Integer &bx);
Integer Mod(Integer &ax, int b);
Integer operator%(Integer &ax, Integer &bx);
Integer operator%(Integer &ax, int b);

Integer PowerMod(int a, int b, int c);
Integer PowerMod(Integer &ax, int b, int c);
Integer PowerMod(Integer &ax, Integer &bx, int c);
Integer PowerMod(Integer &ax, Integer &bx, Integer &cx);

/* Integer_Testing */
bool Equal(Integer &ax, Integer &bx);
bool Equal(int      ax, Integer &bx);
bool Equal(Integer &ax, int      bx);
bool Unequal(Integer &ax, Integer &bx);
bool Unequal(int      ax, Integer &bx);
bool Unequal(Integer &ax, int      bx);
bool Less(Integer &ax, Integer &bx);
bool Less(int      ax, Integer &bx);
bool Less(Integer &ax, int       bx);
bool LessEqual(Integer &ax, Integer &bx);
bool LessEqual(int      ax, Integer &bx);
bool LessEqual(Integer &ax, int      bx);
bool Greater(Integer &ax, Integer &bx);
bool Greater(int      ax, Integer &bx);
bool Greater(Integer &ax, int     bx);
bool GreaterEqual(Integer &ax, Integer &bx);
bool GreaterEqual(int      ax, Integer &bx);
bool GreaterEqual(Integer &ax, int      bx);

bool operator==(Integer &ax, Integer &bx);
bool operator==(int      ax, Integer &bx);
bool operator==(Integer &ax, int      bx);
bool operator!=(Integer &ax, Integer &bx);
bool operator!=(int      ax, Integer &bx);
bool operator!=(Integer &ax, int      bx);
bool operator< (Integer &ax, Integer &bx);
bool operator< (int      ax, Integer &bx);
bool operator< (Integer &ax, int      bx);
bool operator<=(Integer &ax, Integer &bx);
bool operator<=(int      ax, Integer &bx);
bool operator<=(Integer &ax, int      bx);
bool operator> (Integer &ax, Integer &bx);
bool operator> (int      ax, Integer &bx);
bool operator> (Integer &ax, int      bx);
bool operator>=(Integer &ax, Integer &bx);
bool operator>=(int      ax, Integer &bx);
bool operator>=(Integer &ax, int      bx);

std::function<bool(Integer &)> LessThan(Integer &ax);
std::function<bool(Integer &)> LessThan(int     ax);
std::function<bool(Integer &)> LessEqualThan(Integer &ax);
std::function<bool(Integer &)> LessEqualThan(int     ax);
std::function<bool(Integer &)> GreaterThan(Integer &ax);
std::function<bool(Integer &)> GreaterThan(int      ax);
std::function<bool(Integer &)> GreaterEqualThan(Integer &ax);
std::function<bool(Integer &)> GreaterEqualThan(int      ax);
std::function<bool(Integer &)> EqualTo(Integer &ax);
std::function<bool(Integer &)> EqualTo(int      ax);
std::function<bool(Integer &)> UnequalTo(Integer &ax);
std::function<bool(Integer &)> UnequalTo(int      ax);
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
