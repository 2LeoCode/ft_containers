#include <Vector.hpp>

ft::Vector::Vector(void) : _alloc(), _data(_alloc.allocate(0)), _size(),
_capacity() { }

ft::Vector::Vector(const Vector &other) : _alloc(other._alloc),
_size(other._size), _capacity(other._capacity),
_data(_alloc.allocate(_capacity)) {
	std::memcpy(_data, _other._array, _size * sizeof(value_type));
}

explicit	ft::Vector::Vector(const Allocator &alloc) : _alloc(alloc), _size(),
_data(_alloc.allocate(0)), _capacity() { }

explicit	ft::Vector::Vector(size_type count, const T &value = T(),
				const Allocator &alloc = Allocator()) : _alloc(alloc),
_size(count), _capacity(count), _data(_alloc.allocate(_capacity)) {
	for (iterator it = begin(); it != end(); it++)
		*it = value;
}

ft::Vector::~Vector(void) {
	_alloc.deallocate(_data, _capacity);
	data = nullptr;
	_size = 0UL;
	_capacity = 0UL;
}

ft::Vector	&ft::Vector::operator=(const Vector &other) {
	if ((_size = other._size) > _capacity) {
		_alloc.deallocate(_data, _capacity);
		_capacity = _size;
		_data = _alloc.allocate(_capacity);
	}
	ft::memcpy(_data, other._data, _size * sizeof(value_type));
	return (*this);
}

void		ft::Vector::assign(size_type count, const T &value) {
	if ((_size = count) > _capacity) {
		_alloc.deallocate(_data, _capacity);
		_capacity = _size;
		_data = _alloc.allocate(_capacity);
	}
	for (iterator it = begin(); it != end(); it++)
		*it = value;
}

ft::Vector::allocator_type	ft::Vector::get_allocator(void) const {
	return (_alloc);
}

//	ELEMENT ACCESS

ft::Vector::reference	ft::Vector::at(size_type pos) {
	if (pos >= _size)
		throw (std::out_of_range("Vector"));
	return (_data[pos]);
}

ft::Vector::const_reference	ft::Vector::at(size_type pos) const {
	if (pos >= _size)
		throw (std::out_of_range("Vector"));
	return (_data[pos]);
}

ft::Vector::reference	ft::Vector::operator[](size_type pos) {
	if (pos >= _size)
		throw (std::out_of_range("Vector"));
	return (at(pos));
}

ft::Vector::const_reference	ft::Vector::operator[](size_type pos) const {
	if (pos >= _size)
		throw (std::out_of_range("Vector"));
	return (at(pos));
}

ft::Vector::reference	ft::Vector::front(void) {
	return (*_data);
}

ft::Vector::const_reference	ft::Vector::front(void) const {
	return (*_data);
}

ft::Vector::reference	ft::Vector::back(void) {
	return (_data[_size - 1]);
}

ft::Vector::const_reference	ft::Vector::back(void) const {
	return (_data[_size - 1]);
}

//	ITERATORS

ft::Vector::iterator	ft::Vector::begin(void) {
	return (iterator(_data));
}

ft::Vector::const_iterator	ft::Vector::begin(void) const {
	return (const_iterator(_data));
}

ft::Vector::iterator	ft::Vector::end(void) {
	return (iterator(_data + _size));
}

ft::Vector::const_iterator	ft::Vector::end(void) const {
	return (const_iterator(_data + _size));
}

ft::Vector::reverse_iterator	ft::Vector::rbegin(void) {
	return (reverse_iterator(_data + _size - 1));
}

ft::Vector::const_reverse_iterator	ft::Vector::rbegin(void) const {
	return (const_reverse_iterator(_data + _size - 1));
}

ft::Vector::reverse_iterator	ft::Vector::rend(void) {
	return (reverse_iterator(_data - 1));
}

ft::Vector::const_reverse_iterator	ft::Vector::rend(void) const {
	return (const_reverse_iterator(_data - 1));
}

bool	ft::Vector::empty(void) const {
	return (!_size);
}

