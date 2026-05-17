#include <iostream>





// template<typename T>
// void print(T value) {
//     std::cout << "Value = " << value << std::endl;
// }



// template<typename T>
// void print(T* value) {
//     std::cout << "Value = " << *value << std::endl;
// }



// template<>
// void print<int>(int* value) {
//     std::cout << "Int value = " << *value << std::endl;
// }




template<typename... TArgs>
auto sum(TArgs... args) {
    return (args + ...);
}



template<auto... Values>
struct Sum {
    static constexpr auto value = (Values + ...);
};



template<typename... TArgs>
constexpr auto sum2(TArgs... value) {
    return (value + ...);
}




// int main() {
//     std::cout << sum2(1,2,3,4);


// }



// template<>
// void print<int*>(int* value) {
//     std::cout << "Int value = " << *value << std::endl;
// }



// template<typename T>
// std::true_type foo(int T::*);


// template<typename T>
// std::false_type foo(...);




// template<typename T>
// struct is_class : decltype(foo<T>(nullptr)) {};






// template<typename... Types>
// struct is_all_integral : std::false_type {};



/*
    bool is_all_even(int x, int y...) {


        if(x % 2 == 1)
            return false;
        returm is_all_even(y ....)
    }

*/

// template<bool B, typename T, typename U>
// struct condition  {
//     using type = U;
// };


// template<typename T, typename U>
// struct condition<true, T, U>  {
//     using type = T;
// };


// template<bool B, typename T, typename U>
// using condition_t = typename condition<B, T, U>::type;




// template<typename THead, typename... TTail>
// struct is_all_integral<THead, TTail...>
//     : condition_t<
//         std::is_integral_v<THead> && is_all_integral<TTail...>::value,
//         std::true_type, std::false_type
//     >
// {};


// template<>
// struct is_all_integral<> : std::true_type {};



// template<typename... Types>
// constexpr bool is_all_integral_v = is_all_integral<Types...>::value;

// template<typename... Types>
// constexpr bool is_all_integral_v = (std::is_integral_v<Types> && ...);


// int main () {
//     static_assert(is_all_integral_v<int, char, long>);
//     static_assert(!is_all_integral_v<int, std::string, long>);


// }





template<typename T, typename U>
concept Addable = requires(T a, U b) {
    a + b;
};


struct Foo {

};

template<typename T, typename U>
requires Addable<T,U>
auto add(const T& a, const U& b) {
    return a + b;
}


// template<size_t N, typename... TArgs>
// void print_tuple(const std::tuple<TArgs...>& t) {
//     std::cout << (std::get<I>(t) << ...) <<  std::endl;

//     if constexpr(N == 0) {
//         return;
//     } else {
//         std::cout << std::get<N-1>(t) << std::endl;
//         print_tuple<N-1>(t);
//     }
// }

// int main() {

//     std::tuple<int, char, bool> t = {10, 'c', false};

//     print_tuple<std::tuple_size_v<decltype(t)>>(t);


//     //add(1, 2);
// //    add(Foo{}, Foo{});
// }





template<typename T, typename U>
bool same(T&& x, U&& y) {
    return false;
}


template<typename T>
bool same(T&&, T&&) {
    return true;
}



template<typename T, typename U>
struct is_same : std::false_type {};

template<typename T>
struct is_same<T, T> : std::true_type {};




template<typename T>
T&& identity(T&& value) {
    return std::forward<T>(value);
}



namespace details {

template<typename T>
void print(const T& value, std::false_type) {
    std::cout << "Value = " << value << std::endl;
}

template<typename T>
void print(const T& value, std::true_type) {
    std::cout << "Value = " << *value << std::endl;
}

} // namespace details


template<typename T>
void print(const T& value) {
    details::print(value, std::is_pointer<T>);
}



int main() {
    int i = 1;
    print(i);
    print(&i);


    return 0;
    int x = 1;


    std::cout << is_same<int, int>::value << std::endl;
    std::cout << is_same<int, float>::value << std::endl;


    // constexpr int x = 1;
    // constexpr float y = 1.2;

    // constexpr bool same1 = same(x, x);
    // constexpr bool same2 = same(x, y);


    // return 0;
    // print(1);
    // print(1.2);
    // print(&x);
    // print(&y);

}
