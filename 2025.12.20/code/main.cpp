#include <iostream>


template <class T>
struct less {
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};


template <class T, class cmp_t = less<T>>
void buble_sort(T* begin, T* end, cmp_t cmp = cmp_t()) {
    size_t count = end - begin;
    for(size_t i = 0; i < count; ++i) {
        for(size_t j = 0; j < count - i - 1; ++j) {
            if(!cmp(begin[j],begin[j+1]))
                std::swap(begin[j], begin[j+1]);
        }
    }
}


template<size_t N>
struct identity {
    enum { value = N};
};


struct identity_5 {
    enum { value = 5};
};

template<unsigned N>
struct factorial {
    enum {value = N * factorial<N-1>::value };
};

template <>
struct factorial<0> {
    enum {value = 1};
};



struct factorial_4 {
    enum {value = 4 * factorial<3>::value };
};


struct factorial_5 {
    enum {value = 120 };
};


// template<class T>
// struct Boo {
//     void foo() {
//         std::cout << "foo" << std::endl;
//     }
//     void func () {};
// };


// template<>
// struct Boo<int> {
//     void foo() {
//         std::cout << "foo(int)" << std::endl;
//     }
// };


template<class T>
struct is_float {
    static bool value() { return false; }
};

template<>
struct is_float<float> {
    static bool value() { return true; }
};



template<class T>
static bool is_float_v = is_float<T>::value();

struct SomeStruct {
    SomeStruct& operator=(const SomeStruct&) = delete;
    void swap(const SomeStruct&) {}
};


template<class T>
void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}


template<typename T>
void swap(std::vector<T>& a, std::vector<T>& b) {
    a.swap(b);
}

void swap(SomeStruct& a, SomeStruct& b) {
    a.swap(b);
}


template<class T, class U>
struct Boo {
    void foo() { std::cout << "A" << std::endl; }
    void func () {};
};

template<class X>
struct Boo<int, X> {
    void foo() { std::cout << "B" << std::endl; }
};

template<>
struct Boo<int, int> {
    void foo() { std::cout << "C" << std::endl; }
};

template<class T>
struct Boo<T, T> {
    void foo() { std::cout << "B52" << std::endl; }
};




// 1й поток

class CFileDescriptor {
public:
    explicit CFileDescriptor(const char* path, const char* mode) {
        file_ = fopen(path, mode);
        if(file_ == nullptr) {
            // throw some exception (see next lection)
        }
    }
    operator FILE*() {
        return file_;
    }
    
    ~CFileDescriptor(){
        if(file_ != nullptr)
        fclose(file_);
    }
private:
    FILE* file_;
};


int main() {
    CFileDescriptor file("temp.txt", "w");
    //FILE* file = std::fopen("temp.txt", "w");
    int* ptr = new int{2};


    if(true) {
        delete ptr;

        return 0;
    }

    std::fprintf(file, "aaaaa");

    delete ptr;

    return 0;



    Boo<float, float>{}.foo();
    Boo<float, int>{}.foo();
    Boo<int, float>{}.foo();
    Boo<int, int>{}.foo();


    std::vector<int> i{100500};
    std::vector<int> j{100501};
    i.swap(j);

    swap(i, j);

    return 0;
    //Boo<int> b;
    std::cout << is_float_v<float> << std::endl;

    return 0;

    std::cout << factorial<5>::value << std::endl;

    return 0;
    int arr[]={1,2,3};
    buble_sort(arr, arr + 3, less<int>{});
    buble_sort(arr, arr + 3);


    return 0;
}


















// 2 поток

// template<unsigned N>
// struct factorial {
//     enum {value = N * factorial<N-1>::value };
// };


// template <>
// struct factorial<0> {
//     enum {value = 1};
// };


// template<unsigned N>
// struct identity {
//     enum { value = N};
// };



// // template<unsigned N> N = 5;
// struct factorial_5 {
//     enum {value = 5 * factorial<4>::value };
// };


// // template<unsigned N>
// struct factorial_4 {
//     enum {value = 4 * factorial<3>::value };
// };


// // template<class T>
// // struct Boo {
// //     void foo() {
// //         std::cout << "foo" << std::endl;
// //     }
// //     void func () {};
// // };




// // template<>
// // struct Boo<int> {
// //     void foo() {
// //         std::cout << "foo(int)" << std::endl;
// //     }
// // };


// template<class T>
// struct is_float {
//     static bool value() { return false; }
// };

// template<>
// struct is_float<float> {
//     static bool value() { return true; }
// };


// template<class T>
// static bool is_float_v = is_float<T>::value();


// struct SomeStruct {
//     SomeStruct& operator=(const SomeStruct&) = delete;
//     void swap(SomeStruct& other) {}
// };

// template<class T>
// void swap(T& a, T& b) {
//     T tmp = a;
//     a = b;
//     b = tmp;
// }


// template<typename T>
// void swap(std::vector<T>& a, std::vector<T>& b) {
//     a.swap(b);
// }



// template<class T, class U>
// struct Boo {
//     void foo() { std::cout << "A" << std::endl; }
//     void func () {};
// };


// template<class U>
// struct Boo<int, U> {
//     void foo() { std::cout << "B" << std::endl; }
// };


// template<class U>
// struct Boo<U, int> {
//     void foo() { std::cout << "B52" << std::endl; }
// };



// template<>
// struct Boo<int, int> {
//     void foo() { std::cout << "C" << std::endl; }
// };


// template<typename T>
// struct Boo<T, T> {
//     void foo() { std::cout << "D" << std::endl; }
// };




// class CFileDescriptor {
// public:
// explicit CFileDescriptor(const char* path, const char* mode) {
//     file_ = fopen(path, mode);
//     if(file_ == nullptr) {
//         // throw some exception (see next lection)
// }
// }
//     operator FILE*() {
//         return file_;
//     }


//     ~CFileDescriptor(){
//         if(file_ != nullptr)
//             fclose(file_);
//     }
// private:
//     FILE* file_;
// };


// int main(int, char**){

//     // FILE* file = std::fopen("temp.txt", "w");
//     CFileDescriptor file("temp.txt", "w");
//     int* ptr = new int{1};


//     if(true) {
//         delete ptr;
//         return 1;
//     }

//     std::fprintf(file, "aaaa");

//     delete ptr;


//     return 0;

//     Boo<float, float> b;
//     b.foo();


//     return 0;

//     std::vector<int> s1;
//     std::vector<int> s2;

//     swap(s1,s2);

//     //std::cout << is_float_v<int> << std::endl;
//     //Boo<int> b;
//     //b.func();
//     //std::cout << factorial<5>::value << std::endl ;
//     //std::cout << "Hello, from app!\n";
// }
