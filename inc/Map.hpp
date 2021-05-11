#pragma once

#define BLACK false
#define RED true
#define LEFT false
#define RIGHT true

template < class T >
struct BTree {
	bool	col;
	BTree	*p;
	BTree	*left;
	BTree	*right;
	T		*data;
};

template < class T, class Alloc >
void	BTree_Clear(BTree< T > *node, Alloc &alloc) {
	if (node->left)
		BTree_Clear(node->left);
	alloc.destroy(node->data);
	if (node->right)
		BTree_Clear(node->right);
	delete node;
}

template < class T >
void	BTree_Print(BTree< T > *root, std::ofstream &out) {
	if (root->left)
		BTree_Print(root->left, out);
	if (root->col == RED)
		out << *root->data << " [color=red];" << std::endl;
	if (root->p)
		out << *root->data << " -- " << *root->p->data << ';' << std::endl;
	if (root->right)
		BTree_Print(root->right, out);
}

template < class T, class Alloc >
BTree< T >	*BTree_Remove(BTree< T > *node, Alloc &alloc) {
	typedef BTree< T >	node;

	bool	isBlack = false;

	if (!node->left && !node->right) {
		node	*parent = node->p;

		alloc.destroy(node->data);
		if (node->col == BLACK)
			isBlack = true;
		delete node;
		node = nullptr;
		return (node->p * isBlack);
	} else {
		node	*x;

		if (!node->right) {
			x = node->left;
			while (x->left)
				x = x->left;
		} else {
			x = node->right;
			while (x->left)
				x = x->left;
		}
		ft::swap(node->data, x->data);
		return (BTree_Remove(x, alloc));
	}
}

template < class T >
BTree< T >	*RBTree_FindInsertViolation(BTree< T > *root) {
	BTree< T >	*node;

	if (root->left && (node = RBTree_FindInsertViolation(root->left)))
		return (node);
	if (root->right && (node = RBTree_FindInsertViolation(root->right)))
		return (node);
	if (root->left && root->left->col == RED && root->col == RED)
		return (root->left);
	if (root->right && root->right->col == RED && root->col == RED)
		return (root->right);
	return (NULL);
}

template < class T >
RBTree< T >	*BTree_Next(RBTree< T > *cur) {
	if (cur->right) {
		cur = cur->right;
		while (cur->left)
			cur = cur->left;
	} else {
		while (cur->p && cur->p->right == cur)
			cur = cur->p;
		cur = cur->p;
	}
	return (cur);
}

RBTree< T >	*BTree_Prev(RBTree< T > *cur) {
	if (cur->left) {
		cur = cur->left;
		while (cur->right)
			cur = cur->right;
	} else {
		while (cur->p && cur->p->left == cur)
			cur = cur->p;
		cur = cur->p;
	}
	return (cur);
}

template < class T, class Allocator >
struct RBTree {
	public:

	typedef BTree< T >	node;

	RBTree(void);
	RBTree(T value);
	~RBTree(void);

	node	*root(void) const;
	node	*next(node *cur) const;
	void	rotateLeft(node *x);
	void	rotateRight(node *x);
	void	recolor(node *x, bool color);
	node	*push(T value);
	node	*insert(T value);
	void	insertFix(void);
	void	remove(T value);
	void	removeFix(void);
	void	clear(void);

	private:

	node		*_root;
	Allocator	_alloc;
};

template <
    class Key,
    class T,
    class Compare = std::less< Key >,
    class Allocator = std::allocator< ft::Pair< const Key, T > >;
