#include <Map.hpp>

RBTree::RBTree(void) : _root(nullptr), _alloc(Allocator()) { }

RBTree::RBTree(T value) : _root(new BTRee< T >), _alloc(Allocator()) {
	_alloc.construct(_root->data, value);
	_root->col = BLACK;
	_root->left = _root->right = _root->p = nullptr;
}

RBTree::~RBTree(void) {
	BTree_Clear(_root);
}

RBTree::node	*RBTree::root(void) const {
	return (_root);
}

void	RBTree::rotateLeft(node *x) {
	node	*y = x->right;

	if (!y)
		return ;
	x->right = y->left;
	if (y->left)
		y->left->p = x;
	y->p = x->p;
	if (!x->p)
		_root = y;
	else {
		if (x->p->left == x)
			x->p->left = y;
		else
			x->p->right = y;
	}
	x->p = y;
	y->left = x;
}

void	RBTree::rotateRight(node *x) {
	node	*y = x->left;

	if (!y)
		return ;
	x->left = y->right;
	if (y->right)
		y->right->p = x;
	y->p = x->p;
	if (!x->p)
		_root = y;
	else {
		if (x->p->left == x)
			x->p->left = y;
		else
			x->p->right = y;
	}
	x->p = y;
	y->right = x;
}

void	RBTree::recolor(node *x) {
	x->col = !x->col;
	if (x->right)
		x->right->col = !x->col;
	if (x->left)
		x->left->col = !x->col;
}

RBTree::node	*RBTree::push(T value) {
	node	*new_node = new node;
	node	*parent = _root;

	_alloc.construct(new_node->data, value);
	new_node->left = new_node->right = new_node->p = nullptr;
	new_node->col = RED;
	if (!_root)
		_root = new_node;
	else while (!new_node->p) {
		if (value < *parent->data) {
			if (parent->left)
				parent = parent->left;
			else {
				parent->left = new_node;
				new_node->p = parent;
			}
		} else {
			if (parent->right)
				parent = parent->right;
			else {
				parent->right = new_node;
				new_node->p = parent;
			}
		}
	}
	return (new_node);
}

RBTree::node	*RBTree::insert(T value) {
	node	*new_node = push(value);
	insertFix();
	return (new_node);
}

void	RBTree::insertFix(void) {
	node	*z;

	while ((z = RBTree_FindInsertViolation(_root))) {
		node *uncle;

		if (z->p->p->left == z->p)
			uncle = z->p->p->right;
		else
			uncle = z->p->p->left;
		if (!uncle || (uncle->col == BLACK)) {
			node *parent = z->p;

			if (parent->left == z && parent->p->right == z->p)
				rotateRight(parent);
			else if (z->p->right == z && parent->p->left == z->p)
				rotateLeft(parent);
			else {
				if (z->p->left == z && z->p->p->left == z->p)
					rotateRight(parent->p);
				else if (z->p->right == z && z->p->p->right == z->p)
					rotateLeft(parent->p);
				recolor(parent);
			}
		}
		else
			recolor(uncle->p);
	}
	_root->col = BLACK;
}

void	RBTree::remove(node *node) {
	bool	needFix;
	node	*doubleBlackParent;

	if ((doubleBlackParent = BTree_Remove(node, _alloc)))
		removeFix(doubleBlackParent, doubleBlackParent->right ? LEFT : RIGHT);
}

void	RBTree::removeFix(node *DBParent, bool DBSide) {
	node	*sibling = (DBSide ? DBParent->left : DBParent->right);

	if (sibling->col == BLACK) {
		if ((!sibling->left || sibling->left->col == BLACK)
				&& !sibling->right || sibling->right->col == BLACK) {
			sibling->col = RED;
			if (DBParent->col == BLACK && DBParent != _root)
				removeFix(DBParent->p, DBParent->p->right == DBParent);
			DBParent->col = BLACK;
		} else {
			if (DBSide == LEFT) {
				if ((!sibling->right || sibling->right->col == BLACK)
					&& sibling->left && sibling->left->col == RED) {
					ft::swap(sibling->col, sibling->left->col);
					rotateRight(sibling);
					if (!(sibling = DBParent->right))
						return ;
				}
				if (sibling->right && sibling->right == RED) {
					ft::swap(DBParent->col, sibling->col);
					rotateLeft(DBParent);
					if (DBParent->p->left->col == RED)
						DBParent->p->left->col = BLACK;
					else
						DBParent->p->right->col = BLACK;
				}
			} else {
				if ((!sibling->left || sibling->left->col == BLACK)
					&& sibling->right && sibling->right->col == RED) {
					ft::swap(sibling->col, sibling->right->col);
					rotateLeft(sibling);
					if (!(sibling = DBParent->left))
						return ;
				}
				if (sibling->left && sibling->left == RED) {
					ft::swap(DBParent->col, sibling->col);
					rotateRight(DBParent);
					if (DBParent->p->left->col == RED)
						DBParent->p->left->col = BLACK;
					else
						DBParent->p->right->col = BLACK;
				}
			}
		}
	}
	else {
		ft::swap(sibling->col, DBParent->col);
		if (DBSide == LEFT)
			rotateLeft(DBParent);
		else
			rotateRight(DBParent);
		removeFix(DBParent, DBSide);
	}
}

void	RBTree::clear(void) {
	BTree_Clear(_root, _alloc);
}
