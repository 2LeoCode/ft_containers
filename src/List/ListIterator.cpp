#include <List.hpp>

explicit	ft::List::Iterator::Iterator(list_type *data) : _data(data) { }

ft::List::Iterator::Iterator(const Iterator &other) : _data(other._data) { }

ft::List::Iterator::~Iterator(void) {
	_data = nullptr;
}

ft::List::Iterator	&ft::List::Iterator::operator=(const Iterator &other) {
	_data = other._data;
}

ft::List::Iterator::list_type	&*ft::List::Iterator::node(void) {
	return (_data);
}

ft::List::Iterator::Pointer	ft::List::Iterator::address(void) {
	return (_data->data);
}

ft::List::Iterator	&ft::List::Iterator::operator++(void) {
	_data = _data->next;
	return (Iterator(_data));
}

ft::List::Iterator	ft::List::Iterator::operator++(int) {
	_data = _data->next;
	return (Iterator(_data->prev));
}

ft::List::Iterator	&ft::List::Iterator::operator--(void) {
	_data = _data->prev;
	return (Iterator(_data));
}

ft::List::Iterator	ft::List::Iterator::operator--(int) {
	_data = _data->prev;
	return (Iterator(_data->next));
}

bool	ft::List::Iterator::operator==(const Iterator other) const {
	return (_data == other._data);
}

bool	ft::List::Iterator::operator!=(const Iterator other) const {
	return (_data != other._data)
}

ft::List::Iterator::Reference	ft::List::Iterator::operator*(void) {
	return (*_data->data);
}
