#include <iostream>
#include <expected>


// // 2й поток
// // struct Foo {
// //     Foo() {
// //          std::cout << "Foo()\n";
// //     }
// //     ~Foo() {

// //         std::cout << "~Foo()\n";
// //     }
// // };


// // int internalFunc() {
// //     std::cout << "begin of internalFunc()\n";
// //     Foo f;
// //     throw std::runtime_error("Some error");
// //     std::cout << "end of internalFunc()\n";

// //     return 2;
// // }


// // void externalFunc() {
// //     std::cout << "begin of externalFunc()\n";
// //     try {
// //         int i = internalFunc();
// //         std::cout << "Here!!\n";
// //     }
// //     catch (std::exception& e) {
// //         std::cout << e.what() << std::endl;
// //     }

// //     std::cout << "end of externalFunc()\n";
// // }


// struct Foo {
//     int value;

//     Foo(int v)
//         : value(v)
//     {}

//     Foo(const Foo& other)
//         : value(other.value)
//     {
//         if(true)
//             throw std::runtime_error("KEKW");
//     }
// };


// /*
// Инвариант value_ - любое число, foo_ может быть nullptr
// */
// class Boo {
// private:
//     Foo* foo_ = nullptr;
//     int value_ = 0;
// public:
//     Boo(int value = 0)
//         : value_(value)
//     {}

//     Boo(int value, int foo_value)
//         : foo_(new Foo{foo_value})
//         , value_(value)
//     {}


//     Boo(const Boo& other)
//         : value_(other.value_)
//         , foo_(new Foo(*other.foo_))
//     {}


//     Boo& operator=(const Boo& other) {

//         if(this == &other)
//             return *this;

//         Boo tmp{other};
//         swap(tmp);
//         return *this;
//     }


//     void swap(Boo& other) noexcept {
//         std::swap(other.value_, value_);
//         std::swap(other.foo_, foo_);
//     }

//     ~Boo() {
//          delete foo_;
//     }

//     friend std::ostream& operator<< (std::ostream& stream, const Boo& value);
// };


// std::ostream& operator<< (std::ostream& stream, const Boo& value) {
//     if(value.foo_ != nullptr)
//         stream << "Boo(" << value.value_ << ", " << value.foo_->value << ")";
//     else
//         stream << "Boo(" << value.value_  << ")";
//     return stream;
// }


// // uint32_t to_uint(std::string_view str) {
// //     uint32_t result = 0;

// //     if(str.length() == 0)
// //         throw std::invalid_argument("Empty string");


// //    for(char c : str) {
// //         if(!std::isdigit(c)) {
// //             throw std::invalid_argument("Wrong string input");
// //         }
// //         result *= 10;
// //         result += c - '0';
// //    }

// //    return result;
// // }


// enum class EToIntError {
//     EmptyString = 0,
//     NotDigit,
//     TooLongString

// };


// // std::expected<uint32_t, EToIntError> to_uint(std::string_view str) {
// //     uint32_t result = 0;


// //     if(str.length() == 0)
// //         return std::unexpected(EToIntError::EmptyString);

// //     for(char c : str) {
// //         if(!std::isdigit(c)) {
// //             return std::unexpected(EToIntError::NotDigit);
// //         }
// //         result *= 10;
// //         result += c - '0';
// //    }

// //    return result;
// // }


// // uint32_t to_uint(std::string_view str, uint32_t& result) {

// //     if(str.length() == 0)
// //         return 1;

// //     for(char c : str) {
// //         if(!std::isdigit(c)) {
// //             return 2;
// //         }
// //         result *= 10;
// //         result += c - '0';
// //    }

// //    return 0;
// // }



// // bool to_uint(std::string_view str, uint32_t& result) {

// //     if(str.length() == 0)
// //         return false;

// //     for(char c : str) {
// //         if(!std::isdigit(c)) {
// //             return false;
// //         }
// //         result *= 10;
// //         result += c - '0';
// //    }

// //    return true;
// // }



// // std::optional<uint32_t> to_uint(std::string_view str) {
// //     uint32_t result = 0;
// //     if(str.length() == 0)
// //         return {};

