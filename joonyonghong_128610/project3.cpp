#include	<vector>
#include	<ranges>
#include	<iostream>

template<typename T> requires std::ranges::range<T>
void	printView(T v)
{
	for(int i : v)
		std::cout << i << ' ';
	std::cout << std::endl;
}

int	main()
{
	std::vector<int>	v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	// 1
	std::cout << "function version: ";
	printView(v | std::views::drop(3)
		| std::views::filter([](int n) { return n % 2 ==0; })
		| std::views::transform([](int n) { return n * 2; }));

	// 2
	std::cout << "class version: ";
	std::ranges::drop_view	dv(v, 3);
	std::ranges::filter_view	fv(dv, [](int n) { return n % 2 ==0; });
	std::ranges::transform_view	tv(fv, [](int n) { return n * 2; });
	printView(tv);

	return	0;
}