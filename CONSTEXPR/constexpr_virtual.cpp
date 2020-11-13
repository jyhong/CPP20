#include    <iostream>

class Base
{
public:
    virtual int foo(int a, int b) { return a + b;}
};
class Derived : public Base
{
public:
     constexpr virtual int foo(int a, int b) { return a * b;}
};
int main()
{
    Derived d;
    constexpr int ret1 = d.foo(1,2); // ok
    std::cout << ret1 << std::endl;

    Base* p = &d;
    int ret2 = p->foo(1,2); // ok
    std::cout << ret2 << std::endl;

   // constexpr int ret3 = p->foo(1,2); // error
}