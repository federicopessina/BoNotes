// https://www.youtube.com/watch?v=2xUJTXeBZmE&list=PL5jc9xFGsL8FWtnZBeTqZBbniyw0uHyaH&index=5

// Literals

#include <iostream>

long double operator"" _cm(long double x) { return x * 10; }
long double operator"" _m(long double x) { return x * 1000; }
constexpr long double operator"" _mm(long double x) { return x; } // we can use constexpr b/c and calculate at compile time



int main()
{
    // literals are constants
    // C++ has 4 type of literals
    // 1. integer -> 45
    // 2. floating point -> 4.5
    // 3. character -> 'z'
    // 4. string -> "dog"

    // int literal -> 45
    // unsigned int (suffix specifies type) -> 45u
    // long -> 45l

    // User defined literals
    long double height = 3.4_cm;
    std::cout << height << std::endl;


    return 0;
}