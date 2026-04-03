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
        explicit Foo(float f) {
            std::cout << "explicit Foo(float f)";
        };
    };


    struct Boo {
        explicit Boo(const std::string&) {}

        explicit operator int() {
            std::cout << "explicit operator int()\n";
            return 2;
        }
    };



    void test2() {
        Boo b("12345");
        Foo f = static_cast<Foo>(static_cast<int>(b)); // Foo <- float <- int <-Boo

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
        Derived d;
        Base& b = d;
        b.func();   // Base

        Derived d1 = static_cast<Derived>(b);
        d1.func();  // Derrived

        // void* t = new Derived();
        // static_cast<Derived*>(t)->func();
    }
}


namespace staticcast2 {
    struct Base {
        int i = 1;

        virtual ~Base() = default;
    };

    struct Derived : public Base {
        int j = 2;

        void func() {
            std::cout << j << std::endl;
        }
    };


    void func(Base* b) {
        Derived* d1 = static_cast<Derived*>(b);
        d1->func();  // 2

    }

    void test() {
        Base d;
        d.i = 10;
        Base* b = &d;

        Derived* d1 = static_cast<Derived*>(b);
        d1->func();  // 2


        // Base b;
        // Derived d = static_cast<Derived>(b);

        // d.func();
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
        Base* b = new Derived();
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



// template<typename T>
// struct Counter {
//     static int created;

//     Counter() {
//         ++created;
//     }

//     Counter(const Counter&) {
//         ++created;
//     }
// };

// template<typename T> int Counter<T>::created = 0;



// template<typename T>
// class Cloneable {
// public:
//     T clone() const {
//         return T{static_cast<const T&>(*this)};  // ITMO(const ITMO&)
//     }
// };


// class ITMO : public Counter<ITMO>, public Cloneable<ITMO>
// {};

// class SPbSU : public Counter<SPbSU>
// {};



// namespace crtp {
//     template<typename T>
//     class Base {
//     public:
//         void doSomething() {
//             T* derived = static_cast<T*>(this);
//         }
//     };


//     class Derived : public Base<Derived> {
//     };

// }


template<class ConcreateAnimal>
class Animal {
public:
    std::string who() const {
        return static_cast<const ConcreateAnimal*>(this)->who();
    }
};

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


template<class T>
void who_am_i(Animal<T>& animal) {
    std::cout << animal.who() << std::endl;
}



// int main(int, char**){
//     Cat c;
//     Dog d;

//     who_am_i(c);
//     who_am_i(d);


//     ITMO i1;
//     ITMO i2;

//     i2.clone();

//     SPbSU s1;

//     std::cout << ITMO::created << std::endl;
//     std::cout << SPbSU::created << std::endl;



//     //std::cout << sizeof(std::string) << std::endl;
//     //implicit_cast();
//     //cstyle();
//     //constcast();
//     //staticcast2::test();
//   //  dynamiccast::test2();
//     //crtp::test2();
// }


#include <vector>
#include <fstream>
struct SPoint {
    int x;
    int y;
};


template<typename T>
struct Counter {
    static size_t created;

    Counter() {
        ++created;
    }

    Counter(const Counter&) {
        ++created;
    }
};


template<typename T>
class Cloneable {
public:
    T clone() const {
        return T{static_cast<const T&>(*this)};   //ITMO(static_cast<const ITMO&>(*this))
    }
};

struct ITMO : public Counter<ITMO>, Cloneable<ITMO> {
};

struct SPbSU : public Counter<SPbSU> {

};


template<typename T>
size_t Counter<T>::created = 0;





int main() {

    Cat c;
    Dog d;

    who_am_i(c);
    who_am_i(d);


    ITMO i1;
    ITMO i2;

    SPbSU s1;

    ITMO i3 = i1.clone();
    std::cout << ITMO::created << std::endl;
    std::cout << SPbSU::created << std::endl;

    return 0;
    // std::vector<SPoint> points;

    // for(int i = 0; i < 100; ++i) {
    //     points.push_back({i, i});
    // }


    // std::ofstream out{"temp.text"};

    // // for(int i = 0; i < 100; ++i) {
    // //     out << points[i].x << ' ' << points[i].y  << ';';
    // // }


    // out.write(reinterpret_cast<char*>(points.data()), sizeof(SPoint) * 100);


 //   char* buffer = malloc(sizeof(SPoint) * 100)
}