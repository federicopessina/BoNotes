// https://www.youtube.com/watch?v=U6mgsPqV32A&list=PL5jc9xFGsL8FWtnZBeTqZBbniyw0uHyaH

// Initializer List

#include <iostream>
#include <vector>

// nullptr: to replace NULL in C++ 03
void foo(int i)
{
    std::cout << "foo(int)" << std::endl;
}

void foo(char *c)
{
    std::cout << "foo(char*)" << std::endl;
}

int A() { return 6; }
constexpr int B() { return 6; }

template <typename func>
void filter(func f, std::vector<int> arr)
{
    for (auto i : arr)
    {
        if (f(i))
        {
            std::cout << i << std::endl;
        }
    }
}

void printInt(int &i)
{
    std::cout << "lvalue reference: " << i << std::endl;
}

void printInt(int &&i)
{
    std::cout << "rvalue reference: " << i << std::endl;
}

// defining the following function will break the rvalue reference overload of printInt(int &&i)
// because the compiler won't know which function to call when passing an rvalue (like 5) to printInt()
// void printInt(int i)
// {
//     std::cout << "rvalue reference: " << i << std::endl;
// }


int main()
{

    // Uniform Initialization syntax (C++ 11)
    // In C++ 03
    class dog
    {
    public:
        int age;
        std::string name;
    };
    dog d1 = {3, "Fido"}; // C++ 03 initializer list syntax

    // In C++ 11 extended the scope of curly braces to allow for uniform initialization syntax
    class cat
    {
    public:
        int m_age;
        std::string m_name;
        cat(int age, std::string name)
        {
            this->m_age = age;
            this->m_name = name;
        }
    };
    cat c1{3, "Fluffy"}; // C++ 11 uniform initialization syntax

    // Uniform initialization search order:
    // 1. initializer_list constructor
    // 2. regular constructor
    // 3. aggregate initialization

    class bob
    {
    public:
        int m_age; // 3rd choice: aggregate initialization

        bob(int age)
        { // 2nd choice: regular constructor
            this->m_age = age;
        }

        bob(const std::initializer_list<int> &list)
        { // 1st choice: initializer_list constructor
            this->m_age = *list.begin();
        }
    };

    // Auto type

    std::vector<int> v = {1, 2, 3, 4, 5};

    // C++ 03
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    {
        // v.push_back(*it);
    }

    // C++ 11: use auto type to avoid typing the iterator type
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        // v.push_back(*it);
    }

    auto a = 6;   // a is an int
    auto b = 7.0; // b is a double
    auto c = a;   // c is an int

    // Foreach

    // C++ 03
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    {
        // std::cout << *it << std::endl;
    }

    // C++ 11: use auto type to avoid typing the iterator type
    for (auto i : v)
    {                                // works on any class that has begin() and end() methods
        std::cout << i << std::endl; // read-only access to the elements of the vector
    }

    for (auto &i : v)
    {
        i++; // changs the elements of the vector
    }

    // foo(NULL); // ambiguous call

    // C++ 11: use nullptr to avoid ambiguity
    foo(nullptr); // calls foo(char*)

    // enum class

    // C++ 03
    enum apple
    {
        green_apple,
        red_apple
    };
    enum orange
    {
        navel_orange,
        blood_orange
    };

    apple g = green_apple;
    orange o = navel_orange;

    // if (g == o) // error: invalid operands to binary expression
    // {
    //     ...
    // }

    // static_assert

    // run time assertion: assert() in C++ 03
    // assert(a == o); // run time assertion

    // compile time assertion: static_assert() in C++ 11
    static_assert(sizeof(int) == 4, "Integers are not 4 bytes");

    // delegating constructors

    // C++ 03
    class bar
    {
    private:
        int m_age;
        void init() { m_age = 0; }

    public:
        bar() { init(); }
        bar(int age)
        {
            init();
            m_age = age;
        }
    };

    // C++ 11: delegating constructors
    class bar2
    {
    private:
        void doAnotherThing() { std::cout << "doAnotherThing()" << std::endl; }
        int m_age;

    public:
        bar2() : bar2(0) { doAnotherThing(); } // delegates to bar2(int)
        bar2(int age) { m_age = age; }

        // limitation: defaut constructor has to be called first.
    };

    // override (for virtual functions): to avoid inadvertently create new function in derived class
    class reptile
    {
        virtual void walk(int);
        virtual void speak() const;
    };

    class snake : public reptile
    {
        void walk(float); // create new function in derived class.
        void speak();     // create new function in derived class.
    };

    // C++ 11: use override to avoid inadvertently create new function in derived class
    class snake2 : public reptile
    {
        void walk(int) override;     // override the base class function
        void speak() const override; // override the base class function
    };

    // funal (for virtual functions): to avoid further overriding in derived class
    class reptile2
    {
        virtual void walk(int);
        virtual void speak() const final; // cannot be overridden in derived class
    };

    // compiler generated default ctor
    class fish
    {
        int m_age;
        fish(int age) {}
    };

    // fish f1; // error: no default constructor available because fish(int) is user-defined constructor

    // C++ 11: use = default to generate default constructor
    class fish2
    {
        int m_age;

    public:
        fish2(int age) {}
        fish2() = default; // generate default constructor
    };

    // delete (for functions): to avoid inadvertent use of a function
    class bird
    {
    private:
        int m_age;

    public:
        bird(int age) { this->m_age = age; }
    };

    bird bird1(3);
    bird bird2(3.0); // converted from double to int
    bird1 = bird2;   // compiler generated assignment operator

    // C++ 11: use = delete to avoid inadvertent use of a function
    class bird2
    {
    private:
        int m_age;

    public:
        bird2(int age) { this->m_age = age; }
        bird2(double age) = delete;               // delete the constructor that takes double
        bird2 &operator=(const bird2 &) = delete; // delete the assignment operator
    };

    // these will generate compile time error now because the constructor that takes double and the assignment operator are deleted
    // bird2 birdA(3);
    // bird2 birdB(3.0);
    // birdA = birdB;

    // constexpr: to evaluate a function at compile time
    int arr[6]; // ok: 6 is a constant expression

    // arr[A()]; // compile error: A() is not a constant expression

    // C++ 11: use constexpr to evaluate a function at compile time
    arr[B()]; // ok: B() is a constant expression

    // string literals: to avoid creating temporary string objects
    // C++ 03: creates a temporary string object
    auto c0 = "hello";

    // C++ 11: use string literal operator to avoid creating temporary string objects
    auto c2 = u8"hello";  // creates a temporary UTF-8 string literal object
    auto c3 = u"hello";   // creates a temporary UTF-16 string literal object
    auto c4 = U"hello";   // creates a temporary UTF-32 string literal object
    auto c5 = R"(hello)"; // creates a temporary raw string literal object

    // lambda functions
    std::cout << [](int x, int y)
    { return x + y; }(3, 4) << std::endl; // prints 7
    auto f = [](int x, int y)
    { return x + y; };
    std::cout << f(3, 4) << std::endl; // prints 7

    filter([](int x)
           { return x > 3; }, v);

    // lambda functions can even access local variables
    int y = 4;
    filter([&](int x)
           { return x > y; }, v);
    // note: [&] tells the compiler that we want variable captured by reference,
    // so that we can access it inside the lambda function

    std::cout << "end of main" << std::endl;
    return 0;
}
