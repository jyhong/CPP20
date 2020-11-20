#include	<iostream>
#include	<coroutine>
#include	<thread>
#include	<chrono>

#define	INITIAL_VALUE	1

template<typename T> requires std::integral<T>
class Generator
{
public:
	struct Promise
	{
	private:
		T	value;
	public:
		const T& getValue() const { return value; }

		Generator get_return_object()
		{
			return Generator{ std::coroutine_handle<Promise>::from_promise(*this) };
		}
		auto yield_value(const T& n)
		{
			value = n;
			return std::suspend_always{};
		}
		auto initial_suspend() { return std::suspend_always{}; }
		auto return_void()	 { return std::suspend_never{}; }
		auto final_suspend()   { return std::suspend_always{}; }
		void unhandled_exception() { std::exit(1); }
	};
	using promise_type = Promise;
	std::coroutine_handle<promise_type> coro;
	Generator( std::coroutine_handle<promise_type> c ) : coro(c) {}
	~Generator() { if ( coro ) coro.destroy();}
};

Generator<int> Gen(int initial)
{
	for(int i = initial + (initial+1) % 2 ; ; i += 2)
		co_yield i;
}

int main()
{
	Generator<int>	g = Gen(INITIAL_VALUE);

	while(1)
	{
		g.coro.resume();

		std::cout << g.coro.promise().getValue() << std::endl;

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
