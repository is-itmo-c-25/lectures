#include <iostream>
#include <functional>







class GreaterThen {
public:
    GreaterThen(int limit)
        : limit_(limit)
    {}

    bool operator()(int value) const {
        return value > limit_;
    }
private:
    int limit_;
};



template<typename T>
class my_bind {
public:
    my_bind(T functor, int value)
        : functor_(functor)
        , value_(value)
    {}

    int operator()(int value) {
        return functor_(value, value_);
    }
private:
    T functor_;
    int value_;
};


struct A {
    void operator()(int i) {
        std::cout << "int " << i << std::endl;
    }
};


struct B {
    void operator()(const std::string& s) {
        std::cout << "string " << s << std::endl;
    }
};



template<typename T, typename U>
struct SimpleOverloader : public T, U {
SimpleOverloader(T t, U u) : T(t), U(u)
{}
    using T::operator();
    using U::operator();
};




template<typename T, typename U>
SimpleOverloader<T,U> MakeOverloaded(
    const T& t, const U& u
){
    return SimpleOverloader<T, U>(t, u);
}


void SomeHardLogic() {}


class Foo {
public:
    Foo() {
        SomeHardLogic();
    }
};


Foo createFooA() {return Foo{};};
Foo createFooB(){return Foo{};};
Foo createFooC(){return Foo{};};

Foo createFoo(bool someCondition) {
    if(someCondition) {
        return createFooA();
    } else {
        return createFooB();
    }
}


int incr(int value) {
    return value + 1;
}

struct Incr {
    int operator()(int value) const {
        return value + 1;
    }
};








uint64_t factorial(size_t i) {
    if(i == 0)
        return 1;
    return i * factorial(i-1);
}



template<typename T>
class NaiveFunction;



template<typename R, typename Arg>
class NaiveFunction<R(Arg)> {
    using TFunc = R(Arg);


    struct ICallable {
        virtual R invoke(Arg value) = 0;
        virtual ~ICallable() = default;
    };

    template<typename F>
    struct Callable : public ICallable {
        Callable(F func)
            : func_(func)
        {}

        R invoke(Arg value) override {
            return func_(value);
        }

        F func_;
    };


public:

    template<typename F>
    NaiveFunction(F func)
        : func_(new Callable<F>(func)) {

    }

    R operator()(Arg value) {
        return func_->invoke(value);
    }

private:

    std::unique_ptr<ICallable> func_;
};


template<typename T>
int invoke(T callable, int value) {
    return callable(value);
}






int main() {

    // std::cout << invoke(Incr{}, 1);
    // std::cout << invoke(incr, 1);
    // std::cout << invoke([](int value){return value + 1;}, 1);


    NaiveFunction<int(int)> f = Incr{};
    NaiveFunction<int(int)> f2 = incr;
    NaiveFunction<int(int)> f3 = [](int value){return value + 1;};
    //std::cout << f(1);
    //std::cout << f2(1);
    //std::cout << f3(1);

    std::cout << f(1) << " "
              << f2(1) << " "
              << f3(1) << " "
              << std::endl;

    return 0;

    using TFunc = int(int);
    using TFuncPtr = int(*)(int);
    TFunc* ptrf = incr;

    auto fun = *ptrf;

    std::cout << fun(1) << std::endl;


    return 0;


    const auto factorial = [](int n) noexcept {
        auto impl = [](int n, auto& impl) {
            if(n == 0)
                return 1;

            return impl(n-1, impl);
        };

        return impl(n, impl);

    };
    std::cout << factorial(4);




    return 0;


    auto o = MakeOverloaded(
        [](int i) {std::cout << "int " << i << std::endl;},
        [](const std::string& s) {std::cout << "string " << s << std::endl;}
    );

    o(1);
    o("1111");





    return 0;




    bool someCondition = 100500; // количество пятен на сонце четное

    const Foo ffff = std::invoke([someCondition]() -> Foo {
        if(someCondition) {
            return createFooA();
        } else {
            return createFooB();
        }
    });



//    Foo f = someCodition ? createFooA() : createFooB();






    // int x = 0;
    // auto f = [x]() mutable {
    //     ++x;
    //     std::cout << x << std::endl;
    // };

    // f();                             // 1
    // std::cout << x << std::endl;     // 0
    // f();                             // 2
    // std::cout << x << std::endl;     // 0



    return 0;



    std::vector<int> v = {1,2,3,4,5,6,7};
    auto it = std::find_if(
        v.begin(), v.end(),
        //std::bind(std::greater<int>{}, std::placeholders::_1, 4)
        my_bind(std::greater<int>{}, 4)
    );

    if(it != v.end())
        std::cout << *it;
}