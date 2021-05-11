#include "List.class.hpp"

ft::List::List(void) : _alloc(), _sentinel(new LinkedList < T >), _size() {
	_sentinel->next = _sentinel->prev = _sentinel;
}

ft::List::List(const List &other) : _alloc(other._alloc), _size(other._size) {
	iterator	it1;

	_sentinel = new LinkedList< T >;
	it1 = sentinel;
	for (iterator it2 = other.begin(); it2 != other.end(); it2++) {
		it1.node()->next = new LinkedList< T >;
		it1.node()->next->prev = it1.node();
		it1++;
		_alloc.construct(it1.address(), *it2);
	}
	it1.node()->next = _sentinel;
	_sentinel->prev = it1.node();
}

explicit	ft::List::List(const Allocator &alloc) : _alloc(alloc),
_sentinel(new LinkedList< T >), _size() {
	_sentinel->next = _sentinel->prev = _sentinel;
}

explicit	ft::List::List(size_type count, const T &value = T(),
					const Allocator &alloc = Allocator()) : _size(count),
_alloc(alloc), _sentinel(new LinkedList< T >) {
	iterator	it(_sentinel);

	while (count--) {
		it.node()->next = new LinkedList< T >;
		it.node()->next->prev = it.node();
		it++;
		_alloc.construct(it1.address(), *it2);
	}
	it.node()->next = _sentinel;
	_sentinel->prev = it.node();
}

ft::List::~List(void) {
	clear();
	delete _sentinel;
	_sentinel = nullptr;
}

ft::List	&ft::List::operator=(const List &other) {
	assign(other.begin(), other.end(), other._alloc);
	return (*this);
}

void	ft::List::assign(size_type count, const T &value) {
	iterator	it(_sentinel);

	clear();
	_size = count;
	while (count--) {
		it.node()->next = new LinkedList< T >;
		it.node()->next->prev = it.node();
		it++;
		_alloc.construct(it.address(), value);
	}
	it.node()->next = _sentinel;
	_sentinel->prev = it.node();
	return ()
}

ft::List::allocator_type	get_allocator(void) const {
	return (_alloc);
}

//	ELEMENT ACCESS

ft::List::reference	front(void) {
	return (_sentinel->next->data);
}

ft::List::const_reference	front(void) const {
	return (_sentinel->next->data);
}

ft::List::reference	back(void) {
	return (_sentinel->prev->data);
}

ft::List::const_reference	back(void) const {
	return (_sentinel->prev->data);
}

//	ITERATORS

ft::List::iterator	begin(void) {
	return (iterator(_sentinel->next));
}

ft::List::const_iterator	begin(void) const {
	return (const_iterator(_sentinel->next));
}

ft::List::iterator	end(void) {
	return (iterator(_sentinel));
}

ft::List::const_iterator	end(void) const {
	return (const_iterator(_sentinel));
}

ft::List::iterator	rbegin(void) {
	return (reverse_iterator(_sentinel->prev));
}

ft::List::const_iterator	rbegin(void) const {
	return (const_reverse_iterator(_sentinel->prev));
}

ft::List::iterator	rend(void) {
	return (reverse_iterator(_sentinel));
}

ft::List::const_iterator	rend(void) const {
	return (const_reverse_iterator(_sentinel));
}

//	CAPACITY

bool	ft::List::empty(void) const {
	return (!_size);
}

ft::List::size_type	size(void) const {
	return (_size);
}

ft::List::size_type	max_size(void) const {
	return (size_type(-1) / sizeof(LinkedList));
}

//	MODIFIERS

void	ft::List::clear(void) {
	for (iterator it = begin(); it != end(); it++) {
		_alloc.destroy(it.address());
		delete it.node();
	}
	_size = 0UL;
	_sentinel->next = _sentinel->prev = _sentinel;
}

ft::List::iterator	ft::List::insert(iterator pos, const T &value) {
	LinkedList< T >	*new_node(new LinkedList< T >);

	_size++;
	_alloc.construct(new_node->data, value);
	new_node->prev = pos.node();
	new_node->next = pos.node()->next;
	pos.node()->next->prev = pos.node()->next = new_node;
	return (iterator(new_node));
}

ft::List::iterator	ft::List::insert(iterator pos, size_type count,
						const T &value) {
	LinkedList< T > *tmp = pos.node()->next;
	iterator		ret = pos;

	if (!count)
		return (pos);
	_size += count;
	while (count--) {
		pos.node()->next = new LinkedList< T >;
		pos.node()->next->prev = pos.node();
		pos++;
		_alloc.construct(pos.address(), value);
	}
	pos.node()->next = tmp;
	tmp->prev = pos.node();
	ret++;
	return (ret);
}