// //     for(char c : str) {
// //         if(!std::isdigit(c)) {
// //             return {};
// //         }
// //         result *= 10;
// //         result += c - '0';
// //    }

// //    return result;
// // }

// uint32_t to_uint2(std::string_view str) {
//     uint32_t result = 0;


//     if(str.length() == 0)
//         // ..

//     for(char c : str) {
//         if(!std::isdigit(c)) {

//         }
//         result *= 10;
//         result += c - '0';
//    }

//    return result;
// }


// std::expected<uint32_t, std::invalid_argument> to_uint(std::string_view str) {
//     if(str.empty())
//         return std::unexpected{std::invalid_argument("String is empty")};

//     uint32_t result = 0;
//     for(char c : str) {
//         if(c < '0' || c > '9')
//             return std::unexpected{std::invalid_argument{std::format("Argument {} is not a number", str)}};

//         result *= 10;
//         result += c - '0';
//     }

//     return result;
// }


// void test_converter() {

//     std::expected<uint32_t, std::invalid_argument> result = to_uint("a100500");


//     try {
//         std::cout << result.value() << std::endl;
//     } catch(std::bad_expected_access<std::invalid_argument>& err) {
//         std::cout << err.error().what();
//     }

//     //std::cout << to_uint("100500") << std::endl;
//     // std::cout << to_uint("abc") << std::endl;
//     // std::cout << to_uint("abc100500") << std::endl;
//     // std::cout << to_uint("100500abc") << std::endl;
//     // std::cout << to_uint("") << std::endl;
//     // std::cout << to_uint("1000000000000000000000000") << std::endl;
// }


// enum class EDivError {
//     DevisionByZero = 0,
// };


// std::expected<int, EDivError> my_div(int a, int b) {
//     if(b == 0)
//         return std::unexpected{EDivError::DevisionByZero};
//     return a/b;
// }




// void test_expected() {
//     auto r = my_div(8, 0);
//     if(r)
//         std::cout << *r << std::endl;


//     try {
//         std::cout << r.value() << std::endl;
//     } catch (std::bad_expected_access<EDivError>& err) {
//         std::cout << err.what() << std::endl;
//     }
// }



// int main(int, char**){

//     // test_expected();

//     // return 0;
//     test_converter();

//     return 0;


//     Boo b {1,2};
//     Boo b2 {1,2};

//     try {
//         b = b2;
//     } catch (std::runtime_error& e) {
//         std::cout << e.what() << std::endl;
//     }


//     std::cout << b << std::endl;;
//     //externalFunc();
// }



// 1й поток


struct Foo {
    Foo() {
         std::cout << "Foo()\n";
    }
    ~Foo() {
        std::cout << "~Foo()\n";
    }
};


int internalFunc() {
    std::cout << "begin of internalFunc()\n";
    Foo f;
    throw std::runtime_error("Some error");
    //throw Foo{};

    std::cout << "end of internalFunc()\n";

    return 2;
}


void externalFunc() {
    std::cout << "begin of externalFunc()\n";

        int i = internalFunc();
        std::cout << "Here!!\n";


    std::cout << "end of externalFunc()\n";
}

// struct Foo {
//     int value;
//     Foo(int v)
//         : value(v)
//     {}

//     Foo(const Foo& other)
//         : value(other.value)
//     {
//         if(true)
//             throw std::runtime_error("KEKW");
//     }
// };


// class Boo {
// private:
//     Foo* foo_ = nullptr;    // nullptre или сущесвтующий указатель на Foo
//     int value_ = 0;         //любая чиселка интовая
// public:
//     Boo(int value = 0)
//      : value_(value)
//     {}

//     Boo(int value, int foo_value)
//         : foo_(new Foo{foo_value})
//         , value_(value)
//     {}


//     Boo(const Boo& other)
//         : value_(other.value_)
//         , foo_(new Foo(*other.foo_))
//     {}


//     Boo& operator=(const Boo& other) {

//         if(this == &other)
//             return *this;