> class Map {
	public:

	typedef Key									key_type;
	typedef T									mapped_type;
	typedef ft::Pair< const Key, T >			value_type;
	typedef std::size_t							size_type;
	typedef std::ptrdiff_t						difference_type;
	typedef Compare								key_compare;
	typedef Allocator							allocator_type;
	typedef Allocator::reference				reference;
	typedef Allocator::const_reference			const_reference;
	typedef Allocator::pointer					pointer;
	typedef Allocator::const_pointer			const_pointer;
	typedef Iterator							iterator;
	typedef const iterator						const_iterator;
	typedef std::reverse_iterator< Iterator >	reverse_iterator;
	typedef const reverse_iterator				const_reverse_iterator;

	class value_compare {
		typedef bool		result_type;
		typedef value_type	first_argument_type;
		typedef value_type	second_argument_type;

		result_type	operator()(const first_argument_type &lhs,
						const second_argument_type &rhs);

		protected:

		value_compare(Compare c);
		Compare	_comp;
	};
	template < class T = value_type, class Alloc = Allocator >
	class Iterator {
		public:

		typedef BTree< T >	node;

		Iterator(node *member);
		Iterator	&operator++(void);
		Iterator	operator++(int);
		Iterator	&operator--(void);
		Iterator	operator--(int);
		value_type	operator*(void);
		bool		operator==(void);
		bool		operator!=(void);
		value_type	*address(void);

		private:

		node	*_data;
		Alloc	_alloc;
	};

	Map(void);
	explicit									Map(const Compare &comp,
													const Allocator &alloc
													= Allocator());
	template < class InputIt >
	Map(InputIt first, InputIt last, const Compare &comp = Compare(),
		const Allocator &alloc = Allocator()) : _tree(), _key_comp(comp),
		_value_comp(value_compare()), _alloc(alloc), _begin(nullptr),
		_rbegin(nullptr) {
		for (InputIt it = first; it != last; it++)
			insert(*it);
	};
	Map(const Map &other);
	~Map(void);
	Map											&operator=(const Map &other);
	allocator_type								get_allocator(void) const;

	//	ELEMENT_ACCESS

	T											&operator[](const Key &key)
													const;

	//	ITERATORS

	iterator									begin(void);
	const_iterator								begin(void) const;
	iterator									end(void);
	const_iterator								end(void) const;
	reverse_iterator							rbegin(void);
	const_reverse_iterator						rbegin(void) const;
	reverse_iterator							rend(void);
	const_reverse_iterator						rend(void) const;

	//	CAPACITY

	bool										empty(void) const;
	size_type									size(void) const;
	size_type									max_size(void) const;

	//	MODIFIERS

	void										clear(void);
	ft::Pair< iterator, bool >					insert(const value_type &value);
	iterator									insert(iterator hint,
													const value_type &value);
	template < class InputIt >
	void										insert(InputIt first,
													InputIt last) {

	};
	void										erase(iterator pos);
	void										erase(iterator first,
													iterator last);
	size_type									erase(const key_type &key);
	void										swap(Map &other);

	//	LOOKUP

	size_type									count(const key_type &key)
													const;
	iterator									find(const key_type &key);
	const_iterator								find(const key_type &key) const;
	ft::Pair< iterator, iterator >				equal_range(
													const key_type &key);
	ft::Pair< const_iterator, const_iterator >	equal_range(const key_type &key)
													const;
	iterator									lower_bound(
													const key_type &key);
	const_iterator								lower_bound(const key_type &key)
													const;
	iterator									upper_bound(
													const key_type &key);
	const_iterator								upper_bound(const key_type &key)
													const;

	//	OBSERVERS

	key_compare									key_comp(void) const;
	value_compare								value_comp(void) const;


	private:

	void							updateIterators(void);
	RBTree< value_type, Allocator >	_tree;
	size_type						_size;
	key_compare						_key_comp;
	value_compare					_value_comp;
	allocator_type					_alloc;
	iterator						_begin;
	reverse_iterator				_rbegin;
};

template < class Key, class T, class Compare, class Alloc >
bool	operator==(const ft::Map< Key, T, Compare, Alloc > &lhs,
			const ft::Map< Key, T, Compare, Alloc > &rhs) {

}

template < class Key, class T, class Compare, class Alloc >
bool	operator!=(const ft::Map< Key, T, Compare, Alloc > &lhs,
	const ft::Map< Key, T, Compare, Alloc > &rhs) {

}

template < class Key, class T, class Compare, class Alloc >
bool	operator<(const ft::Map< Key, T, Compare, Alloc > &lhs,
	const ft::Map< Key, T, Compare, Alloc > &rhs) {

}

template < class Key, class T, class Compare, class Alloc >
bool	operator<=(const ft::Map< Key, T, Compare, Alloc > &lhs,
	const ft::Map< Key, T, Compare, Alloc > &rhs) {

}

template < class Key, class T, class Compare, class Alloc >
bool	operator>(const ft::Map< Key, T, Compare, Alloc > &lhs,
	const ft::Map< Key, T, Compare, Alloc > &rhs) {

}

template < class Key, class T, class Compare, class Alloc >
bool	operator>=(const ft::Map< Key, T, Compare, Alloc > &lhs,
	const ft::Map< Key, T, Compare, Alloc > &rhs) {

}