ft::List::iterator	ft::List::erase(iterator pos) {
	iterator	ret(pos.node()->next);

	if (pos == end())
		return (pos);
	_size--;
	_alloc.destroy(pos.address());
	pos.node()->prev->next = pos.node()->next;
	pos.node()->next->prev = pos.node()->prev;
	delete pos.node();
	pos.node() = nullptr;
	return (ret);
}

ft::List::iterator	ft::List::erase(iterator first, iterator last) {
	iterator	tmp;

	first.node()->prev->next = last.node();
	last.node()->prev = first.node()->prev;
	_size -= ft::distance(first, last);
	while (first++ != last) {
		_alloc.destroy(first.node()->prev->data);
		delete first.node()->prev;
		first.node()->prev = nullptr;
	}
	return (last);
}

void	ft::List::push_back(const T &value) {
	insert(rbegin(), value);
}

void	ft::List::pop_back(void) {
	erase(rbegin());
}

void	ft::List::push_front(const T &value) {
	insert(rend(), value);
}

void	ft::List::pop_front(const T &value) {
	erase(begin());
}

void	ft::List::resize(size_type count, T value = T()) {
	if (count > size)
		insert(rbegin().base(), count, value);
	else {
		reverse_iterator	last(rbegin());
		reverse_iterator	first(last);

		for (int i = _size; i < count; i++)
			first++;
		erase(first.base(), last.base());
	}
	_size = count;
}

void	ft::List::swap(List &other) {
	ft::swap(_sentinel, other._sentinel);
	ft::swap(_size, other._size);
	ft::swap(_alloc, other._alloc);
}

//	OPERATIONS

void	ft::List::merge(List &other) {
	_sentinel->prev->next = other._sentinel->next;
	_sentinel->prev->next->prev = _sentinel->prev;
	_sentinel->prev = other._sentinel->prev;
	_sentinel->prev->next = _sentinel;
	other._sentinel->prev = other._sentinel->next = other._sentinel;
	_size += other._size;
	other._size = 0UL;
}

void	ft::List::splice(const_iterator pos, List &other) {
	pos.node()->prev->next = other._sentinel->next;
	pos.node()->prev = other._sentinel->prev;
	other._sentinel->prev->next = pos;
	other._sentinel->next->prev = pos.node()->prev;
	other._sentinel->next = other._sentinel->prev = other._sentinel;
	_size += other._size;
	other._size = 0UL;
}

void	ft::List::splice(const_iterator pos, List &other, const_iterator it) {
	it.node()->next->prev = it.node()->prev;
	it.node()->prev->next = it.node()->next;
	it.node()->prev = pos.node()->prev;
	it.node()->next = pos.node();
	pos.node()->prev->next = it.node();
	pos.node()->prev = it.node();
	other._size--;
	_size++;
}

void	ft::List::splice(const_iterator pos, List &other, const_iterator first,
			const_iterator last) {
	size_type	distance = ft::distance(first, last);
	LinkedList	*tmp(first.node()->prev);

	tmp->next = last.node();
	first.node()->prev = pos.node()->prev;
	pos.node()->prev->next = first.node();
	last.node()->prev->next = pos.node();
	pos.node()->prev = last.node()->prev;
	last.node()->prev = tmp;
	_size += distance;
	other._size -= distance;
}

void	ft::List::remove(const T &value) {
	for (iterator it = begin(); it != end(); it++)
		if (*it == value) {
			iterator	tmp(it.node()->next);

			_alloc.destroy(it.address());
			it.node()->prev->next = it.node()->next;
			it.node()->next->prev = it.node()->prev;
			delete it.node();
			it = tmp;
			size--;
		}
}

void	ft::List::reverse(void) {
	for (iterator it = begin(); it != end(); it++)
		ft::swap(it.node()->prev, it.node()->next);
	ft::swap(end().node()->prev, end().node()->next);
}

void	ft::List::unique(void) {
	for (iterator it = begin(), prev = it; ++it != end;)
		if (*prev == *it) {
			_alloc.destroy(it.address());
			it.node()->prev->next = it.node()->next;
			it.node()->next->prev = it.node()->prev;
			delete it.node();
			it = iterator(prev.node()->next);
			_size--;
		}
}

void	ft::List::sort(void) {
	T			&smallest;
	iterator	it1 = begin();

	while (it1 != end()) {
		smallest = *(it1++);
		for (iterator *it2 = it1; it2 != end; it2++)
			if (*it2 < smallest)
				ft::swap(*it2, smallest);
	}
}
