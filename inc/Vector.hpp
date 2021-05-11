#pragma once

#include "containers.hpp"

template <
    class T,
    class Allocator = std::allocator< T >
> class Vector {
	public:

	typedef T									value_type;
	typedef Allocator							allocator_type;
	typedef std::size_t							size_type;
	typedef std::ptrdiff_t						difference_type;
	typedef Allocator::reference				reference;
	typedef Allocator::const_reference			const_reference;
	typedef Allocator::pointer					pointer;
	typedef Allocator::const_pointer			const_pointer;
	typedef Iterator							iterator;
	typedef const iterator						const_iterator;
	typedef std::reverse_iterator< iterator >	reverse_iterator;
	typedef const reverse_iterator				const_reverse_iterator;

	template <
		class Category = std::bidirectional_iterator_tag,
		class Type = T,
		class Distance = std::ptrdiff_t,
		class Pointer = T*,
		class Reference = T&
	> class Iterator
	{
		public:

		explicit	Iterator(Pointer data);
		Iterator(const Iterator &other);
		~Iterator(void);

		Iterator	&operator=(const Iterator other);

		Pointer		address(void);
		Iterator	&operator++(void);
		Iterator	operator++(int);
		Iterator	&operator--(void);
		Iterator	operator--(int);
		Iterator	&operator+=(int amount);
		Iterator	&operator-=(int amount);
		bool		operator==(const Iterator other);
		bool		operator!=(const Iterator other);
		Reference	operator*(void);

		private:

		Pointer	_data;
	};

	Vector(void);
	Vector(const Vector &other);
	explicit				Vector(const Allocator &alloc);
	explicit				Vector(size_type count, const T &value = T(),
								const Allocator &alloc = Allocator());
	template < class InputIt >
	Vector(InputIt first, InputIt last,
		const Allocator &alloc = Allocator()) : _alloc(alloc),
	_size(ft::distance(first, last)), _capacity(size),
	_data(_alloc.allocate(_capacity)) {
		std::memcpy(_data, _first.address(), _size * sizeof(value_type));
	};
	~Vector(void);

	Vector					&operator=(const Vector &other);
	void					assign(size_type count, const T &value);
	template < class InputIt >
	void					assign(InputIt first, InputIt last) {
		if ((_size = ft::distance(first, last)) > _capacity) {
			_alloc.deallocate(_data, _capacity);
			_capacity = _size;
			_data = _alloc.allocate(_capacity);
		}
		for (iterator it = begin(); it != end(); it++)
			*it = *(first++);
	};
	allocator_type			get_allocator(void) const;

	//	ELEMENT ACCESS

	reference				at(size_type pos);
	const_reference			at(size_type pos) const;
	reference				operator[](size_type pos);
	const_reference			operator[](size_type pos) const;
	reference				front(void);
	const_reference			front(void) const;
	reference				back(void);
	const_reference			back(void) const;

	//	ITERATORS

	iterator				begin(void);
	const_iterator			begin(void) const;
	iterator				end(void);
	const_iterator			end(void) const;
	reverse_iterator		rbegin(void);
	const_reverse_iterator	rbegin(void) const;
	reverse_iterator		rend(void);
	const_reverse_iterator	rend(void) const;

	//	CAPACITY

	bool					empty(void) const;
	size_type				size(void) const;
	size_type				max_size(void) const;
	void					reserve(size_type new_cap);
	size_type				capacity(void) const;

	//	MODIFIERS

	void					clear(void);
	iterator				insert(iterator pos, const T &value);
	void					insert(iterator pos, size_type count,
								const T &value);
	template < class InputIt >
	void					insert(iterator pos, InputIt first, InputIt last) {
		size_type	size_before = ft::distance(begin(), pos()),
					size_after = _size - _size_before,
					size_toadd = ft::distance(first, last),;

		if ((_size += size_toadd) > _capacity) {
			size_type	new_cap = _capacity * 2;
			pointer		new_array = _alloc.allocate(new_cap);

			std::memcpy(new_array, _data, size_before);
			std::memcpy(new_array + size_before + size_toadd,
				_data + size_before, size_after);
			_alloc.deallocate(_data, _capacity);
			_capacity = new_cap;
			_data = new_array;
		} else
			std::memmove(_data + size_before + size_toadd, _data + size_before,
				size_after);
		for (unsigned i = 0; i < size_toadd; i++)
			_data[size_before + i] = *(first++);
	};
	iterator				erase(iterator pos);
	iterator				erase(iterator first, iterator last);
	void					push_back(const T &value);
	void					pop_back(void);
	void					resize(size_type count, T value = T());
	void					swap(Vector &other);


	private:

	pointer		_data;
	size_type	_size;
	size_type	_capacity;
	Allocator	_alloc;
};

template < class T, class Alloc >
ft::Vector::Iterator	&operator+(ft::Vector< T, Alloc >::Iterator &it,
							int amount) {
	return (Iterator(it._data + amount));
}

template < class T, class Alloc >
ft::Vector::Iterator	&operator-(ft::Vector< T, Alloc >::Iterator &it,
							int amount) {
	return (Iterator(it._data - amount));
}

template < class T, class Alloc >
bool	operator==(const ft::Vector< T,Alloc > &lhs,
			const ft::Vector< T,Alloc > &rhs) {
	if (lhs._size != rhs._size)
		return (false);
	for (iterator it1 = lhs.begin(), it2 = rhs.begin(); it1 != lhs.end();
			it1++, it2++)
		if (*it1 != *it2)
			return (false);
	return (true);
}

template < class T, class Alloc >
bool	operator!=(const ft::Vector< T,Alloc > &lhs,
	const ft::Vector< T,Alloc > &rhs) {
	return (!(lhs == rhs));
}

template < class T, class Alloc >
bool	operator<(const ft::Vector< T,Alloc > &lhs,
	const ft::Vector< T,Alloc > &rhs) {
	iterator	it1(lhs.begin()),
				it2(rhs.begin());

	while (1) {
		if (it2 == rhs.end())
			return (false);
		if (it1 == lhs.end())
			return (true);
		if (*it1 != *it2)
			return (*it1 < *it2);
		it1++, it2++;
	}
}

template < class T, class Alloc >
bool	operator<=(const ft::Vector< T,Alloc > &lhs,
	const ft::Vector< T,Alloc > &rhs) {
	iterator	it1(lhs.begin()),
				it2(rhs.begin());

	while (1) {
		if (it1 == lhs.end())
			return (true);
		if (it2 == rhs.end())
			return (false);
		if (*it1 != *it2)
			return (*it1 < *it2);
		it1++, it2++;
	}
}

template < class T, class Alloc >
bool	operator>(const ft::Vector< T,Alloc > &lhs,
	const ft::Vector< T,Alloc > &rhs) {
	return (!(lhs <= rhs));
}

template < class T, class Alloc >
bool	operator>=(const ft::Vector< T,Alloc > &lhs,
	const ft::Vector< T,Alloc > &rhs) {
	return (!(lhs < rhs));
}
