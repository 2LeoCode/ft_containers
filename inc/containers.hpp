#pragma once

#include <memory>
#include <cstddef>
#include <cstring>
#include <stdexcept>

namespace ft {
	class List;
	class Vector;
	//class Map;
	//class Stack;
	//class Queue;
	//class Deque;
	//class Multiset;
	//class Multimap;

	template < class T1, class T2 >
	struct Pair {
		typedef T1	first_type;
		typedef T2	second_type;

		Pair(void);
		Pair(const T1 &x, const T2 &y);
		template < class U1, class U2 >
		Pair(const Pair< U1, U2 > &p) : first(reinterpret_cast< T1 >(p.first)),
		second(reinterpret_cast< T2 >(p.second)) {
		};
		Pair(const Pair &p);

		first_type 	first;
		second_type	second;
	};

	template < class T1, class T2 >
	Pair< T1, T2 >	make_pair(T1 t, T2 u) {
		return (Pair< T1, T2 >(t, u));
	}

	template < class InputIt >
	std::ptrdiff_t	distance(InputIt first, InputIt last) {
		std::ptrdiff_t	size(0);

		for (InputIt it = first, it != last, it++)
			size++;
		return (size);
	}

	template < class T >
	void			swap(T &a, T &b) {
		T	tmp = a;
		a = b;
		b = tmp;
	}

	template < class T, class Alloc >
	void			swap(ft::List< T, Alloc > &lhs, ft::List< T, Alloc > &rhs) {
		lhs.swap(rhs);
	}

	template < class Key, class T, class Compare, class Alloc >
	void			swap(ft::Map< Key, T, Compare, Alloc > &lhs,
						ft::Map< Key, T, Compare, Alloc > &rhs) {
		lhs.swap(rhs);
	}
}

template < class T1, class T2 >
bool	operator==(ft::Pair< T1, T2 > &lhs, ft::Pair< T1, T2 > &rhs) {
	return (lhs.first == rhs.first && lhs.second == rhs.second);
}
