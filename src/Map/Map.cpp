#include <Map.hpp>

ft::Map::Map(void) : _tree(), _key_comp(Compare()),
_value_comp(value_compare()), _alloc(Allocator()), _begin(nullptr),
_rbegin(nullptr) { }

ft::Map::Map(const Map &other) : _tree(), _key_comp(Compare()),
_value_comp(value_compare()), _alloc(Allocator()), _begin(nullptr),
_rbegin(nullptr) {
	for (Iterator it = other.begin(); it != other.end(); it++)
		insert(*it);
}

ft::Map::~Map(void) {
	clear();
}


ft::Map	&ft::Map::operator=(const Map &other) {
	clear();
	for (Iterator it = other.begin(); it != other.end(); it++)
		insert(*it);
}

allocator_type	ft::Map::get_allocator(void) const {
	return (_alloc);
}

//	ELEMENT ACCESS

ft::Map::T	ft::Map::operator[](const Key &key) {
	for (Iterator it = begin(); it != end(); it++)
		if ((*it).first == key)
			return ((*it).second);
	throw (std::out_of_range("Map"));
}

//	ITERATORS

ft::Map::iterator	ft::Map::begin(void) {
	return (_begin);
}

ft::Map::const_iterator	ft::Map::begin(void) const {
	return (const_cast< const_iterator >(_begin));
}

ft::Map::iterator	ft::Map::end(void) {
	return (iterator(nullptr));
}

ft::Map::const_iterator	ft::Map::end(void) const {
	return (const_iterator(nullptr));
}

ft::Map::reverse_iterator	ft::Map::rbegin(void) {
	return (_rbegin);
}

ft::Map::const_reverse_iterator	ft::Map::rbegin(void) const {
	return (const_cast< const_reverse_iterator >(_rbegin));
}

ft::Map::reverse_iterator	ft::Map::rend(void) {
	return (iterator(nullptr));
}

ft::Map::const_reverse_iterator	ft::Map::rend(void) const {
	return (const_reverse_iterator(const_iterator(nullptr)));
}

//	CAPACITY

bool	ft::Map::empty(void) const {
	return (!size);
}

ft::Map::size_type	ft::Map::size(void) const {
	return (_size);
}

ft::Map::size_type	ft::Map::max_size(void) const {
	return (size_type(-1)
			- (sizeof(RBTree< T, Allocator >) - sizeof(BTree< T >))
			/ sizeof(BTree< T >));
}

//	MODIFIERS

void	ft::Map::clear(void) {
	_tree.clear();
	_begin = iterator(nullptr);
	_rbegin = reverse_iterator(iterator(nullptr));
}

ft::Pair< ft::Map::iterator, bool >	ft::Map::insert(const value_type &value) {
	ft::Pair< iterator, bool >	ret(iterator(nullptr), false);

	if ((ret.first = find(value)) == iterator(nullptr)) {
		ret.first = iterator(_data.insert(value));
		ret.second = true;
		BTree< value_type >	*tmp = _data.root();
		while (tmp->left)
			tmp = tmp->left;
		_begin = iterator(tmp);
		tmp = _data.root();
		while (tmp->right)
			tmp = tmp->right;
		_rbegin = reverse_iterator(iterator(tmp));
	}
	return (ret);
}

ft::Map::iterator	ft::Map::insert(iterator hint, const value_type &value) {
	ft::Pair< iterator, bool >	ret(iterator(nullptr), false);
	bool found = false;

	for (iterator it = hint; it != end(); it++)
		if (*it == value) {
			found = true;
			break ;
		}
	if (!found) {

	}
}