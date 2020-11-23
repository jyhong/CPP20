#include	<iostream>
#include	<iterator>
#include	<type_traits>

template<typename Derived> class Base
{
public:
	// Derived의 category 속성이 std::random_access_iterator_tag일 경우에만 foo 함수가 제공되도록 코드를 변경해 보세요.
	void	foo() requires std::same_as<typename Derived::category, std::random_access_iterator_tag> {}
	void	goo() {}
};

class	A : public Base<A>
{
public:
	using category = std::random_access_iterator_tag;
};

class	B : public Base<B>
{
public:
	using category = std::bidirectional_iterator_tag;
};

int	main()
{
	A	a;
	B	b;
	a.foo();	// ok
	a.goo();	// ok
	// b.foo();	// error
	b.goo();	// ok
}