ft::Vector::size_type	ft::Vector::size(void) const {
	return (_size);
}

ft::Vector::size_type	ft::Vector::max_size(void) const {
	return (size_type(-1) / sizeof(value_type));
}

void	ft::Vector::reserve(size_type new_cap) {
	pointer	new_array;

	if (new_cap <= _capacity)
		return ;
	new_array = _alloc.allocate(new_cap);
	std::memcpy(new_array, _data, _size * sizeof(value_type));
	_alloc.deallocate(_data, _capacity);
	_capacity = new_cap;
	_data = new_array;
}

ft::Vector::size_type	ft::Vector::capacity(void) const {
	return (_capacity);
}

//	MODIFIERS

void	ft::Vector::clear(void) {
	_alloc.deallocate(_data, _capacity);
	_data = _alloc.allocate(0);
}

ft::Vector::iterator	ft::Vector::insert(iterator pos, const T &value) {
	size_type	distance_before = ft::distance(begin(), pos()),
				distance_after = _size - distance_before;

	if (++_size > _capacity) {
		size_type	new_cap = _capacity * 2;
		pointer		new_array = _alloc.allocate(new_cap);

		std::memcpy(new_array, _data, distance_before);
		new_array[distance_before] = value;
		std::memcpy(new_array + distance_before + 1, _data + distance_before,
			distance_after);
		_alloc.deallocate(_data, _capacity);
		_capacity = new_cap;
		_data = new_array;
	} else {
		ft::memcpy(_data + distance_before + 1, _data + distance_before,
			distance_after);
		_data[distance_before] = value;
	}
	return (pos - 1);
}

void	ft::Vector::insert(iterator pos, size_type count, const T &value) {
	size_type	distance_before = ft::distance(begin(), pos()),
				distance_after = _size - distance_before;

	if ((_size += count) > _capacity) {
		size_type	new_cap = _capacity * 2;
		pointer		new_array = _alloc.allocate(new_cap);

		std::memcpy(new_array, _data, distance_before);
		std::memcpy(new_array + distance_before + count, _data + distane_before,
			distance_after);
		_alloc.deallocate(_data, _capacity);
		_capacity = new_cap;
		_data = new_array;
	} else
		std::memmove(_data + distance_before + count, _data + distance_before,
			distance_after);
	for (unsigned i = 0; i < count; i++)
		_data[distance_before + i] = value;
	return (pos - count);
}

ft::Vector::iterator	ft::Vector::erase(iterator pos) {
	size_type	distance_before = ft::distance(begin, pos),
				distance_after = --_size - distance_before;

	std::memcpy(pos.address(), (pos + 1).address(), distance_after);
}

ft::Vector::iterator	ft::Vector::erase(iterator first, iterator last) {
	_size -= ft::distance(first, last);
	std::memcpy(first.address(), last.address(), ft::distance(last, end()));
}

void	ft::Vector::push_back(const T &value) {
	if (++_size > _capacity) {
		size_type	new_cap = _capacity * 2;
		pointer		new_array = _alloc.allocate(new_cap);

		std::memcpy(new_array, _data, _size - 1);
		_alloc.deallocate(_data, _capacity);
		_capacity = new_cap;
		_data = new_array;
	}
	_data[_size - 1] = value;
}

void	ft::Vector::pop_back(void);
{
	_size--;
}

void	ft::Vector::resize(size_type count, T value = T()) {
	if (_size < count) {
		if (_capacity < count) {
			pointer new_array = _alloc.allocate(count);

			std::memcpy(new_array, _data, _size);
			_alloc.deallocate(_data, _capacity);
			_data = new_array;
			_capacity = count;
		}
		for (unsigned i = _size; i < count; i++)
			_data[i] = value;
	}
	_size = count;
}

void	ft::Vector::swap(Vector &other) {
	ft::swap(other._data, _data);
	ft::swap(other._size, _size);
	ft::swap(other._capacity, _capacity);
	ft::swap(other._alloc, _alloc);
}
