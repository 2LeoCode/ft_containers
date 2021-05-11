#include <Vector.hpp>

explicit	ft::Vector::Iterator::Iterator(Pointer data) : _data(data) { }

ft::Vector::Iterator::Iterator(const Iterator &other) : _data(other._data) { }

ft::Vector::Iterator::~Iterator(void) { }

ft::Vector::Iterator	ft::Vector::Iterator::operator=(const Iterator &other) {
	_data = other._data;
}

ft::Vector::Iterator::Pointer	ft::Vector::Iterator::address(void) {
	return (_data);
}

ft::Vector::Iterator	&ft::Vector::Iterator::operator++(void) {
	_data++;
	return (*this);
}

ft::Vector::Iterator	ft::Vector::Iterator::operator++(int) {
	_data++;
	return (Iterator(_data - 1));
}

ft::Vector::Iterator	&ft::Vector::Iterator::operator--(void) {
	_data--;
	return (*this);
}

ft::Vector::Iterator	ft::Vector::Iterator::operator--(int) {
	_data--;
	return (Iterator(_data + 1));
}

ft::Vector::Iterator	&ft::Vector::Iterator::operator+=(int amount) {
	_data += amount;
	return (*this);
}

ft::Vector::Iterator	&ft::Vector::Iterator::operator-=(int amount) {
	_data -= amount;
	return (*this);
}

bool	ft::Vector::Iterator::operator==(const Iterator &other) {
	return (_data == other._data);
}

bool	ft::Vector::Iterator::operator!=(const Iterator &other) {
	return (_data != other._data);
}

ft::Vector::Iterator::Reference	ft::Vector::Iterator::operator*(void) {
	return (*_data);
}
