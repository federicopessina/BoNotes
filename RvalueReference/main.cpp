// https://www.youtube.com/watch?v=IOkgBrXCtfo&list=PL5jc9xFGsL8FWtnZBeTqZBbniyw0uHyaH&index=3

// Rvalue reference: Move semantics and perfect forwarding

#include <iostream>

void printInt(int &i)
{
    std::cout << "lvalue reference: " << i << std::endl;
}

void printInt(int &&i)
{
    std::cout << "rvalue reference: " << i << std::endl;
}

int main()
{
    // What is rvalue reference?
    int a = 5; // a is an lvalue
    int& b = a; // b is an lvalue reference to a (or just a reference to a)
    int&& c = 5; // c is an rvalue reference to 5

    printInt(a); // calls printInt(int &i)
    printInt(5); // calls printInt(int &&i)

    // Move semantics: to avoid unnecessary copies of objects




    return 0;
}