//         Boo tmp{other};
//         swap(tmp);

//         return *this;
//     }

//     ~Boo() {
//          delete foo_;
//     }

//     void swap(Boo& other) noexcept {
//         std::swap(value_, other.value_);
//         std::swap(foo_, other.foo_);
//     }

//     friend std::ostream& operator<< (std::ostream& stream, const Boo& value);
// };



// std::ostream& operator<< (std::ostream& stream, const Boo& value) {
//     if(value.foo_ == nullptr)
//         stream << "Boo(" << value.value_ << ", nullptr)";
//     else
//         stream << "Boo(" << value.value_ << ", " << value.foo_->value << ")";
//     return stream;
// }



// uint32_t to_uint(std::string_view str) {
//     uint32_t result = 0;

//     if(str.empty())
//         throw std::invalid_argument("String is empty");

//     for(char c : str) {
//         if(!std::isdigit(c))
//             throw std::invalid_argument("String is no number");
//         result *= 10;
//         result += c - '0';
//     }

//     return result;
// }


// int to_uint(std::string_view str, uint32_t& result) {
//     if(str.empty())
//         return 1;

//     for(char c : str) {
//         if(!std::isdigit(c))
//             return 7;
//         result *= 10;
//         result += c - '0';
//     }

//     return 0;
// }

// bool to_uint(std::string_view str, uint32_t& result) {
//     if(str.empty())
//         return false;

//     for(char c : str) {
//         if(!std::isdigit(c))
//             return false;
//         result *= 10;
//         result += c - '0';
//     }

//     return true;
// }




// std::optional<uint32_t> to_uint(std::string_view str) {
//     uint32_t result = 0;
//     if(str.empty())
//         return {};

//     for(char c : str) {
//         if(!std::isdigit(c))
//             return {};
//         result *= 10;
//         result += c - '0';
//     }

//     return result;
// }

enum class EToIntError {
    EmptyString = 0,
    InvalidString,
};



// std::expected<uint32_t, EToIntError>  to_uint(std::string_view str) {
//     uint32_t result = 0;

//     if(str.empty())
//         return std::unexpected(EToIntError::EmptyString);

//     for(char c : str) {
//         if(!std::isdigit(c))
//             return std::unexpected(EToIntError::InvalidString);
//         result *= 10;
//         result += c - '0';
//     }

//     return result;
// }


std::expected<uint32_t, std::invalid_argument> to_uint(std::string_view str) {
    if(str.empty())
        return std::unexpected{std::invalid_argument("String is empty")};

    uint32_t result;

    for(char c : str) {
        if(c < '0' || c > '9')
            return std::unexpected{std::invalid_argument{std::format("Argument {} is not a number", str)}};
        result *= 10;
        result += c - '0';
    }
    return result;
}


void test_convert() {
    std::cout << *to_uint("100500") << std::endl;
    auto exp = to_uint("xyz");


    if(exp)
        std::cout << *exp;
    // try {
    //     std::cout << exp.value() << std::endl;
    // } catch(std::bad_expected_access<std::invalid_argument>& err) {
    //     std::cout << err.error().what() << std::endl;
    // }

    // std::cout << to_uint("aaa100500") << std::endl;
    // std::cout << to_uint("100500aa") << std::endl;
    // std::cout << to_uint("") << std::endl;
}


int main() {

    test_convert();

    return 0;

    // Boo b {1,3};
    // Boo b52 {1,2};



    // std::vector<int> v;
    // v.insert(v.begin(), 0);
    // try {
    //     b = b52;
    // }catch(const std::exception& e) {
    //     std::cout << e.what() << std::endl;
    // }

    // std::cout << b << std::endl;
    // // try {
    // //     externalFunc();
    // // }
    // // catch (const std::exception& e) {
    // //     std::cout << "std::exception " << e.what() << std::endl;
    // // }
    // // catch (const std::runtime_error& e) {
    // //     std::cout << "runtime error " <<  e.what() << std::endl;
    // // }
    // // catch(const Foo&) {
    // //     std::cout << "Foo Here!!\n";
    // // }
}