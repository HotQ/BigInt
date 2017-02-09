#include "Integer.h"
#include <iostream>

static unsigned char maskH2L[8] = { 0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01 };
static unsigned char maskL2H[8] = { 0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80 };

unsigned char Integer::getbit(unsigned int indexE, unsigned int indexI) {
	return (bool)((this->data[indexE]) & maskL2H[indexI]);
}
unsigned char Integer::getbit(unsigned int index) {
	return getbit(index / 8, index % 8);
}
void Integer::setbit(unsigned int index, unsigned char bit) {
	if (bit)
		this->data[index / 8] |= maskL2H[index % 8];
	else
		this->data[index / 8] &= ~maskL2H[index % 8];
}
int Integer::bidigits() {
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
	return digits;
}