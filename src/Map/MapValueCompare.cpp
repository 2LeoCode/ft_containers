#include <Map.hpp>

ft::Map::value_compare::value_compare(Compare comp) : _comp(comp)
{
}

ft::Map::value_compare::result_type	ft::Map::value_compare::operator()(
										const first_argument_type &lhs,
										const second_argument_type &rhs)
{
	return ((*_comp)(lhs, rhs));
}
