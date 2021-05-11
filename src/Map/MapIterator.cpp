#include <Map.hpp>

ft::Map::Iterator::Iterator(node *member) : _data(member), _alloc(Alloc())
{
}

ft::Map::Iterator	&ft::Map::Iterator::operator++(void)
{
	node	*prev = _data;

	_data = BTree_Next(_data);
	return (Iterator(prev));
}

ft::Map::Iterator	ft::Map::Iterator::operator++(int)
{
	_data = BTree_Next(_data);
	return (Iterator(_data));
}

ft::Map::Iterator	&ft::Map::Iterator::operator--(void)
{
	node	*prev = _data;

	_data = BTree_Prev(_data);
	return (Iterator(prev));
}

ft::Map::Iterator	ft::Map::Iterator::operator--(int)
{
	_data = BTree_Prev(_data);
	return (Iterator(_data));
}

ft::Map::Iterator::value_type	ft::Map::Iterator::operator*(void)
{
	return (*_data->data);
}

bool	ft::Map::Iterator::operator==(const Iterator &other)
{
	return (_data == other._data);
}

bool	ft::Map::Iterator::operator!=(const Iterator &other)
{
	return (_data != other._data);
}

ft::Map::Iterator::value_type	ft::Map::Iterator::address(void)
{
	return (_data->data);
}
