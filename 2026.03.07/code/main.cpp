#include <iostream>


void implicit_cast() {
    double d = -12.3456789;
    std::cout << d << std::endl;

    float f = d;
    std::cout << f << std::endl;

    int i = d;
    std::cout << i << std::endl;

    uint32_t ui = d;
    std::cout << ui << std::endl;

    char ch = d;
    std::cout << ch << std::endl;
}



struct Foo {
    int i = 64;
};

struct Boo {
    std::string str = "abc";
};

void func(Boo* b) {
    std::cout << b->str << std::endl;
}


void cstyle() {
    Boo b;
    Foo f;

    func(&b);
    func((Boo*)&f);
}



void constcast() {
    const int i = 0;
    const int* cpi = &i;

    int* pi = const_cast<int*>(cpi);
    *pi = 100500;

    std::cout << i << std::endl;

    std::cout << *pi << std::endl;

    std::cout << &i << "    " << pi << std::endl;

    const char* str = "Hello world!";
    char* s = const_cast<char*>(str);
    s[0] = 'A';

    std::cout << str << std::endl;

}


namespace staticcast {

    struct Foo {
        explicit Foo(float f) {};
    };


    struct Boo {
        Boo(const std::string&) {}

        explicit operator int() {
            return 2;
        }
    };



    void test2() {
        Boo b("12345");
        Foo f = static_cast<Foo>(static_cast<int>(b)); // Foo <- float <- int <- b
    }




    struct Base {
        void func() {
            std::cout << "Base\n";
        }
    };


    struct Derived : public Base {
        void func() {
            std::cout << "Derived\n";
        }
    };

    void test() {
        Base d;
        Base& b = d;
        b.func();

        Derived d1 = static_cast<Derived>(b);
        d1.func();

        void* t = new Derived();
        static_cast<Derived*>(t)->func();
    }
}


namespace staticcast2 {
    struct Base {
        int i = 1;
    };

    struct Derived : public Base {
        int j = 2;
        void func() {
            std::cout << j << std::endl;
        }
    };


    void test() {
        Base b;
        Derived d = static_cast<Derived>(b);

        d.func();
    }

}


namespace dynamiccast {
    struct Base {
        int i = 1;
        virtual ~Base() {};
    };

    struct Derived : public Base {
        int j = 2;
        void func() {
            std::cout << j << std::endl;
        }
    };


    void test() {
        Base* b = new Base();
        Derived* d = dynamic_cast<Derived*>(b);

        std::cout << d << std::endl;
        d->func();
    }

    void test2() {
        Base b;
        Derived& d = dynamic_cast<Derived&>(b);

        d.func();
    }
}


namespace crtp {
    template<typename T>
    struct Counter {
        static int created;

        Counter() {
            ++created;
        }

        Counter(const Counter&) {
            ++created;
        }
    };

    template<typename T> int Counter<T>::created = 0;



    template<typename T>
    class Cloneable {
    public:
        T clone() const {
            return T{static_cast<const T&>(*this)};
        }
    };


    struct Foo : Counter<Foo> {};
    struct Boo : Counter<Boo> {};

    void test() {
        Foo f;
        Foo f2;
        Boo b;

        std::cout << Foo::created << std::endl;
        std::cout << Boo::created << std::endl;

    }



    template<class ConcreateAnimal>
    class Animal {
    public:
        std::string who() const {
            return static_cast<const ConcreateAnimal*>(this)->who();
        }
    };

    template<class T>
    void who_am_i(Animal<T>& animal) {
        std::cout << animal.who() << std::endl;
    }

    class Dog : public Animal<Dog> {
    public:
        std::string who() const {
            return "dog";
        }
    };


    class Cat : public Animal<Cat> {
    public:
        std::string who() const {
            return "cat";
        }
    };


    void test2() {
        Dog d;
        Cat c;
        who_am_i(d);
        who_am_i(c);
    }
}


int main(int, char**){
    //std::cout << sizeof(std::string) << std::endl;
    //implicit_cast();
    //cstyle();
    //constcast();
    staticcast2::test();
    //dynamiccast::test2();
    //crtp::test2();
}
