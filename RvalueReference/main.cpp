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


    // RValue references
    // Users:
    // 1. Move semantics
    // 2. Perfect forwarding

    
    class boVector
    {
        int size_;
        double *arr_;
        
    public:
        boVector(const boVector &rhs) // Copy constructor - takes lvalue reference
        {
            size_ = rhs.size_;
            arr_ = new double[size_];
            for (int i = 0; i < size_; ++i)
            {
                arr_[i] = rhs.arr_[i];
            }
        }

        boVector(boVector &&rhs) // Move constructor - takes rvalue reference 
        {
            size_ = rhs.size_;
            arr_ = rhs.arr_;    // takes the rhs array and use it
            rhs.size_ = 0;      // set the rhs size to 0 !!!
            rhs.arr_ = nullptr; // set the rhs array to nullptr !!!
            // if you don't set the rhs size to 0 and the rhs array to nullptr, 
            // when the rhs object is destroyed, 
            // it will delete the array and the current object 
            // will have a dangling pointer to the deleted array

            // check std::move() to see how it works
        }

        // destructor
        ~boVector()
        {
            delete[] arr_;
        }
    };

    // boVector reusable = createBoVector();
    // void foo_by_ref(boVector &v);
    
    // foo_by_ref(reusable);        // calls no constructor -> less expensive
    // foo(reusabe);                // calls copy constructor -> more expensive
    // foo(std::move(reusable));    // calls move constructor -> mid expensive
    
    // note: move constructor are needed when there is a mix of value and reference semantics

    
    // Perfect forwarding: to forward arguments to another function 
    // without losing their value category (lvalue or rvalue)


    // Reference collapsing: to collapse multiple references into a single reference
    // 1. T& & -> T&
    // 2. T& && -> T&
    // 3. T&& & -> T&
    // 4. T&& && -> T&&

    
    // Remove reference: to remove the reference from a type

    //template<class T>
    //struct remove_reference;
    
    // remove_reference<int&>::type i; // i is an int
    // remove_reference<int>::type i; // i is an int
    

    // T&& is Universal Reference: rvalue, lvalue, const, non-const, etc.
    // Conditions:
    // 1. T is a template tpye
    // 2. Type deduction (reference collapsing) happens to T.
    // T is a function template type, not class template type


    // std::move<T>(arg); // turns arg into an rvalue tpye
    // std::forward<T>(arg); // turns arg to type T&&

    return 0;
}