#include "Integer.h"

Integer& Integer::reset() {
	if (this->data) {
		free(this->data);
		this->data = NULL;
	}
	this->zero = 1;
	this->init = 1;
	this->byte = 0;
	return *this;
}
Integer& Integer::add(const Integer &rhs) {
	return *this;
}
