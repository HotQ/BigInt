#ifndef INTEGER_H_INCLUDED
#define INTEGER_H_INCLUDED

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
    Integer(const char *cchr_src);

	void print();
	int bidigits();

	Integer& expand();
	Integer& expand(int d);
	Integer& reset();
	Integer& add(const Integer &rhs);

	~Integer();

	friend Integer &Integer_add(const Integer &ax, const Integer &bx, Integer &lhs);

};

#endif // !INTEGER_H_INCLUDED
