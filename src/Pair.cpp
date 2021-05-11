#include <containers.hpp>

ft::Pair::Pair(void) : first(), second() { }

ft::Pair::Pair(const T1 &x, const T2 &y) : first(x), second(y) { }

ft::Pair::Pair(const Pair &p) : first(p.first), second(p.second) { }
