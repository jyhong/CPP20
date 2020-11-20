#include	<iostream>

auto	Swap = []<typename T>(T &a, T &b) { T temp = a; a = b; b = temp; };

int	main()
{
	int	x = 1, y = 2;

	Swap(x, y);

	std::cout << x << std::endl;
	std::cout << y << std::endl;

	// ERROR
	// int	xx = 1;
	// short	yy = 2;
	// Swap(xx, yy);
}
