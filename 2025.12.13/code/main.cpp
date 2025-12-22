
#include <iostream>
#include <string>
#include "math.h"

#include <vector>


#define MAX(a, b) (a > b ? a : b)


// template<class T>
// const T& max(const T& a, const T& b) {
//     return a > b ? a : b;
// }

template<class T>
void printMe(const T& value) {
    std::cout << value << std::endl;
}


template<class InputIt, class UnaryFunc>
void for_each(InputIt first, InputIt last, UnaryFunc f) {
    for(;first != last; ++first) {
        f(*first);
    }
};


typedef void(*TFunc)(const int&);
// template<class InputIt, class UnaryFunc> InputIt = int* , UnaryFunc = TFunc;
// void for_each(int* first, int* last, TFunc f) {
//     for(;first != last; ++first) {
//         f(*first);
//     }
// };



template<typename T1, typename T2>
class CPair {
public:
    CPair() = default;

    CPair(const T1& first, const T2& second)
        : first_{first}
        , second_{second}
    {}


    template<typename P1, typename P2>
    CPair& operator=(const CPair<P1, P2>& other) {
        // if(this ==&other)
        //     return *this;

        first_ = other.first_;
        second_ = other.second_;

        return *this;
    }


    T1 first_;
    T2 second_;
};




template <class T>
struct greater{
    bool operator()(const T& a, const T& b) const {
        return a > b;
    }
};

template <class T>
struct less {
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};



template <class T, class cmp_t=less<T>> // T = int, cmp_t =greater <int>
void buble_sort(T*    begin, T*    end, cmp_t cmp = cmp_t()) {
    size_t count = end - begin;
    for(size_t i = 0; i < count; ++i) {
        for(size_t j = 0; j < count - i - 1; ++j) {
            if(!cmp(begin[j],begin[j+1]))
                std::swap(begin[j], begin[j+1]);
        }
    }
}


template<unsigned N>
struct factorial {
    enum {value = N * factorial<N-1>::value };
};

template <>
struct factorial<0> {
    enum {value = 1};
};




// 1й поток
int main() {

    std::cout << factorial<5>::value;

    return 0;

    std::vector v = {1,2,3,4};



    CPair<int, int> p1 {1, 2};
    CPair<int, double> p2 {1, 2};

    CPair<int, int> p3 {1, 3};

    p1 = p2;


    int values[] {1,2,3,4,5};

    buble_sort(values, values + 5, greater<int>{});


    // void(*f)(const int&) = &printMe<int>;  //void ??(int);



    for_each(values, values+5, printMe<int>);

    printMe(max(1, 2));
    // printMe<int>(max<double>(1.1, 1));
    // //std::cout << max<std::string>("aaa", "bbbb");
    return 0;
}
















// 2й поток
// template<class T>
// const T& max(const T& a, const T& b) {
//     return a > b ? a : b;
// }

// template<class T>
// void printMe(const T& value) {
//     std::cout << value;
// }



// template<class InputIt, class UnaryFunc> /// InputIt = int*, UnaryFunc = type of (void(*)(int))
// void for_each(InputIt first, InputIt last, UnaryFunc f) {
//     for(;first != last; ++first) {
//         f(*first);
//     }
// };



// template<typename T1, typename T2>
// class CPair {
// public:
//     CPair() = default;

//     CPair(const T1& first, const T2& second)
//         : first_{first}
//         , second_{second}
//     {}


//     template<typename P1, typename P2>
//     CPair& operator=(const CPair<P1, P2>& other) {
//         // if(this == &other)
//         //     return *this;
//         first_ = other.first_;
//         second_ = other.second_;
//         return *this;
//     }



//     T1 first_;
//     T2 second_;
// };



// template <class T>
// struct greater{
//     bool operator()(const T& a, const T& b) const {
//         return a > b;
//     }
// };



// template <class T>
// struct less {
//     bool operator()(const T& a, const T& b) const {
//         return a < b;
//     }
// };


// template <class T, class cmp_t=less<T>>
// void buble_sort(T* begin, T* end, cmp_t cmp = cmp_t()) {
//     size_t count = end - begin;
//     for(size_t i = 0; i < count; ++i) {
//         for(size_t j = 0; j < count - i - 1; ++j) {
//             if(!cmp(begin[j],begin[j+1]))
//                 std::swap(begin[j], begin[j+1]);
//         }
//     }
// }




// int main(int, char**){


//     std::vector<int> v = {1,2,3,4};

//     CPair<int, double> p;
//     CPair<int, int> p2;


//     p = p2;


//     printMe(max(1, 1));

//     //printMe(max<double>(1, 1.1));

//     int values[] {1,2,3,4,5};

//     buble_sort<int, greater<int>>(values, values + 5);

//     // for_each(values, values + 5, printMe<int>);


//     return 0;

// }
