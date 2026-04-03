#include <iostream>

struct Foo {

    Foo(int* ptr)
        : ptr_(ptr)
    {
        std::cout << "Foo(int* ptr)" << std::endl;

    }


    ~Foo() {
        std::cout << "~Foo" << std::endl;
        delete ptr_;
    }

    Foo(const Foo& other)
        : ptr_ (new int(*other.ptr_))
    {
        std::cout << "Foo(const Foo& other)" << std::endl;
    }

    Foo(Foo&& other)
    {
        std::cout << "Foo(Foo&& other)" << std::endl;
        ptr_ = std::exchange(other.ptr_, nullptr);
    }


    // Foo& operator=(const Foo& other) {
    //     std::cout << "Foo& operator=(const Foo& other)" << std::endl;
    //     if(this == & other)
    //         return *this;

    //     Foo tmp(other);
    //     std::swap(tmp, *this);

    //     return *this;

    // }


    // Foo& operator=(Foo&& other) {
    //     std::cout << "Foo& operator=(Foo&& other)" << std::endl;
    //     std::swap(ptr_, other.ptr_);

    //     return *this;
    // }

    Foo& operator=(Foo value) {
        std::cout << "Foo& operator=(Foo other)" << std::endl;
        std::swap(value.ptr_, ptr_);

        return *this;
    }


private:
    int* ptr_;
};

void foo(Foo& ) {
    std::cout << "void foo(Foo& )\n";
}

void foo(const Foo& ) {
    std::cout << "void foo(const Foo& )\n";
}

void foo(Foo&& ) {
    std::cout << "void foo(Foo&& )\n";
}



Foo createFoo(int i) {
    return Foo{new int{i}};
}



int main(int, char**){



    // {
    //     /*

    //         Foo(int* ptr)
    //         Foo(int* ptr)
    //         Foo& operator=(Foo&& other)
    //         ~Foo
    //         ~Foo
    //     */


    //     Foo f(new int{1});
    //     f = createFoo(4);
    // }


    {

        /*
        Foo(int* ptr)
        Foo(int* ptr)
        Foo& operator=(const Foo& other)
        Foo(const Foo& other)
        Foo(Foo&& other)
        Foo& operator=(Foo&& other)
        Foo& operator=(Foo&& other)
        ~Foo
        ~Foo
        ~Foo
        ~Foo



        Foo(int* ptr)
        Foo(int* ptr)
        Foo(const Foo& other)
        Foo& operator=(Foo other)
        ~Foo
        ~Foo
        ~Foo
        */
        Foo f(new int{1});
        Foo f2(new int{1});

        f = f2;
    }




    // Foo f;
    // const Foo cf;
    // Foo&&  rvf = Foo{};

    // foo(f);         // Foo&
    // foo(cf);        // const Foo&&
    // foo(Foo{});     // Foo&&
    // foo(rvf);       // Foo& / Foo&&
}
