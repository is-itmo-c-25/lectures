#include <iostream>
#include <vector>


class Foo {
public:
    int foo() const {
        return value_;
    }

private:
    int value_ = 2025;
};


class FooPtr {
public:
    explicit FooPtr(Foo* ptr = nullptr)
    : ptr_(ptr)
    {}

    ~FooPtr() {
        delete ptr_;
    }


    Foo& operator*() {
        return *ptr_;
    }

    Foo* operator->() {
        return ptr_;
    }

private:
    Foo* ptr_;
};



void func() {
    FooPtr ptr{new Foo{}};

    ptr->foo();
    if(true) {

        return;
    }

    //delete ptr;
}

template<class T>
class auto_ptr {
public:
    auto_ptr(T* ptr = nullptr)
        :ptr_(ptr)
    {}

    ~auto_ptr() {
        delete ptr_;
    }

    auto_ptr(auto_ptr& other)
        : ptr_(other.release()){
    }

    T* release() {
        T* tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }


    auto_ptr& operator=(auto_ptr& other) {
        if(ptr_ != other.ptr_) {
            delete ptr_;
            ptr_ = other.release();
        }

        return *this;
    }



    T& operator*() {
        return *ptr_;
    }

    T* operator->() {
        return ptr_;
    }


private:
    T* ptr_;


};


struct A; // forward declaration

struct B {
    B() { std::cout << "B\n";}
    ~B() { std::cout << "~B\n";}
    std::shared_ptr<A> ptr;
};

struct A {
    A() { std::cout << "A\n";}
    ~A() { std::cout << "~A\n";}
    std::shared_ptr<B> ptr;
};


void func2(){
    std::shared_ptr<A> a {new A()};
    std::shared_ptr<B> b {new B()};
    std::cout << a.use_count() << std::endl;
    std::cout << b.use_count() << std::endl;
    a->ptr = b;
    b->ptr = a;

    std::cout << a.use_count() << std::endl;
    std::cout << b.use_count() << std::endl;

}






int main(int, char**){
    func2();

    return 0;
    auto_ptr<Foo> f{new Foo{}};

    std::vector<auto_ptr<Foo>> v{2};

    v[0] = f;

    auto_ptr<Foo> tmp = v[0];
















//    func2();





    // auto_ptr<Foo> ptr{new Foo{}};


    // std::vector<auto_ptr<Foo>> v{2};

    // v[0] = ptr;
    // auto_ptr<Foo> temp = v[0];


    // v[0]->foo();


}
