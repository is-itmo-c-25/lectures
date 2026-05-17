#include <iostream>
#include <sstream>
#include <list>
#include <vector>


namespace NVariadicFunction {
    template<typename T>
    std::string to_string(const T& value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
    }


    std::vector<std::string> to_strings() {
    return {} ;
    }

    template<typename T, typename... TArgs>
    std::vector<std::string> to_strings(const T& value, const TArgs&... args) {
    std::vector<std::string> result;
    result.push_back(to_string(value));

    std::vector<std::string> other = to_strings(args...);
    result.insert(result.end(), other.begin(), other.end());
    return result;
    }


}


template<typename... TArgs>
int devide(const TArgs&... args) {
    return (args / ...);
}





namespace NFoldExpressions {
    template<typename ...TArgs>
    auto multiply(TArgs... args) {
        return (args * ... );
    }

    template<typename ...TArgs>
    auto divide1(TArgs... args) {
        return ( ... / args );
    }


    template<typename ...TArgs>
    auto divide2(TArgs... args) {
        return (args / ... );
    }

    template<typename ...TArgs>
    auto divide3(TArgs... args) {
        return (1.0 / ... / args );
    }


    template<typename ...TArgs>
    auto divide4(TArgs... args) {
        return (args / ... / 1.0 );
    }


    void test_devide() {
        std::cout << divide1(1.0, 2.0, 4.0, 8.0) << std::endl; // ((1/2)/4)/8
        std::cout << divide2(1.0, 2.0, 4.0, 8.0) << std::endl; //.1/(2/(4/8))
        std::cout << divide3(1.0, 2.0, 4.0, 8.0) << std::endl; //.(((1/1)/2)/4)/8
        std::cout << divide4(1.0, 2.0, 4.0, 8.0) << std::endl; //.(1/(2/(4/(8/1)))
    }




    template<typename T, typename... Args>
    std::vector<T> make_vector(Args&&... args) {
        std::vector<T> v;
        (v.push_back(std::forward<Args>(args)),...);
        return v;
    }
}



// namespace NTuple {


// template<typename... TArgs>
// struct NaiveTuple;


// template<>
// struct NaiveTuple<> {};



// template<typename T, typename... TArgs>
// struct NaiveTuple<T, TArgs...> : public NaiveTuple<TArgs...> {
//     using Base = NaiveTuple<TArgs...>;
//     NaiveTuple(T&& v, TArgs&&... args)
//         : Base(std::forward<TArgs>(args)...)

//         , value(std::forward<T>(v))
//     {}

//     Base& base() noexcept {
//         return static_cast<Base&>(*this);
//     }

//     T value;
// };

// // //TODO: make partial orders
// // struct GetElem{

// // }

// // template<size_t I, typename... TArgs>
// // auto get_elee(NaiveTuple<TArgs...>& value) {
// //     return GetElem::exec(value);
// //     return get<I-1>(value.base());

// // }


// // template<typename... TArgs>
// // auto get<0, TArgs...>(NaiveTuple<TArgs...>& value) {
// //     return value.value;
// // }



template<typename... TArgs>
struct NaiveTuple;


template<typename T, typename...TArgs>
struct NaiveTuple<T, TArgs...> {

    using TTail = NaiveTuple<TArgs...>;
    using THead = T;

    NaiveTuple(const T& arg, const TArgs&... args)
        : value(arg)
        , tail(args...)
    {}

    THead value;
    TTail tail;
};


template<>
struct NaiveTuple<> {
};




template<size_t I, typename Head, typename... Tail>
struct TupleElement {
    using ElementType = TupleElement<I-1, Tail...>::ElementType;


    static ElementType get(NaiveTuple<Head, Tail...>& tuple) {
        return TupleElement<I-1, Tail...>::get(tuple.tail);
    }
};


template<typename Head, typename... Tail>
struct TupleElement<0, Head, Tail...> {
    using ElementType = Head;

    static ElementType get(NaiveTuple<Head, Tail...>& tuple) {
        return tuple.value;
    }
};


template<size_t I, typename... TArgs>
TupleElement<I, TArgs...>::ElementType get_element(NaiveTuple<TArgs...>& t) {
    return TupleElement<I, TArgs...>::get(t);
}


void tuple_example() {
    std::vector v {1,2,3,4};

    return ;
    NaiveTuple<int, bool, std::string, float, int> t{100500, true, "hello world", 1.2, 2};

    // std::cout << TupleElement<0, int, bool, std::string, float, int>::get(t) << std::endl;
    // std::cout << TupleElement<1, int, bool, std::string, float, int>::get(t) << std::endl;
    // std::cout << TupleElement<2, int, bool, std::string, float, int>::get(t) << std::endl;




    std::cout << t.value << std::endl;

    std::cout << get_element<0>(t) << std::endl;

    std::cout << t.tail.value << std::endl;
    std::cout << get_element<1>(t) << std::endl;

    std::cout << t.tail.tail.value << std::endl;
    std::cout << get_element<2>(t) << std::endl;


//   std::cout
//     << get<0>(t) << std::endl
//     << get<1>(t) << std::endl
//     << get<2>(t) << std::endl;

}

//}


// int main(int, char**) {
//     // for(const auto& s : to_strings(1, "2", false, 2.4f))
//     //     std::cout << s << std::endl;
// }



template<typename... TArgs>
void printAll(const TArgs&... args) {

}


// void printAll() {
// }


// template<typename T, typename... TArgs>
// void printAll(const T& v, const TArgs&... args) {
//     std::cout << v << " ";
//     printAll(args...);

// }




namespace NOverload {

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

}

int main() {
    using namespace NOverload;

    auto o = MakeOverloaded(
        [](int i) {std::cout << "int " << i << std::endl;},
        [](const std::string& s) {std::cout << "string " << s << std::endl;}
    );

    o(1);
    o("1111");

    tuple_example();
}
