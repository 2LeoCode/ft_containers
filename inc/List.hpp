#pragma once

#include "containers.hpp"

template < class T >
struct LinkedList
{
	LinkedList	*next;
	LinkedList	*prev;
	T			*data;
};

template <
    class T,
    class Allocator = std::allocator< T >
> class List {
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
	> class Iterator {
		public:

		typedef list_type	LinkedList< Type >;

		explicit	Iterator(list_type *data);
		Iterator(const Iterator &other);
		~Iterator(void);

		Iterator	&operator=(const Iterator other);
		list_type	&*node(void);
		Pointer		address(void);

		Iterator	&operator++(void);
		Iterator	operator++(int);
		Iterator	&operator--(void);
		Iterator	operator--(int);
		bool		operator==(const Iterator other) const;
		bool		operator!=(const Iterator other) const;
		Reference	operator*(void);


		private:

		list_type	*_data;
	};

	List(void);
	List(const List &other);
	explicit				List(const Allocator &alloc);
	explicit				List(size_type count, const T &value = T(),
								const Allocator &alloc = Allocator());
	template < class InputIt >
	List(InputIt first, InputIt last, const Allocator alloc = Allocator())
	: _alloc(alloc), _sentinel(new LinkedList< T >),
	_size(ft::distance(first, last)) {
		iterator	it1(_sentinel);

		for (InputIt it2 = first; it2 != last; it2++) {
			it1.node()->next = new LinkedList< T >;
			it1.node()->next->prev = it1.node();
			it1++;
			_alloc.construct(it1.address(), *it2);
		}
		it1.node()->next = _sentinel;
		_sentinel->prev = it1.node();
	};
	~List(void);

	List					&operator=(const List &other);
	void					assign(size_type count, const T &value);
	template < class InputIt >
	void					assign(InputIt first, InputIt last) {
		iterator	it1(_sentinel);

		clear();
		_size = ft::distance(first, last);
		for (InputIt it2 = first; it2 != last; it2++) {
			it1.node()->next = new LinkedList< T >;
			it1.node()->next->prev = it1.node();
			it1++;
			_alloc.construct(it1.address(), *it2);
		}
		it1.node()->next = _sentinel;
		_sentinel->prev = it1.node();
	};
	allocator_type			get_allocator(void) const;

	//	ELEMENT ACCESS

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

	//	MODIFIERS

	void					clear(void);
	iterator				insert(iterator pos, const T &value);
	void					insert(iterator pos, size_type count,
								const T &value);
	template < class InputIt >
	void					insert(iterator pos, InputIt first, InputIt last) {
		LinkedList< T >	*tmp = pos.node()->next;

		_size += ft::distance(first, last);
		for (InputIt it = first; it != last; it++) {
			pos.node()->next = new LinkedList< T >;
			pos.node()->next->prev = pos.node();
			pos++;
			_alloc.construct(pos.address(), *it);
		}
		pos.node()->next = tmp;
		tmp->prev = pos.node();
	};
	iterator				erase(iterator pos);
	iterator				erase(iterator first, iterator last);
	void					push_back(const T &value);
	void					pop_back(void);
	void					push_front(const T& value);
	void					pop_front(void);
	void					resize(size_type count, T value = T());
	void					swap(List& other);

	//	OPERATIONS

	void					merge(List &other);
	template < class Compare >
	void					merge(List &other, Compare comp) {
		_sentinel->prev->next = other._sentinel->next;
		_sentinel->prev = other._sentinel->prev;
		other._sentinel->prev->next = _sentinel;
		other._sentinel->next->prev = _sentinel->prev;
		other._sentinel->prev = other._sentinel->next = other._sentinel;
		_size += other._size;
		other._size = 0UL;
		sort(comp);
	};
	void					splice(const_iterator pos, List &other);
	void					splice(const_iterator pos, List &other,
								const_iterator it);
	void					splice(const_iterator pos, List &other,
								const_iterator first, const_iterator last);
	void					remove(const T &value);
	template < class UnaryPredicate >
	void					remove_if(UnaryPredicate p) {
		for (iterator it = begin(); it != end(); it++)
			if ((*p)(*it)) {
				_alloc.destroy(it.address());
				it.node()->prev->next = it.node()->next;
				it.node()->next->prev = it.node()->prev;
				delete it.node();
				_size--;
			}
		if (empty())
			_sentinel->next = _sentinel->prev = _sentinel;
	};
	void					reverse(void);
	void					unique(void);
	template < class BinaryPredicate >
	void					unique(BinaryPredicate p) {
		for (iterator it = begin(), prev = it; ++it != end;)
			if ((*p)(*prev, *it)) {
				_alloc.destroy(it.address());
				it.node()->prev->next = it.node()->next;
				it.node()->next->prev = it.node()->prev;
				delete it.node();
				it = iterator(prev.node()->next);
				_size--;
			}
	};
	void					sort(void);
	template < class Compare >
	void					sort(Compare comp) {
		T			&smallest;
		iterator	it1 = begin();

		while (it1 != end()) {
			smallest = *(it1++);
			for (iterator it2 = it1; it2 != end(); it2++)
				if ((*comp)(*it2, smallest) < 0)
					ft::swap(*it2, smallest);
		}
	};


private:

	LinkedList	*_sentinel;
	size_type	_size;
	Allocator	_alloc;
};

template < class T, class Alloc >
bool	operator==(const ft::List< T, Alloc > &lhs,
			const ft::List< T, Alloc > &rhs) {
	if (lhs._size != rhs._size)
		return (false);
	for (iterator it1 = lhs.begin(), it2 = rhs.begin(); it1 != lhs.end();
			it1++, it2++)
		if (*it1 != *it2)
			return (false);
	return (true);
}

template < class T, class Alloc >
bool	operator!=(const ft::List< T, Alloc > &lhs,
			const ft::List< T, Alloc > &rhs) {
	return (!(lhs == rhs));
}

template < class T, class Alloc >
bool	operator<(const ft::List< T, Alloc > &lhs,
			const ft::List< T, Alloc > &rhs) {
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
bool	operator<=(const ft::List< T, Alloc > &lhs,
			const ft::List< T, Alloc > &rhs) {
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
bool	operator>(const ft::List< T, Alloc > &lhs,
			const ft::List< T, Alloc > &rhs) {
	return (!(lhs <= rhs));
}

template < class T, class Alloc >
bool	operator>=(const ft::List< T, Alloc > &lhs,
			const ft::List< T, Alloc > &rhs) {
	return (!(lhs < rhs));
}
